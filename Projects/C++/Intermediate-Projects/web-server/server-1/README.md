# C++ Web Server - Level 5

## Overview
A high-performance multi-threaded web server demonstrating advanced C++ networking, HTTP protocol implementation, and concurrent connection handling.

## Features
- **Multi-threaded Architecture**: Handle multiple clients concurrently
- **HTTP Protocol**: Full HTTP/1.1 protocol implementation
- **File Serving**: Static file serving with MIME type detection
- **POST Support**: Handle form data and requests
- **Error Handling**: Comprehensive error responses and logging
- **Security Features**: Directory traversal prevention
- **Performance**: Connection pooling and efficient resource management

## Learning Objectives
- Socket programming with Berkeley sockets
- HTTP protocol implementation and parsing
- Multi-threading with std::thread
- File I/O operations and MIME type detection
- Request parsing and response generation
- Error handling and resource management
- Security best practices for web servers

## Prerequisites
- C++17 compatible compiler
- POSIX-compatible system (Linux/macOS) or Windows with WinSock2
- Basic understanding of HTTP protocol
- Familiarity with threading concepts

## Compilation & Running

### Linux/macOS
```bash
# Compile
g++ -std=c++17 -pthread -o web_server web_server.cpp

# Run
./web_server

# With custom port and document root
./web_server --port 3000 --root /var/www
```

### Windows (with MinGW-w64)
```bash
# Compile
g++ -std=c++17 -o web_server.exe web_server.cpp -lws2_32

# Run
web_server.exe

# With custom port and document root
web_server.exe --port 3000 --root C:\inetpub\wwwroot
```

### Windows (Visual Studio)
1. Create new C++ project
2. Add web_server.cpp to project
3. Configure project properties:
   - C++ Language Standard: ISO C++17
   - Additional Dependencies: ws2_32.lib
4. Build and run

## Command Line Options
- `--port <number>`: Set server port (default: 8080)
- `--root <path>`: Set document root directory (default: ./www)
- `--help`: Show help message

## Usage Examples

### Basic Usage
```bash
# Start server on default port 8080
./web_server

# Access in browser: http://localhost:8080
```

### Custom Configuration
```bash
# Start server on port 3000 with custom document root
./web_server --port 3000 --root /var/www/html

# Access in browser: http://localhost:3000
```

### Testing Endpoints
```bash
# Test GET request
curl http://localhost:8080/

# Test GET request for specific file
curl http://localhost:8080/test.txt

# Test POST request
curl -X POST -d "Hello Server" http://localhost:8080/test

# Test error handling
curl http://localhost:8080/nonexistent.html
```

## Code Structure
```cpp
class WebServer {
private:
    int server_socket;
    int port;
    string document_root;
    atomic<bool> running;
    atomic<int> connection_count;
    mutex cout_mutex;
    
public:
    // Core server methods
    bool start();
    void stop();
    void acceptConnections();
    void handleClient(int client_socket, const string& client_ip);
    
    // HTTP handling methods
    void handleGetRequest(int client_socket, const HttpRequest& request);
    void handlePostRequest(int client_socket, const HttpRequest& request);
    void sendErrorResponse(int client_socket, int status_code, const string& message);
    
    // Utility methods
    string readFile(const string& filename);
    string getMimeType(const string& filename);
    string getCurrentTimestamp();
    string generateErrorPage(int status_code, const string& message);
};

struct HttpRequest {
    string method;
    string path;
    string version;
    map<string, string> headers;
    string body;
    
    bool parse(const string& request);
};
```

## Key Concepts Demonstrated
1. **Socket Programming**: Berkeley sockets for network communication
2. **HTTP Protocol**: Complete HTTP/1.1 implementation
3. **Multi-threading**: Concurrent client handling with std::thread
4. **Request Parsing**: HTTP request line and header parsing
5. **Response Generation**: Dynamic HTTP response creation
6. **File Serving**: Static file serving with MIME type detection
7. **Error Handling**: Comprehensive error management
8. **Security**: Directory traversal prevention
9. **Performance**: Atomic operations and efficient resource management

## HTTP Features Implemented
- **GET Requests**: Static file serving
- **POST Requests**: Form data handling
- **MIME Types**: Automatic content-type detection
- **Error Responses**: Standard HTTP error pages
- **Headers**: Proper HTTP header handling
- **Connection Management**: Persistent connection support
- **Security**: Basic security measures

## Supported File Types
- HTML: `text/html`
- CSS: `text/css`
- JavaScript: `application/javascript`
- JSON: `application/json`
- Images: PNG, JPEG, GIF, ICO
- Text: `text/plain`
- PDF: `application/pdf`
- XML: `application/xml`

## Error Handling
- **400 Bad Request**: Malformed HTTP requests
- **403 Forbidden**: Directory traversal attempts
- **404 Not Found**: Missing files
- **405 Method Not Allowed**: Unsupported HTTP methods
- **500 Internal Server Error**: Server-side errors

## Security Features
- **Directory Traversal Prevention**: Blocks `../` attempts
- **Input Validation**: Request parsing validation
- **Resource Limits**: File size and path length limits
- **Connection Limits**: Maximum concurrent connections
- **Safe File Access**: Restricted to document root

## Performance Considerations
- **Thread Pooling**: Efficient thread management
- **Memory Management**: RAII and smart pointers
- **Atomic Operations**: Thread-safe counters
- **File Caching**: In-memory file serving
- **Connection Reuse**: Persistent HTTP connections
- **Resource Cleanup**: Proper socket and memory cleanup

## Troubleshooting

### Compilation Errors
- **"socket was not declared"**: Add `#include <sys/socket.h>`
- **"thread not found"**: Add `#include <thread>` and link with `-pthread`
- **"inet_ntop not found"**: Add `#include <arpa/inet.h>`
- **Linking errors**: Check library dependencies (pthread, ws2_32)

### Runtime Errors
- **"Address already in use"**: Port is in use, try different port
- **"Permission denied"**: Use port > 1024 or run as administrator
- **"Connection refused"**: Server not running or firewall blocking

### Platform-Specific Issues
- **Windows**: Use WinSock2 headers and link with ws2_32.lib
- **Linux**: Link with -pthread, use proper socket headers
- **macOS**: Use BSD socket headers, may need -lsocket

## Testing the Server
```bash
# Test basic functionality
curl -I http://localhost:8080/

# Test file serving
curl http://localhost:8080/test.txt

# Test POST requests
curl -X POST -H "Content-Type: text/plain" -d "Test data" http://localhost:8080/test

# Test error handling
curl http://localhost:8080/../../../etc/passwd

# Load testing
ab -n 1000 -c 10 http://localhost:8080/
```

## Extensions and Enhancements
Try these challenges to improve the server:
1. **HTTPS Support**: Add SSL/TLS encryption
2. **WebSocket Support**: Real-time bidirectional communication
3. **CGI Support**: Dynamic content generation
4. **Virtual Hosts**: Multiple domain hosting
5. **Load Balancing**: Multiple server instances
6. **Caching Layer**: HTTP response caching
7. **Authentication**: Basic or digest authentication
8. **Logging**: Comprehensive request/response logging
9. **Configuration Files**: JSON or INI file support
10. **Performance Monitoring**: Real-time statistics dashboard

## Next Steps
After mastering this web server, try:
- Level 6: Database Integration (SQLite, PostgreSQL)
- Level 7: REST API Development (JSON, RESTful design)
- Level 8: Microservices Architecture (Docker, Kubernetes)
- Level 9: Cloud Deployment (AWS, Azure, GCP)
- Level 10: Advanced Security (OAuth, JWT, HTTPS)

## About This Project
This web server demonstrates advanced C++ networking concepts while maintaining clean, readable code. The implementation focuses on teaching HTTP protocol, socket programming, and concurrent programming through practical application.

Happy coding and happy serving!
