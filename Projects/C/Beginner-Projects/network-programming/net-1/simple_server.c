/*
 * Simple Network Server - Level 6: Socket Programming
 * 
 * Welcome to network programming in C! This is where systems programming meets networking.
 * Learn the fundamentals of client-server architecture and socket programming.
 * 
 * Key concepts you'll learn:
 * - Socket creation and binding
 * - TCP/IP networking basics
 * - Client-server architecture
 * - Network byte order
 * - Error handling in network code
 * - Multi-client handling with select()
 * 
 * WARNING: This is advanced C programming!
 * Network code is complex and requires careful error handling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>
#include <signal.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define BACKLOG 5

// Client structure to track connected clients
typedef struct {
    int socket_fd;
    struct sockaddr_in address;
    char ip_address[INET_ADDRSTRLEN];
    time_t connect_time;
    int message_count;
} Client;

// Server structure to manage server state
typedef struct {
    int server_socket;
    Client clients[MAX_CLIENTS];
    int client_count;
    int running;
    time_t start_time;
    unsigned long total_messages;
} Server;

// Initialize server
void init_server(Server* server) {
    server->server_socket = -1;
    server->client_count = 0;
    server->running = 0;
    server->total_messages = 0;
    server->start_time = time(NULL);
    
    // Initialize all client sockets to -1 (unused)
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].socket_fd = -1;
    }
    
    printf("Server structure initialized\n");
}

// Create and bind server socket
int create_server_socket(Server* server) {
    // Create socket
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_socket == -1) {
        perror("Socket creation failed");
        return -1;
    }
    
    printf("Server socket created: fd=%d\n", server->server_socket);
    
    // Set socket options to reuse address
    int opt = 1;
    if (setsockopt(server->server_socket, SOL_SOCKET, SO_REUSEADDR, 
                   &opt, sizeof(opt)) == -1) {
        perror("Setsockopt failed");
        close(server->server_socket);
        return -1;
    }
    
    // Configure server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);  // Convert to network byte order
    
    // Bind socket to address
    if (bind(server->server_socket, (struct sockaddr*)&server_addr, 
             sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server->server_socket);
        return -1;
    }
    
    printf("Server bound to port %d\n", PORT);
    
    // Start listening for connections
    if (listen(server->server_socket, BACKLOG) == -1) {
        perror("Listen failed");
        close(server->server_socket);
        return -1;
    }
    
    printf("Server listening for connections (backlog=%d)\n", BACKLOG);
    return 0;
}

// Add new client to server
int add_client(Server* server, int client_socket, struct sockaddr_in* client_addr) {
    if (server->client_count >= MAX_CLIENTS) {
        printf("Maximum clients reached (%d)\n", MAX_CLIENTS);
        return -1;
    }
    
    // Find empty slot
    int slot = -1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd == -1) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        printf("No available client slots\n");
        return -1;
    }
    
    // Initialize client
    server->clients[slot].socket_fd = client_socket;
    server->clients[slot].address = *client_addr;
    server->clients[slot].connect_time = time(NULL);
    server->clients[slot].message_count = 0;
    
    // Convert IP address to string
    inet_ntop(AF_INET, &client_addr->sin_addr, 
              server->clients[slot].ip_address, INET_ADDRSTRLEN);
    
    server->client_count++;
    
    printf("Client connected: fd=%d, IP=%s, slot=%d\n", 
           client_socket, server->clients[slot].ip_address, slot);
    
    // Send welcome message
    char welcome_msg[BUFFER_SIZE];
    snprintf(welcome_msg, BUFFER_SIZE, 
             "Welcome to the C Server!\n"
             "You are client #%d connected.\n"
             "Type 'help' for commands.\n"
             "Type 'quit' to disconnect.\n", 
             server->client_count);
    
    send(client_socket, welcome_msg, strlen(welcome_msg), 0);
    
    return slot;
}

// Remove client from server
void remove_client(Server* server, int slot) {
    if (slot < 0 || slot >= MAX_CLIENTS) {
        return;
    }
    
    if (server->clients[slot].socket_fd != -1) {
        printf("Client disconnected: fd=%d, IP=%s, slot=%d, messages=%d\n",
               server->clients[slot].socket_fd,
               server->clients[slot].ip_address,
               slot,
               server->clients[slot].message_count);
        
        close(server->clients[slot].socket_fd);
        server->clients[slot].socket_fd = -1;
        server->client_count--;
    }
}

// Handle client message
void handle_client_message(Server* server, int slot, char* message) {
    if (slot < 0 || slot >= MAX_CLIENTS) {
        return;
    }
    
    Client* client = &server->clients[slot];
    client->message_count++;
    server->total_messages++;
    
    // Remove newline from message
    message[strcspn(message, "\n")] = 0;
    
    printf("Client %d (%s): %s\n", slot, client->ip_address, message);
    
    char response[BUFFER_SIZE];
    
    // Handle different commands
    if (strcmp(message, "help") == 0) {
        snprintf(response, BUFFER_SIZE,
                 "Available commands:\n"
                 "  time    - Show server time\n"
                 "  stats   - Show server statistics\n"
                 "  clients - Show connected clients\n"
                 "  echo <msg> - Echo message back\n"
                 "  quit    - Disconnect from server\n");
        
    } else if (strcmp(message, "time") == 0) {
        time_t now = time(NULL);
        snprintf(response, BUFFER_SIZE, "Server time: %s", ctime(&now));
        
    } else if (strcmp(message, "stats") == 0) {
        time_t uptime = time(NULL) - server->start_time;
        snprintf(response, BUFFER_SIZE,
                 "Server Statistics:\n"
                 "  Uptime: %ld seconds\n"
                 "  Connected clients: %d/%d\n"
                 "  Total messages: %lu\n"
                 "  Server socket: %d\n",
                 uptime, server->client_count, MAX_CLIENTS, 
                 server->total_messages, server->server_socket);
        
    } else if (strcmp(message, "clients") == 0) {
        snprintf(response, BUFFER_SIZE, "Connected clients (%d/%d):\n", 
                 server->client_count, MAX_CLIENTS);
        
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->clients[i].socket_fd != -1) {
                time_t connected = time(NULL) - server->clients[i].connect_time;
                char client_info[200];
                snprintf(client_info, 200, 
                         "  Client %d: fd=%d, IP=%s, connected=%lds, messages=%d\n",
                         i, server->clients[i].socket_fd, 
                         server->clients[i].ip_address, connected,
                         server->clients[i].message_count);
                strncat(response, client_info, BUFFER_SIZE - strlen(response) - 1);
            }
        }
        
    } else if (strncmp(message, "echo ", 5) == 0) {
        snprintf(response, BUFFER_SIZE, "Echo: %s", message + 5);
        
    } else if (strcmp(message, "quit") == 0) {
        snprintf(response, BUFFER_SIZE, "Goodbye! Thanks for visiting.\n");
        send(client->socket_fd, response, strlen(response), 0);
        remove_client(server, slot);
        return;
        
    } else {
        snprintf(response, BUFFER_SIZE, 
                 "Unknown command: '%s'. Type 'help' for commands.\n", message);
    }
    
    send(client->socket_fd, response, strlen(response), 0);
}

// Broadcast message to all clients
void broadcast_message(Server* server, const char* message) {
    printf("Broadcasting to %d clients: %s", server->client_count, message);
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd != -1) {
            if (send(server->clients[i].socket_fd, message, strlen(message), 0) == -1) {
                printf("Failed to send to client %d\n", i);
                remove_client(server, i);
            }
        }
    }
}

// Main server loop using select() for multiplexing
void run_server(Server* server) {
    fd_set read_fds;
    int max_fd;
    struct timeval timeout;
    
    printf("Server running on port %d\n", PORT);
    printf("Connect with: telnet localhost %d\n", PORT);
    printf("Type 'Ctrl+C' to stop server\n\n");
    
    server->running = 1;
    
    while (server->running) {
        // Clear file descriptor set
        FD_ZERO(&read_fds);
        
        // Add server socket to set
        FD_SET(server->server_socket, &read_fds);
        max_fd = server->server_socket;
        
        // Add client sockets to set
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->clients[i].socket_fd > max_fd) {
                max_fd = server->clients[i].socket_fd;
            }
            if (server->clients[i].socket_fd != -1) {
                FD_SET(server->clients[i].socket_fd, &read_fds);
            }
        }
        
        // Set timeout for select()
        timeout.tv_sec = 1;  // 1 second timeout
        timeout.tv_usec = 0;
        
        // Wait for activity
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);
        
        if (activity < 0) {
            perror("Select error");
            break;
        }
        
        if (activity == 0) {
            // Timeout - continue loop
            continue;
        }
        
        // Check for new connections
        if (FD_ISSET(server->server_socket, &read_fds)) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            
            int client_socket = accept(server->server_socket, 
                                      (struct sockaddr*)&client_addr, 
                                      &client_len);
            
            if (client_socket == -1) {
                perror("Accept failed");
            } else {
                add_client(server, client_socket, &client_addr);
                
                // Broadcast new client notification
                char notification[BUFFER_SIZE];
                snprintf(notification, BUFFER_SIZE, 
                         "New client connected! Total: %d\n", server->client_count);
                broadcast_message(server, notification);
            }
        }
        
        // Check for client activity
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->clients[i].socket_fd != -1 && 
                FD_ISSET(server->clients[i].socket_fd, &read_fds)) {
                
                char buffer[BUFFER_SIZE];
                int bytes_received = recv(server->clients[i].socket_fd, 
                                        buffer, BUFFER_SIZE - 1, 0);
                
                if (bytes_received <= 0) {
                    // Client disconnected
                    if (bytes_received == 0) {
                        printf("Client %d disconnected\n", i);
                    } else {
                        perror("Recv failed");
                    }
                    remove_client(server, i);
                } else {
                    // Handle client message
                    buffer[bytes_received] = '\0';
                    handle_client_message(server, i, buffer);
                }
            }
        }
    }
}

// Signal handler for graceful shutdown
void signal_handler(int sig) {
    printf("\nReceived signal %d. Shutting down server...\n", sig);
    // Server will check running flag and exit gracefully
}

// Print server information
void print_server_info() {
    printf("=== C NETWORK SERVER ===\n");
    printf("A simple TCP server demonstrating socket programming\n");
    printf("Features:\n");
    printf("- Multi-client support with select()\n");
    printf("- Command processing (help, time, stats, clients, echo)\n");
    printf("- Client tracking and statistics\n");
    printf("- Graceful shutdown handling\n");
    printf("- Network byte order handling\n");
    printf("- Error handling and recovery\n");
    printf("\nUsage:\n");
    printf("1. Run this server: ./simple_server\n");
    printf("2. Connect with clients: telnet localhost %d\n", PORT);
    printf("3. Try commands: help, time, stats, clients, echo hello\n");
    printf("4. Disconnect: quit\n");
    printf("========================\n");
}

int main() {
    print_server_info();
    
    Server server;
    init_server(&server);
    
    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    // Create and configure server socket
    if (create_server_socket(&server) == -1) {
        fprintf(stderr, "Failed to create server socket\n");
        return 1;
    }
    
    // Run the server
    run_server(&server);
    
    // Cleanup
    printf("\nShutting down server...\n");
    
    // Close all client connections
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server.clients[i].socket_fd != -1) {
            close(server.clients[i].socket_fd);
        }
    }
    
    // Close server socket
    if (server.server_socket != -1) {
        close(server.server_socket);
    }
    
    // Print final statistics
    time_t total_runtime = time(NULL) - server.start_time;
    printf("\n=== FINAL STATISTICS ===\n");
    printf("Server runtime: %ld seconds\n", total_runtime);
    printf("Total clients served: %d\n", server.client_count);
    printf("Total messages processed: %lu\n", server.total_messages);
    printf("Average messages per second: %.2f\n", 
           total_runtime > 0 ? (double)server.total_messages / total_runtime : 0.0);
    printf("========================\n");
    
    printf("Server shutdown complete!\n");
    printf("You've learned:\n");
    printf("- Socket programming fundamentals\n");
    printf("- TCP/IP networking basics\n");
    printf("- Client-server architecture\n");
    printf("- Multi-client handling with select()\n");
    printf("- Network byte order conversion\n");
    printf("- Error handling in network code\n");
    printf("- Signal handling for graceful shutdown\n");
    
    return 0;
}
