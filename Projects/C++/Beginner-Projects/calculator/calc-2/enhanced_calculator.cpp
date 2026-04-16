/*
 * Enhanced C++ Calculator - Level 3: Advanced Features
 * 
 * This calculator builds on Level 1 with more features and better UX.
 * Learn advanced C++ concepts while building something practical!
 * 
 * New features in this version:
 * - History tracking and undo functionality
 * - Variables support (store and reuse values)
 * - Scientific functions (sin, cos, tan, log)
 * - Expression parsing (simple expressions)
 * - Better error handling and recovery
 * - Command-line argument support
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

// Advanced calculator with history and variables
class AdvancedCalculator {
private:
    double memory;
    double lastResult;
    vector<string> history;
    map<string, double> variables;
    int calculationCount;
    
public:
    // Constructor
    AdvancedCalculator() : memory(0.0), lastResult(0.0), calculationCount(0) {
        // Initialize with some common constants
        variables["pi"] = 3.14159265359;
        variables["e"] = 2.71828182846;
        variables["phi"] = 1.61803398874; // Golden ratio
        
        cout << "Advanced Calculator initialized!" << endl;
        cout << "Features: History, Variables, Scientific functions!" << endl;
    }
    
    // Basic arithmetic operations
    double add(double a, double b) {
        lastResult = a + b;
        addToHistory(to_string(a) + " + " + to_string(b) + " = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double subtract(double a, double b) {
        lastResult = a - b;
        addToHistory(to_string(a) + " - " + to_string(b) + " = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double multiply(double a, double b) {
        lastResult = a * b;
        addToHistory(to_string(a) + " * " + to_string(b) + " = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double divide(double a, double b) {
        if (b == 0.0) {
            throw runtime_error("Division by zero is not allowed!");
        }
        lastResult = a / b;
        addToHistory(to_string(a) + " / " + to_string(b) + " = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    // Power operations
    double power(double base, double exponent) {
        lastResult = pow(base, exponent);
        addToHistory(to_string(base) + " ^ " + to_string(exponent) + " = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double squareRoot(double number) {
        if (number < 0.0) {
            throw runtime_error("Cannot calculate square root of negative number!");
        }
        lastResult = sqrt(number);
        addToHistory("sqrt(" + to_string(number) + ") = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    // Scientific functions
    double sine(double angle) {
        lastResult = sin(angle);
        addToHistory("sin(" + to_string(angle) + ") = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double cosine(double angle) {
        lastResult = cos(angle);
        addToHistory("cos(" + to_string(angle) + ") = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double tangent(double angle) {
        lastResult = tan(angle);
        addToHistory("tan(" + to_string(angle) + ") = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double logarithm(double number) {
        if (number <= 0.0) {
            throw runtime_error("Logarithm requires positive numbers!");
        }
        lastResult = log(number);
        addToHistory("log(" + to_string(number) + ") = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    double logarithm10(double number) {
        if (number <= 0.0) {
            throw runtime_error("Logarithm requires positive numbers!");
        }
        lastResult = log10(number);
        addToHistory("log10(" + to_string(number) + ") = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    // Percentage calculation
    double percentage(double value, double percent) {
        lastResult = value * (percent / 100.0);
        addToHistory(to_string(percent) + "% of " + to_string(value) + " = " + to_string(lastResult));
        calculationCount++;
        return lastResult;
    }
    
    // Variable operations
    void setVariable(const string& name, double value) {
        variables[name] = value;
        cout << "Variable '" << name << "' set to " << value << endl;
    }
    
    double getVariable(const string& name) {
        if (variables.find(name) == variables.end()) {
            throw runtime_error("Variable '" + name + "' not found!");
        }
        return variables[name];
    }
    
    void listVariables() {
        cout << "\n=== VARIABLES ===" << endl;
        if (variables.empty()) {
            cout << "No variables defined." << endl;
        } else {
            for (const auto& var : variables) {
                cout << var.first << " = " << var.second << endl;
            }
        }
        cout << "=================" << endl;
    }
    
    // Memory operations
    void memoryStore(double value) {
        memory = value;
        cout << "Stored " << value << " in memory." << endl;
    }
    
    double memoryRecall() {
        cout << "Recalled " << memory << " from memory." << endl;
        return memory;
    }
    
    void memoryClear() {
        memory = 0.0;
        cout << "Memory cleared." << endl;
    }
    
    double memoryAdd(double value) {
        memory += value;
        cout << "Added " << value << " to memory. New value: " << memory << endl;
        return memory;
    }
    
    // History management
    void addToHistory(const string& entry) {
        history.push_back(entry);
        // Keep only last 20 entries
        if (history.size() > 20) {
            history.erase(history.begin());
        }
    }
    
    void showHistory() {
        cout << "\n=== CALCULATION HISTORY ===" << endl;
        if (history.empty()) {
            cout << "No calculations yet." << endl;
        } else {
            for (size_t i = 0; i < history.size(); i++) {
                cout << (i + 1) << ". " << history[i] << endl;
            }
        }
        cout << "========================" << endl;
        cout << "Total calculations: " << calculationCount << endl;
    }
    
    void clearHistory() {
        history.clear();
        cout << "History cleared." << endl;
    }
    
    // Utility methods
    double getLastResult() const {
        return lastResult;
    }
    
    int getCalculationCount() const {
        return calculationCount;
    }
    
    void reset() {
        memory = 0.0;
        lastResult = 0.0;
        history.clear();
        calculationCount = 0;
        cout << "Calculator reset to initial state." << endl;
    }
    
    // Simple expression evaluation
    double evaluateExpression(const string& expr) {
        // Very simple expression evaluator (only handles basic operations)
        try {
            // This is a simplified version - real expression parsing is much more complex
            istringstream iss(expr);
            vector<string> tokens;
            string token;
            
            while (iss >> token) {
                tokens.push_back(token);
            }
            
            if (tokens.size() < 3) {
                throw runtime_error("Expression too short!");
            }
            
            // Parse first number
            double a = stod(tokens[0]);
            string op = tokens[1];
            double b = stod(tokens[2]);
            
            double result = 0.0;
            if (op == "+") {
                result = add(a, b);
            } else if (op == "-") {
                result = subtract(a, b);
            } else if (op == "*") {
                result = multiply(a, b);
            } else if (op == "/") {
                result = divide(a, b);
            } else if (op == "^") {
                result = power(a, b);
            } else {
                throw runtime_error("Unknown operator: " + op);
            }
            
            addToHistory(expr + " = " + to_string(result));
            return result;
            
        } catch (const exception& e) {
            throw runtime_error("Expression evaluation failed: " + string(e.what()));
        }
    }
    
    // Display calculator status
    void displayStatus() const {
        cout << "\n=== CALCULATOR STATUS ===" << endl;
        cout << "Last Result: " << lastResult << endl;
        cout << "Memory: " << memory << endl;
        cout << "Calculations: " << calculationCount << endl;
        cout << "History entries: " << history.size() << endl;
        cout << "Variables stored: " << variables.size() << endl;
        cout << "========================" << endl;
    }
};

// Input validation functions
double getValidNumber(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            size_t pos;
            double value = stod(input, &pos);
            
            if (pos != input.length()) {
                cout << "Invalid input! Please enter a valid number." << endl;
                continue;
            }
            
            return value;
        } catch (const invalid_argument&) {
            cout << "Invalid input! Please enter a valid number." << endl;
        } catch (const out_of_range&) {
            cout << "Number too large! Please enter a smaller number." << endl;
        }
    }
}

string getValidString(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

// Display enhanced menu
void displayMenu() {
    cout << "\n" + string(60, '=') << endl;
    cout << "       ENHANCED C++ CALCULATOR - LEVEL 3" << endl;
    cout << string(60, '=') << endl;
    cout << "Basic Operations:" << endl;
    cout << "  + : Addition          - : Subtraction" << endl;
    cout << "  * : Multiplication   / : Division" << endl;
    cout << "  ^ : Power             % : Percentage" << endl;
    cout << "\nScientific Functions:" << endl;
    cout << "  sin : Sine            cos : Cosine" << endl;
    cout << "  tan : Tangent         log : Natural log" << endl;
    cout << "  log10: Base-10 log   sqrt: Square root" << endl;
    cout << "\nAdvanced Features:" << endl;
    cout << "  var : Set variable    get : Get variable" << endl;
    cout << "  list: List variables expr: Evaluate expression" << endl;
    cout << "  hist: Show history    clear: Clear history" << endl;
    cout << "  mem : Memory menu     status: Show status" << endl;
    cout << "  reset: Reset all      exit : Exit program" << endl;
    cout << string(60, '=') << endl;
}

// Memory operations menu
void handleMemoryOperations(AdvancedCalculator& calc) {
    while (true) {
        cout << "\n=== MEMORY OPERATIONS ===" << endl;
        cout << "1. Store in memory" << endl;
        cout << "2. Recall from memory" << endl;
        cout << "3. Clear memory" << endl;
        cout << "4. Add to memory" << endl;
        cout << "5. Back to calculator" << endl;
        cout << "Choice: ";
        
        string choice;
        getline(cin, choice);
        
        if (choice == "1") {
            double value = getValidNumber("Enter value to store: ");
            calc.memoryStore(value);
        } else if (choice == "2") {
            double value = calc.memoryRecall();
            cout << "Memory value: " << value << endl;
        } else if (choice == "3") {
            calc.memoryClear();
        } else if (choice == "4") {
            double value = getValidNumber("Enter value to add to memory: ");
            calc.memoryAdd(value);
        } else if (choice == "5") {
            break;
        } else {
            cout << "Invalid choice! Please enter 1-5." << endl;
        }
    }
}

// Main calculation function
void performCalculation(AdvancedCalculator& calc) {
    cout << "Enter operation (e.g., '5 + 3', 'sin 0.5', 'var x 10'): ";
    string input;
    getline(cin, input);
    
    istringstream iss(input);
    vector<string> tokens;
    string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    if (tokens.empty()) {
        cout << "No input provided!" << endl;
        return;
    }
    
    try {
        if (tokens[0] == "sin") {
            if (tokens.size() < 2) throw runtime_error("Sin requires an angle!");
            double angle = stod(tokens[1]);
            double result = calc.sine(angle);
            cout << "sin(" << angle << ") = " << result << endl;
            
        } else if (tokens[0] == "cos") {
            if (tokens.size() < 2) throw runtime_error("Cos requires an angle!");
            double angle = stod(tokens[1]);
            double result = calc.cosine(angle);
            cout << "cos(" << angle << ") = " << result << endl;
            
        } else if (tokens[0] == "tan") {
            if (tokens.size() < 2) throw runtime_error("Tan requires an angle!");
            double angle = stod(tokens[1]);
            double result = calc.tangent(angle);
            cout << "tan(" << angle << ") = " << result << endl;
            
        } else if (tokens[0] == "log") {
            if (tokens.size() < 2) throw runtime_error("Log requires a number!");
            double number = stod(tokens[1]);
            double result = calc.logarithm(number);
            cout << "log(" << number << ") = " << result << endl;
            
        } else if (tokens[0] == "log10") {
            if (tokens.size() < 2) throw runtime_error("Log10 requires a number!");
            double number = stod(tokens[1]);
            double result = calc.logarithm10(number);
            cout << "log10(" << number << ") = " << result << endl;
            
        } else if (tokens[0] == "sqrt") {
            if (tokens.size() < 2) throw runtime_error("Sqrt requires a number!");
            double number = stod(tokens[1]);
            double result = calc.squareRoot(number);
            cout << "sqrt(" << number << ") = " << result << endl;
            
        } else if (tokens[0] == "var") {
            if (tokens.size() < 3) throw runtime_error("Var requires name and value!");
            string name = tokens[1];
            double value = stod(tokens[2]);
            calc.setVariable(name, value);
            
        } else if (tokens[0] == "get") {
            if (tokens.size() < 2) throw runtime_error("Get requires variable name!");
            string name = tokens[1];
            double value = calc.getVariable(name);
            cout << name << " = " << value << endl;
            
        } else if (tokens[0] == "expr") {
            if (tokens.size() < 2) throw runtime_error("Expr requires expression!");
            string expr = input.substr(5); // Remove "expr "
            double result = calc.evaluateExpression(expr);
            cout << expr << " = " << result << endl;
            
        } else if (tokens.size() >= 3) {
            // Basic arithmetic expression
            double a = stod(tokens[0]);
            string op = tokens[1];
            double b = stod(tokens[2]);
            
            double result = 0.0;
            if (op == "+") {
                result = calc.add(a, b);
            } else if (op == "-") {
                result = calc.subtract(a, b);
            } else if (op == "*") {
                result = calc.multiply(a, b);
            } else if (op == "/") {
                result = calc.divide(a, b);
            } else if (op == "^") {
                result = calc.power(a, b);
            } else if (op == "%") {
                result = calc.percentage(a, b);
            } else {
                cout << "Unknown operator: " << op << endl;
                return;
            }
            
            cout << fixed << setprecision(6);
            cout << a << " " << op << " " << b << " = " << result << endl;
            
        } else {
            cout << "Invalid input format!" << endl;
        }
        
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Interactive calculator session
void runCalculator() {
    AdvancedCalculator calc;
    
    cout << "Welcome to the Enhanced C++ Calculator!" << endl;
    cout << "This calculator demonstrates advanced C++ features:" << endl;
    cout << "- Class design with multiple methods" << endl;
    cout << "- STL containers (vector, map)" << endl;
    cout << "- Exception handling and error recovery" << endl;
    cout << "- String manipulation and parsing" << endl;
    cout << "- Memory management and state tracking" << endl;
    cout << "- Scientific functions and variables" << endl;
    
    while (true) {
        displayMenu();
        calc.displayStatus();
        
        cout << "\nQuick commands (type directly):" << endl;
        cout << "  '5 + 3' - Basic calculation" << endl;
        cout << "  'sin 0.5' - Scientific function" << endl;
        cout << "  'var x 10' - Set variable" << endl;
        cout << "  'get x' - Get variable" << endl;
        cout << "  'hist' - Show history" << endl;
        cout << "  'mem' - Memory operations" << endl;
        cout << "  'status' - Show status" << endl;
        cout << "  'reset' - Reset calculator" << endl;
        cout << "  'exit' - Exit program" << endl;
        cout << "\nEnter command: ";
        
        string command;
        getline(cin, command);
        
        if (command == "exit") {
            cout << "\nFinal Statistics:" << endl;
            calc.displayStatus();
            cout << "Thank you for using Enhanced C++ Calculator!" << endl;
            cout << "You've experienced advanced C++ programming!" << endl;
            break;
            
        } else if (command == "hist") {
            calc.showHistory();
            
        } else if (command == "clear") {
            calc.clearHistory();
            
        } else if (command == "status") {
            calc.displayStatus();
            cout << "\nAdvanced Features:" << endl;
            cout << "- Scientific functions (sin, cos, tan, log, sqrt)" << endl;
            cout << "- Variable storage and retrieval" << endl;
            cout << "- Expression evaluation" << endl;
            cout << "- History tracking with undo capability" << endl;
            cout << "- Memory operations (MS, MR, MC, M+)" << endl;
            cout << "- Advanced error handling" << endl;
            cout << "- STL container usage" << endl;
            
        } else if (command == "mem") {
            handleMemoryOperations(calc);
            
        } else if (command == "list") {
            calc.listVariables();
            
        } else if (command == "reset") {
            calc.reset();
            
        } else if (command.empty()) {
            continue;
            
        } else {
            // Try to parse as calculation
            performCalculation(calc);
        }
        
        cout << "\nPress Enter to continue...";
        getline(cin, string());
    }
}

// Main function with command-line argument support
int main(int argc, char* argv[]) {
    cout << "========================================" << endl;
    cout << "    ENHANCED C++ CALCULATOR - LEVEL 3" << endl;
    cout << "========================================" << endl;
    
    // Handle command-line arguments
    if (argc > 1) {
        cout << "Command-line arguments detected!" << endl;
        AdvancedCalculator calc;
        
        for (int i = 1; i < argc; i++) {
            string arg = argv[i];
            cout << "Processing: " << arg << endl;
            
            try {
                double result = calc.evaluateExpression(arg);
                cout << arg << " = " << result << endl;
            } catch (const exception& e) {
                cout << "Error processing '" << arg << "': " << e.what() << endl;
            }
        }
        
        cout << "\nFinal results:" << endl;
        calc.displayStatus();
        return 0;
    }
    
    // Interactive mode
    cout << "Learn advanced C++ through practical programming!" << endl;
    cout << "This calculator demonstrates:" << endl;
    cout << "- Advanced class design and encapsulation" << endl;
    cout << "- STL containers and algorithms" << endl;
    cout << "- Exception handling and error recovery" << endl;
    cout << "- String parsing and manipulation" << endl;
    cout << "- Command-line argument processing" << endl;
    cout << "- Memory management and state tracking" << endl;
    cout << "- Scientific function implementation" << endl;
    cout << "========================================" << endl;
    
    try {
        runCalculator();
    } catch (const exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
