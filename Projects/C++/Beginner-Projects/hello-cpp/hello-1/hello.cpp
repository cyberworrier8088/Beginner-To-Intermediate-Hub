/*
 * Hello World in C++ - Level 1: Modern C++ Introduction
 * 
 * Welcome to C++! This is where Object-Oriented Programming meets performance.
 * C++ gives you the power of C with the elegance of classes.
 * 
 * Key concepts you'll learn:
 * - Modern C++ syntax (C++11/14/17)
 * - Header files and namespaces
 * - Input/output streams
 * - String handling
 * - Basic object-oriented programming
 */

#include <iostream>     // For cout, cin (input/output streams)
#include <string>       // For string class
#include <vector>       // For dynamic arrays (vectors)
#include <algorithm>    // For algorithms like sort
#include <memory>       // For smart pointers (modern C++)

using namespace std;    // Standard namespace - avoids writing std:: everywhere

// A simple class to demonstrate OOP in C++
class Greeter {
private:
    string name;
    int greetingCount;
    
public:
    // Constructor - called when object is created
    Greeter(const string& initialName = "World") {
        name = initialName;
        greetingCount = 0;
        cout << "Greeter object created for: " << name << endl;
    }
    
    // Destructor - called when object is destroyed
    ~Greeter() {
        cout << "Greeter object destroyed. Total greetings: " << greetingCount << endl;
    }
    
    // Method to say hello
    void sayHello() {
        greetingCount++;
        cout << "Hello, " << name << "! (Greeting #" << greetingCount << ")" << endl;
    }
    
    // Method to say goodbye
    void sayGoodbye() {
        cout << "Goodbye, " << name << "! Thanks for visiting!" << endl;
    }
    
    // Setter method
    void setName(const string& newName) {
        name = newName;
        cout << "Name changed to: " << name << endl;
    }
    
    // Getter method
    string getName() const {
        return name;
    }
    
    // Get greeting count
    int getGreetingCount() const {
        return greetingCount;
    }
};

// Function to demonstrate modern C++ features
void demonstrateModernCpp() {
    cout << "\n=== MODERN C++ FEATURES ===" << endl;
    
    // Auto keyword - type inference
    auto number = 42;
    auto message = "Modern C++ is awesome!";
    auto pi = 3.14159;
    
    cout << "Auto keyword examples:" << endl;
    cout << "Number: " << number << endl;
    cout << "Message: " << message << endl;
    cout << "Pi: " << pi << endl;
    
    // Range-based for loop (C++11)
    vector<string> languages = {"C++", "Python", "Java", "JavaScript", "Rust"};
    
    cout << "\nProgramming languages (range-based for loop):" << endl;
    for (const auto& lang : languages) {
        cout << "- " << lang << endl;
    }
    
    // Smart pointers (modern memory management)
    cout << "\nSmart pointers (automatic memory management):" << endl;
    
    // unique_ptr - exclusive ownership
    auto uniqueGreeter = make_unique<Greeter>("Smart Pointer");
    uniqueGreeter->sayHello();
    
    // When uniqueGreeter goes out of scope, memory is automatically freed!
    cout << "unique_ptr will automatically clean up memory!" << endl;
    
    // Lambda expressions (C++11)
    cout << "\nLambda expressions (anonymous functions):" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Use lambda with algorithm
    auto evenCount = count_if(numbers.begin(), numbers.end(), 
                           [](int n) { return n % 2 == 0; });
    
    cout << "Even numbers in 1-10: " << evenCount << endl;
    
    // Use lambda to transform vector
    vector<int> doubled;
    transform(numbers.begin(), numbers.end(), back_inserter(doubled),
             [](int n) { return n * 2; });
    
    cout << "Numbers doubled: ";
    for (int n : doubled) {
        cout << n << " ";
    }
    cout << endl;
}

// Function to demonstrate string handling in C++
void demonstrateStringHandling() {
    cout << "\n=== STRING HANDLING IN C++ ===" << endl;
    
    // String class methods
    string text = "C++ is powerful and efficient";
    
    cout << "Original string: " << text << endl;
    cout << "Length: " << text.length() << endl;
    cout << "First character: " << text[0] << endl;
    cout << "Last character: " << text.back() << endl;
    
    // String manipulation
    string upper = text;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    cout << "Uppercase: " << upper << endl;
    
    // String searching
    size_t pos = text.find("powerful");
    if (pos != string::npos) {
        cout << "Found 'powerful' at position: " << pos << endl;
    }
    
    // String substrings
    string substring = text.substr(0, 7);  // "C++ is "
    cout << "First 7 characters: '" << substring << "'" << endl;
    
    // String concatenation
    string greeting = "Hello";
    string target = "C++ Programmers";
    string fullGreeting = greeting + ", " + target + "!";
    cout << "Concatenated: " << fullGreeting << endl;
}

// Function to demonstrate vector operations
void demonstrateVectors() {
    cout << "\n=== VECTOR OPERATIONS ===" << endl;
    
    // Create and initialize vector
    vector<int> scores = {85, 92, 78, 96, 88};
    
    cout << "Original scores: ";
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;
    
    // Add elements
    scores.push_back(95);
    scores.insert(scores.begin(), 100);
    
    cout << "After adding: ";
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;
    
    // Sort vector
    sort(scores.begin(), scores.end());
    
    cout << "Sorted: ";
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;
    
    // Calculate statistics
    double sum = 0;
    for (int score : scores) {
        sum += score;
    }
    double average = sum / scores.size();
    
    cout << "Statistics:" << endl;
    cout << "Count: " << scores.size() << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    cout << "Highest: " << scores.back() << endl;
    cout << "Lowest: " << scores.front() << endl;
}

// Interactive function with user input
void interactiveDemo() {
    cout << "\n=== INTERACTIVE DEMO ===" << endl;
    
    // Get user input
    string userName;
    int userAge;
    string favoriteLanguage;
    
    cout << "Enter your name: ";
    getline(cin, userName);  // getline reads entire line (including spaces)
    
    cout << "Enter your age: ";
    cin >> userAge;
    cin.ignore();  // Clear newline character
    
    cout << "Enter your favorite programming language: ";
    getline(cin, favoriteLanguage);
    
    // Create personalized greeting
    Greeter userGreeter(userName);
    
    cout << "\nHello, " << userName << "!" << endl;
    cout << "You are " << userAge << " years old." << endl;
    cout << "Your favorite language is " << favoriteLanguage << "." << endl;
    
    // Give personalized response based on favorite language
    if (favoriteLanguage == "C++") {
        cout << "Excellent choice! C++ is the language of performance!" << endl;
    } else if (favoriteLanguage == "Python") {
        cout << "Python is great for rapid development!" << endl;
    } else if (favoriteLanguage == "Java") {
        cout << "Java is widely used in enterprise applications!" << endl;
    } else {
        cout << favoriteLanguage << " is an interesting choice!" << endl;
    }
    
    userGreeter.sayHello();
    userGreeter.sayGoodbye();
}

// Main function - program entry point
int main() {
    cout << "========================================" << endl;
    cout << "    HELLO WORLD IN MODERN C++" << endl;
    cout << "========================================" << endl;
    cout << "Welcome to C++ programming!" << endl;
    cout << "This demo showcases modern C++ features." << endl;
    
    // Basic hello world
    cout << "\nHello, World!" << endl;
    
    // Create a simple greeter object
    Greeter worldGreeter("World");
    worldGreeter.sayHello();
    
    // Demonstrate modern C++ features
    demonstrateModernCpp();
    
    // Demonstrate string handling
    demonstrateStringHandling();
    
    // Demonstrate vector operations
    demonstrateVectors();
    
    // Interactive demo
    interactiveDemo();
    
    cout << "\n========================================" << endl;
    cout << "    C++ DEMO COMPLETE!" << endl;
    cout << "========================================" << endl;
    cout << "You've learned:" << endl;
    cout << "1. Basic C++ syntax and structure" << endl;
    cout << "2. Object-oriented programming with classes" << endl;
    cout << "3. Modern C++ features (auto, smart pointers, lambdas)" << endl;
    cout << "4. String handling and manipulation" << endl;
    cout << "5. Vector operations and algorithms" << endl;
    cout << "6. User input and interactive programs" << endl;
    cout << "7. Memory management with smart pointers" << endl;
    cout << "\nReady for more C++ challenges?" << endl;
    cout << "Try the calculator, game, or data structure projects!" << endl;
    
    return 0;  // Return 0 to indicate successful execution
}
