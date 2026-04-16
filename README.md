# 🚀 Beginner-To-Intermediate-Hub

Welcome to the ultimate repository for learning programming! This collection is designed to help learners progress from **absolute beginners** to **intermediate developers** through hands-on projects, now spanning multiple languages!

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

## C PROGRAMMING
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
