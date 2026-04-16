/*
 * To-Do List Manager in C++ - Level 2: Data Structures & File I/O
 * 
 * Welcome to productivity programming in C++! This is where organization meets efficiency.
 * Learn data structures, file operations, and command-line interfaces.
 * 
 * Key concepts you'll learn:
 * - Dynamic data structures (vectors)
 * - File I/O operations with fstream
 * - Date and time handling
 * - Command parsing and validation
 * - State management and persistence
 * - Human-like code with detailed explanations!
 */

#include <iostream>     // For input/output operations (cout, cin)
#include <string>       // For string manipulation
#include <vector>       // For dynamic arrays (vectors)
#include <fstream>      // For file operations (ifstream, ofstream)
#include <algorithm>    // For sorting and searching algorithms
#include <chrono>       // For date and time operations
#include <iomanip>       // For output formatting (setw, setfill)
#include <sstream>       // For string stream operations

using namespace std;    // Standard namespace to avoid std:: prefix

// Task structure to represent a single to-do item
struct Task {
    int id;                    // Unique identifier for the task
    string title;               // Task title/description
    string description;         // Detailed task description
    string priority;            // Priority level (High, Medium, Low)
    string status;              // Current status (Pending, In Progress, Completed)
    string dueDate;            // Due date for the task
    string createdDate;         // When the task was created
    string completedDate;       // When the task was completed (if applicable)
    
    // Constructor to initialize a new task
    Task(int taskId, string taskTitle, string taskDesc, string taskPriority, 
         string taskDueDate) {
        id = taskId;
        title = taskTitle;
        description = taskDesc;
        priority = taskPriority;
        status = "Pending";
        dueDate = taskDueDate;
        createdDate = getCurrentDateTime();
        completedDate = "";
        
        cout << "Created new task: " << title << " (ID: " << id << ")" << endl;
    }
    
    // Get current date and time as formatted string
    string getCurrentDateTime() {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        
        stringstream ss;
        ss << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    // Mark task as completed
    void markCompleted() {
        status = "Completed";
        completedDate = getCurrentDateTime();
        cout << "Task completed: " << title << " at " << completedDate << endl;
    }
    
    // Update task status
    void updateStatus(string newStatus) {
        status = newStatus;
        if (newStatus == "Completed") {
            completedDate = getCurrentDateTime();
        }
        cout << "Task status updated: " << title << " -> " << status << endl;
    }
    
    // Display task information
    void display() const {
        cout << "\n" << string(60, '=') << endl;
        cout << "TASK ID: " << id << endl;
        cout << "TITLE: " << title << endl;
        cout << "DESCRIPTION: " << description << endl;
        cout << "PRIORITY: " << priority << endl;
        cout << "STATUS: " << status << endl;
        cout << "DUE DATE: " << dueDate << endl;
        cout << "CREATED: " << createdDate << endl;
        if (!completedDate.empty()) {
            cout << "COMPLETED: " << completedDate << endl;
        }
        cout << string(60, '=') << endl;
    }
    
    // Display task in table format
    void displayTableRow() const {
        cout << setw(4) << id << " | " 
             << setw(20) << left << title.substr(0, 20) << " | "
             << setw(8) << priority << " | "
             << setw(12) << status << " | "
             << setw(12) << dueDate << endl;
    }
    
    // Convert task to string for file storage
    string serialize() const {
        return to_string(id) + "|" + title + "|" + description + "|" + 
               priority + "|" + status + "|" + dueDate + "|" + 
               createdDate + "|" + completedDate;
    }
    
    // Create task from serialized string
    static Task deserialize(const string& data) {
        stringstream ss(data);
        string token;
        vector<string> parts;
        
        // Split by '|' delimiter
        while (getline(ss, token, '|')) {
            parts.push_back(token);
        }
        
        if (parts.size() >= 7) {
            Task task(stoi(parts[0]), parts[1], parts[2], parts[3], parts[6]);
            task.status = parts[4];
            task.dueDate = parts[5];
            task.createdDate = parts[6];
            if (parts.size() > 7) {
                task.completedDate = parts[7];
            }
            return task;
        }
        
        // Return empty task if deserialization fails
        return Task(0, "", "", "", "", "");
    }
};

// To-Do List Manager class to handle all operations
class TodoListManager {
private:
    vector<Task> tasks;          // Vector to store all tasks
    int nextTaskId;             // Next available task ID
    string filename;             // File to save/load tasks
    int taskCount;              // Total number of tasks created
    
public:
    // Constructor - initialize the manager
    TodoListManager(string dataFile = "tasks.txt") {
        filename = dataFile;
        nextTaskId = 1;
        taskCount = 0;
        
        cout << "To-Do List Manager initialized!" << endl;
        cout << "Data file: " << filename << endl;
        
        // Load existing tasks from file
        loadTasks();
    }
    
    // Add a new task
    void addTask() {
        cout << "\n" << string(50, '-') << endl;
        cout << "ADD NEW TASK" << endl;
        cout << string(50, '-') << endl;
        
        // Get task details from user
        cout << "Enter task title: ";
        string title;
        getline(cin, title);
        
        if (title.empty()) {
            cout << "Error: Task title cannot be empty!" << endl;
            return;
        }
        
        cout << "Enter task description: ";
        string description;
        getline(cin, description);
        
        // Get priority with validation
        string priority = getValidPriority();
        
        // Get due date with validation
        string dueDate = getValidDueDate();
        
        // Create and add the task
        Task newTask(nextTaskId++, title, description, priority, dueDate);
        tasks.push_back(newTask);
        taskCount++;
        
        cout << "Task added successfully!" << endl;
        cout << "Total tasks: " << tasks.size() << endl;
        
        // Save to file
        saveTasks();
    }
    
    // Get valid priority from user
    string getValidPriority() {
        while (true) {
            cout << "Enter priority (High/Medium/Low): ";
            string priority;
            getline(cin, priority);
            
            // Convert to lowercase for case-insensitive comparison
            transform(priority.begin(), priority.end(), priority.begin(), ::tolower);
            
            if (priority == "high" || priority == "medium" || priority == "low") {
                // Convert to proper case
                if (priority == "high") return "High";
                if (priority == "medium") return "Medium";
                if (priority == "low") return "Low";
            }
            
            cout << "Error: Invalid priority! Please enter High, Medium, or Low." << endl;
        }
    }
    
    // Get valid due date from user
    string getValidDueDate() {
        while (true) {
            cout << "Enter due date (YYYY-MM-DD) or press Enter for no due date: ";
            string dueDate;
            getline(cin, dueDate);
            
            if (dueDate.empty()) {
                return "No due date";
            }
            
            // Basic date validation (YYYY-MM-DD format)
            if (dueDate.length() == 10 && dueDate[4] == '-' && dueDate[7] == '-') {
                try {
                    int year = stoi(dueDate.substr(0, 4));
                    int month = stoi(dueDate.substr(5, 2));
                    int day = stoi(dueDate.substr(8, 2));
                    
                    if (year >= 2020 && year <= 2030 && 
                        month >= 1 && month <= 12 && 
                        day >= 1 && day <= 31) {
                        return dueDate;
                    }
                } catch (...) {
                    // Invalid date format
                }
            }
            
            cout << "Error: Invalid date format! Please use YYYY-MM-DD." << endl;
        }
    }
    
    // List all tasks
    void listTasks() {
        cout << "\n" << string(80, '=') << endl;
        cout << "ALL TASKS" << endl;
        cout << string(80, '=') << endl;
        
        if (tasks.empty()) {
            cout << "No tasks found!" << endl;
            cout << "Use option 1 to add your first task." << endl;
            return;
        }
        
        // Display table header
        cout << setw(4) << "ID" << " | " 
             << setw(20) << left << "TITLE" << " | "
             << setw(8) << "PRIORITY" << " | "
             << setw(12) << "STATUS" << " | "
             << setw(12) << "DUE DATE" << endl;
        cout << string(80, '-') << endl;
        
        // Display all tasks
        for (const Task& task : tasks) {
            task.displayTableRow();
        }
        
        cout << string(80, '=') << endl;
        cout << "Total tasks: " << tasks.size() << endl;
        
        // Show statistics
        showStatistics();
    }
    
    // Show task statistics
    void showStatistics() {
        cout << "\n" << string(40, '-') << endl;
        cout << "TASK STATISTICS" << endl;
        cout << string(40, '-') << endl;
        
        int pendingCount = 0;
        int inProgressCount = 0;
        int completedCount = 0;
        int highPriorityCount = 0;
        
        for (const Task& task : tasks) {
            if (task.status == "Pending") pendingCount++;
            else if (task.status == "In Progress") inProgressCount++;
            else if (task.status == "Completed") completedCount++;
            
            if (task.priority == "High") highPriorityCount++;
        }
        
        cout << "Total tasks: " << tasks.size() << endl;
        cout << "Pending: " << pendingCount << endl;
        cout << "In Progress: " << inProgressCount << endl;
        cout << "Completed: " << completedCount << endl;
        cout << "High Priority: " << highPriorityCount << endl;
        
        if (tasks.size() > 0) {
            double completionRate = (double)completedCount / tasks.size() * 100;
            cout << "Completion Rate: " << fixed << setprecision(1) << completionRate << "%" << endl;
        }
        
        cout << string(40, '-') << endl;
    }
    
    // Search for tasks
    void searchTasks() {
        cout << "\n" << string(50, '-') << endl;
        cout << "SEARCH TASKS" << endl;
        cout << string(50, '-') << endl;
        
        cout << "Enter search keyword: ";
        string keyword;
        getline(cin, keyword);
        
        if (keyword.empty()) {
            cout << "Error: Search keyword cannot be empty!" << endl;
            return;
        }
        
        vector<Task> foundTasks;
        
        // Search in task titles and descriptions
        for (const Task& task : tasks) {
            string titleLower = task.title;
            string descLower = task.description;
            string keywordLower = keyword;
            
            // Convert to lowercase for case-insensitive search
            transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
            transform(descLower.begin(), descLower.end(), descLower.begin(), ::tolower);
            transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);
            
            if (titleLower.find(keywordLower) != string::npos || 
                descLower.find(keywordLower) != string::npos) {
                foundTasks.push_back(task);
            }
        }
        
        // Display search results
        cout << "\nSearch Results for '" << keyword << "':" << endl;
        cout << string(50, '-') << endl;
        
        if (foundTasks.empty()) {
            cout << "No tasks found matching '" << keyword << "'" << endl;
        } else {
            cout << "Found " << foundTasks.size() << " task(s):" << endl;
            
            for (const Task& task : foundTasks) {
                task.displayTableRow();
            }
        }
        
        cout << string(50, '-') << endl;
    }
    
    // Update task status
    void updateTaskStatus() {
        cout << "\n" << string(50, '-') << endl;
        cout << "UPDATE TASK STATUS" << endl;
        cout << string(50, '-') << endl;
        
        if (tasks.empty()) {
            cout << "No tasks available to update!" << endl;
            return;
        }
        
        // Show available tasks
        cout << "Available tasks:" << endl;
        for (const Task& task : tasks) {
            cout << "ID: " << task.id << " - " << task.title 
                 << " (" << task.status << ")" << endl;
        }
        
        // Get task ID
        int taskId = getValidTaskId();
        
        // Find the task
        Task* taskToUpdate = nullptr;
        for (Task& task : tasks) {
            if (task.id == taskId) {
                taskToUpdate = &task;
                break;
            }
        }
        
        if (!taskToUpdate) {
            cout << "Error: Task with ID " << taskId << " not found!" << endl;
            return;
        }
        
        // Display current status
        cout << "Current task:" << endl;
        taskToUpdate->display();
        
        // Get new status
        string newStatus = getValidStatus();
        
        // Update the task
        taskToUpdate->updateStatus(newStatus);
        
        // Save to file
        saveTasks();
        
        cout << "Task status updated successfully!" << endl;
    }
    
    // Get valid task ID from user
    int getValidTaskId() {
        while (true) {
            cout << "Enter task ID: ";
            string input;
            getline(cin, input);
            
            try {
                int taskId = stoi(input);
                
                // Check if task ID exists
                for (const Task& task : tasks) {
                    if (task.id == taskId) {
                        return taskId;
                    }
                }
                
                cout << "Error: Task ID " << taskId << " not found!" << endl;
            } catch (...) {
                cout << "Error: Please enter a valid number!" << endl;
            }
        }
    }
    
    // Get valid status from user
    string getValidStatus() {
        while (true) {
            cout << "Enter new status (Pending/In Progress/Completed): ";
            string status;
            getline(cin, status);
            
            // Convert to lowercase for case-insensitive comparison
            transform(status.begin(), status.end(), status.begin(), ::tolower);
            
            if (status == "pending" || status == "in progress" || status == "completed") {
                // Convert to proper case
                if (status == "pending") return "Pending";
                if (status == "in progress") return "In Progress";
                if (status == "completed") return "Completed";
            }
            
            cout << "Error: Invalid status! Please enter Pending, In Progress, or Completed." << endl;
        }
    }
    
    // Delete a task
    void deleteTask() {
        cout << "\n" << string(50, '-') << endl;
        cout << "DELETE TASK" << endl;
        cout << string(50, '-') << endl;
        
        if (tasks.empty()) {
            cout << "No tasks available to delete!" << endl;
            return;
        }
        
        // Show available tasks
        cout << "Available tasks:" << endl;
        for (const Task& task : tasks) {
            cout << "ID: " << task.id << " - " << task.title 
                 << " (" << task.status << ")" << endl;
        }
        
        // Get task ID
        int taskId = getValidTaskId();
        
        // Find and delete the task
        bool found = false;
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == taskId) {
                cout << "Deleting task: " << it->title << endl;
                tasks.erase(it);
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Error: Task with ID " << taskId << " not found!" << endl;
            return;
        }
        
        cout << "Task deleted successfully!" << endl;
        cout << "Remaining tasks: " << tasks.size() << endl;
        
        // Save to file
        saveTasks();
    }
    
    // Save tasks to file
    void saveTasks() {
        ofstream outFile(filename);
        
        if (!outFile.is_open()) {
            cout << "Error: Could not open file " << filename << " for writing!" << endl;
            return;
        }
        
        // Write each task to file
        for (const Task& task : tasks) {
            outFile << task.serialize() << endl;
        }
        
        outFile.close();
        cout << "Tasks saved to " << filename << endl;
    }
    
    // Load tasks from file
    void loadTasks() {
        ifstream inFile(filename);
        
        if (!inFile.is_open()) {
            cout << "No existing task file found. Starting with empty list." << endl;
            return;
        }
        
        string line;
        int loadedCount = 0;
        
        // Read each line and deserialize task
        while (getline(inFile, line)) {
            if (!line.empty()) {
                Task task = Task::deserialize(line);
                if (task.id > 0) {  // Valid task
                    tasks.push_back(task);
                    loadedCount++;
                    
                    // Update next task ID
                    if (task.id >= nextTaskId) {
                        nextTaskId = task.id + 1;
                    }
                }
            }
        }
        
        inFile.close();
        
        if (loadedCount > 0) {
            cout << "Loaded " << loadedCount << " tasks from " << filename << endl;
        }
    }
    
    // Display menu
    void displayMenu() {
        cout << "\n" << string(60, '=') << endl;
        cout << "    C++ TO-DO LIST MANAGER" << endl;
        cout << string(60, '=') << endl;
        cout << "1. Add new task" << endl;
        cout << "2. List all tasks" << endl;
        cout << "3. Search tasks" << endl;
        cout << "4. Update task status" << endl;
        cout << "5. Delete task" << endl;
        cout << "6. Show statistics" << endl;
        cout << "7. Exit" << endl;
        cout << string(60, '=') << endl;
    }
    
    // Run the main application loop
    void run() {
        cout << "Welcome to C++ To-Do List Manager!" << endl;
        cout << "This application demonstrates:" << endl;
        cout << "- Object-oriented programming with classes and structs" << endl;
        cout << "- Dynamic data structures (vectors)" << endl;
        cout << "- File I/O operations and data persistence" << endl;
        cout << "- String manipulation and parsing" << endl;
        cout << "- User input validation and error handling" << endl;
        cout << "- State management and business logic" << endl;
        cout << "- Human-like code with detailed comments!" << endl;
        
        while (true) {
            displayMenu();
            
            cout << "Enter your choice (1-7): ";
            string choice;
            getline(cin, choice);
            
            if (choice == "1") {
                addTask();
            } else if (choice == "2") {
                listTasks();
            } else if (choice == "3") {
                searchTasks();
            } else if (choice == "4") {
                updateTaskStatus();
            } else if (choice == "5") {
                deleteTask();
            } else if (choice == "6") {
                showStatistics();
            } else if (choice == "7") {
                cout << "\nThank you for using C++ To-Do List Manager!" << endl;
                cout << "You've learned:" << endl;
                cout << "- Object-oriented programming principles" << endl;
                cout << "- Dynamic data structures and algorithms" << endl;
                cout << "- File I/O and data persistence" << endl;
                cout << "- User input validation and sanitization" << endl;
                cout << "- State management and business logic" << endl;
                cout << "- Human-readable, maintainable code!" << endl;
                break;
            } else {
                cout << "Error: Invalid choice! Please enter 1-7." << endl;
            }
            
            // Add a small pause for better user experience
            if (choice != "7") {
                cout << "\nPress Enter to continue...";
                string pause;
                getline(cin, pause);
            }
        }
    }
};

// Main function - program entry point
int main() {
    cout << "========================================" << endl;
    cout << "    C++ TO-DO LIST MANAGER" << endl;
    cout << "========================================" << endl;
    cout << "Learn modern C++ through practical programming!" << endl;
    cout << "This to-do list manager demonstrates:" << endl;
    cout << "- Class design and encapsulation" << endl;
    cout << "- Dynamic data structures (vectors)" << endl;
    cout << "- File I/O operations and persistence" << endl;
    cout << "- String manipulation and parsing" << endl;
    cout << "- User input validation and error handling" << endl;
    cout << "- State management and business logic" << endl;
    cout << "- Human-like code with detailed comments!" << endl;
    cout << "========================================" << endl;
    
    // Create and run the to-do list manager
    TodoListManager manager;
    manager.run();
    
    return 0;  // Successful program execution
}
