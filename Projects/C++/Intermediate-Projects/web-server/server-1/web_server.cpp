/*
 * Web Server in C++ - Level 5: Network Programming & HTTP Protocol
 * 
 * Welcome to web development in C++! This is where systems programming meets internet.
 * Learn socket programming, HTTP protocol, and multi-client handling.
 * 
 * Key concepts you'll learn:
 * - Socket programming with Berkeley sockets
 * - HTTP protocol implementation
 * - Multi-threading for concurrent connections
 * - File serving and MIME types
 * - Request parsing and response generation
 * - Error handling and resource management
 * - Human-like code with detailed explanations!
 */

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

// HTTP response structure
struct HttpResponse {
    int status_code;
    string status_text;
    map<string, string> headers;
    string body;
    
    HttpResponse(int code, const string& text) : status_code(code), status_text(text) {}
    
    void setHeader(const string& name, const string& value) {
        headers[name] = value;
    }
    
    void setBody(const string& content, const string& content_type) {
        body = content;
        setHeader("Content-Type", content_type);
        setHeader("Content-Length", to_string(body.length()));
    }
    
    string toString() const {
        stringstream response;
        response << "HTTP/1.1 " << status_code << " " << status_text << "\r\n";
        
        for (const auto& header : headers) {
            response << header.first << ": " << header.second << "\r\n";
        }
        
        response << "\r\n" << body;
        return response.str();
    }
};

// MIME type mapping
const map<string, string> MIME_TYPES = {
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".json", "application/json"},
    {".png", "image/png"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".gif", "image/gif"},
    {".ico", "image/x-icon"},
    {".txt", "text/plain"},
    {".pdf", "application/pdf"},
    {".xml", "application/xml"},
};

// Get MIME type for file extension
string getMimeType(const string& filename) {
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos == string::npos) {
        return "text/plain";
    }
    
    string extension = filename.substr(dot_pos);
    auto it = MIME_TYPES.find(extension);
    
    if (it != MIME_TYPES.end()) {
        return it->second;
    }
    
    return "application/octet-stream";
}

// Get current timestamp string
string getCurrentTimestamp() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
    
    return string(buffer);
}

// Read file content
string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Parse HTTP request
struct HttpRequest {
    string method;
    string path;
    string version;
    map<string, string> headers;
    string body;
    
    bool parse(const string& request) {
        cout << "Parsing HTTP request..." << endl;
        cout << "Request size: " << request.length() << " bytes" << endl;
        
        stringstream ss(request);
        string line;
        
        // Parse request line
        if (!getline(ss, line)) {
            cout << "Error: No request line found" << endl;
            return false;
        }
        
        stringstream request_line(line);
        request_line >> method >> path >> version;
        
        cout << "Method: " << method << endl;
        cout << "Path: " << path << endl;
        cout << "Version: " << version << endl;
        
        // Parse headers
        while (getline(ss, line) && line != "\r") {
            size_t colon_pos = line.find(':');
            if (colon_pos != string::npos) {
                string name = line.substr(0, colon_pos);
                string value = line.substr(colon_pos + 1);
                
                // Trim whitespace
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                
                headers[name] = value;
                cout << "Header: " << name << " = " << value << endl;
            }
        }
        
        // Read body if present
        stringstream body_stream;
        body_stream << ss.rdbuf();
        body = body_stream.str();
        
        if (!body.empty()) {
            cout << "Body length: " << body.length() << " bytes" << endl;
        }
        
        cout << "HTTP request parsed successfully!" << endl;
        return true;
    }
};

// Web server class
class WebServer {
private:
    int server_socket;
    int port;
    string document_root;
    atomic<bool> running;
    atomic<int> connection_count;
    mutex cout_mutex;
    
public:
    WebServer(int server_port, const string& doc_root) 
        : port(server_port), document_root(doc_root), running(false), connection_count(0) {
        server_socket = -1;
        cout << "WebServer initialized!" << endl;
        cout << "Port: " << port << endl;
        cout << "Document root: " << document_root << endl;
    }
    
    ~WebServer() {
        stop();
    }
    
    // Start the server
    bool start() {
        cout << "\n=== STARTING WEB SERVER ===" << endl;
        
        // Create socket
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket < 0) {
            cout << "Error: Failed to create socket" << endl;
            return false;
        }
        
        cout << "Socket created successfully!" << endl;
        
        // Set socket options
        int opt = 1;
        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            cout << "Error: Failed to set socket options" << endl;
            close(server_socket);
            return false;
        }
        
        cout << "Socket options set!" << endl;
        
        // Bind socket
        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);
        
        if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            cout << "Error: Failed to bind socket to port " << port << endl;
            close(server_socket);
            return false;
        }
        
        cout << "Socket bound to port " << port << endl;
        
        // Start listening
        if (listen(server_socket, 10) < 0) {
            cout << "Error: Failed to listen on socket" << endl;
            close(server_socket);
            return false;
        }
        
        cout << "Server listening on port " << port << endl;
        cout << "Document root: " << document_root << endl;
        cout << "Server URL: http://localhost:" << port << endl;
        cout << "==============================" << endl;
        
        running = true;
        
        // Start accepting connections
        acceptConnections();
        
        return true;
    }
    
    // Stop the server
    void stop() {
        if (running) {
            cout << "\n=== STOPPING WEB SERVER ===" << endl;
            running = false;
            
            if (server_socket >= 0) {
                close(server_socket);
                cout << "Server socket closed" << endl;
            }
            
            cout << "Web server stopped!" << endl;
            cout << "=============================" << endl;
        }
    }
    
    // Accept incoming connections
    void acceptConnections() {
        cout << "Starting to accept connections..." << endl;
        
        while (running) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            
            cout << "Waiting for connection..." << endl;
            
            int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
            
            if (client_socket < 0) {
                if (running) {
                    cout << "Error: Failed to accept connection" << endl;
                }
                continue;
            }
            
            // Get client information
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
            
            int current_connections = ++connection_count;
            
            {
                lock_guard<mutex> lock(cout_mutex);
                cout << "New connection accepted!" << endl;
                cout << "Client IP: " << client_ip << endl;
                cout << "Client port: " << ntohs(client_addr.sin_port) << endl;
                cout << "Total connections: " << current_connections << endl;
                cout << "----------------------------" << endl;
            }
            
            // Handle connection in a separate thread
            thread client_thread(&WebServer::handleClient, this, client_socket, client_ip);
            client_thread.detach();
        }
    }
    
    // Handle individual client
    void handleClient(int client_socket, const string& client_ip) {
        cout << "Handling client: " << client_ip << endl;
        
        // Read request
        char buffer[4096];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytes_received <= 0) {
            cout << "Client disconnected: " << client_ip << endl;
            close(client_socket);
            return;
        }
        
        buffer[bytes_received] = '\0';
        string request_str(buffer);
        
        cout << "Received " << bytes_received << " bytes from " << client_ip << endl;
        
        // Parse HTTP request
        HttpRequest request;
        if (!request.parse(request_str)) {
            cout << "Error: Failed to parse HTTP request from " << client_ip << endl;
            sendErrorResponse(client_socket, 400, "Bad Request");
            close(client_socket);
            return;
        }
        
        // Handle different methods
        if (request.method == "GET") {
            handleGetRequest(client_socket, request);
        } else if (request.method == "POST") {
            handlePostRequest(client_socket, request);
        } else {
            cout << "Unsupported method: " << request.method << " from " << client_ip << endl;
            sendErrorResponse(client_socket, 405, "Method Not Allowed");
        }
        
        close(client_socket);
        cout << "Connection closed for: " << client_ip << endl;
    }
    
    // Handle GET requests
    void handleGetRequest(int client_socket, const HttpRequest& request) {
        cout << "Handling GET request for: " << request.path << endl;
        
        // Handle root path
        string file_path = request.path;
        if (file_path == "/") {
            file_path = "/index.html";
        }
        
        // Security check - prevent directory traversal
        if (file_path.find("..") != string::npos) {
            cout << "Security alert: Directory traversal attempt blocked" << endl;
            sendErrorResponse(client_socket, 403, "Forbidden");
            return;
        }
        
        // Construct full file path
        string full_path = document_root + file_path;
        
        cout << "Requested file: " << full_path << endl;
        
        // Try to read file
        string file_content = readFile(full_path);
        
        if (file_content.empty()) {
            cout << "File not found: " << full_path << endl;
            sendErrorResponse(client_socket, 404, "Not Found");
            return;
        }
        
        cout << "File found and read successfully!" << endl;
        cout << "File size: " << file_content.length() << " bytes" << endl;
        
        // Send successful response
        HttpResponse response(200, "OK");
        response.setHeader("Server", "C++ WebServer/1.0");
        response.setHeader("Date", getCurrentTimestamp());
        response.setHeader("Connection", "close");
        response.setBody(file_content, getMimeType(file_path));
        
        string response_str = response.toString();
        
        cout << "Sending response..." << endl;
        cout << "Response size: " << response_str.length() << " bytes" << endl;
        
        send(client_socket, response_str.c_str(), response_str.length(), 0);
        
        cout << "Response sent successfully!" << endl;
    }
    
    // Handle POST requests
    void handlePostRequest(int client_socket, const HttpRequest& request) {
        cout << "Handling POST request for: " << request.path << endl;
        cout << "POST data: " << request.body << endl;
        
        // For demo purposes, just echo back the POST data
        string html_response = generatePostResponse(request);
        
        HttpResponse response(200, "OK");
        response.setHeader("Server", "C++ WebServer/1.0");
        response.setHeader("Date", getCurrentTimestamp());
        response.setHeader("Connection", "close");
        response.setBody(html_response, "text/html");
        
        string response_str = response.toString();
        
        cout << "Sending POST response..." << endl;
        cout << "Response size: " << response_str.length() << " bytes" << endl;
        
        send(client_socket, response_str.c_str(), response_str.length(), 0);
        
        cout << "POST response sent successfully!" << endl;
    }
    
    // Generate POST response HTML
    string generatePostResponse(const HttpRequest& request) {
        stringstream html;
        html << "<!DOCTYPE html>\n";
        html << "<html>\n";
        html << "<head>\n";
        html << "    <title>POST Response</title>\n";
        html << "    <style>\n";
        html << "        body { font-family: Arial, sans-serif; margin: 40px; }\n";
        html << "        .container { max-width: 600px; margin: 0 auto; }\n";
        html << "        .header { background: #f4f4f4; padding: 20px; border-radius: 5px; }\n";
        html << "        .content { background: #f9f9f9; padding: 20px; margin-top: 20px; border-radius: 5px; }\n";
        html << "        .data { background: #e9e9e9; padding: 15px; margin-top: 10px; border-radius: 5px; }\n";
        html << "    </style>\n";
        html << "</head>\n";
        html << "<body>\n";
        html << "    <div class=\"container\">\n";
        html << "        <div class=\"header\">\n";
        html << "            <h1>POST Request Received</h1>\n";
        html << "            <p>Your POST request has been processed successfully!</p>\n";
        html << "        </div>\n";
        html << "        <div class=\"content\">\n";
        html << "            <h2>Request Details:</h2>\n";
        html << "            <p><strong>Method:</strong> " << request.method << "</p>\n";
        html << "            <p><strong>Path:</strong> " << request.path << "</p>\n";
        html << "            <p><strong>Version:</strong> " << request.version << "</p>\n";
        html << "        </div>\n";
        html << "        <div class=\"data\">\n";
        html << "            <h3>POST Data:</h3>\n";
        html << "            <pre>" << request.body << "</pre>\n";
        html << "        </div>\n";
        html << "    </div>\n";
        html << "</body>\n";
        html << "</html>\n";
        
        return html.str();
    }
    
    // Send error response
    void sendErrorResponse(int client_socket, int status_code, const string& message) {
        cout << "Sending error response: " << status_code << " " << message << endl;
        
        HttpResponse response(status_code, message);
        response.setHeader("Server", "C++ WebServer/1.0");
        response.setHeader("Date", getCurrentTimestamp());
        response.setHeader("Connection", "close");
        
        string error_html = generateErrorPage(status_code, message);
        response.setBody(error_html, "text/html");
        
        string response_str = response.toString();
        
        send(client_socket, response_str.c_str(), response_str.length(), 0);
        
        cout << "Error response sent!" << endl;
    }
    
    // Generate error page HTML
    string generateErrorPage(int status_code, const string& message) {
        stringstream html;
        html << "<!DOCTYPE html>\n";
        html << "<html>\n";
        html << "<head>\n";
        html << "    <title>Error " << status_code << " - " << message << "</title>\n";
        html << "    <style>\n";
        html << "        body { font-family: Arial, sans-serif; margin: 40px; background: #f5f5f5; }\n";
        html << "        .container { max-width: 600px; margin: 0 auto; background: white; padding: 40px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }\n";
        html << "        .error-code { font-size: 72px; color: #e74c3c; font-weight: bold; margin-bottom: 20px; }\n";
        html << "        .error-message { font-size: 24px; color: #333; margin-bottom: 30px; }\n";
        html << "        .details { background: #f8f9fa; padding: 20px; border-radius: 5px; border-left: 4px solid #e74c3c; }\n";
        html << "    </style>\n";
        html << "</head>\n";
        html << "<body>\n";
        html << "    <div class=\"container\">\n";
        html << "        <div class=\"error-code\">" << status_code << "</div>\n";
        html << "        <div class=\"error-message\">" << message << "</div>\n";
        html << "        <div class=\"details\">\n";
        html << "            <h3>What happened?</h3>\n";
        html << "            <p>The server encountered an error while processing your request.</p>\n";
        html << "            <p><strong>Status Code:</strong> " << status_code << "</p>\n";
        html << "            <p><strong>Message:</strong> " << message << "</p>\n";
        html << "            <p><strong>Time:</strong> " << getCurrentTimestamp() << "</p>\n";
        html << "        </div>\n";
        html << "    </div>\n";
        html << "</body>\n";
        html << "</html>\n";
        
        return html.str();
    }
    
    // Get server statistics
    void getStatistics() {
        lock_guard<mutex> lock(cout_mutex);
        cout << "\n=== WEB SERVER STATISTICS ===" << endl;
        cout << "Server Status: " << (running ? "Running" : "Stopped") << endl;
        cout << "Port: " << port << endl;
        cout << "Document Root: " << document_root << endl;
        cout << "Current Connections: " << connection_count.load() << endl;
        cout << "Server Socket: " << server_socket << endl;
        cout << "============================" << endl;
    }
};

// Create default HTML files
void createDefaultFiles(const string& document_root) {
    cout << "Creating default HTML files..." << endl;
    
    // Create index.html
    string index_html = "<!DOCTYPE html>\n"
                      "<html>\n"
                      "<head>\n"
                      "    <title>C++ Web Server</title>\n"
                      "    <style>\n"
                      "        body { font-family: Arial, sans-serif; margin: 40px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; }\n"
                      "        .container { max-width: 800px; margin: 0 auto; background: rgba(255,255,255,0.1); padding: 40px; border-radius: 15px; backdrop-filter: blur(10px); }\n"
                      "        h1 { text-align: center; margin-bottom: 30px; font-size: 2.5em; }\n"
                      "        .feature { background: rgba(255,255,255,0.2); margin: 20px 0; padding: 20px; border-radius: 10px; }\n"
                      "        .stats { display: grid; grid-template-columns: 1fr 1fr; gap: 20px; margin-top: 30px; }\n"
                      "        .stat-box { background: rgba(255,255,255,0.15); padding: 20px; border-radius: 10px; text-align: center; }\n"
                      "        .code { background: #2d3748; color: #e2e8f0; padding: 15px; border-radius: 5px; font-family: monospace; margin: 10px 0; }\n"
                      "    </style>\n"
                      "</head>\n"
                      "<body>\n"
                      "    <div class=\"container\">\n"
                      "        <h1>🚀 C++ Web Server</h1>\n"
                      "        <div class=\"feature\">\n"
                      "            <h2>Welcome to your C++ Web Server!</h2>\n"
                      "            <p>This server is built with modern C++ and demonstrates:</p>\n"
                      "            <ul>\n"
                      "                <li>Socket programming and network communication</li>\n"
                      "                <li>HTTP protocol implementation</li>\n"
                      "                <li>Multi-threading for concurrent connections</li>\n"
                      "                <li>File serving with MIME type detection</li>\n"
                      "                <li>Error handling and resource management</li>\n"
                      "            </ul>\n"
                      "        </div>\n"
                      "        <div class=\"stats\">\n"
                      "            <div class=\"stat-box\">\n"
                      "                <h3>📡 GET Requests</h3>\n"
                      "                <p>Serves static files and content</p>\n"
                      "            </div>\n"
                      "            <div class=\"stat-box\">\n"
                      "                <h3>📤 POST Requests</h3>\n"
                      "                <p>Handles form data and uploads</p>\n"
                      "            </div>\n"
                      "        </div>\n"
                      "        <div class=\"feature\">\n"
                      "            <h2>Try These URLs:</h2>\n"
                      "            <div class=\"code\">\n"
                      "                <p>GET /index.html - Main page</p>\n"
                      "                <p>GET /test.txt - Text file</p>\n"
                      "                <p>POST /test - Test POST endpoint</p>\n"
                      "            </div>\n"
                      "        </div>\n"
                      "    </div>\n"
                      "</body>\n"
                      "</html>\n";
    
    ofstream index_file(document_root + "/index.html");
    index_file << index_html;
    index_file.close();
    cout << "Created: " << document_root << "/index.html" << endl;
    
    // Create test.txt
    ofstream test_file(document_root + "/test.txt");
    test_file << "Hello from C++ Web Server!\n";
    test_file << "This is a test text file.\n";
    test_file << "Server is running successfully!\n";
    test_file << "Timestamp: " << getCurrentTimestamp() << "\n";
    test_file.close();
    cout << "Created: " << document_root << "/test.txt" << endl;
    
    cout << "Default files created successfully!" << endl;
}

// Main function
int main(int argc, char* argv[]) {
    cout << "========================================" << endl;
    cout << "    C++ WEB SERVER - LEVEL 5" << endl;
    cout << "========================================" << endl;
    cout << "Welcome to web development in C++!" << endl;
    cout << "This server demonstrates:" << endl;
    cout << "- Socket programming with Berkeley sockets" << endl;
    cout << "- HTTP protocol implementation" << endl;
    cout << "- Multi-threading for concurrent connections" << endl;
    cout << "- File serving with MIME type detection" << endl;
    cout << "- Request parsing and response generation" << endl;
    cout << "- Error handling and resource management" << endl;
    cout << "- Human-like code with detailed comments!" << endl;
    cout << "========================================" << endl;
    
    // Default values
    int port = 8080;
    string document_root = "./www";
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--port" && i + 1 < argc) {
            port = atoi(argv[i + 1]);
            i++;
        } else if (string(argv[i]) == "--root" && i + 1 < argc) {
            document_root = argv[i + 1];
            i++;
        } else if (string(argv[i]) == "--help") {
            cout << "Usage: " << argv[0] << " [options]" << endl;
            cout << "Options:" << endl;
            cout << "  --port <number>    Set server port (default: 8080)" << endl;
            cout << "  --root <path>      Set document root (default: ./www)" << endl;
            cout << "  --help             Show this help message" << endl;
            cout << "\nExample:" << endl;
            cout << "  " << argv[0] << " --port 3000 --root /var/www" << endl;
            return 0;
        }
    }
    
    // Create document root directory
    struct stat st = {0};
    if (stat(document_root.c_str(), &st) == -1) {
        cout << "Creating document root directory: " << document_root << endl;
        if (mkdir(document_root.c_str(), 0755) == 0) {
            cout << "Directory created successfully!" << endl;
        } else {
            cout << "Error: Failed to create directory!" << endl;
            return 1;
        }
    }
    
    // Create default files
    createDefaultFiles(document_root);
    
    // Create and start web server
    WebServer server(port, document_root);
    
    cout << "\nStarting web server..." << endl;
    cout << "Press Ctrl+C to stop the server" << endl;
    
    if (!server.start()) {
        cout << "Failed to start web server!" << endl;
        return 1;
    }
    
    cout << "\nWeb server is running!" << endl;
    cout << "Access it at: http://localhost:" << port << endl;
    cout << "Press Ctrl+C to stop..." << endl;
    
    // Wait for user interrupt
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        
        // You could add server statistics display here
        static int counter = 0;
        if (++counter % 30 == 0) {  // Every 30 seconds
            server.getStatistics();
        }
    }
    
    return 0;
}
