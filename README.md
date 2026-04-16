# 🚀 Beginner-To-Intermediate-Hub

Welcome to the ultimate repository for learning programming! This collection is designed to help learners progress from **absolute beginners** to **intermediate developers** through hands-on projects, now spanning multiple languages!

##  How to Use This Repository

### Quick Start Guide

1. **Choose Your Language**: Pick Python, C, C++, or Rust based on your goals
2. **Check Prerequisites**: Install required tools (see detailed setup below)
3. **Start at Level 1**: Begin with beginner projects and work your way up
4. **Follow the Instructions**: Each project has its own README with detailed steps
5. **Experiment and Learn**: Modify the code, try new ideas, and have fun!

###  Installation & Setup

#### Python Setup
```bash
# Check Python installation
python --version

# Install dependencies for all projects
pip install -r requirements.txt

# Run a Python project
python Projects/Python/Beginner-Projects/calculator/calc-1/calculator.py
```

**Required for Python:**
- Python 3.7 or higher
- pip (Python package manager)
- IDE or text editor (VS Code recommended)

#### C Setup
```bash
# Check GCC installation
gcc --version

# Compile a C project
gcc Projects/C/Beginner-Projects/calculator/calc-1/calculator.c -o calculator

# Run the compiled program
./calculator
```

**Required for C:**
- GCC compiler (MinGW-w64 on Windows, build-essential on Linux)
- Make or build system
- IDE or text editor

#### C++ Setup
```bash
# Check C++ compiler
g++ --version

# Compile a C++ project
g++ -std=c++17 Projects/C++/Beginner-Projects/calculator/calc-1/calculator.cpp -o calculator

# Run the compiled program
./calculator
```

**Required for C++:**
- C++17 compatible compiler (g++, clang++, or MSVC)
- Standard library
- IDE or text editor

#### Rust Setup
```bash
# Install Rust (if not already installed)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# Check Rust installation
rustc --version
cargo --version

# Run a Rust project
cd Projects/Rust/Beginner-Projects/hello-rust/hello-1
cargo run
```

**Required for Rust:**
- Rust toolchain (rustup)
- Cargo (package manager)
- IDE or text editor

###  Project Structure & Running

#### Python Projects
```bash
# Navigate to project
cd Projects/Python/Beginner-Projects/[project-name]/[level]/

# Install specific dependencies (if requirements.txt exists)
pip install -r requirements.txt

# Run the program
python script.py
```

#### C Projects
```bash
# Navigate to project
cd Projects/C/Beginner-Projects/[project-name]/[level]/

# Compile
gcc script.c -o program

# Run
./program
```

#### C++ Projects
```bash
# Navigate to project
cd Projects/C++/Beginner-Projects/[project-name]/[level]/

# Compile with C++17 standard
g++ -std=c++17 script.cpp -o program

# Run
./program
```

#### Rust Projects
```bash
# Navigate to project
cd Projects/Rust/Beginner-Projects/[project-name]/[level]/

# Run with Cargo (recommended)
cargo run

# Or compile and run manually
rustc main.rs
./main
```

###  Common Issues & Solutions

#### Python Issues
- **ModuleNotFoundError**: Run `pip install -r requirements.txt`
- **Python version**: Ensure you're using Python 3.7+
- **Path issues**: Use `python` instead of `python3` if needed

#### C/C++ Issues
- **Compiler not found**: Install GCC/MinGW-w64
- **Permission denied**: Use `chmod +x program` on Linux/macOS
- **Linking errors**: Check if you're using the correct compiler flags

#### Rust Issues
- **Cargo not found**: Install Rust using rustup
- **Permission denied**: Check file permissions
- **Compilation errors**: Ensure you're using the correct Rust edition

###  IDE Recommendations

#### Visual Studio Code (All Languages)
- Extensions: Python, C/C++, Rust
- Integrated terminal
- Debugging support

#### PyCharm (Python)
- Professional Python IDE
- Built-in debugger
- Virtual environment support

#### CLion (C/C++/Rust)
- Professional C/C++ IDE
- Rust support via plugin
- Integrated debugger

#### Vim/Emacs (All Languages)
- Lightweight and powerful
- Highly customizable
- Great for learning

###  Learning Path

1. **Start Simple**: Begin with "Hello, World!" projects
2. **Progress Gradually**: Move through levels 1-10
3. **Experiment**: Modify code and see what happens
4. **Build Projects**: Create your own variations
5. **Share**: Contribute back to the repository

###  Getting Help

- **Project READMEs**: Each project has detailed instructions
- **Code Comments**: Extensive explanations in the code
- **Community**: Ask questions in GitHub discussions
- **Documentation**: Check language-specific documentation

## 📚 Quick Start Guide

### 📝 For Complete Beginners
1. **Choose your language**: Python (easier) or C (fundamentals)
2. **Install the tools**: See setup guides below
3. **Start with Level 1**: Follow the learning path
4. **Compile and run**: Each project has instructions

### 🛠️ Setup Instructions
- **Python Setup**: [Python Setup Guide](./Projects/Python/Beginner-Projects/README.md)
- **C Setup**: [C Setup Guide](./Projects/C/Beginner-Projects/README.md)

### 🗂️ Repository Structure
```
beginner-projects/
  Projects/
    Python/
      Beginner-Projects/    # 11 projects, Levels 1-3
      Intermediate-Projects/ # 5 projects, Levels 9-10+
    C/
      Beginner-Projects/    # 6 projects, Levels 1-4
      Intermediate-Projects/ # 2 projects, Levels 5-6+
```

## 📊 How This Repository Works

### 🚫 No Executable Files 
This repository contains **source code only**. You'll learn to compile and run programs yourself - this is part of the learning process!

### 📈 Progressive Learning
Each language has a **level system** that builds skills progressively:
- **Level 1-3**: Core concepts (no external libraries)
- **Level 4-6**: Standard libraries and intermediate concepts  
- **Level 7-8**: GUI and visual applications
- **Level 9-10+**: Real-world applications (APIs, databases, web)

### 📁 Each Project Includes
-  Source code with detailed comments
-  README with step-by-step instructions
-  Learning objectives and key concepts
-  Challenges to test your skills
-  Troubleshooting guide

### 🛠️ Dependency Management
**Python Projects**: Each intermediate project includes `requirements.txt` with exact package versions:
```bash
pip install -r requirements.txt
```

**C Projects**: All projects use standard C libraries only. No external dependencies needed!

### 🧪 Professional Testing
- **Python**: `pytest` framework for unit testing
- **C**: Unity-style testing framework included
- **Test-driven development** examples provided

---

## 🐍 PYTHON PROGRAMMING

### 📈 The Universal Level System (Python)
Across all Python projects in this repository, you will find a consistent "Level System":
- **Levels 1 to 3 (Core Python)**: Pure logic. Absolutely **NO** imported libraries. You will learn the raw mechanics of loops, variables, functions, and classes.
- **Levels 4 to 6 (The Standard Library)**: These levels introduce Python's "built-in" libraries (like `math`, `json`, `datetime`). We always explicitly state why the library is used and how it replaces hard manual work.
- **Levels 7 to 8 (Early Intermediate/GUIs)**: The "Boss Levels." We wrap our code in visual windows using the built-in `tkinter` library.
- **Levels 9 to 10+ (The Real World)**: The true Intermediate tier! Here, we finally use `pip` to install **Third-Party Libraries** (like `requests` and `BeautifulSoup4`). We talk to the Internet (APIs/Scraping), build Relational Databases (`sqlite3`), and analyze real-world data.

### 🌱 Beginner Projects

#### 🧮 1. Calculator Project
*Learn conditional logic, mathematics, and interface building.*
- **[Level 1: The Simplest Method](./Projects/Python/Beginner-Projects/calculator/calculator-1/)** (Basic variables and if-else).
- **[Level 2: The Modular Method](./Projects/Python/Beginner-Projects/calculator/calculator-2/)** (Using functions).
- **[Level 3: The Advanced Method](./Projects/Python/Beginner-Projects/calculator/calculator-3/)** (Using classes and error handling).
- **[Level 4: The "Elegant" Method](./Projects/Python/Beginner-Projects/calculator/calculator-4/)** (Dictionary mapping and `operator`).
- **[Level 5: The "Visual" Method](./Projects/Python/Beginner-Projects/calculator/calculator-5/)** (Basic GUI with `tkinter`).
- **[Level 6: Precision Physics Method](./Projects/Python/Beginner-Projects/calculator/calculator-6/)** (`math` and `decimal`).
- **[Level 7: The Pro GUI Edition](./Projects/Python/Beginner-Projects/calculator/calculator-7/)** (Advanced `tkinter` & Keyboard Binding).

#### 2. To-Do List Project
*Learn data structures, persistent storage, and memory management.*
- **[Level 1: The Memory Track](./Projects/Python/Beginner-Projects/todo-list/todo-1/)** (Lists, while-loops).
- **[Level 2: The File Keeper](./Projects/Python/Beginner-Projects/todo-list/todo-2/)** (File I/O `.txt`).
*Learn control flow, exception handling, and basic algorithms.*
- **[Level 1: The Basic Loop](./Projects/Python/Beginner-Projects/number-guesser/guesser-1/)** (While-loops and random matching).
- **[Level 2: Bulletproof Code](./Projects/Python/Beginner-Projects/number-guesser/guesser-2/)** (`try/except ValueError` to stop crashes).
- **[Level 3: Persistent High Scores](./Projects/Python/Beginner-Projects/number-guesser/guesser-3/)** (Tracking best scores via File I/O).

#### 🖐️ 3. Rock, Paper, Scissors
*Learn game logic, randomization, and user input validation.*
- **[Level 1: Classic Game](./Projects/Python/Beginner-Projects/rock-paper-scissors/rps-1/)** (Game mechanics and score tracking).

#### 🎯 4. Hangman Game
*Learn string manipulation, loops, and game state management.*
- **[Level 1: Word Guessing](./Projects/Python/Beginner-Projects/hangman/hangman-1/)** (Visual hangman and word management).

#### 🏦 5. Bank Account Manager
*Learn object-oriented programming, classes, and financial logic.*
- **[Level 1: Basic Banking](./Projects/Python/Beginner-Projects/bank-account/account-1/)** (Account management and transactions).

#### 📇 6. Contact Book
*Learn data structures, search algorithms, and CRUD operations.*
- **[Level 1: Contact Management](./Projects/Python/Beginner-Projects/contact-book/contact-1/)** (Add, search, update, delete contacts).

#### 🌡️ 7. Temperature Converter
*Learn mathematical operations, functions, and unit conversions.*
- **[Level 1: Unit Conversion](./Projects/Python/Beginner-Projects/temperature-converter/converter-1/)** (Temperature scales and conversion formulas).

#### 📊 8. Student Grade Manager
*Learn OOP, data structures, and statistical calculations.*
- **[Level 1: Grade Management](./Projects/Python/Beginner-Projects/student-grades/grades-1/)** (Classes, averages, letter grades).

#### 🎮 9. Text Adventure Game
*Learn game development, state management, and interactive storytelling.*
- **[Level 2: Interactive Storytelling](./Projects/Python/Beginner-Projects/text-adventure/game-1/)** (Room exploration, combat, inventory systems).

####  10. Hello, World! Masterclass
*The ultimate "Hello, World!" experience - from simplest to most complex methods!*
- **[Level 1: The Complete Journey](./Projects/Python/Beginner-Projects/hello-world/)** (35 different methods from beginner to expert level!).

### 🚀 Intermediate Projects
*These projects require connecting to the internet, using databases, and `pip install`.*

#### 🌦️ 1. Live Weather Dashboard (API Integration)
- **[Level 9: The Raw Network Call](./Projects/Python/Intermediate-Projects/weather-app/weather-9/)** (`pip install requests` to fetch API JSON).
- **[Level 10: Live Visual Dashboard](./Projects/Python/Intermediate-Projects/weather-app/weather-10/)** (Asynchronous threading to prevent GUI freezing).

#### 2. Personal Expense Tracker (Relational Databases)
- **[Level 9: The SQLite Database](./Projects/Python/Intermediate-Projects/expense-tracker/expense-9/)** (`sqlite3` built-in library, SQL Queries).
- **[Level 10: Advanced Reporting](./Projects/Python/Intermediate-Projects/expense-tracker/expense-10/)** (`pip install prettytable`, SQL `SUM` and `GROUP BY`).

#### 3. Web API Client
*Learn HTTP requests, JSON parsing, and external service integration.*
- **[Level 9: API Integration](./Projects/Python/Intermediate-Projects/web-api/api-1/)** (`requests` library, error handling, demo weather API).

#### 4. Web Scraper Data Miner (HTML Parsing)
- **[Level 9: The HTML Extractor](./Projects/Python/Intermediate-Projects/web-scraper/scraper-1/)** (`pip install beautifulsoup4` to scrape text from websites).
- **[Level 10: The CSV Exporter](./Projects/Python/Intermediate-Projects/web-scraper/scraper-10/)** (Automatically scraping multi-page sites and saving to Excel `.csv`).

#### 5. Async Weather Dashboard
*Learn threading and asynchronous programming to prevent GUI freezing.*
- **[Level 10: GUI Threading](./Projects/Python/Intermediate-Projects/async-weather/weather-1/)** (`tkinter` + `threading` for responsive interfaces).

#### 6. Unit Testing Framework
*Learn professional testing practices - what separates hobbyists from professionals.*
- **[Level 10: Test-Driven Development](./Projects/Python/Intermediate-Projects/unit-testing/test-1/)** (`pytest` framework, test design, code quality).

---

##  C++ PROGRAMMING

###  C++ Level System
C++ bridges the gap between low-level control and high-level abstraction:
- **Level 1-2**: Modern C++ syntax, classes, and OOP
- **Level 3-4**: STL containers, smart pointers, and memory management
- **Level 5-6**: Template programming and advanced features
- **Level 7-8**: GUI programming with Qt or frameworks
- **Level 9-10**: Performance optimization and systems programming

###  C++ Beginner Projects

####  1. Hello World Modern C++
*Learn modern C++ syntax, classes, and standard library features.*
- **[Level 1: Modern C++ Introduction](./Projects/C++/Beginner-Projects/hello-cpp/hello-1/)** (Auto keyword, smart pointers, lambda expressions).

####  2. Object-Oriented Calculator
*Master C++ classes, methods, and exception handling.*
- **[Level 2: OOP Calculator](./Projects/C++/Beginner-Projects/calculator/calc-1/)** (Class design, method overloading, input validation).

---

##  RUST PROGRAMMING

###  Rust Level System
Rust provides safety without sacrificing performance:
- **Level 1-2**: Ownership, borrowing, and basic syntax
- **Level 3-4**: Pattern matching, error handling, and collections
- **Level 5-6**: Lifetimes, traits, and advanced features
- **Level 7-8**: Concurrent programming and async
- **Level 9-10**: Systems programming and performance

###  Rust Beginner Projects

####  1. Hello World Safe Systems
*Learn Rust's ownership system, pattern matching, and memory safety.*
- **[Level 1: Safe Systems Programming](./Projects/Rust/Beginner-Projects/hello-rust/hello-1/)** (Ownership, borrowing, Result type, modern syntax).

####  2. Safe Calculator
*Master Rust's safety guarantees and modern syntax.*
- **[Level 2: Safe Calculator](./Projects/Rust/Beginner-Projects/calculator/calc-1/)** (Pattern matching, error handling, structs, enums).

---

##  C PROGRAMMING
C is a low-level, compiled language. Unlike Python, there is no "magic" involved. We must declare our variables strictly and manually build our logic. 
*Note: To run these, you require a compiler like `gcc` (MinGW-w64 on Windows).*

### 🛠️ The C Level System
- **Level 1**: Basic Compilation & I/O (`printf`, `scanf`, basic variables and math).
- **Level 2**: Control Structures (Loops, `switch` statements, building menus).
- **Level 3**: Functions, Arrays, and Intro to Pointers (Passing by reference).
- **Level 4**: Structs and dynamic memory allocation (`malloc`, `free`, handling RAM natively).

### 🌱 Beginner Projects

#### 👋 1. The Advanced Greeter
*Learn how to take user input, format strings, and calculate basic math.*
- **[Level 1: Basic I/O](./Projects/C/Beginner-Projects/greeter/greeter-1/)** (Using `printf` and `scanf`).

#### 🧮 2. Terminal Calculator
*Learn control flow, functions, and menu systems.*
- **[Level 1: Basic Operations](./Projects/C/Beginner-Projects/calculator/calc-1/)** (Switch-case and basic arithmetic).
- **[Level 2: Modular Design](./Projects/C/Beginner-Projects/calculator/calc-2/)** (Functions and menu systems).

#### 🎲 3. Number Guessing Game
*Learn randomization, loops, and game logic.*
- **[Level 1: Basic Game](./Projects/C/Beginner-Projects/number-guesser/guess-1/)** (Random numbers and input validation).

#### 🎮 4. Text RPG Game
*Learn game development, character systems, and combat mechanics.*
- **[Level 3: Game Systems](./Projects/C/Beginner-Projects/rpg-game/game-1/)** (Character stats, combat, leveling system).

#### 4. Memory-Managed To-Do List
*The Ultimate C Boss! Learn how to manage the computer's physical RAM.*
- **[Level 1: Struct-Based Manager](./Projects/C/Beginner-Projects/todo-list/todo-1/)** (Structs, arrays, and menu systems).
- **[Level 4: Memory Mastery](./Projects/C/Beginner-Projects/todo-list/todo-4/)** (Using `malloc()` to dynamically allocate memory, and `free()` to prevent leaks!).

#### 5. Sorting Algorithms
*Master fundamental algorithms and data manipulation.*
- **[Level 2: Algorithm Implementation](./Projects/C/Beginner-Projects/sorting-algorithms/sort-1/)** (Bubble, Selection, Insertion sort with performance analysis).

#### 6. String Operations
*Master string manipulation, character arrays, and text processing.*
- **[Level 1: Text Processing](./Projects/C/Beginner-Projects/string-operations/string-1/)** (String functions, case conversion, word counting).

#### 7. File Manager
*Learn file I/O, file operations, and persistence.*
- **[Level 1: Basic File Operations](./Projects/C/Beginner-Projects/file-manager/file-1/)** (Create, read, append, delete files).

###  Network Programming (Level 6)
*Learn socket programming, client-server architecture, and network protocols.*
- **[Level 6: TCP Server](./Projects/C/Beginner-Projects/network-programming/net-1/)** (Socket programming, multi-client handling, select()).

### 🚀 Intermediate Projects
*These projects require advanced C concepts, file I/O, and data structures.*

#### 1. Student Database System
*Learn file persistence, data structures, and database concepts.*
- **[Level 5: File-Based Database](./Projects/C/Intermediate-Projects/database/db-1/)** (Binary file I/O, CRUD operations, statistics).

#### 2. Linked List Data Structure
*Master dynamic data structures and pointer manipulation.*
- **[Level 5: Dynamic Structures](./Projects/C/Intermediate-Projects/linked-list/list-1/)** (Node creation, memory management, linked operations).

#### 3. Network Programming (Coming Soon)
*Learn socket programming, client-server architecture, and network protocols.*
- **[Level 6: Basic TCP Server](./Projects/C/Intermediate-Projects/network/net-1/)** (Socket programming, client-server communication).

---
*Happy Coding!* 💻
