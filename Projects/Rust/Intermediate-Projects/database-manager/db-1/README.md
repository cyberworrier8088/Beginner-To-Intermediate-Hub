# Rust Database Manager - Level 6

## Overview
A comprehensive file-based database system demonstrating advanced Rust programming, data persistence, and SQL-like operations with memory safety guarantees.

## Features
- **Binary File Operations**: Efficient data serialization with serde
- **B-tree Indexing**: Fast record lookups and queries
- **SQL-like Operations**: Create, Read, Update, Delete (CRUD)
- **Transaction Management**: Atomic operations with rollback support
- **JSON Import/Export**: Data interchange and backup capabilities
- **Command Line Interface**: Both interactive and CLI modes
- **Memory Safety**: Rust's ownership system prevents data corruption
- **Error Handling**: Comprehensive Result types for robust operations

## Learning Objectives
- File I/O operations with binary data
- B-tree indexing for fast lookups
- SQL-like query parsing and execution
- Data serialization and deserialization with serde
- Transaction management and rollback
- Command line argument parsing with clap
- Human-like code with detailed explanations

## Prerequisites
- Rust 1.70+ (2021 edition)
- Cargo package manager
- Basic understanding of database concepts
- Familiarity with JSON and data serialization

## Installation & Setup

### Install Rust (if not already installed)
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source ~/.cargo/env
```

### Compilation & Running
```bash
# Navigate to project
cd Projects/Rust/Intermediate-Projects/database-manager/db-1/

# Run with Cargo (recommended)
cargo run

# Run with custom database file
cargo run -- --database my_database.json

# Or compile and run manually
cargo build --release
./target/release/database-manager
```

## Usage Examples

### Interactive Mode
```bash
# Start interactive mode
cargo run

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
10. Show statistics
11. Export to JSON
12. Import from JSON
13. Exit

Choice: 1
Enter record name: John Doe
Enter record data: Software Engineer
```

### Command Line Interface
```bash
# Create a new record
cargo run -- --database employees.json create --name "Alice Smith" --data "Data Scientist"

# Read a record
cargo run -- --database employees.json read --id 1

# Update a record
cargo run -- --database employees.json update --id 1 --data "Senior Data Scientist"

# Delete a record
cargo run -- --database employees.json delete --id 1

# Search records
cargo run -- --database employees.json search --term "engineer"

# List all records
cargo run -- --database employees.json list

# Show statistics
cargo run -- --database employees.json stats

# Export to JSON
cargo run -- --database employees.json export --file backup.json

# Import from JSON
cargo run -- --database employees.json import --file backup.json
```

## Code Structure
```rust
// Record structure with serde serialization
#[derive(Debug, Clone, Serialize, Deserialize)]
struct Record {
    id: u32,                              // Unique identifier
    name: String,                           // Record name
    data: String,                           // Record data
    created_at: DateTime<Utc>,               // Creation timestamp
    updated_at: DateTime<Utc>,               // Last update timestamp
}

// Database manager with comprehensive operations
struct DatabaseManager {
    database_file: String,
    index_file: String,
    records: HashMap<u32, Record>,
    next_id: u32,
    transaction_active: bool,
    transaction_backup: HashMap<u32, Record>,
}

impl DatabaseManager {
    // Core CRUD operations
    fn create_record(&mut self, name: String, data: String) -> io::Result<u32>;
    fn read_record(&self, id: u32) -> Option<&Record>;
    fn update_record(&mut self, id: u32, new_data: String) -> io::Result<bool>;
    fn delete_record(&mut self, id: u32) -> io::Result<bool>;
    
    // Search and query operations
    fn search_records(&self, search_term: &str) -> Vec<&Record>;
    fn list_records(&self);
    
    // Transaction management
    fn begin_transaction(&mut self) -> io::Result<()>;
    fn commit_transaction(&mut self) -> io::Result<()>;
    fn rollback_transaction(&mut self) -> io::Result<()>;
    
    // Import/Export operations
    fn export_to_json(&self, filename: &str) -> io::Result<()>;
    fn import_from_json(&mut self, filename: &str) -> io::Result<u32>;
    
    // Utility operations
    fn get_statistics(&self) -> io::Result<DatabaseStats>;
}
```

## Key Concepts Demonstrated
1. **File I/O Operations**: Binary data serialization and storage
2. **B-tree Indexing**: Fast lookup data structure implementation
3. **SQL-like Operations**: Complete CRUD functionality
4. **Transaction Management**: Atomic operations with rollback support
5. **Data Serialization**: Serde for JSON and binary formats
6. **Memory Safety**: Rust's ownership system prevents data corruption
7. **Error Handling**: Result types for robust error management
8. **Command Line Parsing**: Clap for professional CLI interface
9. **Human-Like Code**: Detailed comments and user feedback

## Data Structures
```rust
// Record structure with automatic serialization
#[derive(Debug, Clone, Serialize, Deserialize)]
struct Record {
    id: u32,                              // Unique identifier
    name: String,                           // Record name
    data: String,                           // Record data
    created_at: DateTime<Utc>,               // Creation timestamp
    updated_at: DateTime<Utc>,               // Last update timestamp
}

// Database statistics
#[derive(Debug, Clone, Serialize, Deserialize)]
struct DatabaseStats {
    total_records: u32,
    next_id: u32,
    file_size_bytes: u64,
    index_size_bytes: u64,
    last_backup: Option<DateTime<Utc>>,
}

// Query operations
#[derive(Debug, Clone)]
enum Query {
    Select { id: Option<u32>, name: Option<String> },
    Insert { name: String, data: String },
    Update { id: u32, data: String },
    Delete { id: u32 },
    CreateIndex { field: String },
    DropIndex { field: String },
}
```

## Performance Considerations
- **Time Complexity**: O(log n) for indexed lookups
- **Space Complexity**: O(n) for storage
- **Memory Usage**: Efficient HashMap caching
- **Serialization**: Zero-copy deserialization where possible
- **Indexing**: B-tree provides balanced performance
- **Transactions**: Minimal overhead for atomic operations

## Error Handling
- **File Operations**: Comprehensive Result types
- **Data Validation**: Input sanitization and verification
- **Transaction Safety**: Automatic rollback on failure
- **Memory Safety**: Compile-time guarantees with Rust
- **User Feedback**: Clear error messages and guidance

## File Formats
```json
// Database file format (JSON)
{
  "export_info": {
    "exported_at": "2024-01-15T10:30:00Z",
    "total_records": 100,
    "database_file": "database.json",
    "version": "1.0"
  },
  "records": [
    {
      "id": 1,
      "name": "John Doe",
      "data": "Software Engineer",
      "created_at": "2024-01-15T10:30:00Z",
      "updated_at": "2024-01-15T10:30:00Z"
    }
  ]
}

// Index file format (JSON)
{
  "record_count": 100,
  "next_id": 101,
  "created_at": "2024-01-15T10:30:00Z",
  "field_indexes": {
    "id": "btree",
    "name": "hash",
    "created_at": "btree",
    "updated_at": "btree"
  }
}
```

## Troubleshooting

### Compilation Errors
- **"serde not found"**: Add serde to Cargo.toml dependencies
- **"chrono not found"**: Add chrono to Cargo.toml dependencies
- **"clap not found"**: Add clap to Cargo.toml dependencies
- **"HashMap not found"**: Add `use std::collections::HashMap;`

### Runtime Errors
- **File not found**: Program creates new database automatically
- **Permission denied**: Check file permissions and access rights
- **Invalid JSON**: Built-in validation and error recovery
- **Corrupted data**: Automatic detection and recovery attempts

### Performance Issues
- **Slow lookups**: Check index file integrity
- **High memory usage**: Monitor with system tools
- **Large files**: Consider file splitting or compression

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
- **Caching Layer**: Fast data access for web applications
- **Mobile Apps**: Local database for mobile applications

## Next Steps
After mastering this database manager, try:
- Level 7: REST API Development (HTTP, JSON, web services)
- Level 8: Microservices Architecture (distributed systems)
- Level 9: Cloud Deployment (AWS, Azure, GCP)
- Level 10: Advanced Database Systems (PostgreSQL, MongoDB)

## About This Project
This database manager demonstrates advanced Rust concepts through practical database implementation. The code includes detailed explanations of file operations, data structures, and transaction management, making it perfect for learning systems programming and data persistence with memory safety guarantees.

Happy coding and happy data management!
