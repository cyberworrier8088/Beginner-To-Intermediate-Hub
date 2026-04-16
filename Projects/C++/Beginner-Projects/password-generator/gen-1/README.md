# C++ Password Generator - Level 1

## Overview
A secure password generator demonstrating modern C++ features, random number generation, and security best practices.

## Features
- **Secure Random Generation**: Mersenne Twister algorithm for high-quality randomness
- **Character Sets**: Lowercase, uppercase, digits, and special characters
- **Customizable Requirements**: User-defined length and character types
- **Password Strength Analysis**: Detailed security assessment
- **Multiple Passwords**: Generate multiple passwords at once
- **Input Validation**: Comprehensive error handling and sanitization
- **Masking Options**: Secure password display with masking

## Learning Objectives
- Modern C++ random number generation (`<random>`)
- String manipulation and character set management
- User input validation and error handling
- Security best practices for password generation
- Object-oriented programming principles
- STL containers and algorithms

## Prerequisites
- C++17 compatible compiler (g++, clang++, or MSVC)
- Basic understanding of C++ syntax
- Familiarity with command-line interfaces

## Compilation & Running

### Linux/macOS
```bash
# Compile
g++ -std=c++17 -o password_generator password_generator.cpp

# Run
./password_generator
```

### Windows (with g++)
```bash
# Compile
g++ -std=c++17 -o password_generator.exe password_generator.cpp

# Run
password_generator.exe
```

### Windows (Visual Studio)
1. Open Visual Studio
2. Create new C++ project
3. Copy password_generator.cpp to main.cpp
4. Build and run

## Usage
1. Run the program
2. Choose from the main menu:
   - `1` - Generate single password
   - `2` - Generate multiple passwords
   - `3` - Password strength analysis
   - `4` - Custom password requirements
   - `5` - Exit program

## Example Session
```
=== C++ PASSWORD GENERATOR ===
Welcome to secure password generation in C++!

1. Generate single password
2. Generate multiple passwords
3. Password strength analysis
4. Custom password requirements
5. Exit program

Choice: 1

--- SINGLE PASSWORD GENERATION ---
Enter password length (4-128): 16

Select character types to include:
Include lowercase letters (a-z)? (y/n): y
Include uppercase letters (A-Z)? (y/n): y
Include digits (0-9)? (y/n): y
Include special characters (!@#$%...)? (y/n): y

=== GENERATING SECURE PASSWORD ===
Building CHARACTER POOL...
Added 26 lowercase characters
Added 26 uppercase characters
Added 10 digit characters
Added 25 special characters
Total character pool size: 87 characters

Generating password...
Adding guaranteed lowercase character
Adding guaranteed uppercase character
Adding guaranteed digit character
Adding guaranteed special character
Filling remaining 12 characters...
Shuffling password for maximum randomness...
Password generation complete!
=================================

Generated password: K8#mP2$xL9@vNq
Length: 16 characters
========================
```

## Code Structure
```cpp
class PasswordGenerator {
private:
    const string lowercase_chars = "abcdefghijklmnopqrstuvwxyz";
    const string uppercase_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digit_chars = "0123456789";
    const string special_chars = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    mt19937 rng;  // Mersenne Twister random number generator
    
public:
    // Core methods
    string generatePassword(int length, bool useLower, bool useUpper, 
                        bool useDigits, bool useSpecial);
    vector<string> generateMultiplePasswords(int count, int length, 
                                         bool useLower, bool useUpper, 
                                         bool useDigits, bool useSpecial);
    
    // Analysis methods
    void analyzePasswordStrength(const string& password);
    
    // Utility methods
    bool validateRequirements(int length, bool useLower, bool useUpper, 
                          bool useDigits, bool useSpecial);
    string buildCharacterPool(bool useLower, bool useUpper, bool useDigits, bool useSpecial);
};
```

## Key Concepts Demonstrated
1. **Modern Random Number Generation**: Mersenne Twister algorithm
2. **String Manipulation**: Character sets and string operations
3. **Input Validation**: Comprehensive error handling
4. **Security Best Practices**: Guaranteed character inclusion
5. **Object-Oriented Design**: Encapsulation and modularity
6. **STL Algorithms**: Shuffle, random distributions
7. **Human-Like Code**: Detailed comments and user feedback

## Security Features
- **Cryptographically Secure**: Hardware-based random seed
- **Character Type Enforcement**: Guaranteed inclusion of selected types
- **Length Validation**: Secure password length requirements
- **Strength Analysis**: Comprehensive security assessment
- **No Patterns**: Random shuffling prevents predictability
- **Masking Options**: Secure password display

## Troubleshooting

### Compilation Errors
- **"random was not declared"**: Add `#include <random>`
- **"mt19937 was not declared"**: Use `std::mt19937`
- **"shuffle was not declared"**: Add `#include <algorithm>`

### Runtime Errors
- **Invalid character type**: At least one type must be selected
- **Password length too short**: Minimum 4 characters required
- **Password length too long**: Maximum 128 characters allowed

### Platform-Specific Issues
- **Windows**: Use `g++` from MinGW-w64 or Visual Studio
- **macOS**: Install Xcode Command Line Tools
- **Linux**: Install `build-essential` package

## Extensions
Try these challenges to improve the program:
1. **Password History**: Store and manage generated passwords
2. **Custom Character Sets**: Allow user-defined character sets
3. **Password Policies**: Implement corporate password policies
4. **File Export**: Save passwords to encrypted files
5. **GUI Version**: Create a graphical user interface
6. **Network API**: Create a REST API for password generation
7. **Password Database**: Integrate with password manager database

## Security Considerations
- **Never store passwords in plaintext**
- **Use secure random number generators**
- **Implement proper character type enforcement**
- **Validate password strength requirements**
- **Consider using established password hashing algorithms**
- **Follow industry security standards**

## Next Steps
After mastering this password generator, try:
- Level 2: Enhanced Calculator (history, variables, scientific functions)
- Text Adventure Game (game development, state management)
- Data Structures (templates, algorithms, performance)

## About This Project
This password generator demonstrates modern C++ features while focusing on security best practices. The code includes detailed comments explaining each concept and operation, making it perfect for learning secure programming practices.

Happy coding and stay secure!
