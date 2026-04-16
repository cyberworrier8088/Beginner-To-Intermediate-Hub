/*
 * File Manager in Rust - Level 3: File I/O and Error Handling
 * 
 * Welcome to systems programming in Rust! This is where safety meets practicality.
 * Learn file operations, error handling, and command-line interfaces.
 * 
 * Key concepts you'll learn:
 * - File I/O operations with std::fs
 * - Error handling with Result and Option
 * - Path manipulation and validation
 * - Command-line argument parsing
 * - Directory traversal and file operations
 * - Safe memory management with no garbage collection
 * - Human-like code with detailed explanations!
 */

use std::env;
use std::fs::{self, File, DirEntry};
use std::io::{self, Write, Read, BufReader, BufRead};
use std::path::{Path, PathBuf};
use std::collections::HashMap;

// File manager structure to manage operations
struct FileManager {
    current_dir: PathBuf,
    operation_count: u32,
}

impl FileManager {
    // Create new file manager
    fn new() -> io::Result<Self> {
        let current_dir = env::current_dir()?;
        Ok(FileManager {
            current_dir,
            operation_count: 0,
        })
    }
    
    // Change directory
    fn change_directory(&mut self, path: &str) -> io::Result<()> {
        let new_path = if path == ".." {
            self.current_dir.parent()
                .ok_or_else(|| io::Error::new(io::ErrorKind::NotFound, "Already at root"))?
                .to_path_buf()
        } else if path.starts_with('/') {
            PathBuf::from(path)
        } else {
            self.current_dir.join(path)
        };
        
        if !new_path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "Directory does not exist"));
        }
        
        if !new_path.is_dir() {
            return Err(io::Error::new(io::ErrorKind::InvalidInput, "Path is not a directory"));
        }
        
        self.current_dir = new_path.canonicalize()?;
        self.operation_count += 1;
        
        println!("Changed to directory: {}", self.current_dir.display());
        Ok(())
    }
    
    // List directory contents
    fn list_directory(&self) -> io::Result<()> {
        println!("\n=== Directory Contents ===");
        println!("Path: {}", self.current_dir.display());
        println!("{}", "=".repeat(60));
        
        let entries = fs::read_dir(&self.current_dir)?;
        
        let mut files = Vec::new();
        let mut directories = Vec::new();
        
        for entry in entries {
            let entry = entry?;
            let metadata = entry.metadata()?;
            
            if metadata.is_dir() {
                directories.push(entry);
            } else {
                files.push(entry);
            }
        }
        
        // Sort directories and files
        directories.sort_by(|a, b| a.file_name().cmp(&b.file_name()));
        files.sort_by(|a, b| a.file_name().cmp(&b.file_name()));
        
        // Display directories first
        if !directories.is_empty() {
            println!("DIRECTORIES:");
            for entry in directories {
                let metadata = entry.metadata()?;
                let name = entry.file_name().to_string_lossy();
                let size = if let Ok(size) = metadata.len() {
                    format!("{} bytes", size)
                } else {
                    "Unknown".to_string()
                };
                
                println!("  [DIR]  {:<30} {}", name, size);
            }
        }
        
        // Display files
        if !files.is_empty() {
            if !directories.is_empty() {
                println!();
            }
            println!("FILES:");
            for entry in files {
                let metadata = entry.metadata()?;
                let name = entry.file_name().to_string_lossy();
                let size = metadata.len();
                let modified = metadata.modified()
                    .map(|time| format!("{:?}", time))
                    .unwrap_or_else(|_| "Unknown".to_string());
                
                println!("  [FILE] {:<30} {:>10} bytes", name, size);
                println!("         Modified: {}", modified);
            }
        }
        
        if directories.is_empty() && files.is_empty() {
            println!("Directory is empty");
        }
        
        println!("{}", "=".repeat(60));
        println!("Total: {} directories, {} files", directories.len(), files.len());
        
        Ok(())
    }
    
    // Create directory
    fn create_directory(&mut self, name: &str) -> io::Result<()> {
        let path = self.current_dir.join(name);
        
        if path.exists() {
            return Err(io::Error::new(io::ErrorKind::AlreadyExists, "Directory already exists"));
        }
        
        fs::create_dir(&path)?;
        self.operation_count += 1;
        
        println!("Created directory: {}", path.display());
        Ok(())
    }
    
    // Create file
    fn create_file(&mut self, name: &str, content: Option<&str>) -> io::Result<()> {
        let path = self.current_dir.join(name);
        
        if path.exists() {
            return Err(io::Error::new(io::ErrorKind::AlreadyExists, "File already exists"));
        }
        
        let mut file = File::create(&path)?;
        
        if let Some(content) = content {
            file.write_all(content.as_bytes())?;
        }
        
        self.operation_count += 1;
        
        println!("Created file: {}", path.display());
        if content.is_some() {
            println!("Content written successfully");
        }
        
        Ok(())
    }
    
    // Read file
    fn read_file(&self, name: &str) -> io::Result<()> {
        let path = self.current_dir.join(name);
        
        if !path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "File does not exist"));
        }
        
        if !path.is_file() {
            return Err(io::Error::new(io::ErrorKind::InvalidInput, "Path is not a file"));
        }
        
        let file = File::open(&path)?;
        let reader = BufReader::new(file);
        
        println!("\n=== File Contents ===");
        println!("Path: {}", path.display());
        println!("{}", "=".repeat(60));
        
        for (line_num, line) in reader.lines().enumerate() {
            let line = line?;
            println!("{:4}: {}", line_num + 1, line);
        }
        
        println!("{}", "=".repeat(60));
        
        Ok(())
    }
    
    // Write to file
    fn write_file(&mut self, name: &str, content: &str) -> io::Result<()> {
        let path = self.current_dir.join(name);
        
        if !path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "File does not exist"));
        }
        
        if !path.is_file() {
            return Err(io::Error::new(io::ErrorKind::InvalidInput, "Path is not a file"));
        }
        
        let mut file = File::create(&path)?;
        file.write_all(content.as_bytes())?;
        
        self.operation_count += 1;
        
        println!("Written to file: {}", path.display());
        Ok(())
    }
    
    // Append to file
    fn append_file(&mut self, name: &str, content: &str) -> io::Result<()> {
        let path = self.current_dir.join(name);
        
        if !path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "File does not exist"));
        }
        
        if !path.is_file() {
            return Err(io::Error::new(io::ErrorKind::InvalidInput, "Path is not a file"));
        }
        
        let mut file = fs::OpenOptions::new()
            .append(true)
            .open(&path)?;
        
        file.write_all(content.as_bytes())?;
        file.write_all(b"\n")?;
        
        self.operation_count += 1;
        
        println!("Appended to file: {}", path.display());
        Ok(())
    }
    
    // Delete file or directory
    fn delete(&mut self, name: &str) -> io::Result<()> {
        let path = self.current_dir.join(name);
        
        if !path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "Path does not exist"));
        }
        
        if path.is_dir() {
            fs::remove_dir(&path)?;
            println!("Deleted directory: {}", path.display());
        } else {
            fs::remove_file(&path)?;
            println!("Deleted file: {}", path.display());
        }
        
        self.operation_count += 1;
        Ok(())
    }
    
    // Copy file
    fn copy_file(&mut self, source: &str, destination: &str) -> io::Result<()> {
        let source_path = self.current_dir.join(source);
        let dest_path = self.current_dir.join(destination);
        
        if !source_path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "Source file does not exist"));
        }
        
        if !source_path.is_file() {
            return Err(io::Error::new(io::ErrorKind::InvalidInput, "Source is not a file"));
        }
        
        if dest_path.exists() {
            return Err(io::Error::new(io::ErrorKind::AlreadyExists, "Destination already exists"));
        }
        
        fs::copy(&source_path, &dest_path)?;
        self.operation_count += 1;
        
        println!("Copied: {} -> {}", source_path.display(), dest_path.display());
        Ok(())
    }
    
    // Move/rename file or directory
    fn move_item(&mut self, source: &str, destination: &str) -> io::Result<()> {
        let source_path = self.current_dir.join(source);
        let dest_path = self.current_dir.join(destination);
        
        if !source_path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "Source does not exist"));
        }
        
        if dest_path.exists() {
            return Err(io::Error::new(io::ErrorKind::AlreadyExists, "Destination already exists"));
        }
        
        fs::rename(&source_path, &dest_path)?;
        self.operation_count += 1;
        
        println!("Moved: {} -> {}", source_path.display(), dest_path.display());
        Ok(())
    }
    
    // Get file information
    fn get_info(&self, name: &str) -> io::Result<()> {
        let path = self.current_dir.join(name);
        
        if !path.exists() {
            return Err(io::Error::new(io::ErrorKind::NotFound, "Path does not exist"));
        }
        
        let metadata = path.metadata()?;
        
        println!("\n=== File/Directory Information ===");
        println!("Path: {}", path.display());
        println!("{}", "=".repeat(60));
        println!("Type: {}", if metadata.is_dir() { "Directory" } else { "File" });
        println!("Size: {} bytes", metadata.len());
        
        if let Ok(modified) = metadata.modified() {
            println!("Modified: {:?}", modified);
        }
        
        if let Ok(created) = metadata.created() {
            println!("Created: {:?}", created);
        }
        
        if let Ok(accessed) = metadata.accessed() {
            println!("Accessed: {:?}", accessed);
        }
        
        if metadata.is_file() {
            if let Ok(file_name) = path.file_name() {
                if let Some(extension) = file_name.to_str() {
                    println!("Extension: {}", extension);
                }
            }
        }
        
        println!("Read-only: {}", metadata.permissions().readonly());
        println!("{}", "=".repeat(60));
        
        Ok(())
    }
    
    // Search for files
    fn search_files(&self, pattern: &str) -> io::Result<()> {
        println!("\n=== Search Results for '{}' ===", pattern);
        println!("Searching in: {}", self.current_dir.display());
        println!("{}", "=".repeat(60));
        
        let mut found_files = Vec::new();
        let mut found_dirs = Vec::new();
        
        self.search_recursive(&self.current_dir, pattern, &mut found_files, &mut found_dirs)?;
        
        if found_files.is_empty() && found_dirs.is_empty() {
            println!("No files or directories found matching '{}'", pattern);
        } else {
            if !found_dirs.is_empty() {
                println!("Directories:");
                for dir in &found_dirs {
                    println!("  [DIR]  {}", dir.display());
                }
            }
            
            if !found_files.is_empty() {
                if !found_dirs.is_empty() {
                    println!();
                }
                println!("Files:");
                for file in &found_files {
                    if let Ok(metadata) = file.metadata() {
                        println!("  [FILE] {:<40} {:>10} bytes", 
                                file.file_name().to_string_lossy(), 
                                metadata.len());
                    }
                }
            }
        }
        
        println!("Found: {} directories, {} files", found_dirs.len(), found_files.len());
        println!("{}", "=".repeat(60));
        
        Ok(())
    }
    
    // Recursive search helper
    fn search_recursive(&self, dir: &Path, pattern: &str, 
                       files: &mut Vec<PathBuf>, dirs: &mut Vec<PathBuf>) -> io::Result<()> {
        let entries = fs::read_dir(dir)?;
        
        for entry in entries {
            let entry = entry?;
            let path = entry.path();
            let name = entry.file_name().to_string_lossy();
            
            if name.to_lowercase().contains(&pattern.to_lowercase()) {
                if path.is_dir() {
                    dirs.push(path.clone());
                } else {
                    files.push(path.clone());
                }
            }
            
            if path.is_dir() {
                // Recursively search subdirectories
                self.search_recursive(&path, pattern, files, dirs)?;
            }
        }
        
        Ok(())
    }
    
    // Display current directory
    fn display_current_dir(&self) {
        println!("Current directory: {}", self.current_dir.display());
        println!("Operations performed: {}", self.operation_count);
    }
    
    // Show statistics
    fn show_statistics(&self) -> io::Result<()> {
        println!("\n=== File Manager Statistics ===");
        self.display_current_dir();
        
        let entries = fs::read_dir(&self.current_dir)?;
        let mut file_count = 0;
        let mut dir_count = 0;
        let mut total_size = 0u64;
        
        for entry in entries {
            let entry = entry?;
            let metadata = entry.metadata()?;
            
            if metadata.is_dir() {
                dir_count += 1;
            } else {
                file_count += 1;
                total_size += metadata.len();
            }
        }
        
        println!("Files in current directory: {}", file_count);
        println!("Directories in current directory: {}", dir_count);
        println!("Total size of files: {} bytes", total_size);
        println!("Total size: {:.2} MB", total_size as f64 / 1_048_576.0);
        println!("Operations performed: {}", self.operation_count);
        println!("============================");
        
        Ok(())
    }
}

// Command structure
struct Command {
    name: String,
    description: String,
    usage: String,
}

impl Command {
    fn new(name: &str, description: &str, usage: &str) -> Self {
        Command {
            name: name.to_string(),
            description: description.to_string(),
            usage: usage.to_string(),
        }
    }
}

// Display help
fn display_help(commands: &[Command]) {
    println!("\n=== FILE MANAGER HELP ===");
    println!("{}", "=".repeat(60));
    
    for cmd in commands {
        println!("{:<15} - {}", cmd.name, cmd.description);
        println!("{<15}   Usage: {}", "", cmd.usage);
        println!();
    }
    
    println!("Additional notes:");
    println("- All paths are relative to current directory");
    println!("Use '..' to go to parent directory");
    println("- File operations are safe with Rust's error handling");
    println!("No data corruption or memory leaks!");
    println!("{}", "=".repeat(60));
}

// Get user input
fn get_input(prompt: &str) -> String {
    print!("{}", prompt);
    io::stdout().flush().unwrap();
    
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    
    input.trim().to_string()
}

// Parse command arguments
fn parse_command(input: &str) -> (String, Vec<String>) {
    let parts: Vec<&str> = input.trim().split_whitespace().collect();
    
    if parts.is_empty() {
        return (String::new(), Vec::new());
    }
    
    let command = parts[0].to_lowercase();
    let args: Vec<String> = parts[1..].iter().map(|s| s.to_string()).collect();
    
    (command, args)
}

// Main application loop
fn main() -> io::Result<()> {
    println!("========================================");
    println!("    RUST FILE MANAGER - LEVEL 3");
    println!("========================================");
    println!("Welcome to safe file management in Rust!");
    println!("This program demonstrates:");
    println!("- Safe file I/O operations");
    println!("- Error handling with Result types");
    println!("- Path manipulation and validation");
    println!("- Memory safety without garbage collection");
    println!("- Human-like code with personality!");
    println!("========================================");
    
    // Initialize file manager
    let mut file_manager = FileManager::new()?;
    
    // Define available commands
    let commands = vec![
        Command::new("ls", "List directory contents", "ls"),
        Command::new("cd", "Change directory", "cd <directory>"),
        Command::new("mkdir", "Create directory", "mkdir <name>"),
        Command::new("touch", "Create file", "touch <name> [content]"),
        Command::new("cat", "Read file contents", "cat <filename>"),
        Command::new("write", "Write to file", "write <filename> <content>"),
        Command::new("append", "Append to file", "append <filename> <content>"),
        Command::new("rm", "Delete file or directory", "rm <name>"),
        Command::new("cp", "Copy file", "cp <source> <destination>"),
        Command::new("mv", "Move/rename file or directory", "mv <source> <destination>"),
        Command::new("info", "Show file/directory information", "info <name>"),
        Command::new("search", "Search for files", "search <pattern>"),
        Command::new("pwd", "Show current directory", "pwd"),
        Command::new("stats", "Show statistics", "stats"),
        Command::new("help", "Show help", "help"),
        Command::new("exit", "Exit program", "exit"),
    ];
    
    println!("Type 'help' for available commands.");
    
    loop {
        // Show prompt
        println!();
        file_manager.display_current_dir();
        let input = get_input("file-manager> ");
        
        if input.is_empty() {
            continue;
        }
        
        let (command, args) = parse_command(&input);
        
        match command.as_str() {
            "ls" => {
                file_manager.list_directory()?;
            }
            
            "cd" => {
                if args.is_empty() {
                    println!("Usage: cd <directory>");
                    continue;
                }
                match file_manager.change_directory(&args[0]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "mkdir" => {
                if args.is_empty() {
                    println!("Usage: mkdir <name>");
                    continue;
                }
                match file_manager.create_directory(&args[0]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "touch" => {
                if args.is_empty() {
                    println!("Usage: touch <name> [content]");
                    continue;
                }
                
                let content = if args.len() > 1 {
                    Some(args[1..].join(" ").as_str())
                } else {
                    None
                };
                
                match file_manager.create_file(&args[0], content) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "cat" => {
                if args.is_empty() {
                    println!("Usage: cat <filename>");
                    continue;
                }
                match file_manager.read_file(&args[0]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "write" => {
                if args.len() < 2 {
                    println!("Usage: write <filename> <content>");
                    continue;
                }
                
                let content = args[1..].join(" ");
                match file_manager.write_file(&args[0], &content) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "append" => {
                if args.len() < 2 {
                    println!("Usage: append <filename> <content>");
                    continue;
                }
                
                let content = args[1..].join(" ");
                match file_manager.append_file(&args[0], &content) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "rm" => {
                if args.is_empty() {
                    println!("Usage: rm <name>");
                    continue;
                }
                match file_manager.delete(&args[0]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "cp" => {
                if args.len() < 2 {
                    println!("Usage: cp <source> <destination>");
                    continue;
                }
                match file_manager.copy_file(&args[0], &args[1]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "mv" => {
                if args.len() < 2 {
                    println!("Usage: mv <source> <destination>");
                    continue;
                }
                match file_manager.move_item(&args[0], &args[1]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "info" => {
                if args.is_empty() {
                    println!("Usage: info <name>");
                    continue;
                }
                match file_manager.get_info(&args[0]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "search" => {
                if args.is_empty() {
                    println!("Usage: search <pattern>");
                    continue;
                }
                match file_manager.search_files(&args[0]) {
                    Ok(_) => {}
                    Err(e) => println!("Error: {}", e),
                }
            }
            
            "pwd" => {
                file_manager.display_current_dir();
            }
            
            "stats" => {
                file_manager.show_statistics()?;
            }
            
            "help" => {
                display_help(&commands);
            }
            
            "exit" | "quit" => {
                println!("Thanks for using Rust File Manager!");
                println!("You've experienced safe file operations!");
                file_manager.show_statistics()?;
                break;
            }
            
            _ => {
                println!("Unknown command: '{}'", command);
                println!("Type 'help' for available commands.");
            }
        }
    }
    
    println!("\nYou've learned:");
    println!("- Safe file I/O operations in Rust");
    println!("- Error handling with Result types");
    println!("- Path manipulation and validation");
    println!("- Command-line interface design");
    println!("- Memory safety without garbage collection");
    println!("- Human-readable, maintainable code!");
    
    Ok(())
}
