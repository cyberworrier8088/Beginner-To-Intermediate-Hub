# Rust Text Analyzer - Level 2

## Overview
A comprehensive text analysis tool demonstrating Rust's pattern matching, collection operations, and statistical analysis capabilities.

## Features
- **Text Statistics**: Character, word, and line counting
- **Character Analysis**: Vowel/consonant counting, digit/special character analysis
- **Frequency Analysis**: Word and character frequency with sorting
- **Pattern Matching**: Rust's match expressions for character classification
- **String Manipulation**: Case conversion, whitespace/punctuation removal
- **Error Handling**: Option types for robust error management
- **Human-Like Code**: Detailed comments explaining each operation

## Learning Objectives
- String manipulation and iteration in Rust
- Pattern matching with match expressions
- Collection operations and filtering
- Statistical analysis and counting
- Error handling with Option types
- HashMap usage for frequency counting
- Human-like code with detailed explanations

## Prerequisites
- Rust 1.70+ (2021 edition)
- Cargo package manager
- Basic understanding of Rust syntax

## Installation & Setup

### Install Rust (if not already installed)
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source ~/.cargo/env
```

### Compilation & Running
```bash
# Navigate to project
cd Projects/Rust/Beginner-Projects/text-analyzer/analyze-1/

# Run with Cargo (recommended)
cargo run

# Or compile and run manually
rustc main.rs
./main
```

## Usage
1. Run the program
2. Choose from the main menu:
   - `1` - Set new text
   - `2` - Get character count
   - `3` - Get word count
   - `4` - Get line count
   - `5` - Count specific character
   - `6` - Count vowels and consonants
   - `7` - Count digits and special characters
   - `8` - Get word frequency
   - `9` - Get character frequency
   - `10` - Find longest word
   - `11` - Convert to uppercase
   - `12` - Convert to lowercase
   - `13` - Remove whitespace
   - `14` - Remove punctuation
   - `15` - Reverse text
   - `16` - Display current text
   - `17` - Display comprehensive statistics
   - `18` - Reset to original
   - `19` - Exit program

## Example Session
```
    RUST TEXT ANALYZER
========================================
Welcome to text analysis in Rust!

=== TEXT ANALYZER MENU ===
1. Set new text
2. Get character count
3. Get word count
4. Get line count
5. Count specific character
6. Count vowels and consonants
7. Count digits and special characters
8. Get word frequency
9. Get character frequency
10. Find longest word
11. Convert to uppercase
12. Convert to lowercase
13. Remove whitespace
14. Remove punctuation
15. Reverse text
16. Display current text
17. Display comprehensive statistics
18. Reset to original
19. Exit

Choice: 2

=== COUNTING CHARACTERS ===
Total characters: 27
========================

Choice: 6

=== COUNTING VOWELS AND CONSONANTS ===
Vowels: 11 (40.7%)
Consonants: 12 (44.4%)
Total letters: 23
=================================
```

## Code Structure
```rust
struct TextAnalyzer {
    text: String,
    original_text: String,
}

impl TextAnalyzer {
    // Core analysis methods
    fn get_character_count(&self) -> usize;
    fn get_word_count(&self) -> usize;
    fn get_line_count(&self) -> usize;
    fn count_character(&self, target: char) -> usize;
    
    // Character analysis methods
    fn count_vowels_consonants(&self) -> (usize, usize);
    fn count_digits_special(&self) -> (usize, usize);
    
    // Frequency analysis methods
    fn get_word_frequency(&self) -> HashMap<String, usize>;
    fn get_character_frequency(&self) -> HashMap<char, usize>;
    
    // Text manipulation methods
    fn to_uppercase(&mut self);
    fn to_lowercase(&mut self);
    fn remove_whitespace(&mut self);
    fn remove_punctuation(&mut self);
    fn reverse_text(&mut self);
    
    // Utility methods
    fn find_longest_word(&self) -> Option<String>;
    fn display_statistics(&self);
}
```

## Key Concepts Demonstrated
1. **String Manipulation**: Iteration, case conversion, filtering
2. **Pattern Matching**: Match expressions for character classification
3. **Collection Operations**: HashMap usage, sorting, filtering
4. **Statistical Analysis**: Frequency counting, percentage calculations
5. **Error Handling**: Option types for safe operations
6. **Memory Safety**: Rust's ownership system in action
7. **Human-Like Code**: Detailed comments and user feedback

## Pattern Matching Examples
```rust
// Character classification with match
match lower_char {
    'a' | 'e' | 'i' | 'o' | 'u' => vowels += 1,
    'b' | 'c' | 'd' | 'f' | 'g' | 'h' | 'j' | 'k' | 'l' | 'm' |
    'n' | 'p' | 'q' | 'r' | 's' | 't' | 'v' | 'w' | 'x' | 'y' | 'z' => consonants += 1,
    _ => {} // Ignore non-alphabetic characters
}

// Character type classification
match char {
    '0'..='9' => digits += 1,
    _ => {
        if !char.is_alphabetic() && !char.is_whitespace() {
            special += 1;
        }
    }
}
```

## Collection Operations
```rust
// Word frequency analysis
let mut frequency: HashMap<String, usize> = HashMap::new();

// Sort and display results
let mut sorted_words: Vec<_> = frequency.iter().collect();
sorted_words.sort_by(|a, b| b.1.cmp(a.1));

// Display top results
for (i, (word, count)) in sorted_words.iter().take(10).enumerate() {
    println!("{:<20} {:>10}", word, count);
}
```

## Performance Considerations
- **Time Complexity**: O(n) for most operations
- **Space Complexity**: O(n) for frequency maps
- **Memory Usage**: Efficient string operations with minimal allocations
- **Iterator Usage**: Lazy evaluation for better performance
- **HashMap Performance**: O(1) average case for lookups

## Troubleshooting

### Compilation Errors
- **"HashMap not found"**: Add `use std::collections::HashMap;`
- **"io not found"**: Add `use std::io::{self, Write};`
- **"Option not found"**: Add `use std::option::Option;`

### Runtime Errors
- **Empty input**: Program validates and handles gracefully
- **Invalid character**: Input validation prevents crashes
- **Unicode handling**: Rust handles UTF-8 by default

### Performance Issues
- **Large texts**: Consider streaming for very large files
- **Memory usage**: Monitor with tools like `valgrind`
- **Slow operations**: Profile and optimize hot paths

## Extensions
Try these challenges to improve the program:
1. **File Operations**: Read/write text files
2. **Unicode Support**: Enhanced international character handling
3. **Advanced Statistics**: Readability scores, sentiment analysis
4. **Pattern Search**: Implement regex-like pattern matching
5. **Batch Processing**: Process multiple texts at once
6. **GUI Interface**: Create graphical user interface
7. **Web API**: Convert to web service
8. **Performance Optimization**: Use more efficient algorithms

## Educational Benefits
- **Pattern Matching**: Master Rust's powerful match expressions
- **Collection Mastery**: Learn HashMap, Vec, and iterator patterns
- **Memory Safety**: Understand Rust's ownership and borrowing
- **Algorithmic Thinking**: Develop problem-solving skills
- **Statistical Analysis**: Learn data analysis techniques
- **Error Handling**: Master Option and Result types

## Next Steps
After mastering this text analyzer, try:
- Level 3: File Manager (file I/O, path manipulation)
- Level 4: Web Scraper (HTTP requests, HTML parsing)
- Level 5: Bank Account Manager (OOP, data structures)
- Intermediate Projects: Advanced algorithms and data structures

## About This Project
This text analyzer demonstrates Rust's strengths in pattern matching, collection operations, and safe memory management. The code includes detailed comments explaining each concept and operation, making it perfect for learning Rust through practical application.

Happy analyzing!
