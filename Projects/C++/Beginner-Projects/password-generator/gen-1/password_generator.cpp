/*
 * Password Generator in C++ - Level 1: String Manipulation & Randomness
 * 
 * Welcome to security programming in C++! This is where randomness meets safety.
 * Learn string manipulation, random number generation, and security concepts.
 * 
 * Key concepts you'll learn:
 * - Random number generation with <random>
 * - String manipulation and character sets
 * - User input validation and sanitization
 * - Command-line argument processing
 * - Security best practices for password generation
 * - Human-like code with detailed explanations!
 */

#include <iostream>     // For input/output operations (cout, cin)
#include <string>       // For string manipulation
#include <vector>       // For dynamic arrays (vectors)
#include <random>       // For modern random number generation
#include <algorithm>    // For shuffle algorithm
#include <cctype>       // For character type checking (isupper, islower, etc.)
#include <iomanip>       // For output formatting (setw)

using namespace std;    // Standard namespace to avoid std:: prefix

// Password generator class - encapsulates all password generation logic
class PasswordGenerator {
private:
    // Character sets for different types of characters
    const string lowercase_chars = "abcdefghijklmnopqrstuvwxyz";  // All lowercase letters
    const string uppercase_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // All uppercase letters
    const string digit_chars = "0123456789";                    // All digits
    const string special_chars = "!@#$%^&*()_+-=[]{}|;:,.<>?";     // Special characters
    
    // Random number generator - Mersenne Twister engine for high-quality randomness
    mt19937 rng;
    
public:
    // Constructor - initialize the random number generator
    PasswordGenerator() {
        // Seed the random number generator with a high-quality random seed
        random_device rd;  // Hardware-based random number generator
        rng.seed(rd());    // Seed the Mersenne Twister
        cout << "Password Generator initialized with secure random seed!" << endl;
    }
    
    // Generate a random integer within a range [min, max]
    int getRandomInt(int min, int max) {
        uniform_int_distribution<int> dist(min, max);  // Uniform distribution
        return dist(rng);  // Generate random number
    }
    
    // Generate a random character from a given character set
    char getRandomChar(const string& charset) {
        int index = getRandomInt(0, charset.length() - 1);  // Get random index
        return charset[index];  // Return character at that index
    }
    
    // Validate password requirements
    bool validateRequirements(int length, bool useLower, bool useUpper, 
                          bool useDigits, bool useSpecial) {
        cout << "\n=== VALIDATING PASSWORD REQUIREMENTS ===" << endl;
        
        // Check if at least one character type is selected
        if (!useLower && !useUpper && !useDigits && !useSpecial) {
            cout << "Error: At least one character type must be selected!" << endl;
            return false;
        }
        
        // Check if length is reasonable
        if (length < 4) {
            cout << "Error: Password length must be at least 4 characters!" << endl;
            return false;
        }
        
        if (length > 128) {
            cout << "Error: Password length cannot exceed 128 characters!" << endl;
            return false;
        }
        
        // Display validation results
        cout << "Password length: " << length << " characters" << endl;
        cout << "Character types selected:" << endl;
        if (useLower) cout << "  ✓ Lowercase letters (a-z)" << endl;
        if (useUpper) cout << "  ✓ Uppercase letters (A-Z)" << endl;
        if (useDigits) cout << "  ✓ Digits (0-9)" << endl;
        if (useSpecial) cout << "  ✓ Special characters (!@#$%...)" << endl;
        
        cout << "✓ Password requirements are valid!" << endl;
        cout << "=====================================" << endl;
        return true;
    }
    
    // Build character pool based on user preferences
    string buildCharacterPool(bool useLower, bool useUpper, bool useDigits, bool useSpecial) {
        string pool = "";  // Initialize empty character pool
        
        cout << "\n=== BUILDING CHARACTER POOL ===" << endl;
        
        // Add character types to pool based on user selection
        if (useLower) {
            pool += lowercase_chars;
            cout << "Added " << lowercase_chars.length() << " lowercase characters" << endl;
        }
        
        if (useUpper) {
            pool += uppercase_chars;
            cout << "Added " << uppercase_chars.length() << " uppercase characters" << endl;
        }
        
        if (useDigits) {
            pool += digit_chars;
            cout << "Added " << digit_chars.length() << " digit characters" << endl;
        }
        
        if (useSpecial) {
            pool += special_chars;
            cout << "Added " << special_chars.length() << " special characters" << endl;
        }
        
        cout << "Total character pool size: " << pool.length() << " characters" << endl;
        cout << "Character pool: " << pool << endl;
        cout << "================================" << endl;
        
        return pool;
    }
    
    // Generate password with guaranteed character types
    string generatePassword(int length, bool useLower, bool useUpper, 
                        bool useDigits, bool useSpecial) {
        cout << "\n=== GENERATING SECURE PASSWORD ===" << endl;
        
        // Build character pool based on requirements
        string charPool = buildCharacterPool(useLower, useUpper, useDigits, useSpecial);
        
        string password = "";  // Initialize empty password
        
        // First, ensure at least one character of each required type is included
        if (useLower) {
            password += getRandomChar(lowercase_chars);
            cout << "Added guaranteed lowercase character" << endl;
        }
        
        if (useUpper) {
            password += getRandomChar(uppercase_chars);
            cout << "Added guaranteed uppercase character" << endl;
        }
        
        if (useDigits) {
            password += getRandomChar(digit_chars);
            cout << "Added guaranteed digit character" << endl;
        }
        
        if (useSpecial) {
            password += getRandomChar(special_chars);
            cout << "Added guaranteed special character" << endl;
        }
        
        // Fill the rest of the password with random characters from the pool
        int remainingLength = length - password.length();
        cout << "Filling remaining " << remainingLength << " characters..." << endl;
        
        for (int i = 0; i < remainingLength; i++) {
            password += getRandomChar(charPool);
        }
        
        // Shuffle the password to ensure randomness
        cout << "Shuffling password for maximum randomness..." << endl;
        shuffle(password.begin(), password.end(), rng);
        
        cout << "Password generation complete!" << endl;
        cout << "=================================" << endl;
        
        return password;
    }
    
    // Check password strength
    void analyzePasswordStrength(const string& password) {
        cout << "\n=== PASSWORD STRENGTH ANALYSIS ===" << endl;
        
        int score = 0;  // Initialize strength score
        string feedback = "";  // Initialize feedback message
        
        // Length analysis
        if (password.length() >= 8) score += 2;
        if (password.length() >= 12) score += 2;
        if (password.length() >= 16) score += 2;
        
        // Character variety analysis
        bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
        
        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
            else hasSpecial = true;
        }
        
        if (hasLower) score += 2;
        if (hasUpper) score += 2;
        if (hasDigit) score += 2;
        if (hasSpecial) score += 2;
        
        // Determine strength based on score
        if (score >= 10) {
            feedback = "VERY STRONG - Excellent password!";
        } else if (score >= 8) {
            feedback = "STRONG - Good password!";
        } else if (score >= 6) {
            feedback = "MODERATE - Consider adding more character types";
        } else if (score >= 4) {
            feedback = "WEAK - Add more character variety";
        } else {
            feedback = "VERY WEAK - Use longer password with more character types";
        }
        
        // Display analysis results
        cout << "Password length: " << password.length() << " characters" << endl;
        cout << "Character types used:" << endl;
        if (hasLower) cout << "  ✓ Lowercase letters" << endl;
        if (hasUpper) cout << "  ✓ Uppercase letters" << endl;
        if (hasDigit) cout << "  ✓ Digits" << endl;
        if (hasSpecial) cout << "  ✓ Special characters" << endl;
        
        cout << "Strength score: " << score << "/10" << endl;
        cout << "Strength rating: " << feedback << endl;
        cout << "==================================" << endl;
    }
    
    // Generate multiple passwords
    vector<string> generateMultiplePasswords(int count, int length, bool useLower, 
                                         bool useUpper, bool useDigits, bool useSpecial) {
        cout << "\n=== GENERATING MULTIPLE PASSWORDS ===" << endl;
        cout << "Generating " << count << " passwords..." << endl;
        
        vector<string> passwords;  // Vector to store generated passwords
        
        for (int i = 0; i < count; i++) {
            cout << "Generating password " << (i + 1) << "/" << count << "..." << endl;
            string password = generatePassword(length, useLower, useUpper, useDigits, useSpecial);
            passwords.push_back(password);
        }
        
        cout << "Successfully generated " << passwords.size() << " passwords!" << endl;
        cout << "====================================" << endl;
        
        return passwords;
    }
    
    // Display password with masking option
    void displayPassword(const string& password, bool mask = false) {
        cout << "\n=== GENERATED PASSWORD ===" << endl;
        
        if (mask) {
            // Show masked password (show first and last character only)
            cout << "Masked: ";
            if (password.length() <= 2) {
                for (size_t i = 0; i < password.length(); i++) {
                    cout << "*";
                }
            } else {
                cout << password[0];
                for (size_t i = 1; i < password.length() - 1; i++) {
                    cout << "*";
                }
                cout << password[password.length() - 1];
            }
            cout << endl;
        } else {
            // Show full password
            cout << "Password: " << password << endl;
        }
        
        cout << "Length: " << password.length() << " characters" << endl;
        cout << "========================" << endl;
    }
    
    // Display multiple passwords
    void displayMultiplePasswords(const vector<string>& passwords, bool mask = false) {
        cout << "\n=== GENERATED PASSWORDS ===" << endl;
        cout << "Total passwords: " << passwords.size() << endl;
        cout << setw(4) << "No." << setw(20) << "Password" << setw(10) << "Length" << endl;
        cout << setw(4) << "---" << setw(20) << "--------" << setw(10) << "------" << endl;
        
        for (size_t i = 0; i < passwords.size(); i++) {
            cout << setw(4) << (i + 1) << setw(20);
            
            if (mask) {
                const string& password = passwords[i];
                if (password.length() <= 2) {
                    for (size_t j = 0; j < password.length(); j++) {
                        cout << "*";
                    }
                } else {
                    cout << password[0];
                    for (size_t j = 1; j < password.length() - 1; j++) {
                        cout << "*";
                    }
                    cout << password[password.length() - 1];
                }
            } else {
                cout << passwords[i];
            }
            
            cout << setw(10) << passwords[i].length() << endl;
        }
        
        cout << "=========================" << endl;
    }
};

// Input validation functions with detailed error handling
int getValidPositiveInteger(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            int value = stoi(input);  // Try to convert string to integer
            
            if (value <= 0) {
                cout << "Error: Please enter a positive number!" << endl;
                continue;
            }
            
            return value;
        } catch (const invalid_argument&) {
            cout << "Error: Please enter a valid integer!" << endl;
        } catch (const out_of_range&) {
            cout << "Error: Number too large! Please enter a smaller number." << endl;
        }
    }
}

bool getYesNoResponse(const string& prompt) {
    while (true) {
        cout << prompt << " (y/n): ";
        string response;
        getline(cin, response);
        
        // Convert to lowercase for case-insensitive comparison
        transform(response.begin(), response.end(), response.begin(), ::tolower);
        
        if (response == "y" || response == "yes") {
            return true;
        } else if (response == "n" || response == "no") {
            return false;
        } else {
            cout << "Error: Please enter 'y' or 'n'!" << endl;
        }
    }
}

// Display program introduction and features
void displayIntroduction() {
    cout << "========================================" << endl;
    cout << "    C++ PASSWORD GENERATOR" << endl;
    cout << "========================================" << endl;
    cout << "Welcome to secure password generation in C++!" << endl;
    cout << "This program demonstrates:" << endl;
    cout << "- Modern C++ random number generation" << endl;
    cout << "- String manipulation and character sets" << endl;
    cout << "- User input validation and sanitization" << endl;
    cout << "- Security best practices" << endl;
    cout << "- Object-oriented programming principles" << endl;
    cout << "- Human-like code with detailed comments!" << endl;
    cout << "========================================" << endl;
}

// Display main menu options
void displayMenu() {
    cout << "\n=== PASSWORD GENERATOR MENU ===" << endl;
    cout << "1. Generate single password" << endl;
    cout << "2. Generate multiple passwords" << endl;
    cout << "3. Password strength analysis" << endl;
    cout << "4. Custom password requirements" << endl;
    cout << "5. Exit program" << endl;
    cout << "===============================" << endl;
}

// Generate single password with user interaction
void generateSinglePassword(PasswordGenerator& generator) {
    cout << "\n--- SINGLE PASSWORD GENERATION ---" << endl;
    
    // Get password length
    int length = getValidPositiveInteger("Enter password length (4-128): ");
    
    // Get character type preferences
    cout << "\nSelect character types to include:" << endl;
    bool useLower = getYesNoResponse("Include lowercase letters (a-z)?");
    bool useUpper = getYesNoResponse("Include uppercase letters (A-Z)?");
    bool useDigits = getYesNoResponse("Include digits (0-9)?");
    bool useSpecial = getYesNoResponse("Include special characters (!@#$%...)?");
    
    // Validate requirements
    if (!generator.validateRequirements(length, useLower, useUpper, useDigits, useSpecial)) {
        cout << "Invalid requirements. Please try again." << endl;
        return;
    }
    
    // Generate password
    string password = generator.generatePassword(length, useLower, useUpper, useDigits, useSpecial);
    
    // Ask if user wants to mask the password
    bool maskPassword = getYesNoResponse("Mask password for security?");
    
    // Display password
    generator.displayPassword(password, maskPassword);
    
    // Analyze password strength
    generator.analyzePasswordStrength(password);
}

// Generate multiple passwords with user interaction
void generateMultiplePasswords(PasswordGenerator& generator) {
    cout << "\n--- MULTIPLE PASSWORD GENERATION ---" << endl;
    
    // Get number of passwords
    int count = getValidPositiveInteger("Enter number of passwords to generate: ");
    
    // Get password length
    int length = getValidPositiveInteger("Enter password length (4-128): ");
    
    // Get character type preferences
    cout << "\nSelect character types to include:" << endl;
    bool useLower = getYesNoResponse("Include lowercase letters (a-z)?");
    bool useUpper = getYesNoResponse("Include uppercase letters (A-Z)?");
    bool useDigits = getYesNoResponse("Include digits (0-9)?");
    bool useSpecial = getYesNoResponse("Include special characters (!@#$%...)?");
    
    // Validate requirements
    if (!generator.validateRequirements(length, useLower, useUpper, useDigits, useSpecial)) {
        cout << "Invalid requirements. Please try again." << endl;
        return;
    }
    
    // Generate passwords
    vector<string> passwords = generator.generateMultiplePasswords(count, length, useLower, useUpper, useDigits, useSpecial);
    
    // Ask if user wants to mask passwords
    bool maskPasswords = getYesNoResponse("Mask passwords for security?");
    
    // Display passwords
    generator.displayMultiplePasswords(passwords, maskPasswords);
    
    // Analyze first password strength
    if (!passwords.empty()) {
        generator.analyzePasswordStrength(passwords[0]);
    }
}

// Analyze existing password
void analyzePassword(PasswordGenerator& generator) {
    cout << "\n--- PASSWORD STRENGTH ANALYSIS ---" << endl;
    
    cout << "Enter password to analyze: ";
    string password;
    getline(cin, password);
    
    if (password.empty()) {
        cout << "Error: Password cannot be empty!" << endl;
        return;
    }
    
    // Analyze password strength
    generator.analyzePasswordStrength(password);
}

// Custom password requirements
void customPasswordRequirements(PasswordGenerator& generator) {
    cout << "\n--- CUSTOM PASSWORD REQUIREMENTS ---" << endl;
    
    // Get custom requirements
    int minLength = getValidPositiveInteger("Enter minimum password length: ");
    int maxLength = getValidPositiveInteger("Enter maximum password length: ");
    
    if (minLength > maxLength) {
        cout << "Error: Minimum length cannot be greater than maximum length!" << endl;
        return;
    }
    
    // Generate password with random length within range
    int length = generator.getRandomInt(minLength, maxLength);
    cout << "Randomly selected password length: " << length << endl;
    
    // Get character type preferences
    cout << "\nSelect character types to include:" << endl;
    bool useLower = getYesNoResponse("Include lowercase letters (a-z)?");
    bool useUpper = getYesNoResponse("Include uppercase letters (A-Z)?");
    bool useDigits = getYesNoResponse("Include digits (0-9)?");
    bool useSpecial = getYesNoResponse("Include special characters (!@#$%...)?");
    
    // Validate requirements
    if (!generator.validateRequirements(length, useLower, useUpper, useDigits, useSpecial)) {
        cout << "Invalid requirements. Please try again." << endl;
        return;
    }
    
    // Generate password
    string password = generator.generatePassword(length, useLower, useUpper, useDigits, useSpecial);
    
    // Display password
    generator.displayPassword(password, false);
    
    // Analyze password strength
    generator.analyzePasswordStrength(password);
}

// Main program loop
int main() {
    displayIntroduction();
    
    PasswordGenerator generator;  // Create password generator instance
    
    while (true) {
        displayMenu();
        
        cout << "Enter your choice (1-5): ";
        string choice;
        getline(cin, choice);
        
        if (choice == "1") {
            generateSinglePassword(generator);
        } else if (choice == "2") {
            generateMultiplePasswords(generator);
        } else if (choice == "3") {
            analyzePassword(generator);
        } else if (choice == "4") {
            customPasswordRequirements(generator);
        } else if (choice == "5") {
            cout << "\nThank you for using C++ Password Generator!" << endl;
            cout << "You've learned:" << endl;
            cout << "- Modern C++ random number generation" << endl;
            cout << "- String manipulation and character sets" << endl;
            cout << "- User input validation and sanitization" << endl;
            cout << "- Object-oriented programming principles" << endl;
            cout << "- Security best practices" << endl;
            cout << "- Human-like code with detailed comments!" << endl;
            break;
        } else {
            cout << "Error: Invalid choice! Please enter 1-5." << endl;
        }
        
        // Add a small pause for better user experience
        if (choice != "5") {
            cout << "\nPress Enter to continue...";
            string pause;
            getline(cin, pause);
        }
    }
    
    return 0;  // Successful program execution
}
