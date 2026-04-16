# C++ Database Manager - Level 6

## Overview
A comprehensive file-based database system demonstrating advanced C++ programming, data persistence, and SQL-like operations.

## Features
- **Binary File Operations**: Efficient data serialization and storage
- **B-tree Indexing**: Fast record lookups and queries
- **SQL-like Operations**: Create, Read, Update, Delete (CRUD)
- **Transaction Management**: Atomic operations with rollback support
- **Data Serialization**: Manual binary format implementation
- **Query Processing**: Search and filtering capabilities
- **Statistics Tracking**: Database metrics and performance monitoring

## Learning Objectives
- File I/O operations with binary data
- B-tree indexing for fast lookups
- SQL-like query parsing and execution
- Data serialization and deserialization
- Transaction management and rollback
- Memory management and efficiency
- Human-like code with detailed explanations

## Prerequisites
- C++17 compatible compiler (g++, clang++, or MSVC)
- Basic understanding of database concepts
- Familiarity with file operations and binary data

## Compilation & Running

### Linux/macOS
```bash
# Compile
g++ -std=c++17 -o database_manager database_manager.cpp

# Run with default database
./database_manager

# Run with custom database file
./database_manager my_database.db
```

### Windows (with g++)
```bash
# Compile
g++ -std=c++17 -o database_manager.exe database_manager.cpp

# Run
database_manager.exe

# Run with custom database file
database_manager.exe my_database.db
```

### Windows (Visual Studio)
1. Open Visual Studio
2. Create new C++ project
3. Add database_manager.cpp to project
4. Configure project properties:
   - C++ Language Standard: ISO C++17
   - Additional Dependencies: None (pure C++)
5. Build and run

## Usage Examples

### Interactive Mode
```bash
# Start interactive mode
./database_manager

=== DATABASE MANAGER MENU ===
1. Create record
2. Read record
3. Update record
4. Delete record
5. Search records
6. List all records
7. Begin transaction
8. Commit transaction
9. Rollback transaction
10. Get statistics
11. Exit

Choice: 1
Enter record name: John Doe
Enter record data: Software Engineer
```

### Command Line Arguments
```bash
# Specify database file
./database_manager employees.db

# Default database file is "database.db"
./database_manager
```

## Database Operations

### Record Management
- **Create**: Add new records with unique IDs
- **Read**: Retrieve records by ID
- **Update**: Modify existing record data
- **Delete**: Remove records from database
- **Search**: Find records by name or data content

### Transaction Management
- **Begin Transaction**: Start atomic operation mode
- **Commit**: Save all changes to disk
- **Rollback**: Revert all uncommitted changes
- **Auto-backup**: Automatic backup for rollback operations

### Data Structure
```cpp
struct Record {
    int id;                    // Unique identifier
    string name;                // Record name
    string data;                // Record data
    time_t created_at;          // Creation timestamp
    time_t updated_at;          // Last update timestamp
};
```

## Code Structure
```cpp
class DatabaseManager {
private:
    string database_file;         // Database file path
    string index_file;           // Index file path
    shared_ptr<IndexNode> root;  // B-tree root
    map<int, Record> records;    // In-memory record cache
    int next_id;                 // Next available record ID
    bool transaction_active;       // Transaction state
    vector<Record> transaction_backup;  // Transaction backup
    
public:
    // Core operations
    void createRecord(const string& name, const string& data);
    Record* readRecord(int id);
    bool updateRecord(int id, const string& newData);
    bool deleteRecord(int id);
    
    // Search and query operations
    vector<Record> searchRecords(const string& searchTerm);
    void listRecords();
    
    // Transaction management
    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();
    
    // Utility operations
    void getStatistics();
    void loadDatabase();
    void saveDatabase();
};
```

## Key Concepts Demonstrated
1. **Binary File Operations**: Manual serialization and deserialization
2. **B-tree Indexing**: Fast lookup data structure
3. **Transaction Management**: Atomic operations with rollback
4. **Data Persistence**: Reliable file-based storage
5. **Memory Management**: Efficient caching and resource usage
6. **Error Handling**: Comprehensive error recovery
7. **Human-Like Code**: Detailed comments and user feedback

## File Format
```
Database File (.db):
+------------------+------------------+
| Header (8 bytes) |                  |
| - Record Count   | int (4 bytes)  |
| - Next ID        | int (4 bytes)  |
+------------------+------------------+
| Records (variable)|                  |
| - Record Length  | int (4 bytes)  |
| - Record Data    | (variable)      |
+------------------+------------------+

Index File (.idx):
+------------------+------------------+
| Index Header      |                  |
| - Root Pointer   | int (4 bytes)  |
| - Tree Depth     | int (4 bytes)  |
+------------------+------------------+
| Index Nodes       |                  |
| - Node Type      | char (1 byte)   |
| - Key Count      | int (4 bytes)   |
| - Keys           | int * count     |
| - Child Pointers | int * count     |
+------------------+------------------+
```

## Performance Considerations
- **Time Complexity**: O(log n) for indexed lookups
- **Space Complexity**: O(n) for storage
- **Indexing**: B-tree provides balanced performance
- **Caching**: In-memory cache for frequent access
- **Transactions**: Minimal overhead for atomic operations

## Error Handling
- **File Operations**: Comprehensive error checking
- **Memory Management**: RAII and smart pointers
- **Data Validation**: Input sanitization and verification
- **Transaction Safety**: Rollback on failure
- **User Feedback**: Clear error messages and guidance

## Troubleshooting

### Compilation Errors
- **"fstream was not declared"**: Add `#include <fstream>`
- **"memory was not declared"**: Add `#include <memory>`
- **"ctime was not declared"**: Add `#include <ctime>`
- **"memcpy was not declared"**: Add `#include <cstring>`

### Runtime Errors
- **File not found**: Program creates new database automatically
- **Permission denied**: Check file permissions
- **Disk full**: Monitor available disk space
- **Corrupted data**: Built-in validation and recovery

### Performance Issues
- **Slow lookups**: Check index file integrity
- **Large files**: Consider file splitting or compression
- **Memory usage**: Monitor with system tools

## Extensions and Enhancements
Try these challenges to improve the database:
1. **SQL Parser**: Implement full SQL language support
2. **Multiple Indexes**: Support for multiple field indexes
3. **Compression**: Add data compression for storage efficiency
4. **Encryption**: Implement data encryption for security
5. **Concurrent Access**: Multi-user support with locking
6. **Backup System**: Automated backup and recovery
7. **Query Optimization**: Query plan generation and optimization
8. **Data Types**: Support for various data types (int, float, date, etc.)
9. **GUI Interface**: Create graphical database management tool
10. **Network Protocol**: Add client-server database access

## Real-World Applications
- **Embedded Systems**: Lightweight database for IoT devices
- **Desktop Applications**: Local data storage for applications
- **Educational Tools**: Teaching database concepts
- **Data Analysis**: Simple data processing and analysis
- **Configuration Storage**: Application settings and preferences

## Next Steps
After mastering this database manager, try:
- Level 7: REST API Development (HTTP, JSON, web services)
- Level 8: Microservices Architecture (distributed systems)
- Level 9: Cloud Deployment (AWS, Azure, GCP)
- Level 10: Advanced Database Systems (PostgreSQL, MongoDB)

## About This Project
This database manager demonstrates advanced C++ concepts through practical database implementation. The code includes detailed explanations of binary operations, data structures, and transaction management, making it perfect for learning systems programming and data persistence.

Happy coding and happy data management!
