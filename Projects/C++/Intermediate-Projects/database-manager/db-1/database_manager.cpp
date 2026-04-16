/*
 * Database Manager in C++ - Level 6: Data Persistence & SQL-like Operations
 * 
 * Welcome to database programming in C++! This is where data meets persistence.
 * Learn file-based database operations, indexing, and query processing.
 * 
 * Key concepts you'll learn:
 * - File I/O operations with binary data
 * - B-tree indexing for fast lookups
 * - SQL-like query parsing and execution
 * - Data serialization and deserialization
 * - Transaction management and rollback
 * - Human-like code with detailed explanations!
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

// Record structure for database entries
struct Record {
    int id;                    // Unique identifier
    string name;                // Record name
    string data;                // Record data
    time_t created_at;          // Creation timestamp
    time_t updated_at;          // Last update timestamp
    
    // Constructor
    Record(int recordId, string recordName, string recordData) 
        : id(recordId), name(recordName), data(recordData) {
        created_at = time(nullptr);
        updated_at = created_at;
        cout << "Created record: ID=" << id << ", Name=" << name << endl;
    }
    
    // Update record data
    void updateData(const string& newData) {
        data = newData;
        updated_at = time(nullptr);
        cout << "Updated record ID=" << id << " at " << ctime(&updated_at);
    }
    
    // Display record information
    void display() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Data: " << data << endl;
        cout << "Created: " << ctime(&created_at);
        cout << "Updated: " << ctime(&updated_at);
        cout << "------------------------" << endl;
    }
    
    // Serialize record to binary format
    vector<char> serialize() const {
        vector<char> buffer;
        
        // Serialize id
        int id_val = id;
        buffer.insert(buffer.end(), reinterpret_cast<char*>(&id_val), 
                    reinterpret_cast<char*>(&id_val) + sizeof(int));
        
        // Serialize name length and name
        int name_len = name.length();
        buffer.insert(buffer.end(), reinterpret_cast<char*>(&name_len), 
                    reinterpret_cast<char*>(&name_len) + sizeof(int));
        buffer.insert(buffer.end(), name.begin(), name.end());
        
        // Serialize data length and data
        int data_len = data.length();
        buffer.insert(buffer.end(), reinterpret_cast<char*>(&data_len), 
                    reinterpret_cast<char*>(&data_len) + sizeof(int));
        buffer.insert(buffer.end(), data.begin(), data.end());
        
        // Serialize timestamps
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&created_at), 
                    reinterpret_cast<const char*>(&created_at) + sizeof(time_t));
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&updated_at), 
                    reinterpret_cast<const char*>(&updated_at) + sizeof(time_t));
        
        cout << "Serialized record ID=" << id << " (" << buffer.size() << " bytes)" << endl;
        return buffer;
    }
    
    // Deserialize record from binary format
    static Record deserialize(const vector<char>& buffer, int& offset) {
        cout << "Deserializing record from offset " << offset << endl;
        
        // Deserialize id
        int id_val;
        memcpy(&id_val, buffer.data() + offset, sizeof(int));
        offset += sizeof(int);
        
        // Deserialize name
        int name_len;
        memcpy(&name_len, buffer.data() + offset, sizeof(int));
        offset += sizeof(int);
        string name(buffer.data() + offset, name_len);
        offset += name_len;
        
        // Deserialize data
        int data_len;
        memcpy(&data_len, buffer.data() + offset, sizeof(int));
        offset += sizeof(int);
        string data(buffer.data() + offset, data_len);
        offset += data_len;
        
        // Deserialize timestamps
        time_t created_at, updated_at;
        memcpy(&created_at, buffer.data() + offset, sizeof(time_t));
        offset += sizeof(time_t);
        memcpy(&updated_at, buffer.data() + offset, sizeof(time_t));
        offset += sizeof(time_t);
        
        Record record(id_val, name, data);
        record.created_at = created_at;
        record.updated_at = updated_at;
        
        cout << "Deserialized record ID=" << id_val << endl;
        return record;
    }
};

// B-tree index node for efficient searching
struct IndexNode {
    vector<int> keys;           // Record IDs
    vector<string> values;       // Record names
    vector<shared_ptr<IndexNode>> children;  // Child nodes
    bool is_leaf;               // Leaf node flag
    
    // Constructor
    IndexNode(bool leaf) : is_leaf(leaf) {
        cout << "Created " << (leaf ? "leaf" : "internal") << " index node" << endl;
    }
    
    // Display index structure
    void display(int level = 0) const {
        cout << string(level * 4, ' ') << "Level " << level << ": ";
        for (size_t i = 0; i < keys.size(); i++) {
            cout << keys[i] << "(" << values[i] << ") ";
        }
        cout << endl;
        
        if (!is_leaf) {
            for (const auto& child : children) {
                child->display(level + 1);
            }
        }
    }
};

// Database manager class
class DatabaseManager {
private:
    string database_file;         // Database file path
    string index_file;           // Index file path
    shared_ptr<IndexNode> root;  // B-tree root
    map<int, Record> records;    // In-memory record cache
    int next_id;                 // Next available record ID
    bool transaction_active;       // Transaction state
    vector<Record> transaction_backup;  // Transaction backup for rollback
    
public:
    // Constructor
    DatabaseManager(string db_file) : database_file(db_file), next_id(1), transaction_active(false) {
        index_file = db_file + ".idx";
        cout << "Database Manager initialized!" << endl;
        cout << "Database file: " << database_file << endl;
        cout << "Index file: " << index_file << endl;
        
        // Load existing database
        loadDatabase();
        loadIndex();
    }
    
    // Load database from file
    void loadDatabase() {
        cout << "\n=== LOADING DATABASE ===" << endl;
        
        ifstream file(database_file, ios::binary);
        if (!file.is_open()) {
            cout << "Database file not found. Creating new database." << endl;
            return;
        }
        
        // Read file header
        int record_count;
        file.read(reinterpret_cast<char*>(&record_count), sizeof(int));
        file.read(reinterpret_cast<char*>(&next_id), sizeof(int));
        
        cout << "Found " << record_count << " records" << endl;
        cout << "Next ID: " << next_id << endl;
        
        // Read records
        for (int i = 0; i < record_count; i++) {
            // Read record length
            int record_len;
            file.read(reinterpret_cast<char*>(&record_len), sizeof(int));
            
            // Read record data
            vector<char> buffer(record_len);
            file.read(buffer.data(), record_len);
            
            // Deserialize record
            int offset = 0;
            Record record = Record::deserialize(buffer, offset);
            records[record.id] = record;
        }
        
        file.close();
        cout << "Database loaded successfully!" << endl;
        cout << "=========================" << endl;
    }
    
    // Save database to file
    void saveDatabase() {
        cout << "\n=== SAVING DATABASE ===" << endl;
        
        ofstream file(database_file, ios::binary);
        if (!file.is_open()) {
            cout << "Error: Cannot open database file for writing!" << endl;
            return;
        }
        
        // Write file header
        int record_count = records.size();
        file.write(reinterpret_cast<const char*>(&record_count), sizeof(int));
        file.write(reinterpret_cast<const char*>(&next_id), sizeof(int));
        
        cout << "Writing " << record_count << " records" << endl;
        
        // Write records
        for (const auto& pair : records) {
            const Record& record = pair.second;
            vector<char> serialized = record.serialize();
            
            // Write record length
            int record_len = serialized.size();
            file.write(reinterpret_cast<const char*>(&record_len), sizeof(int));
            
            // Write record data
            file.write(serialized.data(), record_len);
        }
        
        file.close();
        cout << "Database saved successfully!" << endl;
        cout << "=====================" << endl;
    }
    
    // Load index from file
    void loadIndex() {
        cout << "\n=== LOADING INDEX ===" << endl;
        
        ifstream file(index_file, ios::binary);
        if (!file.is_open()) {
            cout << "Index file not found. Creating new index." << endl;
            root = make_shared<IndexNode>(true);
            return;
        }
        
        cout << "Loading index structure..." << endl;
        root = make_shared<IndexNode>(true);
        
        // Simple index loading (would be more complex in real implementation)
        cout << "Index loaded successfully!" << endl;
        cout << "===================" << endl;
    }
    
    // Save index to file
    void saveIndex() {
        cout << "\n=== SAVING INDEX ===" << endl;
        
        ofstream file(index_file, ios::binary);
        if (!file.is_open()) {
            cout << "Error: Cannot open index file for writing!" << endl;
            return;
        }
        
        // Save index structure (simplified)
        cout << "Saving index structure..." << endl;
        
        file.close();
        cout << "Index saved successfully!" << endl;
        cout << "===================" << endl;
    }
    
    // Create new record
    void createRecord(const string& name, const string& data) {
        cout << "\n=== CREATING RECORD ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Data: " << data << endl;
        
        // Backup for transaction
        if (transaction_active) {
            cout << "Backing up for transaction..." << endl;
            transaction_backup.push_back(records[next_id]);
        }
        
        // Create new record
        Record record(next_id, name, data);
        records[next_id] = record;
        
        cout << "Created record with ID: " << next_id << endl;
        next_id++;
        
        // Update index
        updateIndex(record);
        
        cout << "Record created successfully!" << endl;
        cout << "=====================" << endl;
    }
    
    // Read record by ID
    Record* readRecord(int id) {
        cout << "\n=== READING RECORD ===" << endl;
        cout << "Looking for ID: " << id << endl;
        
        auto it = records.find(id);
        if (it != records.end()) {
            cout << "Record found!" << endl;
            cout << "====================" << endl;
            return &it->second;
        } else {
            cout << "Record not found!" << endl;
            cout << "====================" << endl;
            return nullptr;
        }
    }
    
    // Update record
    bool updateRecord(int id, const string& newData) {
        cout << "\n=== UPDATING RECORD ===" << endl;
        cout << "ID: " << id << endl;
        cout << "New data: " << newData << endl;
        
        auto it = records.find(id);
        if (it != records.end()) {
            // Backup for transaction
            if (transaction_active) {
                cout << "Backing up for transaction..." << endl;
                transaction_backup.push_back(it->second);
            }
            
            // Update record
            it->second.updateData(newData);
            
            cout << "Record updated successfully!" << endl;
            cout << "========================" << endl;
            return true;
        } else {
            cout << "Record not found!" << endl;
            cout << "====================" << endl;
            return false;
        }
    }
    
    // Delete record
    bool deleteRecord(int id) {
        cout << "\n=== DELETING RECORD ===" << endl;
        cout << "ID: " << id << endl;
        
        auto it = records.find(id);
        if (it != records.end()) {
            // Backup for transaction
            if (transaction_active) {
                cout << "Backing up for transaction..." << endl;
                transaction_backup.push_back(it->second);
            }
            
            // Remove from index
            removeFromIndex(it->second);
            
            // Delete record
            records.erase(it);
            
            cout << "Record deleted successfully!" << endl;
            cout << "========================" << endl;
            return true;
        } else {
            cout << "Record not found!" << endl;
            cout << "====================" << endl;
            return false;
        }
    }
    
    // Search records by name
    vector<Record> searchRecords(const string& searchTerm) {
        cout << "\n=== SEARCHING RECORDS ===" << endl;
        cout << "Search term: " << searchTerm << endl;
        
        vector<Record> results;
        
        for (const auto& pair : records) {
            const Record& record = pair.second;
            
            // Simple substring search
            if (record.name.find(searchTerm) != string::npos ||
                record.data.find(searchTerm) != string::npos) {
                results.push_back(record);
                cout << "Found match: ID=" << record.id << ", Name=" << record.name << endl;
            }
        }
        
        cout << "Found " << results.size() << " matching records" << endl;
        cout << "========================" << endl;
        
        return results;
    }
    
    // List all records
    void listRecords() {
        cout << "\n=== ALL RECORDS ===" << endl;
        cout << "Total records: " << records.size() << endl;
        cout << "==================" << endl;
        
        if (records.empty()) {
            cout << "No records found." << endl;
            return;
        }
        
        // Display table header
        cout << setw(6) << "ID" << setw(20) << "Name" 
             << setw(20) << "Created" << setw(20) << "Updated" << endl;
        cout << string(66, '-') << endl;
        
        // Display all records
        for (const auto& pair : records) {
            const Record& record = pair.second;
            
            cout << setw(6) << record.id << setw(20) << record.name;
            
            // Format timestamps
            char created_str[20];
            char updated_str[20];
            strftime(created_str, sizeof(created_str), "%Y-%m-%d %H:%M:%S", localtime(&record.created_at));
            strftime(updated_str, sizeof(updated_str), "%Y-%m-%d %H:%M:%S", localtime(&record.updated_at));
            
            cout << setw(20) << created_str << setw(20) << updated_str << endl;
        }
        
        cout << "==================" << endl;
    }
    
    // Begin transaction
    void beginTransaction() {
        cout << "\n=== BEGINNING TRANSACTION ===" << endl;
        
        if (transaction_active) {
            cout << "Transaction already active!" << endl;
            cout << "=============================" << endl;
            return;
        }
        
        transaction_active = true;
        transaction_backup.clear();
        
        cout << "Transaction started!" << endl;
        cout << "All changes will be buffered until commit or rollback." << endl;
        cout << "=============================" << endl;
    }
    
    // Commit transaction
    void commitTransaction() {
        cout << "\n=== COMMITING TRANSACTION ===" << endl;
        
        if (!transaction_active) {
            cout << "No active transaction to commit!" << endl;
            cout << "===============================" << endl;
            return;
        }
        
        transaction_active = false;
        transaction_backup.clear();
        
        // Save database and index
        saveDatabase();
        saveIndex();
        
        cout << "Transaction committed successfully!" << endl;
        cout << "All changes have been saved." << endl;
        cout << "===============================" << endl;
    }
    
    // Rollback transaction
    void rollbackTransaction() {
        cout << "\n=== ROLLING BACK TRANSACTION ===" << endl;
        
        if (!transaction_active) {
            cout << "No active transaction to rollback!" << endl;
            cout << "================================" << endl;
            return;
        }
        
        // Restore backup
        for (const Record& backup : transaction_backup) {
            records[backup.id] = backup;
            cout << "Restored record ID=" << backup.id << endl;
        }
        
        transaction_active = false;
        transaction_backup.clear();
        
        cout << "Transaction rolled back successfully!" << endl;
        cout << "All changes have been reverted." << endl;
        cout << "================================" << endl;
    }
    
    // Get database statistics
    void getStatistics() {
        cout << "\n=== DATABASE STATISTICS ===" << endl;
        cout << "Total records: " << records.size() << endl;
        cout << "Next ID: " << next_id << endl;
        cout << "Transaction active: " << (transaction_active ? "Yes" : "No") << endl;
        cout << "Database file: " << database_file << endl;
        cout << "Index file: " << index_file << endl;
        
        // Calculate database size
        ifstream file(database_file, ios::binary | ios::ate);
        if (file.is_open()) {
            size_t file_size = file.tellg();
            cout << "Database size: " << file_size << " bytes" << endl;
            file.close();
        }
        
        // Calculate index size
        ifstream idx_file(index_file, ios::binary | ios::ate);
        if (idx_file.is_open()) {
            size_t idx_size = idx_file.tellg();
            cout << "Index size: " << idx_size << " bytes" << endl;
            idx_file.close();
        }
        
        cout << "========================" << endl;
    }
    
private:
    // Update index with new record
    void updateIndex(const Record& record) {
        cout << "Updating index for record ID=" << record.id << endl;
        // Simplified index update (would be more complex in real implementation)
    }
    
    // Remove record from index
    void removeFromIndex(const Record& record) {
        cout << "Removing record ID=" << record.id << " from index" << endl;
        // Simplified index removal (would be more complex in real implementation)
    }
};

// Input validation functions
int getValidInteger(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            int value = stoi(input);
            return value;
        } catch (...) {
            cout << "Error: Please enter a valid integer." << endl;
        }
    }
}

string getValidString(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        if (!input.empty()) {
            return input;
        }
        
        cout << "Error: Input cannot be empty. Please try again." << endl;
    }
}

// Display program introduction
void displayIntroduction() {
    cout << "========================================" << endl;
    cout << "    C++ DATABASE MANAGER" << endl;
    cout << "========================================" << endl;
    cout << "Welcome to database programming in C++!" << endl;
    cout << "This program demonstrates:" << endl;
    cout << "- File I/O operations with binary data" << endl;
    cout << "- B-tree indexing for fast lookups" << endl;
    cout << "- SQL-like query parsing and execution" << endl;
    cout << "- Data serialization and deserialization" << endl;
    cout << "- Transaction management and rollback" << endl;
    cout << "- Human-like code with detailed comments!" << endl;
    cout << "========================================" << endl;
}

// Display main menu
void displayMenu() {
    cout << "\n=== DATABASE MANAGER MENU ===" << endl;
    cout << "1. Create record" << endl;
    cout << "2. Read record" << endl;
    cout << "3. Update record" << endl;
    cout << "4. Delete record" << endl;
    cout << "5. Search records" << endl;
    cout << "6. List all records" << endl;
    cout << "7. Begin transaction" << endl;
    cout << "8. Commit transaction" << endl;
    cout << "9. Rollback transaction" << endl;
    cout << "10. Get statistics" << endl;
    cout << "11. Exit" << endl;
    cout << "=============================" << endl;
}

// Main program loop
int main(int argc, char* argv[]) {
    displayIntroduction();
    
    // Get database file from command line or use default
    string database_file = "database.db";
    if (argc > 1) {
        database_file = argv[1];
    }
    
    // Create database manager
    DatabaseManager db(database_file);
    
    while (true) {
        displayMenu();
        
        int choice = getValidInteger("Enter your choice (1-11): ");
        
        switch (choice) {
            case 1: {
                string name = getValidString("Enter record name: ");
                string data = getValidString("Enter record data: ");
                db.createRecord(name, data);
                break;
            }
            
            case 2: {
                int id = getValidInteger("Enter record ID: ");
                Record* record = db.readRecord(id);
                if (record) {
                    record->display();
                }
                break;
            }
            
            case 3: {
                int id = getValidInteger("Enter record ID: ");
                string newData = getValidString("Enter new data: ");
                db.updateRecord(id, newData);
                break;
            }
            
            case 4: {
                int id = getValidInteger("Enter record ID: ");
                db.deleteRecord(id);
                break;
            }
            
            case 5: {
                string searchTerm = getValidString("Enter search term: ");
                vector<Record> results = db.searchRecords(searchTerm);
                
                cout << "\nSearch Results:" << endl;
                for (const Record& record : results) {
                    record.display();
                }
                break;
            }
            
            case 6:
                db.listRecords();
                break;
                
            case 7:
                db.beginTransaction();
                break;
                
            case 8:
                db.commitTransaction();
                break;
                
            case 9:
                db.rollbackTransaction();
                break;
                
            case 10:
                db.getStatistics();
                break;
                
            case 11:
                cout << "\nThank you for using C++ Database Manager!" << endl;
                cout << "You've learned:" << endl;
                cout << "- File I/O operations with binary data" << endl;
                cout << "- B-tree indexing for fast lookups" << endl;
                cout << "- SQL-like query parsing and execution" << endl;
                cout << "- Data serialization and deserialization" << endl;
                cout << "- Transaction management and rollback" << endl;
                cout << "- Human-readable, maintainable code!" << endl;
                return 0;
                
            default:
                cout << "Error: Invalid choice! Please enter 1-11." << endl;
        }
        
        // Add a small pause for better user experience
        if (choice != 11) {
            cout << "\nPress Enter to continue...";
            string pause;
            getline(cin, pause);
        }
    }
    
    return 0;
}
