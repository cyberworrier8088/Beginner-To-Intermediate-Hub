# 🚀 Beginner-To-Intermediate-Hub

Welcome to the ultimate repository for learning programming! This collection is designed to help learners progress from **absolute beginners** to **intermediate developers** through hands-on projects, now spanning multiple languages!

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
- **[Level 3: The JSON Database](./Projects/Python/Beginner-Projects/todo-list/todo-3/)** (`json` library for structured data).
- **[Level 4: The Visual Planner](./Projects/Python/Beginner-Projects/todo-list/todo-4/)** (A beautiful `tkinter` window application).

#### 3. Random Password Generator
*Learn string manipulation, randomization algorithms, and security basics.*
- **[Level 1: Basic Logic](./Projects/Python/Beginner-Projects/password-gen/password-1/)** (`random` built-in library).
- **[Level 2: Configurable OOP](./Projects/Python/Beginner-Projects/password-gen/password-2/)** (`string` built-in library and customizable rules).
- **[Level 3: Visual Generator](./Projects/Python/Beginner-Projects/password-gen/password-3/)** (`tkinter` dashboard with sliders).

#### 🎲 4. Number Guessing Game
*Learn control flow, exception handling, and basic algorithms.*
- **[Level 1: The Basic Loop](./Projects/Python/Beginner-Projects/number-guesser/guesser-1/)** (While-loops and random matching).
- **[Level 2: Bulletproof Code](./Projects/Python/Beginner-Projects/number-guesser/guesser-2/)** (`try/except ValueError` to stop crashes).
- **[Level 3: Persistent High Scores](./Projects/Python/Beginner-Projects/number-guesser/guesser-3/)** (Tracking best scores via File I/O).

#### 🖐️ 5. Rock, Paper, Scissors
*Learn game logic, randomization, and user input validation.*
- **[Level 1: Classic Game](./Projects/Python/Beginner-Projects/rock-paper-scissors/rps-1/)** (Game mechanics and score tracking).

#### 🎯 6. Hangman Game
*Learn string manipulation, loops, and game state management.*
- **[Level 1: Word Guessing](./Projects/Python/Beginner-Projects/hangman/hangman-1/)** (Visual hangman and word management).

#### 🏦 7. Bank Account Manager
*Learn object-oriented programming, classes, and financial logic.*
- **[Level 1: Basic Banking](./Projects/Python/Beginner-Projects/bank-account/account-1/)** (Account management and transactions).

#### 📇 8. Contact Book
*Learn data structures, search algorithms, and CRUD operations.*
- **[Level 1: Contact Management](./Projects/Python/Beginner-Projects/contact-book/contact-1/)** (Add, search, update, delete contacts).

####  9. Hello, World! Masterclass
*The ultimate "Hello, World!" experience - from simplest to most complex methods!*
- **[Level 1: The Complete Journey](./Projects/Python/Beginner-Projects/Hello, world/)** (35 different methods from beginner to expert level!)

### 🚀 Intermediate Projects
*These projects require connecting to the internet, using databases, and `pip install`.*

#### 🌦️ 1. Live Weather Dashboard (API Integration)
- **[Level 9: The Raw Network Call](./Projects/Python/Intermediate-Projects/weather-app/weather-9/)** (`pip install requests` to fetch API JSON).
- **[Level 10: Live Visual Dashboard](./Projects/Python/Intermediate-Projects/weather-app/weather-10/)** (Asynchronous threading to prevent GUI freezing).

#### 💸 2. Personal Expense Tracker (Relational Databases)
- **[Level 9: The SQLite Database](./Projects/Python/Intermediate-Projects/expense-tracker/expense-9/)** (`sqlite3` built-in library, SQL Queries).
- **[Level 10: Advanced Reporting](./Projects/Python/Intermediate-Projects/expense-tracker/expense-10/)** (`pip install prettytable`, SQL `SUM` and `GROUP BY`).

#### 🕸️ 3. Web Scraper Data Miner (HTML Parsing)
- **[Level 9: The HTML Extractor](./Projects/Python/Intermediate-Projects/web-scraper/scraper-9/)** (`pip install beautifulsoup4` to scrape text from websites).
- **[Level 10: The CSV Exporter](./Projects/Python/Intermediate-Projects/web-scraper/scraper-10/)** (Automatically scraping multi-page sites and saving to Excel `.csv`).

---

## ⚙️ C PROGRAMMING
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

#### 📝 4. Memory-Managed To-Do List
*The Ultimate C Boss! Learn how to manage the computer's physical RAM.*
- **[Level 1: Struct-Based Manager](./Projects/C/Beginner-Projects/todo-list/todo-1/)** (Structs, arrays, and menu systems).

---
*Happy Coding!* 💻
