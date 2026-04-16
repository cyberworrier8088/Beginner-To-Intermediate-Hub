/*
 * Text Analyzer in Rust - Level 2: String Processing & Algorithms
 * 
 * Welcome to text analysis in Rust! This is where strings meet statistics.
 * Learn string manipulation, pattern matching, and algorithmic thinking.
 * 
 * Key concepts you'll learn:
 * - String manipulation and iteration
 * - Pattern matching with match expressions
 * - Collection operations and filtering
 * - Statistical analysis and counting
 * - Error handling with Option types
 * - Human-like code with detailed explanations!
 */

use std::collections::HashMap;
use std::io::{self, Write};

// Text analyzer structure
struct TextAnalyzer {
    text: String,
    original_text: String,
}

impl TextAnalyzer {
    // Create new text analyzer
    fn new(text: String) -> Self {
        println!("Creating text analyzer...");
        println!("Input text length: {} characters", text.len());
        
        TextAnalyzer {
            original_text: text.clone(),
            text,
        }
    }
    
    // Set new text
    fn set_text(&mut self, text: String) {
        println!("\n=== SETTING NEW TEXT ===");
        println!("New text length: {} characters", text.len());
        
        self.original_text = text.clone();
        self.text = text;
        
        println!("Text set successfully!");
        println!("========================");
    }
    
    // Reset to original text
    fn reset(&mut self) {
        println!("\n=== RESETTING TO ORIGINAL ===");
        let original_length = self.original_text.len();
        self.text = self.original_text.clone();
        
        println!("Reset to original text!");
        println!("Text length: {} characters", original_length);
        println!("=============================");
    }
    
    // Get character count
    fn get_character_count(&self) -> usize {
        println!("\n=== COUNTING CHARACTERS ===");
        let count = self.text.len();
        println!("Total characters: {}", count);
        println!("========================");
        count
    }
    
    // Get word count
    fn get_word_count(&self) -> usize {
        println!("\n=== COUNTING WORDS ===");
        
        let mut word_count = 0;
        let mut in_word = false;
        
        for char in self.text.chars() {
            if char.is_whitespace() {
                if in_word {
                    word_count += 1;
                    in_word = false;
                }
            } else {
                in_word = true;
            }
        }
        
        // Count last word if text doesn't end with whitespace
        if in_word {
            word_count += 1;
        }
        
        println!("Total words: {}", word_count);
        println!("==================");
        word_count
    }
    
    // Get line count
    fn get_line_count(&self) -> usize {
        println!("\n=== COUNTING LINES ===");
        
        let mut line_count = 1; // Start with 1 line
        
        for char in self.text.chars() {
            if char == '\n' {
                line_count += 1;
            }
        }
        
        println!("Total lines: {}", line_count);
        println!("=================");
        line_count
    }
    
    // Count specific character
    fn count_character(&self, target: char) -> usize {
        println!("\n=== COUNTING CHARACTER '{}' ===", target);
        
        let mut count = 0;
        
        for char in self.text.chars() {
            if char == target {
                count += 1;
            }
        }
        
        let percentage = if self.text.len() > 0 {
            (count as f64 / self.text.len() as f64) * 100.0
        } else {
            0.0
        };
        
        println!("Character '{}' appears {} times", target, count);
        println!("Percentage: {:.2}%", percentage);
        println!("=================================");
        count
    }
    
    // Count vowels and consonants
    fn count_vowels_consonants(&self) -> (usize, usize) {
        println!("\n=== COUNTING VOWELS AND CONSONANTS ===");
        
        let mut vowels = 0;
        let mut consonants = 0;
        
        for char in self.text.chars() {
            let lower_char = char.to_ascii_lowercase();
            
            match lower_char {
                'a' | 'e' | 'i' | 'o' | 'u' => vowels += 1,
                'b' | 'c' | 'd' | 'f' | 'g' | 'h' | 'j' | 'k' | 'l' | 'm' |
                'n' | 'p' | 'q' | 'r' | 's' | 't' | 'v' | 'w' | 'x' | 'y' | 'z' => consonants += 1,
                _ => {} // Ignore non-alphabetic characters
            }
        }
        
        let total_letters = vowels + consonants;
        let vowel_percentage = if total_letters > 0 {
            (vowels as f64 / total_letters as f64) * 100.0
        } else {
            0.0
        };
        
        println!("Vowels: {} ({:.2}%)", vowels, vowel_percentage);
        println!("Consonants: {} ({:.2}%)", consonants, 100.0 - vowel_percentage);
        println!("Total letters: {}", total_letters);
        println!("=================================");
        
        (vowels, consonants)
    }
    
    // Count digits and special characters
    fn count_digits_special(&self) -> (usize, usize) {
        println!("\n=== COUNTING DIGITS AND SPECIAL CHARACTERS ===");
        
        let mut digits = 0;
        let mut special = 0;
        
        for char in self.text.chars() {
            match char {
                '0'..='9' => digits += 1,
                _ => {
                    if !char.is_alphabetic() && !char.is_whitespace() {
                        special += 1;
                    }
                }
            }
        }
        
        let total_non_letters = digits + special;
        let digit_percentage = if total_non_letters > 0 {
            (digits as f64 / total_non_letters as f64) * 100.0
        } else {
            0.0
        };
        
        println!("Digits: {} ({:.2}%)", digits, digit_percentage);
        println!("Special characters: {} ({:.2}%)", special, 100.0 - digit_percentage);
        println!("Total non-letters: {}", total_non_letters);
        println!("===========================================");
        
        (digits, special)
    }
    
    // Get word frequency
    fn get_word_frequency(&self) -> HashMap<String, usize> {
        println!("\n=== CALCULATING WORD FREQUENCY ===");
        
        let mut frequency: HashMap<String, usize> = HashMap::new();
        let mut current_word = String::new();
        
        for char in self.text.chars() {
            if char.is_alphabetic() || char == '\'' {
                current_word.push(char.to_ascii_lowercase());
            } else if !current_word.is_empty() {
                *frequency.entry(current_word.clone()).or_insert(0) += 1;
                current_word.clear();
            }
        }
        
        // Add last word if exists
        if !current_word.is_empty() {
            *frequency.entry(current_word).or_insert(0) += 1;
        }
        
        println!("Found {} unique words", frequency.len());
        
        // Sort and display top words
        let mut sorted_words: Vec<_> = frequency.iter().collect();
        sorted_words.sort_by(|a, b| b.1.cmp(a.1));
        
        println!("Top 10 most frequent words:");
        println!("{:<20} {:>10}", "Word", "Count");
        println!("{}", "-".repeat(35));
        
        for (i, (word, count)) in sorted_words.iter().take(10).enumerate() {
            println!("{:<20} {:>10}", word, count);
        }
        
        println!("=================================");
        frequency
    }
    
    // Get character frequency
    fn get_character_frequency(&self) -> HashMap<char, usize> {
        println!("\n=== CALCULATING CHARACTER FREQUENCY ===");
        
        let mut frequency: HashMap<char, usize> = HashMap::new();
        
        for char in self.text.chars() {
            *frequency.entry(char).or_insert(0) += 1;
        }
        
        println!("Found {} unique characters", frequency.len());
        
        // Sort and display top characters
        let mut sorted_chars: Vec<_> = frequency.iter().collect();
        sorted_chars.sort_by(|a, b| b.1.cmp(a.1));
        
        println!("Top 10 most frequent characters:");
        println!("{:<10} {:>10} {:>10}", "Character", "Count", "Type");
        println!("{}", "-".repeat(35));
        
        for (char, count) in sorted_chars.iter().take(10) {
            let char_type = if char.is_alphabetic() {
                "Letter"
            } else if char.is_numeric() {
                "Digit"
            } else if char.is_whitespace() {
                "Space"
            } else {
                "Special"
            };
            
            println!("{:<10} {:>10} {:>10}", char, count, char_type);
        }
        
        println!("=========================================");
        frequency
    }
    
    // Find longest word
    fn find_longest_word(&self) -> Option<String> {
        println!("\n=== FINDING LONGEST WORD ===");
        
        let mut longest_word = String::new();
        let mut current_word = String::new();
        
        for char in self.text.chars() {
            if char.is_alphabetic() || char == '\'' {
                current_word.push(char);
            } else if !current_word.is_empty() {
                if current_word.len() > longest_word.len() {
                    longest_word = current_word.clone();
                }
                current_word.clear();
            }
        }
        
        // Check last word
        if current_word.len() > longest_word.len() {
            longest_word = current_word;
        }
        
        if longest_word.is_empty() {
            println!("No words found in text");
            println!("========================");
            None
        } else {
            println!("Longest word: '{}'", longest_word);
            println!("Length: {} characters", longest_word.len());
            println!("========================");
            Some(longest_word)
        }
    }
    
    // Convert to uppercase
    fn to_uppercase(&mut self) {
        println!("\n=== CONVERTING TO UPPERCASE ===");
        println!("Original length: {} characters", self.text.len());
        
        self.text = self.text.to_uppercase();
        
        println!("Converted to uppercase!");
        println!("New length: {} characters", self.text.len());
        println!("===============================");
    }
    
    // Convert to lowercase
    fn to_lowercase(&mut self) {
        println!("\n=== CONVERTING TO LOWERCASE ===");
        println!("Original length: {} characters", self.text.len());
        
        self.text = self.text.to_lowercase();
        
        println!("Converted to lowercase!");
        println!("New length: {} characters", self.text.len());
        println!("===============================");
    }
    
    // Remove whitespace
    fn remove_whitespace(&mut self) {
        println!("\n=== REMOVING WHITESPACE ===");
        println!("Original length: {} characters", self.text.len());
        
        let original_length = self.text.len();
        self.text = self.text.chars().filter(|c| !c.is_whitespace()).collect();
        
        let removed = original_length - self.text.len();
        println!("Removed {} whitespace characters", removed);
        println!("New length: {} characters", self.text.len());
        println!("=============================");
    }
    
    // Remove punctuation
    fn remove_punctuation(&mut self) {
        println!("\n=== REMOVING PUNCTUATION ===");
        println!("Original length: {} characters", self.text.len());
        
        let original_length = self.text.len();
        self.text = self.text.chars()
            .filter(|c| c.is_alphanumeric() || c.is_whitespace())
            .collect();
        
        let removed = original_length - self.text.len();
        println!("Removed {} punctuation characters", removed);
        println!("New length: {} characters", self.text.len());
        println!("==============================");
    }
    
    // Reverse text
    fn reverse_text(&mut self) {
        println!("\n=== REVERSING TEXT ===");
        println!("Original length: {} characters", self.text.len());
        
        self.text = self.text.chars().rev().collect();
        
        println!("Text reversed!");
        println!("New length: {} characters", self.text.len());
        println!("====================");
    }
    
    // Display current text
    fn display_text(&self) {
        println!("\n=== CURRENT TEXT ===");
        println!("Length: {} characters", self.text.len());
        println!("Content: \"{}\"", self.text);
        println!("==================");
    }
    
    // Display comprehensive statistics
    fn display_statistics(&self) {
        println!("\n" + "=".repeat(50));
        println!("    COMPREHENSIVE TEXT STATISTICS");
        println!("{}", "=".repeat(50));
        
        let char_count = self.get_character_count();
        let word_count = self.get_word_count();
        let line_count = self.get_line_count();
        
        let (vowels, consonants) = self.count_vowels_consonants();
        let (digits, special) = self.count_digits_special();
        
        println!("\nSUMMARY:");
        println!("Characters: {}", char_count);
        println!("Words: {}", word_count);
        println!("Lines: {}", line_count);
        println!("Vowels: {}", vowels);
        println!("Consonants: {}", consonants);
        println!("Digits: {}", digits);
        println!("Special: {}", special);
        
        if let Some(longest) = self.find_longest_word() {
            println!("Longest word: '{}'", longest);
        }
        
        println!("{}", "=".repeat(50));
    }
}

// Input validation functions
fn get_valid_string(prompt: &str) -> String {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        let trimmed = input.trim();
        if !trimmed.is_empty() {
            return trimmed.to_string();
        }
        
        println!("Error: Input cannot be empty. Please try again.");
    }
}

fn get_valid_character(prompt: &str) -> char {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        let trimmed = input.trim();
        if trimmed.len() == 1 {
            return trimmed.chars().next().unwrap();
        }
        
        println!("Error: Please enter exactly one character.");
    }
}

fn get_valid_choice(prompt: &str, min: usize, max: usize) -> usize {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim().parse::<usize>() {
            Ok(choice) if choice >= min && choice <= max => return choice,
            Ok(_) => println!("Error: Please enter a number between {} and {}.", min, max),
            Err(_) => println!("Error: Please enter a valid number."),
        }
    }
}

// Display program introduction
fn display_introduction() {
    println!("========================================");
    println!("    RUST TEXT ANALYZER");
    println!("========================================");
    println!("Welcome to text analysis in Rust!");
    println!("This program demonstrates:");
    println!("- String manipulation and iteration");
    println!("- Pattern matching with match expressions");
    println!("- Collection operations and filtering");
    println!("- Statistical analysis and counting");
    println!("- Error handling with Option types");
    println!("- Human-like code with detailed comments!");
    println!("========================================");
}

// Display main menu
fn display_menu() {
    println!("\n=== TEXT ANALYZER MENU ===");
    println!("1. Set new text");
    println!("2. Get character count");
    println!("3. Get word count");
    println!("4. Get line count");
    println!("5. Count specific character");
    println!("6. Count vowels and consonants");
    println!("7. Count digits and special characters");
    println!("8. Get word frequency");
    println!("9. Get character frequency");
    println!("10. Find longest word");
    println!("11. Convert to uppercase");
    println!("12. Convert to lowercase");
    println!("13. Remove whitespace");
    println!("14. Remove punctuation");
    println!("15. Reverse text");
    println!("16. Display current text");
    println!("17. Display comprehensive statistics");
    println!("18. Reset to original");
    println!("19. Exit");
    println!("=============================");
}

fn main() {
    display_introduction();
    
    // Create text analyzer with default text
    let mut analyzer = TextAnalyzer::new(
        "Hello, World! This is a sample text for analysis. It contains various characters, numbers 123, and punctuation marks!".to_string()
    );
    
    loop {
        display_menu();
        
        let choice = get_valid_choice("Enter your choice (1-19): ", 1, 19);
        
        match choice {
            1 => {
                let text = get_valid_string("Enter text to analyze: ");
                analyzer.set_text(text);
            }
            
            2 => {
                analyzer.get_character_count();
            }
            
            3 => {
                analyzer.get_word_count();
            }
            
            4 => {
                analyzer.get_line_count();
            }
            
            5 => {
                let target = get_valid_character("Enter character to count: ");
                analyzer.count_character(target);
            }
            
            6 => {
                analyzer.count_vowels_consonants();
            }
            
            7 => {
                analyzer.count_digits_special();
            }
            
            8 => {
                analyzer.get_word_frequency();
            }
            
            9 => {
                analyzer.get_character_frequency();
            }
            
            10 => {
                analyzer.find_longest_word();
            }
            
            11 => {
                analyzer.to_uppercase();
            }
            
            12 => {
                analyzer.to_lowercase();
            }
            
            13 => {
                analyzer.remove_whitespace();
            }
            
            14 => {
                analyzer.remove_punctuation();
            }
            
            15 => {
                analyzer.reverse_text();
            }
            
            16 => {
                analyzer.display_text();
            }
            
            17 => {
                analyzer.display_statistics();
            }
            
            18 => {
                analyzer.reset();
            }
            
            19 => {
                println!("\nThank you for using Rust Text Analyzer!");
                println!("You've learned:");
                println!("- String manipulation and iteration");
                println!("- Pattern matching with match expressions");
                println!("- Collection operations and filtering");
                println!("- Statistical analysis and counting");
                println!("- Error handling with Option types");
                println!("- Human-readable, maintainable code!");
                break;
            }
            
            _ => {
                println!("Error: Invalid choice. Please try again.");
            }
        }
        
        // Add a small pause for better user experience
        if choice != 19 {
            println!("\nPress Enter to continue...");
            let mut _pause = String::new();
            io::stdin().read_line(&mut _pause).unwrap();
        }
    }
}
