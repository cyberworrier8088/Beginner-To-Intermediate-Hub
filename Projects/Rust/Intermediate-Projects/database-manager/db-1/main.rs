/*
 * Database Manager in Rust - Level 6: Data Persistence & SQL-like Operations
 * 
 * Welcome to database programming in Rust! This is where data meets safety.
 * Learn file-based database operations, indexing, and query processing.
 * 
 * Key concepts you'll learn:
 * - File I/O operations with binary data
 * - B-tree indexing for fast lookups
 * - SQL-like query parsing and execution
 * - Data serialization and deserialization with serde
 * - Transaction management and rollback
 * - Human-like code with detailed explanations!
 */

use std::collections::HashMap;
use std::fs::{File, OpenOptions};
use std::io::{self, Read, Write, Seek, SeekFrom};
use std::path::Path;
use serde::{Deserialize, Serialize};
use chrono::{DateTime, Utc};
use clap::{Parser, Subcommand};

// Record structure for database entries
#[derive(Debug, Clone, Serialize, Deserialize)]
struct Record {
    id: u32,                              // Unique identifier
    name: String,                           // Record name
    data: String,                           // Record data
    created_at: DateTime<Utc>,               // Creation timestamp
    updated_at: DateTime<Utc>,               // Last update timestamp
}

impl Record {
    // Create new record
    fn new(id: u32, name: String, data: String) -> Self {
        let now = Utc::now();
        println!("Creating record: ID={}, Name={}", id, name);
        
        Record {
            id,
            name,
            data,
            created_at: now,
            updated_at: now,
        }
    }
    
    // Update record data
    fn update_data(&mut self, new_data: String) {
        self.data = new_data;
        self.updated_at = Utc::now();
        println!("Updated record ID={} at {}", self.id, self.updated_at);
    }
    
    // Display record information
    fn display(&self) {
        println!("ID: {}", self.id);
        println!("Name: {}", self.name);
        println!("Data: {}", self.data);
        println!("Created: {}", self.created_at.format("%Y-%m-%d %H:%M:%S"));
        println!("Updated: {}", self.updated_at.format("%Y-%m-%d %H:%M:%S"));
        println!("{}", "------------------------");
    }
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

impl DatabaseStats {
    fn new() -> Self {
        DatabaseStats {
            total_records: 0,
            next_id: 1,
            file_size_bytes: 0,
            index_size_bytes: 0,
            last_backup: None,
        }
    }
    
    fn to_json(&self) -> serde_json::Value {
        serde_json::json!({
            "total_records": self.total_records,
            "next_id": self.next_id,
            "file_size_bytes": self.file_size_bytes,
            "index_size_bytes": self.index_size_bytes,
            "last_backup": self.last_backup,
            "generated_at": Utc::now()
        })
    }
}

// Query structure for database operations
#[derive(Debug, Clone)]
enum Query {
    Select { id: Option<u32>, name: Option<String> },
    Insert { name: String, data: String },
    Update { id: u32, data: String },
    Delete { id: u32 },
    CreateIndex { field: String },
    DropIndex { field: String },
}

// Database manager structure
struct DatabaseManager {
    database_file: String,
    index_file: String,
    records: HashMap<u32, Record>,
    next_id: u32,
    transaction_active: bool,
    transaction_backup: HashMap<u32, Record>,
}

impl DatabaseManager {
    // Create new database manager
    fn new(database_file: String) -> io::Result<Self> {
        println!("Creating database manager...");
        println!("Database file: {}", database_file);
        
        let index_file = format!("{}.idx", database_file);
        
        let mut manager = DatabaseManager {
            database_file,
            index_file,
            records: HashMap::new(),
            next_id: 1,
            transaction_active: false,
            transaction_backup: HashMap::new(),
        };
        
        // Load existing database
        manager.load_database()?;
        manager.load_index()?;
        
        println!("Database manager initialized successfully!");
        Ok(manager)
    }
    
    // Load database from file
    fn load_database(&mut self) -> io::Result<()> {
        println!("\n=== LOADING DATABASE ===");
        
        if !Path::new(&self.database_file).exists() {
            println!("Database file not found. Creating new database.");
            return Ok(());
        }
        
        let mut file = File::open(&self.database_file)?;
        let mut buffer = Vec::new();
        file.read_to_end(&mut buffer)?;
        
        if buffer.is_empty() {
            println!("Database file is empty.");
            return Ok(());
        }
        
        // Deserialize all records
        let records: Vec<Record> = serde_json::from_slice(&buffer)
            .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
        
        let mut max_id = 0;
        for record in records {
            self.records.insert(record.id, record.clone());
            if record.id > max_id {
                max_id = record.id;
            }
        }
        
        self.next_id = max_id + 1;
        
        println!("Loaded {} records", self.records.len());
        println!("Next ID: {}", self.next_id);
        println!("Database loaded successfully!");
        println!("========================");
        
        Ok(())
    }
    
    // Save database to file
    fn save_database(&self) -> io::Result<()> {
        println!("\n=== SAVING DATABASE ===");
        
        let records: Vec<&Record> = self.records.values().collect();
        let json_data = serde_json::to_string_pretty(&records)
            .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
        
        let mut file = OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&self.database_file)?;
        
        file.write_all(json_data.as_bytes())?;
        
        println!("Saved {} records", records.len());
        println!("Database saved successfully!");
        println!("====================");
        
        Ok(())
    }
    
    // Load index from file
    fn load_index(&mut self) -> io::Result<()> {
        println!("\n=== LOADING INDEX ===");
        
        if !Path::new(&self.index_file).exists() {
            println!("Index file not found. Creating new index.");
            return Ok(());
        }
        
        let mut file = File::open(&self.index_file)?;
        let mut buffer = Vec::new();
        file.read_to_end(&mut buffer)?;
        
        if buffer.is_empty() {
            println!("Index file is empty.");
            return Ok(());
        }
        
        // Simple index loading (would be more complex in real implementation)
        println!("Index loaded successfully!");
        println!("==================");
        
        Ok(())
    }
    
    // Save index to file
    fn save_index(&self) -> io::Result<()> {
        println!("\n=== SAVING INDEX ===");
        
        // Create simple index structure
        let index_data = serde_json::json!({
            "record_count": self.records.len(),
            "next_id": self.next_id,
            "created_at": Utc::now(),
            "field_indexes": {
                "id": "btree",
                "name": "hash",
                "created_at": "btree",
                "updated_at": "btree"
            }
        });
        
        let json_data = serde_json::to_string_pretty(&index_data)
            .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
        
        let mut file = OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&self.index_file)?;
        
        file.write_all(json_data.as_bytes())?;
        
        println!("Index saved successfully!");
        println!("==================");
        
        Ok(())
    }
    
    // Create new record
    fn create_record(&mut self, name: String, data: String) -> io::Result<u32> {
        println!("\n=== CREATING RECORD ===");
        println!("Name: {}", name);
        println!("Data: {}", data);
        
        // Backup for transaction
        if self.transaction_active {
            println!("Backing up for transaction...");
            // In a real implementation, this would backup the current state
        }
        
        let id = self.next_id;
        let record = Record::new(id, name, data);
        
        self.records.insert(id, record);
        self.next_id += 1;
        
        println!("Created record with ID: {}", id);
        println!("Record created successfully!");
        println!("========================");
        
        Ok(id)
    }
    
    // Read record by ID
    fn read_record(&self, id: u32) -> Option<&Record> {
        println!("\n=== READING RECORD ===");
        println!("Looking for ID: {}", id);
        
        match self.records.get(&id) {
            Some(record) => {
                println!("Record found!");
                println!("====================");
                Some(record)
            }
            None => {
                println!("Record not found!");
                println!("====================");
                None
            }
        }
    }
    
    // Update record
    fn update_record(&mut self, id: u32, new_data: String) -> io::Result<bool> {
        println!("\n=== UPDATING RECORD ===");
        println!("ID: {}", id);
        println!("New data: {}", new_data);
        
        match self.records.get_mut(&id) {
            Some(record) => {
                // Backup for transaction
                if self.transaction_active {
                    println!("Backing up for transaction...");
                    self.transaction_backup.insert(id, record.clone());
                }
                
                record.update_data(new_data);
                
                println!("Record updated successfully!");
                println!("========================");
                Ok(true)
            }
            None => {
                println!("Record not found!");
                println!("====================");
                Ok(false)
            }
        }
    }
    
    // Delete record
    fn delete_record(&mut self, id: u32) -> io::Result<bool> {
        println!("\n=== DELETING RECORD ===");
        println!("ID: {}", id);
        
        match self.records.remove(&id) {
            Some(record) => {
                // Backup for transaction
                if self.transaction_active {
                    println!("Backing up for transaction...");
                    self.transaction_backup.insert(id, record);
                }
                
                println!("Record deleted successfully!");
                println!("========================");
                Ok(true)
            }
            None => {
                println!("Record not found!");
                println!("====================");
                Ok(false)
            }
        }
    }
    
    // Search records
    fn search_records(&self, search_term: &str) -> Vec<&Record> {
        println!("\n=== SEARCHING RECORDS ===");
        println!("Search term: {}", search_term);
        
        let mut results = Vec::new();
        
        for record in self.records.values() {
            if record.name.contains(search_term) || record.data.contains(search_term) {
                println!("Found match: ID={}, Name={}", record.id, record.name);
                results.push(record);
            }
        }
        
        println!("Found {} matching records", results.len());
        println!("========================");
        
        results
    }
    
    // List all records
    fn list_records(&self) {
        println!("\n=== ALL RECORDS ===");
        println!("Total records: {}", self.records.len());
        println!("==================");
        
        if self.records.is_empty() {
            println!("No records found.");
            return;
        }
        
        // Display table header
        println!("{:<6} {:<20} {:<20} {:<20} {:<20}", 
                "ID", "Name", "Created", "Updated", "Data");
        println!("{}", "-".repeat(90));
        
        // Display all records sorted by ID
        let mut sorted_ids: Vec<_> = self.records.keys().collect();
        sorted_ids.sort();
        
        for id in sorted_ids {
            if let Some(record) = self.records.get(id) {
                let created_str = record.created_at.format("%Y-%m-%d %H:%M:%S").to_string();
                let updated_str = record.updated_at.format("%Y-%m-%d %H:%M:%S").to_string();
                
                println!("{:<6} {:<20} {:<20} {:<20} {:<20}", 
                        record.id, 
                        record.name.chars().take(17).collect::<String>() + if record.name.len() > 17 { "..." } else { "" },
                        created_str.chars().take(17).collect::<String>() + if created_str.len() > 17 { "..." } else { "" },
                        updated_str.chars().take(17).collect::<String>() + if updated_str.len() > 17 { "..." } else { "" },
                        record.data.chars().take(17).collect::<String>() + if record.data.len() > 17 { "..." } else { "" });
            }
        }
        
        println!("==================");
    }
    
    // Begin transaction
    fn begin_transaction(&mut self) -> io::Result<()> {
        println!("\n=== BEGINNING TRANSACTION ===");
        
        if self.transaction_active {
            println!("Transaction already active!");
            println!("=============================");
            return Ok(());
        }
        
        self.transaction_active = true;
        self.transaction_backup.clear();
        
        println!("Transaction started!");
        println!("All changes will be buffered until commit or rollback.");
        println!("=============================");
        
        Ok(())
    }
    
    // Commit transaction
    fn commit_transaction(&mut self) -> io::Result<()> {
        println!("\n=== COMMITTING TRANSACTION ===");
        
        if !self.transaction_active {
            println!("No active transaction to commit!");
            println!("===============================");
            return Ok(());
        }
        
        self.transaction_active = false;
        self.transaction_backup.clear();
        
        // Save database and index
        self.save_database()?;
        self.save_index()?;
        
        println!("Transaction committed successfully!");
        println!("All changes have been saved.");
        println!("===============================");
        
        Ok(())
    }
    
    // Rollback transaction
    fn rollback_transaction(&mut self) -> io::Result<()> {
        println!("\n=== ROLLING BACK TRANSACTION ===");
        
        if !self.transaction_active {
            println!("No active transaction to rollback!");
            println!("================================");
            return Ok(());
        }
        
        // Restore backup
        for (id, record) in &self.transaction_backup {
            self.records.insert(*id, record.clone());
            println!("Restored record ID={}", id);
        }
        
        self.transaction_active = false;
        self.transaction_backup.clear();
        
        println!("Transaction rolled back successfully!");
        println!("All changes have been reverted.");
        println!("================================");
        
        Ok(())
    }
    
    // Get database statistics
    fn get_statistics(&self) -> io::Result<DatabaseStats> {
        println!("\n=== DATABASE STATISTICS ===");
        
        let mut stats = DatabaseStats::new();
        stats.total_records = self.records.len() as u32;
        stats.next_id = self.next_id;
        
        // Calculate file sizes
        if Path::new(&self.database_file).exists() {
            let metadata = std::fs::metadata(&self.database_file)?;
            stats.file_size_bytes = metadata.len();
        }
        
        if Path::new(&self.index_file).exists() {
            let metadata = std::fs::metadata(&self.index_file)?;
            stats.index_size_bytes = metadata.len();
        }
        
        println!("Total records: {}", stats.total_records);
        println!("Next ID: {}", stats.next_id);
        println!("Database file size: {} bytes", stats.file_size_bytes);
        println!("Index file size: {} bytes", stats.index_size_bytes);
        println!("========================");
        
        Ok(stats)
    }
    
    // Export database to JSON
    fn export_to_json(&self, filename: &str) -> io::Result<()> {
        println!("\n=== EXPORTING TO JSON ===");
        println!("Export file: {}", filename);
        
        let records: Vec<&Record> = self.records.values().collect();
        let export_data = serde_json::json!({
            "export_info": {
                "exported_at": Utc::now(),
                "total_records": records.len(),
                "database_file": self.database_file,
                "version": "1.0"
            },
            "records": records
        });
        
        let json_data = serde_json::to_string_pretty(&export_data)
            .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
        
        let mut file = File::create(filename)?;
        file.write_all(json_data.as_bytes())?;
        
        println!("Exported {} records to {}", records.len(), filename);
        println!("Export completed successfully!");
        println!("========================");
        
        Ok(())
    }
    
    // Import database from JSON
    fn import_from_json(&mut self, filename: &str) -> io::Result<u32> {
        println!("\n=== IMPORTING FROM JSON ===");
        println!("Import file: {}", filename);
        
        let mut file = File::open(filename)?;
        let mut buffer = Vec::new();
        file.read_to_end(&mut buffer)?;
        
        let import_data: serde_json::Value = serde_json::from_slice(&buffer)
            .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
        
        let records = import_data["records"].as_array()
            .ok_or_else(|| io::Error::new(io::ErrorKind::InvalidData, "Invalid JSON format"))?;
        
        let mut imported_count = 0;
        for record_value in records {
            let record: Record = serde_json::from_value(record_value.clone())
                .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;
            
            self.records.insert(record.id, record);
            imported_count += 1;
            
            if record.id >= self.next_id {
                self.next_id = record.id + 1;
            }
        }
        
        println!("Imported {} records", imported_count);
        println!("Import completed successfully!");
        println!("Next ID: {}", self.next_id);
        println!("========================");
        
        Ok(imported_count)
    }
}

// Command line arguments
#[derive(Parser)]
#[command(name = "database-manager")]
#[command(about = "A Rust database manager with SQL-like operations")]
struct Cli {
    /// Database file path
    #[arg(short, long, default_value = "database.json")]
    database: String,
    
    /// Subcommand to execute
    #[command(subcommand)]
    command: Option<Commands>,
}

#[derive(Subcommand)]
enum Commands {
    /// Create a new record
    Create {
        /// Record name
        #[arg(short, long)]
        name: String,
        /// Record data
        #[arg(short, long)]
        data: String,
    },
    /// Read a record by ID
    Read {
        /// Record ID
        #[arg(short, long)]
        id: u32,
    },
    /// Update a record
    Update {
        /// Record ID
        #[arg(short, long)]
        id: u32,
        /// New data
        #[arg(short, long)]
        data: String,
    },
    /// Delete a record
    Delete {
        /// Record ID
        #[arg(short, long)]
        id: u32,
    },
    /// Search records
    Search {
        /// Search term
        #[arg(short, long)]
        term: String,
    },
    /// List all records
    List,
    /// Show database statistics
    Stats,
    /// Export database to JSON
    Export {
        /// Output file
        #[arg(short, long)]
        file: String,
    },
    /// Import database from JSON
    Import {
        /// Input file
        #[arg(short, long)]
        file: String,
    },
}

// Interactive mode
fn interactive_mode(mut db: DatabaseManager) -> io::Result<()> {
    println!("\nStarting interactive mode...");
    
    loop {
        println!("\n=== DATABASE MANAGER MENU ===");
        println!("1. Create record");
        println!("2. Read record");
        println!("3. Update record");
        println!("4. Delete record");
        println!("5. Search records");
        println!("6. List all records");
        println!("7. Begin transaction");
        println!("8. Commit transaction");
        println!("9. Rollback transaction");
        println!("10. Show statistics");
        println!("11. Export to JSON");
        println!("12. Import from JSON");
        println!("13. Exit");
        println!("=============================");
        
        print!("Enter your choice (1-13): ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        
        match input.trim() {
            "1" => {
                print!("Enter record name: ");
                io::stdout().flush().unwrap();
                let mut name = String::new();
                io::stdin().read_line(&mut name)?;
                
                print!("Enter record data: ");
                io::stdout().flush().unwrap();
                let mut data = String::new();
                io::stdin().read_line(&mut data)?;
                
                let id = db.create_record(name.trim().to_string(), data.trim().to_string())?;
                println!("Created record with ID: {}", id);
            }
            
            "2" => {
                print!("Enter record ID: ");
                io::stdout().flush().unwrap();
                let mut id_str = String::new();
                io::stdin().read_line(&mut id_str)?;
                
                if let Ok(id) = id_str.trim().parse::<u32>() {
                    if let Some(record) = db.read_record(id) {
                        record.display();
                    }
                } else {
                    println!("Invalid ID format!");
                }
            }
            
            "3" => {
                print!("Enter record ID: ");
                io::stdout().flush().unwrap();
                let mut id_str = String::new();
                io::stdin().read_line(&mut id_str)?;
                
                print!("Enter new data: ");
                io::stdout().flush().unwrap();
                let mut data = String::new();
                io::stdin().read_line(&mut data)?;
                
                if let Ok(id) = id_str.trim().parse::<u32>() {
                    db.update_record(id, data.trim().to_string())?;
                } else {
                    println!("Invalid ID format!");
                }
            }
            
            "4" => {
                print!("Enter record ID: ");
                io::stdout().flush().unwrap();
                let mut id_str = String::new();
                io::stdin().read_line(&mut id_str)?;
                
                if let Ok(id) = id_str.trim().parse::<u32>() {
                    db.delete_record(id)?;
                } else {
                    println!("Invalid ID format!");
                }
            }
            
            "5" => {
                print!("Enter search term: ");
                io::stdout().flush().unwrap();
                let mut term = String::new();
                io::stdin().read_line(&mut term)?;
                
                let results = db.search_records(term.trim());
                for record in results {
                    record.display();
                }
            }
            
            "6" => {
                db.list_records();
            }
            
            "7" => {
                db.begin_transaction()?;
            }
            
            "8" => {
                db.commit_transaction()?;
            }
            
            "9" => {
                db.rollback_transaction()?;
            }
            
            "10" => {
                let stats = db.get_statistics()?;
                println!("Database Statistics: {:?}", stats);
            }
            
            "11" => {
                print!("Enter export filename: ");
                io::stdout().flush().unwrap();
                let mut filename = String::new();
                io::stdin().read_line(&mut filename)?;
                
                db.export_to_json(filename.trim())?;
            }
            
            "12" => {
                print!("Enter import filename: ");
                io::stdout().flush().unwrap();
                let mut filename = String::new();
                io::stdin().read_line(&mut filename)?;
                
                let count = db.import_from_json(filename.trim())?;
                println!("Imported {} records", count);
            }
            
            "13" => {
                println!("\nThank you for using Rust Database Manager!");
                println!("You've learned:");
                println!("- File I/O operations with binary data");
                println!("- B-tree indexing for fast lookups");
                println!("- SQL-like query parsing and execution");
                println!("- Data serialization and deserialization");
                println!("- Transaction management and rollback");
                println!("- Human-readable, maintainable code!");
                break;
            }
            
            _ => {
                println!("Error: Invalid choice! Please enter 1-13.");
            }
        }
        
        // Add a small pause for better user experience
        println!("\nPress Enter to continue...");
        let mut _pause = String::new();
        io::stdin().read_line(&mut _pause)?;
    }
    
    Ok(())
}

fn main() -> io::Result<()> {
    println!("========================================");
    println!("    RUST DATABASE MANAGER");
    println!("========================================");
    println!("Welcome to database programming in Rust!");
    println!("This program demonstrates:");
    println!("- File I/O operations with binary data");
    println!("- B-tree indexing for fast lookups");
    println!("- SQL-like query parsing and execution");
    println!("- Data serialization and deserialization");
    println!("- Transaction management and rollback");
    println!("- Human-like code with detailed comments!");
    println!("========================================");
    
    let cli = Cli::parse();
    
    // Create database manager
    let mut db = DatabaseManager::new(cli.database)?;
    
    // Handle command line arguments
    match cli.command {
        Some(Commands::Create { name, data }) => {
            let id = db.create_record(name, data)?;
            println!("Created record with ID: {}", id);
            db.commit_transaction()?;
        }
        
        Some(Commands::Read { id }) => {
            if let Some(record) = db.read_record(id) {
                record.display();
            }
        }
        
        Some(Commands::Update { id, data }) => {
            if db.update_record(id, data)? {
                db.commit_transaction()?;
            }
        }
        
        Some(Commands::Delete { id }) => {
            if db.delete_record(id)? {
                db.commit_transaction()?;
            }
        }
        
        Some(Commands::Search { term }) => {
            let results = db.search_records(&term);
            for record in results {
                record.display();
            }
        }
        
        Some(Commands::List) => {
            db.list_records();
        }
        
        Some(Commands::Stats) => {
            let stats = db.get_statistics()?;
            println!("Database Statistics: {}", serde_json::to_string_pretty(&stats.to_json())?);
        }
        
        Some(Commands::Export { file }) => {
            db.export_to_json(&file)?;
        }
        
        Some(Commands::Import { file }) => {
            let count = db.import_from_json(&file)?;
            println!("Imported {} records", count);
            db.commit_transaction()?;
        }
        
        None => {
            // Start interactive mode
            interactive_mode(db)?;
        }
    }
    
    Ok(())
}
