/*
 * Rust Calculator - Level 2: Safe Systems Programming
 * 
 * Learn modern Rust through a practical calculator application.
 * This demonstrates Rust's safety guarantees and modern syntax.
 * 
 * Key concepts:
 * - Pattern matching for operations
 * - Result type for error handling
 * - Ownership and borrowing
 * - Structs and impl blocks
 * - Enums for operation types
 * - Input validation and error recovery
 */

use std::io::{self, Write};
use std::collections::HashMap;

// Enum for calculator operations
#[derive(Debug, Clone, Copy)]
enum Operation {
    Add,
    Subtract,
    Multiply,
    Divide,
    Power,
    SquareRoot,
    Percentage,
}

impl Operation {
    fn from_char(c: char) -> Option<Self> {
        match c {
            '+' => Some(Operation::Add),
            '-' => Some(Operation::Subtract),
            '*' => Some(Operation::Multiply),
            '/' => Some(Operation::Divide),
            '^' => Some(Operation::Power),
            'r' => Some(Operation::SquareRoot),
            '%' => Some(Operation::Percentage),
            _ => None,
        }
    }
    
    fn symbol(&self) -> char {
        match self {
            Operation::Add => '+',
            Operation::Subtract => '-',
            Operation::Multiply => '*',
            Operation::Divide => '/',
            Operation::Power => '^',
            Operation::SquareRoot => 'r',
            Operation::Percentage => '%',
        }
    }
    
    fn description(&self) -> &'static str {
        match self {
            Operation::Add => "Addition",
            Operation::Subtract => "Subtraction",
            Operation::Multiply => "Multiplication",
            Operation::Divide => "Division",
            Operation::Power => "Power",
            Operation::SquareRoot => "Square Root",
            Operation::Percentage => "Percentage",
        }
    }
}

// Calculator struct with memory and history
#[derive(Debug)]
struct Calculator {
    memory: f64,
    last_result: Option<f64>,
    history: Vec<String>,
    calculation_count: u32,
}

impl Calculator {
    // Constructor
    fn new() -> Self {
        Calculator {
            memory: 0.0,
            last_result: None,
            history: Vec::new(),
            calculation_count: 0,
        }
    }
    
    // Perform calculation with Result type for error handling
    fn calculate(&mut self, op: Operation, a: f64, b: Option<f64>) -> Result<f64, String> {
        let result = match op {
            Operation::Add => a + b.unwrap_or(0.0),
            Operation::Subtract => a - b.unwrap_or(0.0),
            Operation::Multiply => a * b.unwrap_or(1.0),
            Operation::Divide => {
                let divisor = b.ok_or_else(|| "Division requires two numbers".to_string())?;
                if divisor == 0.0 {
                    return Err("Cannot divide by zero!".to_string());
                }
                a / divisor
            },
            Operation::Power => {
                let exponent = b.ok_or_else(|| "Power operation requires two numbers".to_string())?;
                if a < 0.0 && exponent.fract() != 0.0 {
                    return Err("Cannot calculate fractional power of negative number!".to_string());
                }
                a.powf(exponent)
            },
            Operation::SquareRoot => {
                if a < 0.0 {
                    return Err("Cannot calculate square root of negative number!".to_string());
                }
                a.sqrt()
            },
            Operation::Percentage => {
                let percent = b.ok_or_else(|| "Percentage requires two numbers".to_string())?;
                a * (percent / 100.0)
            },
        };
        
        // Update state
        self.last_result = Some(result);
        self.calculation_count += 1;
        
        // Add to history
        let history_entry = match op {
            Operation::SquareRoot => format!("sqrt({}) = {}", a, result),
            Operation::Percentage => format!("{}% of {} = {}", b.unwrap_or(0.0), a, result),
            _ => format!("{} {} {} = {}", a, op.symbol(), b.unwrap_or(0.0), result),
        };
        self.history.push(history_entry);
        
        Ok(result)
    }
    
    // Memory operations
    fn memory_store(&mut self, value: f64) {
        self.memory = value;
        println!("Stored {} in memory", value);
    }
    
    fn memory_recall(&self) -> f64 {
        println!("Recalled {} from memory", self.memory);
        self.memory
    }
    
    fn memory_clear(&mut self) {
        self.memory = 0.0;
        println!("Memory cleared");
    }
    
    fn memory_add(&mut self, value: f64) {
        self.memory += value;
        println!("Added {} to memory. New value: {}", value, self.memory);
    }
    
    // Getters
    fn get_last_result(&self) -> Option<f64> {
        self.last_result
    }
    
    fn get_calculation_count(&self) -> u32 {
        self.calculation_count
    }
    
    // Display history
    fn display_history(&self) {
        println!("\n=== CALCULATION HISTORY ===");
        if self.history.is_empty() {
            println!("No calculations yet!");
        } else {
            for (i, entry) in self.history.iter().enumerate() {
                println!("{}. {}", i + 1, entry);
            }
        }
        println!("Total calculations: {}", self.calculation_count);
    }
    
    // Display status
    fn display_status(&self) {
        println!("\n=== CALCULATOR STATUS ===");
        println!("Memory: {}", self.memory);
        match self.last_result {
            Some(result) => println!("Last Result: {}", result),
            None => println!("Last Result: None"),
        }
        println!("Calculations: {}", self.calculation_count);
        println!("History entries: {}", self.history.len());
    }
    
    // Reset calculator
    fn reset(&mut self) {
        self.memory = 0.0;
        self.last_result = None;
        self.history.clear();
        self.calculation_count = 0;
        println!("Calculator reset to initial state");
    }
}

// Input validation functions
fn get_valid_number(prompt: &str) -> f64 {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read input");
        
        match input.trim().parse::<f64>() {
            Ok(num) => return num,
            Err(_) => println!("Invalid input! Please enter a valid number."),
        }
    }
}

fn get_valid_operation() -> Operation {
    loop {
        print!("Enter operation (+, -, *, /, ^, r, %): ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read input");
        
        let input = input.trim();
        if input.len() == 1 {
            if let Some(op) = Operation::from_char(input.chars().next().unwrap()) {
                return op;
            }
        }
        
        println!("Invalid operation! Valid operations: +, -, *, /, ^(power), r(sqrt), %(percent)");
    }
}

fn get_valid_choice(min: u32, max: u32) -> u32 {
    loop {
        print!("Enter choice ({}-{}): ", min, max);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read input");
        
        match input.trim().parse::<u32>() {
            Ok(choice) if choice >= min && choice <= max => return choice,
            Ok(_) => println!("Choice out of range!"),
            Err(_) => println!("Invalid input! Please enter a number."),
        }
    }
}

// Memory operations menu
fn handle_memory_operations(calc: &mut Calculator) {
    loop {
        println!("\n=== MEMORY OPERATIONS ===");
        println!("1. Store in memory");
        println!("2. Recall from memory");
        println!("3. Clear memory");
        println!("4. Add to memory");
        println!("5. Back to calculator");
        
        let choice = get_valid_choice(1, 5);
        
        match choice {
            1 => {
                let value = get_valid_number("Enter value to store: ");
                calc.memory_store(value);
            },
            2 => {
                let value = calc.memory_recall();
                println!("Memory value: {}", value);
            },
            3 => {
                calc.memory_clear();
            },
            4 => {
                let value = get_valid_number("Enter value to add to memory: ");
                calc.memory_add(value);
            },
            5 => break,
        }
    }
}

// Display menu
fn display_menu() {
    println!("\n{}", "=".repeat(50));
    println!("       RUST CALCULATOR - LEVEL 2");
    println!("{}", "=".repeat(50));
    println!("Operations:");
    println!("  + : Addition");
    println!("  - : Subtraction");
    println!("  * : Multiplication");
    println!("  / : Division");
    println!("  ^ : Power (base^exponent)");
    println!("  r : Square Root");
    println!("  % : Percentage (value%percent)");
    println!("{}", "=".repeat(50));
}

// Main calculation function
fn perform_calculation(calc: &mut Calculator) {
    let op = get_valid_operation();
    
    let a = get_valid_number("Enter first number: ");
    
    let result = if op == Operation::SquareRoot {
        calc.calculate(op, a, None)
    } else if op == Operation::Percentage {
        let b = get_valid_number("Enter percentage: ");
        calc.calculate(op, a, Some(b))
    } else {
        let b = get_valid_number("Enter second number: ");
        calc.calculate(op, a, Some(b))
    };
    
    match result {
        Ok(value) => {
            println!("Result: {}", value);
            
            // Show additional info for percentage
            if op == Operation::Percentage {
                let b = get_valid_number("Enter percentage (for display): ");
                println!("{}% of {} = {}", b, a, value);
            }
        },
        Err(e) => println!("Error: {}", e),
    }
}

// Use last result
fn use_last_result(calc: &mut Calculator) {
    match calc.get_last_result() {
        Some(last_result) => {
            println!("Using last result: {}", last_result);
            
            let op = get_valid_operation();
            
            if op == Operation::SquareRoot {
                println!("Cannot use square root with last result only");
                return;
            }
            
            let b = get_valid_number("Enter second number: ");
            
            match calc.calculate(op, last_result, Some(b)) {
                Ok(result) => println!("{} {} {} = {}", last_result, op.symbol(), b, result),
                Err(e) => println!("Error: {}", e),
            }
        },
        None => println!("No previous result available!"),
    }
}

// Interactive calculator session
fn run_calculator() {
    let mut calc = Calculator::new();
    
    println!("Welcome to the Rust Calculator!");
    println!("This calculator demonstrates Rust's safety guarantees:");
    println!("- Memory safety without garbage collection");
    println!("- Compile-time error prevention");
    println!("- Pattern matching and error handling");
    println!("- Ownership and borrowing system");
    
    loop {
        display_menu();
        calc.display_status();
        
        println!("\nOptions:");
        println!("1. Perform calculation");
        println!("2. Use last result as first number");
        println!("3. View calculation history");
        println!("4. Memory operations");
        println!("5. View detailed status");
        println!("6. Reset calculator");
        println!("7. Exit");
        
        let choice = get_valid_choice(1, 7);
        
        match choice {
            1 => perform_calculation(&mut calc),
            2 => use_last_result(&mut calc),
            3 => calc.display_history(),
            4 => handle_memory_operations(&mut calc),
            5 => {
                calc.display_status();
                println!("\nRust Calculator Features:");
                println!("- Memory safety guaranteed at compile time");
                println!("- No null pointer exceptions");
                println!("- No data races");
                println!("- Pattern matching for all operations");
                println!("- Result type for error handling");
                println!("- Ownership system prevents memory leaks");
            },
            6 => calc.reset(),
            7 => {
                println!("\nFinal Statistics:");
                calc.display_status();
                println!("Thank you for using Rust Calculator!");
                println!("You've experienced safe systems programming!");
                break;
            },
        }
        
        println!("\nPress Enter to continue...");
        let mut _input = String::new();
        io::stdin().read_line(&mut _input).unwrap();
    }
}

// Main function
fn main() {
    println!("{}", "=".repeat(40));
    println!("    RUST CALCULATOR - LEVEL 2");
    println!("{}", "=".repeat(40));
    println!("Learn safe systems programming with Rust!");
    println!("This calculator demonstrates:");
    println!("- Memory safety without performance loss");
    println!("- Pattern matching and error handling");
    println!("- Ownership and borrowing system");
    println!("- Modern syntax and type safety");
    println!("- Zero-cost abstractions");
    println!("{}", "=".repeat(40));
    
    run_calculator();
}
