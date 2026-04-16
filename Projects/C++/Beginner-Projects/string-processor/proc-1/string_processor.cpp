/*
 * String Processor in C++ - Level 1: String Manipulation & Algorithms
 * 
 * Welcome to text processing in C++! This is where strings meet algorithms.
 * Learn string manipulation, text analysis, and algorithmic thinking.
 * 
 * Key concepts you'll learn:
 * - String manipulation with <string> and <algorithm>
 * - Text analysis and statistics
 * - Algorithm implementation without external libraries
 * - User input validation and sanitization
 * - Memory management and efficiency
 * - Human-like code with detailed explanations!
 */

#include <iostream>     // For input/output operations (cout, cin)
#include <string>       // For string manipulation
#include <vector>       // For dynamic arrays (vectors)
#include <algorithm>    // For string algorithms (transform, sort, etc.)
#include <cctype>       // For character type checking (isupper, islower, etc.)
#include <sstream>       // For string stream operations
#include <iomanip>       // For output formatting (setw, setprecision)

using namespace std;    // Standard namespace to avoid std:: prefix

// String processor class - encapsulates all text processing functionality
class StringProcessor {
private:
    string originalText;      // Store original input text
    string processedText;     // Store processed text
    int characterCount;       // Total character count
    int wordCount;          // Total word count
    int lineCount;          // Total line count
    
public:
    // Constructor - initialize processor with empty text
    StringProcessor() : characterCount(0), wordCount(0), lineCount(0) {
        cout << "String Processor initialized!" << endl;
        cout << "Ready to process text without external libraries!" << endl;
    }
    
    // Set input text and analyze basic statistics
    void setText(const string& text) {
        cout << "\n=== SETTING INPUT TEXT ===" << endl;
        cout << "Input text length: " << text.length() << " characters" << endl;
        
        originalText = text;
        processedText = text;
        
        // Analyze basic statistics
        analyzeText();
        
        cout << "Text set successfully!" << endl;
        cout << "Characters: " << characterCount << endl;
        cout << "Words: " << wordCount << endl;
        cout << "Lines: " << lineCount << endl;
        cout << "=========================" << endl;
    }
    
    // Analyze text for basic statistics
    void analyzeText() {
        cout << "\n=== ANALYZING TEXT STATISTICS ===" << endl;
        
        characterCount = originalText.length();
        wordCount = 0;
        lineCount = 1;  // Start with 1 line
        
        bool inWord = false;
        
        for (size_t i = 0; i < originalText.length(); i++) {
            char c = originalText[i];
            
            // Count words
            if (isspace(c)) {
                if (inWord) {
                    wordCount++;
                    inWord = false;
                }
            } else {
                inWord = true;
            }
            
            // Count lines
            if (c == '\n') {
                lineCount++;
            }
        }
        
        // Count last word if text doesn't end with space
        if (inWord) {
            wordCount++;
        }
        
        cout << "Analysis complete!" << endl;
        cout << "===============================" << endl;
    }
    
    // Convert text to uppercase
    void toUpperCase() {
        cout << "\n=== CONVERTING TO UPPERCASE ===" << endl;
        cout << "Original length: " << processedText.length() << " characters" << endl;
        
        // Manual uppercase conversion without using transform
        string result = processedText;
        for (size_t i = 0; i < result.length(); i++) {
            if (result[i] >= 'a' && result[i] <= 'z') {
                result[i] = result[i] - ('a' - 'A');  // Convert to uppercase
            }
        }
        
        processedText = result;
        
        cout << "Converted to uppercase successfully!" << endl;
        cout << "New length: " << processedText.length() << " characters" << endl;
        cout << "===============================" << endl;
    }
    
    // Convert text to lowercase
    void toLowerCase() {
        cout << "\n=== CONVERTING TO LOWERCASE ===" << endl;
        cout << "Original length: " << processedText.length() << " characters" << endl;
        
        // Manual lowercase conversion without using transform
        string result = processedText;
        for (size_t i = 0; i < result.length(); i++) {
            if (result[i] >= 'A' && result[i] <= 'Z') {
                result[i] = result[i] + ('a' - 'A');  // Convert to lowercase
            }
        }
        
        processedText = result;
        
        cout << "Converted to lowercase successfully!" << endl;
        cout << "New length: " << processedText.length() << " characters" << endl;
        cout << "===============================" << endl;
    }
    
    // Remove all whitespace from text
    void removeWhitespace() {
        cout << "\n=== REMOVING WHITESPACE ===" << endl;
        cout << "Original length: " << processedText.length() << " characters" << endl;
        
        string result = "";
        int removedCount = 0;
        
        // Manual whitespace removal
        for (size_t i = 0; i < processedText.length(); i++) {
            if (!isspace(processedText[i])) {
                result += processedText[i];
            } else {
                removedCount++;
            }
        }
        
        processedText = result;
        
        cout << "Removed " << removedCount << " whitespace characters" << endl;
        cout << "New length: " << processedText.length() << " characters" << endl;
        cout << "=============================" << endl;
    }
    
    // Remove all punctuation from text
    void removePunctuation() {
        cout << "\n=== REMOVING PUNCTUATION ===" << endl;
        cout << "Original length: " << processedText.length() << " characters" << endl;
        
        string result = "";
        int removedCount = 0;
        
        // Manual punctuation removal
        for (size_t i = 0; i < processedText.length(); i++) {
            char c = processedText[i];
            if (isalnum(c) || isspace(c)) {
                result += c;
            } else {
                removedCount++;
            }
        }
        
        processedText = result;
        
        cout << "Removed " << removedCount << " punctuation characters" << endl;
        cout << "New length: " << processedText.length() << " characters" << endl;
        cout << "=============================" << endl;
    }
    
    // Reverse the text
    void reverseText() {
        cout << "\n=== REVERSING TEXT ===" << endl;
        cout << "Original length: " << processedText.length() << " characters" << endl;
        
        string result = "";
        
        // Manual reversal
        for (int i = processedText.length() - 1; i >= 0; i--) {
            result += processedText[i];
        }
        
        processedText = result;
        
        cout << "Text reversed successfully!" << endl;
        cout << "New length: " << processedText.length() << " characters" << endl;
        cout << "====================" << endl;
    }
    
    // Count specific character occurrences
    void countCharacter(char targetChar) {
        cout << "\n=== COUNTING CHARACTER OCCURRENCES ===" << endl;
        cout << "Target character: '" << targetChar << "'" << endl;
        cout << "Text length: " << processedText.length() << " characters" << endl;
        
        int count = 0;
        
        // Manual character counting
        for (size_t i = 0; i < processedText.length(); i++) {
            if (processedText[i] == targetChar) {
                count++;
            }
        }
        
        cout << "Character '" << targetChar << "' appears " << count << " times" << endl;
        cout << "Percentage: " << fixed << setprecision(2) 
             << (double)count / processedText.length() * 100 << "%" << endl;
        cout << "==================================" << endl;
    }
    
    // Find and replace text
    void findAndReplace(const string& findText, const string& replaceText) {
        cout << "\n=== FIND AND REPLACE ===" << endl;
        cout << "Find: \"" << findText << "\"" << endl;
        cout << "Replace with: \"" << replaceText << "\"" << endl;
        cout << "Original length: " << processedText.length() << " characters" << endl;
        
        string result = "";
        int replacements = 0;
        size_t i = 0;
        
        // Manual find and replace
        while (i < processedText.length()) {
            bool found = true;
            
            // Check if findText matches at current position
            for (size_t j = 0; j < findText.length(); j++) {
                if (i + j >= processedText.length() || 
                    processedText[i + j] != findText[j]) {
                    found = false;
                    break;
                }
            }
            
            if (found && i + findText.length() <= processedText.length()) {
                result += replaceText;
                i += findText.length();
                replacements++;
            } else {
                result += processedText[i];
                i++;
            }
        }
        
        processedText = result;
        
        cout << "Made " << replacements << " replacements" << endl;
        cout << "New length: " << processedText.length() << " characters" << endl;
        cout << "====================" << endl;
    }
    
    // Extract words from text
    vector<string> extractWords() {
        cout << "\n=== EXTRACTING WORDS ===" << endl;
        cout << "Text length: " << processedText.length() << " characters" << endl;
        
        vector<string> words;
        string currentWord = "";
        
        // Manual word extraction
        for (size_t i = 0; i < processedText.length(); i++) {
            char c = processedText[i];
            
            if (isalnum(c)) {
                currentWord += c;
            } else {
                if (!currentWord.empty()) {
                    words.push_back(currentWord);
                    currentWord = "";
                }
            }
        }
        
        // Add last word if exists
        if (!currentWord.empty()) {
            words.push_back(currentWord);
        }
        
        cout << "Extracted " << words.size() << " words" << endl;
        cout << "====================" << endl;
        
        return words;
    }
    
    // Count word frequency
    void wordFrequency() {
        cout << "\n=== WORD FREQUENCY ANALYSIS ===" << endl;
        
        vector<string> words = extractWords();
        
        // Manual frequency counting
        vector<string> uniqueWords;
        vector<int> frequencies;
        
        for (const string& word : words) {
            string lowerWord = word;
            
            // Convert to lowercase for case-insensitive counting
            for (size_t i = 0; i < lowerWord.length(); i++) {
                if (lowerWord[i] >= 'A' && lowerWord[i] <= 'Z') {
                    lowerWord[i] = lowerWord[i] + ('a' - 'A');
                }
            }
            
            // Check if word already exists
            bool found = false;
            for (size_t i = 0; i < uniqueWords.size(); i++) {
                string existingLower = uniqueWords[i];
                for (size_t j = 0; j < existingLower.length(); j++) {
                    if (existingLower[j] >= 'A' && existingLower[j] <= 'Z') {
                        existingLower[j] = existingLower[j] + ('a' - 'A');
                    }
                }
                
                if (lowerWord == existingLower) {
                    frequencies[i]++;
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                uniqueWords.push_back(word);
                frequencies.push_back(1);
            }
        }
        
        // Display results
        cout << "Word frequency analysis:" << endl;
        cout << setw(20) << "Word" << setw(10) << "Count" << endl;
        cout << setw(30) << setfill('-') << "" << setfill(' ') << endl;
        
        for (size_t i = 0; i < uniqueWords.size(); i++) {
            cout << setw(20) << uniqueWords[i] << setw(10) << frequencies[i] << endl;
        }
        
        cout << "=============================" << endl;
    }
    
    // Display current text
    void displayText() const {
        cout << "\n=== CURRENT TEXT ===" << endl;
        cout << "Length: " << processedText.length() << " characters" << endl;
        cout << "Content: \"" << processedText << "\"" << endl;
        cout << "==================" << endl;
    }
    
    // Display detailed statistics
    void displayStatistics() const {
        cout << "\n=== DETAILED STATISTICS ===" << endl;
        cout << "Original text length: " << originalText.length() << " characters" << endl;
        cout << "Processed text length: " << processedText.length() << " characters" << endl;
        cout << "Character count: " << characterCount << endl;
        cout << "Word count: " << wordCount << endl;
        cout << "Line count: " << lineCount << endl;
        
        // Additional statistics
        int vowelCount = 0;
        int consonantCount = 0;
        int digitCount = 0;
        int spaceCount = 0;
        
        for (char c : processedText) {
            if (isspace(c)) {
                spaceCount++;
            } else if (isdigit(c)) {
                digitCount++;
            } else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                      c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                vowelCount++;
            } else if (isalpha(c)) {
                consonantCount++;
            }
        }
        
        cout << "\nCharacter breakdown:" << endl;
        cout << "Vowels: " << vowelCount << endl;
        cout << "Consonants: " << consonantCount << endl;
        cout << "Digits: " << digitCount << endl;
        cout << "Spaces: " << spaceCount << endl;
        
        if (processedText.length() > 0) {
            cout << "\nPercentages:" << endl;
            cout << "Vowels: " << fixed << setprecision(1) 
                 << (double)vowelCount / processedText.length() * 100 << "%" << endl;
            cout << "Consonants: " << fixed << setprecision(1) 
                 << (double)consonantCount / processedText.length() * 100 << "%" << endl;
            cout << "Digits: " << fixed << setprecision(1) 
                 << (double)digitCount / processedText.length() * 100 << "%" << endl;
            cout << "Spaces: " << fixed << setprecision(1) 
                 << (double)spaceCount / processedText.length() * 100 << "%" << endl;
        }
        
        cout << "=========================" << endl;
    }
    
    // Reset to original text
    void reset() {
        cout << "\n=== RESETTING TO ORIGINAL ===" << endl;
        processedText = originalText;
        analyzeText();
        cout << "Reset to original text!" << endl;
        cout << "=========================" << endl;
    }
};

// Input validation functions
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

char getValidCharacter(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        if (input.length() == 1) {
            return input[0];
        }
        
        cout << "Error: Please enter exactly one character." << endl;
    }
}

int getValidChoice(const string& prompt, int min, int max) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            int choice = stoi(input);
            
            if (choice >= min && choice <= max) {
                return choice;
            }
            
            cout << "Error: Please enter a number between " << min << " and " << max << "." << endl;
        } catch (...) {
            cout << "Error: Please enter a valid number." << endl;
        }
    }
}

// Display program introduction
void displayIntroduction() {
    cout << "========================================" << endl;
    cout << "    C++ STRING PROCESSOR" << endl;
    cout << "========================================" << endl;
    cout << "Welcome to text processing in C++!" << endl;
    cout << "This program demonstrates:" << endl;
    cout << "- String manipulation without external libraries" << endl;
    cout << "- Manual algorithm implementation" << endl;
    cout << "- Text analysis and statistics" << endl;
    cout << "- User input validation and sanitization" << endl;
    cout << "- Memory management and efficiency" << endl;
    cout << "- Human-like code with detailed comments!" << endl;
    cout << "========================================" << endl;
}

// Display main menu
void displayMenu() {
    cout << "\n=== STRING PROCESSOR MENU ===" << endl;
    cout << "1. Set input text" << endl;
    cout << "2. Convert to uppercase" << endl;
    cout << "3. Convert to lowercase" << endl;
    cout << "4. Remove whitespace" << endl;
    cout << "5. Remove punctuation" << endl;
    cout << "6. Reverse text" << endl;
    cout << "7. Count character occurrences" << endl;
    cout << "8. Find and replace" << endl;
    cout << "9. Word frequency analysis" << endl;
    cout << "10. Display current text" << endl;
    cout << "11. Display detailed statistics" << endl;
    cout << "12. Reset to original" << endl;
    cout << "13. Exit" << endl;
    cout << "=============================" << endl;
}

// Main program loop
int main() {
    displayIntroduction();
    
    StringProcessor processor;
    
    // Set default text for demonstration
    processor.setText("Hello, World! This is a sample text for processing. It contains various characters, numbers 123, and punctuation marks!");
    
    while (true) {
        displayMenu();
        
        int choice = getValidChoice("Enter your choice (1-13): ", 1, 13);
        
        switch (choice) {
            case 1: {
                string text = getValidString("Enter text to process: ");
                processor.setText(text);
                break;
            }
            
            case 2:
                processor.toUpperCase();
                break;
                
            case 3:
                processor.toLowerCase();
                break;
                
            case 4:
                processor.removeWhitespace();
                break;
                
            case 5:
                processor.removePunctuation();
                break;
                
            case 6:
                processor.reverseText();
                break;
                
            case 7: {
                char target = getValidCharacter("Enter character to count: ");
                processor.countCharacter(target);
                break;
            }
            
            case 8: {
                string findText = getValidString("Enter text to find: ");
                string replaceText = getValidString("Enter replacement text: ");
                processor.findAndReplace(findText, replaceText);
                break;
            }
            
            case 9:
                processor.wordFrequency();
                break;
                
            case 10:
                processor.displayText();
                break;
                
            case 11:
                processor.displayStatistics();
                break;
                
            case 12:
                processor.reset();
                break;
                
            case 13:
                cout << "\nThank you for using C++ String Processor!" << endl;
                cout << "You've learned:" << endl;
                cout << "- String manipulation without external libraries" << endl;
                cout << "- Manual algorithm implementation" << endl;
                cout << "- Text analysis and statistics" << endl;
                cout << "- User input validation and sanitization" << endl;
                cout << "- Memory management and efficiency" << endl;
                cout << "- Human-readable, maintainable code!" << endl;
                return 0;
        }
        
        // Add a small pause for better user experience
        cout << "\nPress Enter to continue...";
        string pause;
        getline(cin, pause);
    }
    
    return 0;
}
