# C++ String Processor - Level 1

## Overview
A comprehensive text processing tool demonstrating C++ string manipulation, algorithmic thinking, and manual implementation without external libraries.

## Features
- **String Manipulation**: Uppercase, lowercase, reverse, trim operations
- **Text Analysis**: Character counting, word frequency, statistics
- **Search & Replace**: Find and replace functionality
- **No External Libraries**: Manual implementation of all algorithms
- **User Input Validation**: Comprehensive error handling and sanitization
- **Memory Management**: Efficient string operations and memory usage

## Learning Objectives
- String manipulation with `<string>` and `<algorithm>`
- Manual algorithm implementation without external dependencies
- Text analysis and statistical computing
- User input validation and error handling
- Memory management and efficiency considerations
- Human-like code with detailed explanations

## Prerequisites
- C++17 compatible compiler (g++, clang++, or MSVC)
- Basic understanding of C++ syntax
- Familiarity with command-line interfaces

## Compilation & Running

### Linux/macOS
```bash
# Compile
g++ -std=c++17 -o string_processor string_processor.cpp

# Run
./string_processor
```

### Windows (with g++)
```bash
# Compile
g++ -std=c++17 -o string_processor.exe string_processor.cpp

# Run
string_processor.exe
```

### Windows (Visual Studio)
1. Open Visual Studio
2. Create new C++ project
3. Copy string_processor.cpp to main.cpp
4. Build and run

## Usage
1. Run the program
2. Choose from the main menu:
   - `1` - Set input text
   - `2` - Convert to uppercase
   - `3` - Convert to lowercase
   - `4` - Remove whitespace
   - `5` - Remove punctuation
   - `6` - Reverse text
   - `7` - Count character occurrences
   - `8` - Find and replace
   - `9` - Word frequency analysis
   - `10` - Display current text
   - `11` - Display detailed statistics
   - `12` - Reset to original
   - `13` - Exit program

## Example Session
```
=== C++ STRING PROCESSOR ===
Welcome to text processing in C++!

1. Set input text
2. Convert to uppercase
3. Convert to lowercase
4. Remove whitespace
5. Remove punctuation
6. Reverse text
7. Count character occurrences
8. Find and replace
9. Word frequency analysis
10. Display current text
11. Display detailed statistics
12. Reset to original
13. Exit program

Choice: 1
Enter text to process: Hello, World! This is a test.

=== SETTING INPUT TEXT ===
Input text length: 27 characters
Text set successfully!
Characters: 27
Words: 6
Lines: 1
=========================

Choice: 2

=== CONVERTING TO UPPERCASE ===
Original length: 27 characters
Converted to uppercase successfully!
New length: 27 characters
===============================
```

## Code Structure
```cpp
class StringProcessor {
private:
    string originalText;      // Store original input text
    string processedText;     // Store processed text
    int characterCount;       // Total character count
    int wordCount;          // Total word count
    int lineCount;          // Total line count
    
public:
    // Core processing methods
    void toUpperCase();
    void toLowerCase();
    void removeWhitespace();
    void removePunctuation();
    void reverseText();
    
    // Analysis methods
    void countCharacter(char targetChar);
    void findAndReplace(const string& findText, const string& replaceText);
    vector<string> extractWords();
    void wordFrequency();
    
    // Utility methods
    void analyzeText();
    void displayText() const;
    void displayStatistics() const;
    void reset();
};
```

## Key Concepts Demonstrated
1. **String Manipulation**: Manual implementation of common string operations
2. **Algorithm Implementation**: Custom algorithms without external libraries
3. **Text Analysis**: Statistical analysis and character counting
4. **Memory Management**: Efficient string operations and memory usage
5. **Input Validation**: Comprehensive error handling and sanitization
6. **Human-Like Code**: Detailed comments explaining each operation

## Manual Algorithms Implemented
- **Character Case Conversion**: Manual ASCII value manipulation
- **Whitespace Removal**: Iterative filtering without `erase_if`
- **Punctuation Removal**: Character classification and filtering
- **String Reversal**: Manual index-based reversal
- **Word Extraction**: Character-by-character word boundary detection
- **Frequency Counting**: Manual hash map population and counting
- **Search and Replace**: Substring matching and replacement

## Performance Considerations
- **Time Complexity**: O(n) for most operations
- **Space Complexity**: O(n) for storing processed text
- **Memory Usage**: Minimal additional memory allocation
- **Efficiency**: Manual algorithms optimized for clarity
- **Scalability**: Handles large texts efficiently

## Troubleshooting

### Compilation Errors
- **"string was not declared"**: Add `#include <string>`
- **"algorithm was not declared"**: Add `#include <algorithm>`
- **"cctype was not declared"**: Add `#include <cctype>`
- **"sstream was not declared"**: Add `#include <sstream>`

### Runtime Errors
- **Empty input**: Program validates and prompts for non-empty input
- **Invalid character**: Input validation prevents crashes
- **Memory issues**: Manual memory management prevents leaks

### Platform-Specific Issues
- **Windows**: Use `g++` from MinGW-w64 or Visual Studio
- **macOS**: Install Xcode Command Line Tools
- **Linux**: Install `build-essential` package

## Extensions
Try these challenges to improve the program:
1. **Advanced Statistics**: Add readability scores, sentiment analysis
2. **Pattern Matching**: Implement regex-like pattern searching
3. **File Operations**: Read/write text files
4. **Unicode Support**: Handle international characters
5. **Performance Optimization**: Use more efficient algorithms
6. **GUI Interface**: Create graphical user interface
7. **Plugin System**: Add extensible text processing modules
8. **Batch Processing**: Process multiple texts at once

## Educational Benefits
- **Algorithmic Thinking**: Manual implementation builds problem-solving skills
- **Memory Management**: Understanding of string storage and manipulation
- **Performance Analysis**: Learning about algorithm efficiency
- **Code Organization**: Structured approach to complex problems
- **Debugging Skills**: Manual implementation requires careful testing

## Next Steps
After mastering this string processor, try:
- Level 2: Password Generator (random generation, security)
- Level 3: To-Do List Manager (data structures, file I/O)
- Level 4: Calculator (OOP, mathematical operations)
- Level 5: Data Structures (templates, algorithms)

## About This Project
This string processor demonstrates fundamental C++ concepts through practical text manipulation. The manual implementation of algorithms helps learners understand the underlying mechanics of string operations and builds strong problem-solving skills.

Happy coding and happy processing!
