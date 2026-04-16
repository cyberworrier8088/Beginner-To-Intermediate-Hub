/*
 * Hello World in Rust - Level 1: Safe Systems Programming
 * 
 * Welcome to Rust! This is where safety meets performance.
 * Rust gives you the speed of C++ with memory safety guarantees.
 * 
 * Key concepts you'll learn:
 * - Rust ownership system (no garbage collector needed!)
 * - Pattern matching and error handling
 * - Immutable by default
 * - Modern syntax with strong typing
 * - Cargo package manager
 * - Memory safety without performance loss
 */

// Import standard library modules
use std::io::{self, Write};  // For input/output
use std::collections::HashMap;  // For hash maps
use std::vec::Vec;  // For vectors

// A simple struct to demonstrate Rust's type system
#[derive(Debug)]  // Automatically generate debug formatting
struct Greeter {
    name: String,
    greeting_count: u32,
}

impl Greeter {
    // Constructor function (associated function)
    fn new(name: String) -> Self {
        println!("Greeter created for: {}", name);
        Greeter {
            name,
            greeting_count: 0,
        }
    }
    
    // Method to say hello
    fn say_hello(&mut self) {
        self.greeting_count += 1;
        println!("Hello, {}! (Greeting #{})", self.name, self.greeting_count);
    }
    
    // Method to say goodbye
    fn say_goodbye(&self) {
        println!("Goodbye, {}! Thanks for visiting!", self.name);
    }
    
    // Getter method
    fn get_name(&self) -> &str {
        &self.name
    }
    
    // Getter for greeting count
    fn get_greeting_count(&self) -> u32 {
        self.greeting_count
    }
}

// Function to demonstrate basic Rust features
fn demonstrate_basics() {
    println!("\n=== RUST BASICS ===");
    
    // Variable binding with type inference
    let number = 42;        // i32 (inferred)
    let pi: f64 = 3.14159;  // Explicit type
    let message = "Rust is awesome!";
    
    println!("Number: {}", number);
    println!("Pi: {}", pi);
    println!("Message: {}", message);
    
    // Mutable variables
    let mut counter = 0;
    println!("Initial counter: {}", counter);
    counter += 1;
    println!("Updated counter: {}", counter);
    
    // Constants (must have type)
    const MAX_USERS: u32 = 1000;
    println!("Maximum users: {}", MAX_USERS);
}

// Function to demonstrate ownership and borrowing
fn demonstrate_ownership() {
    println!("\n=== OWNERSHIP AND BORROWING ===");
    
    let s1 = String::from("hello");
    let s2 = s1;  // s1 is moved to s2 (s1 is no longer valid)
    
    // println!("{}", s1);  // This would cause a compile error!
    println!("s2: {}", s2);
    
    // Borrowing with references
    let s3 = String::from("world");
    let len = calculate_length(&s3);  // Borrow s3
    
    println!("Length of '{}': {}", s3, len);  // s3 is still valid
    
    // Mutable borrowing
    let mut s4 = String::from("mutable");
    change_string(&mut s4);
    println!("Changed string: {}", s4);
}

fn calculate_length(s: &String) -> usize {
    s.len()
}

fn change_string(s: &mut String) {
    s.push_str(" and changed!");
}

// Function to demonstrate pattern matching
fn demonstrate_pattern_matching() {
    println!("\n=== PATTERN MATCHING ===");
    
    let number = 42;
    
    match number {
        0 => println!("Zero!"),
        1 => println!("One!"),
        2 | 3 | 5 | 7 | 11 => println!("Prime number!"),
        13..=19 => println!("Teen!"),
        _ => println!("Something else: {}", number),
    }
    
    // Matching with Option
    let maybe_number = Some(42);
    
    match maybe_number {
        Some(n) => println!("Found number: {}", n),
        None => println!("No number found!"),
    }
    
    // If let for simpler matching
    if let Some(n) = maybe_number {
        println!("If let found: {}", n);
    }
}

// Function to demonstrate vectors and collections
fn demonstrate_collections() {
    println!("\n=== COLLECTIONS ===");
    
    // Vectors (dynamic arrays)
    let mut numbers: Vec<i32> = vec![1, 2, 3, 4, 5];
    
    println!("Original vector: {:?}", numbers);
    
    numbers.push(6);
    numbers.push(7);
    
    println!("After pushing: {:?}", numbers);
    
    // Iterating over vector
    println!("Iterating:");
    for num in &numbers {
        println!("  {}", num);
    }
    
    // Hash maps
    let mut scores = HashMap::new();
    scores.insert("Alice", 95);
    scores.insert("Bob", 87);
    scores.insert("Charlie", 92);
    
    println!("\nScores:");
    for (name, score) in &scores {
        println!("  {}: {}", name, score);
    }
    
    // Accessing hash map values
    match scores.get("Alice") {
        Some(score) => println!("Alice's score: {}", score),
        None => println!("Alice not found!"),
    }
}

// Function to demonstrate error handling
fn demonstrate_error_handling() {
    println!("\n=== ERROR HANDLING ===");
    
    // Result type for operations that might fail
    match divide(10.0, 2.0) {
        Ok(result) => println!("10 / 2 = {}", result),
        Err(e) => println!("Error: {}", e),
    }
    
    match divide(10.0, 0.0) {
        Ok(result) => println!("10 / 0 = {}", result),
        Err(e) => println!("Error: {}", e),
    }
    
    // Using unwrap_or for default values
    let result = divide(5.0, 2.0).unwrap_or(0.0);
    println!("5 / 2 (with default) = {}", result);
    
    // Using expect for better error messages
    let result = divide(8.0, 4.0).expect("Division should work!");
    println!("8 / 4 (with expect) = {}", result);
}

fn divide(a: f64, b: f64) -> Result<f64, String> {
    if b == 0.0 {
        Err("Cannot divide by zero!".to_string())
    } else {
        Ok(a / b)
    }
}

// Function to demonstrate string manipulation
fn demonstrate_strings() {
    println!("\n=== STRING MANIPULATION ===");
    
    let mut text = String::from("Rust is powerful and safe");
    
    println!("Original: {}", text);
    println!("Length: {}", text.len());
    
    // Push characters
    text.push('!');
    println!("After push: {}", text);
    
    // Push string slice
    text.push_str(" and fast!");
    println!("After push_str: {}", text);
    
    // String slicing
    let slice = &text[0..12];
    println!("First 12 chars: {}", slice);
    
    // Replace
    let replaced = text.replace("powerful", "awesome");
    println!("Replaced: {}", replaced);
    
    // Split
    let words: Vec<&str> = text.split_whitespace().collect();
    println!("Words: {:?}", words);
    
    // Format strings
    let formatted = format!("{} has {} words", text, words.len());
    println!("Formatted: {}", formatted);
}

// Interactive function with user input
fn interactive_demo() {
    println!("\n=== INTERACTIVE DEMO ===");
    
    println!("Enter your name:");
    let mut name = String::new();
    
    io::stdout().flush().unwrap();  // Ensure prompt is displayed
    io::stdin().read_line(&mut name).expect("Failed to read line");
    
    let name = name.trim();  // Remove newline and whitespace
    
    println!("Enter your age:");
    let mut age_input = String::new();
    io::stdin().read_line(&mut age_input).expect("Failed to read line");
    
    let age: u32 = match age_input.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Invalid age, using 0 as default");
            0
        }
    };
    
    println!("Enter your favorite programming language:");
    let mut language = String::new();
    io::stdin().read_line(&mut language).expect("Failed to read line");
    let language = language.trim();
    
    // Create greeter
    let mut greeter = Greeter::new(name.to_string());
    
    println!("\nHello, {}!", greeter.get_name());
    println!("You are {} years old.", age);
    println!("Your favorite language is {}.", language);
    
    // Give personalized response
    match language {
        "Rust" => println!("Excellent choice! Rust is the future of systems programming!"),
        "C++" => println!("C++ is powerful! Rust improves on many of its concepts!"),
        "Python" => println!("Python is great! Rust can be used for Python extensions!"),
        "Java" => println!("Java is widely used! Rust offers better memory safety!"),
        _ => println!("{} is interesting! Rust might surprise you!", language),
    }
    
    greeter.say_hello();
    greeter.say_goodbye();
}

// Function to demonstrate advanced features
fn demonstrate_advanced() {
    println!("\n=== ADVANCED RUST FEATURES ===");
    
    // Closures (anonymous functions)
    let numbers = vec![1, 2, 3, 4, 5];
    let doubled: Vec<i32> = numbers.iter().map(|x| x * 2).collect();
    
    println!("Original: {:?}", numbers);
    println!("Doubled: {:?}", doubled);
    
    // Filter
    let evens: Vec<i32> = numbers.iter().filter(|&&x| x % 2 == 0).cloned().collect();
    println!("Even numbers: {:?}", evens);
    
    // Option and Result chaining
    let maybe_value = Some(42);
    let result = maybe_value
        .filter(|&x| x > 40)
        .map(|x| x * 2)
        .unwrap_or(0);
    
    println!("Chained operations result: {}", result);
    
    // Struct with methods
    #[derive(Debug)]
    struct Point {
        x: f64,
        y: f64,
    }
    
    impl Point {
        fn new(x: f64, y: f64) -> Self {
            Point { x, y }
        }
        
        fn distance_from_origin(&self) -> f64 {
            (self.x.powi(2) + self.y.powi(2)).sqrt()
        }
        
        fn translate(&mut self, dx: f64, dy: f64) {
            self.x += dx;
            self.y += dy;
        }
    }
    
    let mut point = Point::new(3.0, 4.0);
    println!("Point: {:?}", point);
    println!("Distance from origin: {}", point.distance_from_origin());
    
    point.translate(1.0, 2.0);
    println!("After translation: {:?}", point);
    println!("New distance: {}", point.distance_from_origin());
}

// Main function - program entry point
fn main() {
    println!("========================================");
    println!("    HELLO WORLD IN RUST");
    println!("========================================");
    println!("Welcome to Rust programming!");
    println!("This demo showcases modern Rust features:");
    println!("- Memory safety without garbage collection");
    println!("- Pattern matching and error handling");
    println!("- Ownership system and borrowing");
    println!("- Modern syntax and strong typing");
    println!("- Zero-cost abstractions");
    
    // Basic hello world
    println!("\nHello, World!");
    
    // Run all demonstrations
    demonstrate_basics();
    demonstrate_ownership();
    demonstrate_pattern_matching();
    demonstrate_collections();
    demonstrate_error_handling();
    demonstrate_strings();
    demonstrate_advanced();
    
    // Interactive demo
    interactive_demo();
    
    println!("\n========================================");
    println!("    RUST DEMO COMPLETE!");
    println!("========================================");
    println!("You've learned:");
    println!("1. Basic Rust syntax and type system");
    println!("2. Ownership, borrowing, and lifetimes");
    println!("3. Pattern matching and error handling");
    println!("4. Collections (vectors, hash maps)");
    println!("5. String manipulation and formatting");
    println!("6. Closures and functional programming");
    println!("7. Structs and methods");
    println!("8. Memory safety guarantees");
    println!("9. Zero-cost abstractions");
    println!("10. Modern systems programming");
    
    println!("\nReady for more Rust challenges?");
    println!("Try the calculator, game, or systems programming projects!");
    
    println!("\nKey takeaways:");
    println!("- Rust prevents entire classes of bugs at compile time");
    println!("- No null pointer exceptions!");
    println!("- No data races!");
    println!("- Memory safe without garbage collection!");
    println!("- Performance comparable to C and C++!");
}
