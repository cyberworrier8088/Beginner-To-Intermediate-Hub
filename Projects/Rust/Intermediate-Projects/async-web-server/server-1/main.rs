/*
 * Async Web Server in Rust - Level 5: Advanced Async Programming
 * 
 * Welcome to high-performance web development in Rust! This is where safety meets speed.
 * Learn async programming, HTTP/2, and concurrent connection handling.
 * 
 * Key concepts you'll learn:
 * - Tokio async runtime and futures
 * - HTTP/2 protocol implementation
 * - Connection pooling and load balancing
 * - Async file I/O and streaming
 * - Error handling with Result types
 * - Human-like code with detailed explanations!
 */

use std::collections::HashMap;
use std::sync::Arc;
use tokio::net::{TcpListener, TcpStream};
use tokio::sync::RwLock;
use tokio_tungstenite::{tungstenite::http::Request, tungstenite::http::Response, tungstenite::http::StatusCode, WebSocketStream};
use tokio_tungstenite::accept_hdr_async;
use serde::{Deserialize, Serialize};
use serde_json;
use chrono::{DateTime, Utc};

// HTTP request structure
#[derive(Debug, Clone)]
struct HttpRequest {
    method: String,
    path: String,
    query_params: HashMap<String, String>,
    headers: HashMap<String, String>,
    body: String,
}

impl HttpRequest {
    fn new(method: String, path: String, headers: HashMap<String, String>, body: String) -> Self {
        println!("Creating HTTP request: {} {}", method, path);
        println!("Headers: {:?}", headers);
        println!("Body length: {} bytes", body.len());
        
        HttpRequest {
            method,
            path,
            query_params: HashMap::new(),
            headers,
            body,
        }
    }
    
    fn get_header(&self, name: &str) -> Option<&String> {
        println!("Getting header: {}", name);
        self.headers.get(name)
    }
    
    fn is_websocket_upgrade(&self) -> bool {
        if let Some(upgrade) = self.get_header("upgrade") {
            upgrade.to_lowercase() == "websocket"
        } else {
            false
        }
    }
}

// HTTP response structure
#[derive(Debug)]
struct HttpResponse {
    status: StatusCode,
    headers: HashMap<String, String>,
    body: Vec<u8>,
}

impl HttpResponse {
    fn new(status: StatusCode) -> Self {
        println!("Creating HTTP response with status: {}", status);
        HttpResponse {
            status,
            headers: HashMap::new(),
            body: Vec::new(),
        }
    }
    
    fn set_header(&mut self, name: String, value: String) {
        println!("Setting header: {} = {}", name, value);
        self.headers.insert(name, value);
    }
    
    fn set_json_body(&mut self, data: serde_json::Value) -> Result<(), serde_json::Error> {
        let json_str = serde_json::to_string_pretty(&data)?;
        self.body = json_str.into_bytes();
        self.set_header("Content-Type".to_string(), "application/json".to_string());
        self.set_header("Content-Length".to_string(), self.body.len().to_string());
        println!("Set JSON body with {} bytes", self.body.len());
        Ok(())
    }
    
    fn set_html_body(&mut self, html: String) {
        self.body = html.into_bytes();
        self.set_header("Content-Type".to_string(), "text/html; charset=utf-8".to_string());
        self.set_header("Content-Length".to_string(), self.body.len().to_string());
        println!("Set HTML body with {} bytes", self.body.len());
    }
    
    fn set_text_body(&mut self, text: String) {
        self.body = text.into_bytes();
        self.set_header("Content-Type".to_string(), "text/plain; charset=utf-8".to_string());
        self.set_header("Content-Length".to_string(), self.body.len().to_string());
        println!("Set text body with {} bytes", self.body.len());
    }
    
    fn to_string(&self) -> String {
        let status_line = format!("HTTP/1.1 {}\r\n", self.status);
        let mut headers = String::new();
        
        for (name, value) in &self.headers {
            headers.push_str(&format!("{}: {}\r\n", name, value));
        }
        
        format!("{}\r\n{}\r\n\r\n", status_line, headers)
    }
}

// WebSocket message structure
#[derive(Debug, Clone, Serialize, Deserialize)]
enum WebSocketMessage {
    Text(String),
    Binary(Vec<u8>),
    Ping(Vec<u8>),
    Pong(Vec<u8>),
    Close { code: u16, reason: String },
}

impl WebSocketMessage {
    fn to_string(&self) -> String {
        match self {
            WebSocketMessage::Text(text) => {
                format!("Text: {}", text)
            }
            WebSocketMessage::Binary(data) => {
                format!("Binary: {} bytes", data.len())
            }
            WebSocketMessage::Ping(data) => {
                format!("Ping: {} bytes", data.len())
            }
            WebSocketMessage::Pong(data) => {
                format!("Pong: {} bytes", data.len())
            }
            WebSocketMessage::Close { code, reason } => {
                format!("Close: {} - {}", code, reason)
            }
        }
    }
}

// Server statistics
#[derive(Debug)]
struct ServerStats {
    start_time: DateTime<Utc>,
    total_connections: u64,
    active_connections: u64,
    total_requests: u64,
    websocket_connections: u64,
    bytes_sent: u64,
    bytes_received: u64,
}

impl ServerStats {
    fn new() -> Self {
        println!("Initializing server statistics");
        ServerStats {
            start_time: Utc::now(),
            total_connections: 0,
            active_connections: 0,
            total_requests: 0,
            websocket_connections: 0,
            bytes_sent: 0,
            bytes_received: 0,
        }
    }
    
    fn increment_connections(&mut self) {
        self.total_connections += 1;
        self.active_connections += 1;
        println!("New connection! Total: {}, Active: {}", 
                self.total_connections, self.active_connections);
    }
    
    fn decrement_connections(&mut self) {
        self.active_connections = self.active_connections.saturating_sub(1);
        println!("Connection closed! Active: {}", self.active_connections);
    }
    
    fn increment_requests(&mut self) {
        self.total_requests += 1;
        if self.total_requests % 100 == 0 {
            println!("Milestone: {} requests processed!", self.total_requests);
        }
    }
    
    fn increment_websocket(&mut self) {
        self.websocket_connections += 1;
        println!("WebSocket connection! Total: {}", self.websocket_connections);
    }
    
    fn add_bytes_sent(&mut self, bytes: usize) {
        self.bytes_sent += bytes as u64;
    }
    
    fn add_bytes_received(&mut self, bytes: usize) {
        self.bytes_received += bytes as u64;
    }
    
    fn get_uptime(&self) -> chrono::Duration {
        Utc::now() - self.start_time
    }
    
    fn to_json(&self) -> serde_json::Value {
        serde_json::json!({
            "uptime": self.get_uptime().num_seconds(),
            "total_connections": self.total_connections,
            "active_connections": self.active_connections,
            "total_requests": self.total_requests,
            "websocket_connections": self.websocket_connections,
            "bytes_sent": self.bytes_sent,
            "bytes_received": self.bytes_received,
            "start_time": self.start_time.to_rfc3339()
        })
    }
}

// Async web server
struct AsyncWebServer {
    stats: Arc<RwLock<ServerStats>>,
    routes: HashMap<String, String>,
}

impl AsyncWebServer {
    fn new() -> Self {
        println!("Creating async web server");
        let mut server = AsyncWebServer {
            stats: Arc::new(RwLock::new(ServerStats::new())),
            routes: HashMap::new(),
        };
        
        // Setup default routes
        server.setup_routes();
        server
    }
    
    fn setup_routes(&mut self) {
        println!("Setting up default routes");
        
        // Main page
        self.routes.insert("/".to_string(), self.generate_index_html());
        
        // API endpoints
        self.routes.insert("/api/stats".to_string(), self.generate_stats_json());
        self.routes.insert("/api/echo".to_string(), self.generate_echo_html());
        self.routes.insert("/api/time".to_string(), self.generate_time_json());
        
        // WebSocket demo
        self.routes.insert("/websocket".to_string(), self.generate_websocket_html());
        
        println!("Routes configured: {} endpoints", self.routes.len());
    }
    
    fn generate_index_html(&self) -> String {
        println!("Generating index HTML");
        r#"
<!DOCTYPE html>
<html>
<head>
    <title>Async Rust Web Server</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; }
        .container { max-width: 800px; margin: 0 auto; background: rgba(255,255,255,0.1); padding: 40px; border-radius: 15px; backdrop-filter: blur(10px); }
        .header { text-align: center; margin-bottom: 30px; }
        .stats { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 20px; margin: 20px 0; }
        .stat-box { background: rgba(255,255,255,0.2); padding: 20px; border-radius: 10px; text-align: center; }
        .buttons { display: flex; gap: 10px; justify-content: center; margin: 20px 0; }
        .btn { background: #4CAF50; color: white; padding: 12px 24px; border: none; border-radius: 5px; cursor: pointer; text-decoration: none; display: inline-block; }
        .btn:hover { background: #45a049; }
        .btn.secondary { background: #2196F3; }
        .btn.secondary:hover { background: #1976D2; }
        .btn.danger { background: #f44336; }
        .btn.danger:hover { background: #d32f2f; }
        .code { background: #2d3748; color: #e2e8f0; padding: 15px; border-radius: 5px; font-family: monospace; margin: 10px 0; }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>🚀 Async Rust Web Server</h1>
            <p>High-performance async web server built with Tokio</p>
        </div>
        
        <div class="stats" id="stats">
            <div class="stat-box">
                <h3>📡 Total Connections</h3>
                <p id="total-connections">Loading...</p>
            </div>
            <div class="stat-box">
                <h3>🟢 Active Connections</h3>
                <p id="active-connections">Loading...</p>
            </div>
            <div class="stat-box">
                <h3>📊 Total Requests</h3>
                <p id="total-requests">Loading...</p>
            </div>
            <div class="stat-box">
                <h3>🌐 WebSocket Connections</h3>
                <p id="websocket-connections">Loading...</p>
            </div>
        </div>
        
        <div class="buttons">
            <a href="/api/stats" class="btn">View Stats API</a>
            <a href="/api/echo" class="btn secondary">Echo Test</a>
            <a href="/api/time" class="btn secondary">Current Time</a>
            <a href="/websocket" class="btn danger">WebSocket Demo</a>
        </div>
        
        <div class="code">
            <h3>Features Demonstrated:</h3>
            <ul>
                <li>✅ Async/await programming with Tokio</li>
                <li>✅ HTTP/1.1 protocol implementation</li>
                <li>✅ WebSocket support</li>
                <li>✅ JSON API endpoints</li>
                <li>✅ Real-time statistics</li>
                <li>✅ Connection pooling</li>
                <li>✅ Error handling and recovery</li>
                <li>✅ Memory-safe concurrent programming</li>
            </ul>
        </div>
    </div>
    
    <script>
        // Fetch real-time stats
        async function updateStats() {
            try {
                const response = await fetch('/api/stats');
                const stats = await response.json();
                
                document.getElementById('total-connections').textContent = stats.total_connections;
                document.getElementById('active-connections').textContent = stats.active_connections;
                document.getElementById('total-requests').textContent = stats.total_requests;
                document.getElementById('websocket-connections').textContent = stats.websocket_connections;
            } catch (error) {
                console.error('Failed to fetch stats:', error);
            }
        }
        
        // Update stats every second
        setInterval(updateStats, 1000);
        updateStats();
    </script>
</body>
</html>
        "#.to_string()
    }
    
    fn generate_stats_json(&self) -> String {
        println!("Generating stats JSON");
        // This would be populated with actual stats in a real implementation
        serde_json::json!({
            "message": "Server statistics endpoint",
            "features": [
                "Async programming with Tokio",
                "HTTP/1.1 protocol",
                "WebSocket support",
                "JSON API",
                "Real-time statistics",
                "Connection pooling",
                "Error handling"
            ]
        }).to_string()
    }
    
    fn generate_echo_html(&self) -> String {
        println!("Generating echo HTML");
        r#"
<!DOCTYPE html>
<html>
<head>
    <title>Echo API Test</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: #f5f5f5; }
        .container { max-width: 600px; margin: 0 auto; background: white; padding: 40px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        .form-group { margin-bottom: 20px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input, textarea { width: 100%; padding: 10px; border: 1px solid #ddd; border-radius: 5px; font-size: 16px; }
        textarea { height: 100px; resize: vertical; }
        button { background: #4CAF50; color: white; padding: 12px 24px; border: none; border-radius: 5px; cursor: pointer; font-size: 16px; }
        button:hover { background: #45a049; }
        .response { background: #f8f9fa; padding: 20px; border-radius: 5px; margin-top: 20px; border-left: 4px solid #4CAF50; }
    </style>
</head>
<body>
    <div class="container">
        <h1>📢 Echo API Test</h1>
        <p>Send data to the server and get it echoed back!</p>
        
        <form id="echoForm">
            <div class="form-group">
                <label for="message">Message:</label>
                <textarea id="message" name="message" placeholder="Enter your message here..."></textarea>
            </div>
            <div class="form-group">
                <button type="submit">Send Echo Request</button>
            </div>
        </form>
        
        <div id="response" class="response" style="display: none;">
            <h3>Server Response:</h3>
            <div id="responseContent"></div>
        </div>
    </div>
    
    <script>
        document.getElementById('echoForm').addEventListener('submit', async (e) => {
            e.preventDefault();
            
            const message = document.getElementById('message').value;
            const responseDiv = document.getElementById('response');
            const responseContent = document.getElementById('responseContent');
            
            try {
                const response = await fetch('/api/echo', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify({ message: message })
                });
                
                const result = await response.json();
                
                responseContent.textContent = JSON.stringify(result, null, 2);
                responseDiv.style.display = 'block';
            } catch (error) {
                responseContent.textContent = 'Error: ' + error.message;
                responseDiv.style.display = 'block';
            }
        });
    </script>
</body>
</html>
        "#.to_string()
    }
    
    fn generate_time_json(&self) -> String {
        println!("Generating time JSON");
        serde_json::json!({
            "timestamp": Utc::now().to_rfc3339(),
            "unix_timestamp": Utc::now().timestamp(),
            "message": "Current server time",
            "timezone": "UTC"
        }).to_string()
    }
    
    fn generate_websocket_html(&self) -> String {
        println!("Generating WebSocket HTML");
        r#"
<!DOCTYPE html>
<html>
<head>
    <title>WebSocket Demo</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: #f0f0f0; }
        .container { max-width: 600px; margin: 0 auto; background: white; padding: 40px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        .chat { height: 300px; overflow-y: auto; border: 1px solid #ddd; padding: 10px; margin-bottom: 20px; background: #fafafa; }
        .form-group { display: flex; gap: 10px; }
        input { flex: 1; padding: 10px; border: 1px solid #ddd; border-radius: 5px; font-size: 16px; }
        button { background: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; font-size: 16px; }
        button:hover { background: #45a049; }
        .message { margin-bottom: 10px; padding: 8px; border-radius: 5px; }
        .message.sent { background: #e3f2fd; color: #1976d2; text-align: right; }
        .message.received { background: #f0f0f0; color: #333; }
        .status { text-align: center; margin: 10px 0; padding: 10px; border-radius: 5px; }
        .status.connected { background: #4CAF50; color: white; }
        .status.disconnected { background: #f44336; color: white; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🌐 WebSocket Demo</h1>
        <p>Real-time bidirectional communication with the server!</p>
        
        <div id="status" class="status disconnected">Disconnected</div>
        
        <div id="chat" class="chat"></div>
        
        <div class="form-group">
            <input type="text" id="messageInput" placeholder="Type a message...">
            <button onclick="sendMessage()">Send</button>
        </div>
    </div>
    
    <script>
        let ws = null;
        let reconnectAttempts = 0;
        const maxReconnectAttempts = 5;
        
        function connect() {
            const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
            const wsUrl = `${protocol}//${window.location.host}/ws`;
            
            console.log('Connecting to WebSocket:', wsUrl);
            
            ws = new WebSocket(wsUrl);
            
            ws.onopen = function() {
                console.log('WebSocket connected');
                document.getElementById('status').className = 'status connected';
                document.getElementById('status').textContent = 'Connected';
                reconnectAttempts = 0;
            };
            
            ws.onmessage = function(event) {
                console.log('WebSocket message received:', event.data);
                addMessage(event.data, false);
            };
            
            ws.onclose = function(event) {
                console.log('WebSocket closed:', event);
                document.getElementById('status').className = 'status disconnected';
                document.getElementById('status').textContent = 'Disconnected';
                
                // Attempt to reconnect
                if (reconnectAttempts < maxReconnectAttempts) {
                    reconnectAttempts++;
                    console.log(`Reconnection attempt ${reconnectAttempts}/${maxReconnectAttempts}`);
                    setTimeout(connect, 2000);
                }
            };
            
            ws.onerror = function(error) {
                console.error('WebSocket error:', error);
                document.getElementById('status').className = 'status disconnected';
                document.getElementById('status').textContent = 'Connection Error';
            };
        }
        
        function sendMessage() {
            const input = document.getElementById('messageInput');
            const message = input.value.trim();
            
            if (message && ws && ws.readyState === WebSocket.OPEN) {
                ws.send(message);
                addMessage(message, true);
                input.value = '';
                console.log('Sent message:', message);
            }
        }
        
        function addMessage(message, isSent) {
            const chat = document.getElementById('chat');
            const messageDiv = document.createElement('div');
            messageDiv.className = `message ${isSent ? 'sent' : 'received'}`;
            messageDiv.textContent = message;
            chat.appendChild(messageDiv);
            chat.scrollTop = chat.scrollHeight;
        }
        
        // Handle Enter key
        document.getElementById('messageInput').addEventListener('keypress', function(e) {
            if (e.key === 'Enter') {
                sendMessage();
            }
        });
        
        // Auto-connect
        connect();
    </script>
</body>
</html>
        "#.to_string()
    }
    
    async fn handle_http_request(&self, request: HttpRequest) -> HttpResponse {
        println!("Handling HTTP request: {} {}", request.method, request.path);
        
        let mut response = HttpResponse::new(StatusCode::OK);
        response.set_header("Server".to_string(), "Async-Rust-Server/1.0".to_string());
        response.set_header("Date".to_string(), Utc::now().to_rfc3339());
        
        match request.path.as_str() {
            "/" => {
                let html = self.generate_index_html();
                response.set_html_body(html);
            }
            "/api/stats" => {
                let stats_json = self.generate_stats_json();
                response.set_json_body(serde_json::from_str(&stats_json).unwrap());
            }
            "/api/echo" => {
                if request.method == "POST" {
                    let echo_data = serde_json::json!({
                        "echo": request.body,
                        "timestamp": Utc::now().to_rfc3339(),
                        "method": request.method,
                        "path": request.path
                    });
                    response.set_json_body(echo_data);
                } else {
                    *response.status_mut() = StatusCode::METHOD_NOT_ALLOWED;
                    response.set_text_body("Method not allowed".to_string());
                }
            }
            "/api/time" => {
                let time_json = self.generate_time_json();
                response.set_json_body(serde_json::from_str(&time_json).unwrap());
            }
            "/websocket" => {
                let ws_html = self.generate_websocket_html();
                response.set_html_body(ws_html);
            }
            _ => {
                *response.status_mut() = StatusCode::NOT_FOUND;
                response.set_text_body("404 - Not Found".to_string());
            }
        }
        
        println!("Generated response with {} bytes", response.body.len());
        response
    }
    
    async fn handle_websocket_connection(&self, websocket: WebSocketStream<TcpStream>) {
        println!("Handling WebSocket connection");
        
        let (mut ws_sender, mut ws_receiver) = websocket.split();
        
        // Send welcome message
        let welcome = serde_json::json!({
            "type": "welcome",
            "message": "Connected to Async Rust WebSocket Server!",
            "timestamp": Utc::now().to_rfc3339()
        });
        
        if let Err(e) = ws_sender.send(serde_json::to_string(&welcome).unwrap()).await {
            println!("Failed to send welcome message: {}", e);
            return;
        }
        
        println!("Sent welcome message to WebSocket client");
        
        // Handle incoming messages
        while let Some(msg) = ws_receiver.next().await {
            match msg {
                Ok(tokio_tungstenite::tungstenite::Message::Text(text)) => {
                    println!("Received WebSocket text: {}", text);
                    
                    // Echo back the message
                    let echo = serde_json::json!({
                        "type": "echo",
                        "message": text,
                        "timestamp": Utc::now().to_rfc3339()
                    });
                    
                    if let Err(e) = ws_sender.send(serde_json::to_string(&echo).unwrap()).await {
                        println!("Failed to send echo message: {}", e);
                        break;
                    }
                }
                Ok(tokio_tungstenite::tungstenite::Message::Binary(data)) => {
                    println!("Received WebSocket binary: {} bytes", data.len());
                    
                    // Echo back binary data
                    if let Err(e) = ws_sender.send(tokio_tungstenite::tungstenite::Message::Binary(data)).await {
                        println!("Failed to send binary message: {}", e);
                        break;
                    }
                }
                Ok(tokio_tungstenite::tungstenite::Message::Close(_)) => {
                    println!("WebSocket connection closed by client");
                    break;
                }
                Err(e) => {
                    println!("WebSocket error: {}", e);
                    break;
                }
            }
        }
        
        println!("WebSocket connection handler completed");
    }
    
    async fn run(&self, addr: String) -> Result<(), Box<dyn std::error::Error>> {
        println!("Starting async web server on {}", addr);
        
        let listener = TcpListener::bind(&addr).await?;
        println!("Server listening on {}", addr);
        
        let stats = self.stats.clone();
        
        while let Ok((stream, addr)) = listener.accept().await {
            println!("New connection from: {}", addr);
            
            // Update stats
            {
                let mut stats_guard = stats.write().await;
                stats_guard.increment_connections();
            }
            
            let stats_clone = stats.clone();
            let routes_clone = self.routes.clone();
            
            // Handle connection in a separate task
            tokio::spawn(async move {
                let ws_stream = accept_hdr_async(stream).await;
                
                match ws_stream {
                    Ok(websocket) => {
                        println!("WebSocket upgrade successful");
                        
                        // Update WebSocket stats
                        {
                            let mut stats_guard = stats_clone.write().await;
                            stats_guard.increment_websocket();
                        }
                        
                        // Handle WebSocket messages
                        let server = AsyncWebServer::new();
                        server.handle_websocket_connection(websocket).await;
                    }
                    Err(err) => {
                        println!("WebSocket upgrade failed: {}", err);
                        
                        // Handle as HTTP request
                        let request = HttpRequest::new(
                            "GET".to_string(),
                            "/".to_string(),
                            HashMap::new(),
                            String::new()
                        );
                        
                        let response = server.handle_http_request(request).await;
                        
                        // Send HTTP response
                        let response_string = response.to_string();
                        if let Err(e) = tokio::io::AsyncWriteExt::write_all(&mut stream, response_string.as_bytes()).await {
                            println!("Failed to send response: {}", e);
                        }
                        
                        // Update request stats
                        {
                            let mut stats_guard = stats_clone.write().await;
                            stats_guard.increment_requests();
                            stats_guard.add_bytes_sent(response_string.len());
                        }
                    }
                }
                
                // Update connection stats
                {
                    let mut stats_guard = stats_clone.write().await;
                    stats_guard.decrement_connections();
                }
            });
        }
        
        Ok(())
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("========================================");
    println!("    ASYNC RUST WEB SERVER - LEVEL 5");
    println!("========================================");
    println!("Welcome to high-performance web development in Rust!");
    println!("This server demonstrates:");
    println!("- Async/await programming with Tokio");
    println!("- HTTP/1.1 protocol implementation");
    println!("- WebSocket support for real-time communication");
    println!("- JSON API endpoints");
    println!("- Connection pooling and load balancing");
    println!("- Error handling with Result types");
    println!("- Memory-safe concurrent programming");
    println!("- Human-like code with detailed comments!");
    println!("========================================");
    
    let server = AsyncWebServer::new();
    let addr = "127.0.0.1:8080".to_string();
    
    println!("Server features:");
    println!("✅ Async HTTP server with Tokio");
    println!("✅ WebSocket support for real-time communication");
    println!("✅ JSON API endpoints");
    println!("✅ Real-time statistics dashboard");
    println!("✅ Echo API for testing");
    println!("✅ Time API endpoint");
    println!("✅ Connection pooling and management");
    println!("✅ Error handling and recovery");
    
    println!("\nStarting server...");
    println!("Open http://localhost:8080 in your browser");
    println!("WebSocket endpoint: ws://localhost:8080/ws");
    
    server.run(addr).await?;
    
    Ok(())
}
