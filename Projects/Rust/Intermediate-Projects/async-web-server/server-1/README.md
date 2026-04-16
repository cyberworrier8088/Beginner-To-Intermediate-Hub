# Async Web Server in Rust - Level 5

## Overview
A high-performance asynchronous web server demonstrating advanced Rust programming, Tokio async runtime, and HTTP/2 protocol implementation.

## Features
- **Async/Await Programming**: Tokio runtime for non-blocking operations
- **HTTP/1.1 Protocol**: Complete HTTP request/response handling
- **WebSocket Support**: Real-time bidirectional communication
- **JSON API**: RESTful endpoints with serde serialization
- **Connection Pooling**: Efficient concurrent connection management
- **Error Handling**: Result types for robust error management
- **Real-time Statistics**: Live server metrics dashboard
- **Security Features**: Input validation and safe defaults

## Learning Objectives
- Async/await programming with Tokio
- HTTP protocol implementation and parsing
- WebSocket protocol for real-time communication
- Connection pooling and load balancing
- Error handling with Result types
- JSON serialization with serde
- Human-like code with detailed comments

## Prerequisites
- Rust 1.70+ (2021 edition)
- Cargo package manager
- Basic understanding of HTTP protocol
- Familiarity with async programming concepts

## Installation & Setup

### Install Rust (if not already installed)
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source ~/.cargo/env
```

### Compilation & Running
```bash
# Navigate to project
cd Projects/Rust/Intermediate-Projects/async-web-server/server-1/

# Run with Cargo (recommended)
cargo run

# Or compile and run manually
cargo build --release
./target/release/async-web-server
```

## Usage
1. Run the server
2. Open browser to access web interface
3. Test different endpoints and features

## Available Endpoints

### Web Interface
- **Main Page**: `http://localhost:8080/` - Interactive dashboard
- **Stats API**: `http://localhost:8080/api/stats` - Server statistics
- **Echo API**: `http://localhost:8080/api/echo` - POST echo service
- **Time API**: `http://localhost:8080/api/time` - Current server time
- **WebSocket**: `ws://localhost:8080/ws` - Real-time communication

### API Examples

#### Get Server Statistics
```bash
curl http://localhost:8080/api/stats
```

#### Echo Service
```bash
curl -X POST -H "Content-Type: application/json" \
     -d '{"message": "Hello, Rust Server!"}' \
     http://localhost:8080/api/echo
```

#### Get Current Time
```bash
curl http://localhost:8080/api/time
```

#### WebSocket Connection
```javascript
const ws = new WebSocket('ws://localhost:8080/ws');
ws.onmessage = function(event) {
    console.log('Received:', event.data);
};
ws.send('Hello, Server!');
```

## Example Session
```
========================================
    ASYNC RUST WEB SERVER - LEVEL 5
========================================
Welcome to high-performance web development in Rust!
This server demonstrates:
- Async/await programming with Tokio
- HTTP/1.1 protocol implementation
- WebSocket support for real-time communication
- JSON API endpoints
- Connection pooling and load balancing
- Error handling with Result types
- Human-like code with detailed comments!
========================================

Server features:
✅ Async HTTP server with Tokio
✅ WebSocket support for real-time communication
✅ JSON API endpoints
✅ Real-time statistics dashboard
✅ Echo API for testing
✅ Time API endpoint
✅ Connection pooling and management
✅ Error handling and recovery

Starting server...
Open http://localhost:8080 in your browser
WebSocket endpoint: ws://localhost:8080/ws
Press Ctrl+C to stop...

Server listening on 127.0.0.1:8080
New connection from 127.0.0.1:54321
WebSocket upgrade successful
Sent welcome message to WebSocket client
WebSocket connection handler completed
```

## Code Structure
```rust
// HTTP request structure
#[derive(Debug, Clone)]
struct HttpRequest {
    method: String,
    path: String,
    query_params: HashMap<String, String>,
    headers: HashMap<String, String>,
    body: String,
}

// HTTP response structure
#[derive(Debug)]
struct HttpResponse {
    status: StatusCode,
    headers: HashMap<String, String>,
    body: Vec<u8>,
}

// WebSocket message types
#[derive(Debug, Clone, Serialize, Deserialize)]
enum WebSocketMessage {
    Text(String),
    Binary(Vec<u8>),
    Ping(Vec<u8>),
    Pong(Vec<u8>),
    Close { code: u16, reason: String },
}

// Main server structure
struct AsyncWebServer {
    stats: Arc<RwLock<ServerStats>>,
    routes: HashMap<String, String>,
}

impl AsyncWebServer {
    async fn handle_http_request(&self, request: HttpRequest) -> HttpResponse;
    async fn handle_websocket_connection(&self, websocket: WebSocketStream<TcpStream>);
    async fn run(&self, addr: String) -> Result<(), Box<dyn std::error::Error>>;
}
```

## Key Concepts Demonstrated
1. **Async/Await Programming**: Non-blocking operations with Tokio
2. **HTTP Protocol Implementation**: Request parsing and response generation
3. **WebSocket Communication**: Real-time bidirectional messaging
4. **Connection Pooling**: Efficient concurrent connection handling
5. **Error Handling**: Result types for robust error management
6. **JSON Serialization**: Serde for structured data handling
7. **Thread Safety**: Arc and RwLock for shared state
8. **Human-Like Code**: Detailed comments and user feedback

## Performance Features
- **Non-blocking I/O**: Async operations prevent thread blocking
- **Connection Pooling**: Efficient resource management
- **Memory Safety**: Rust's ownership system prevents memory leaks
- **Zero-cost Abstractions**: Compile-time optimizations
- **Error Recovery**: Graceful handling of network errors
- **Load Balancing**: Distributed connection handling

## Security Considerations
- **Input Validation**: All user inputs are validated
- **Safe Defaults**: Secure configuration by default
- **Error Handling**: No panic cases in production
- **Resource Limits**: Connection and request size limits
- **Type Safety**: Compile-time prevention of vulnerabilities

## Troubleshooting

### Compilation Errors
- **"tokio not found"**: Add tokio to Cargo.toml dependencies
- **"tungstenite not found"**: Add tokio-tungstenite to dependencies
- **"serde not found"**: Add serde and serde_json to dependencies

### Runtime Errors
- **"Address already in use"**: Port is occupied, try different port
- **"Permission denied"**: Use port > 1024 or run as administrator
- **"Connection refused"**: Server not running or firewall blocking

### Performance Issues
- **High CPU usage**: Check for blocking operations in async context
- **Memory leaks**: Monitor with valgrind or similar tools
- **Slow responses**: Profile and optimize async operations

## Extensions and Enhancements
Try these challenges to improve the server:
1. **HTTPS Support**: Add TLS/SSL encryption
2. **HTTP/2 Protocol**: Implement multiplexed requests
3. **Authentication**: Add JWT or OAuth2 support
4. **Database Integration**: Connect to PostgreSQL or MongoDB
5. **Caching Layer**: Add Redis or in-memory caching
6. **Load Testing**: Implement connection rate limiting
7. **Metrics Collection**: Add Prometheus metrics
8. **Docker Deployment**: Containerize the application
9. **Configuration Files**: Add TOML/YAML configuration
10. **Logging System**: Implement structured logging

## Next Steps
After mastering this async web server, try:
- Level 6: Database Integration with SQLx
- Level 7: REST API Development with Axum
- Level 8: Microservices Architecture
- Level 9: Cloud Deployment and DevOps
- Level 10: Advanced Security and Performance

## About This Project
This async web server demonstrates advanced Rust programming concepts while maintaining clean, human-readable code. The implementation focuses on teaching async programming, HTTP protocol handling, and real-time communication through practical application.

Happy coding and happy serving!
