# 💸 Expense Tracker - Level 9: The SQLite Database

Welcome to the true Intermediate Database module! Say goodbye to flat `.txt` or `.json` files. We are now using a real Relational Database.

### 🧠 The Core Concept: SQLite3
Every single iPhone and Android device in the world runs SQLite internally to store app data. It is a powerful, lightweight Database Management System (DBMS). Luckily, Python comes with the `sqlite3` library built-in!

### 🛠️ Technical Deep Dive
1.  **Tables and Columns**: Unlike a Python List where you can throw anything inside, a Database Table is strict. We use `CREATE TABLE` to demand that every entry has a `date` (Text), `category` (Text), and `amount` (REAL / Float).
2.  **Primary Keys**: Notice `id INTEGER PRIMARY KEY AUTOINCREMENT`? Every time we add an expense, the database assigns it a unique number (`1`, `2`, `3`). This guarantees we can identify a specific purchase forever, even if we bought two $5.00 coffees on the same day.
3.  **SQL Commands**: `INSERT INTO` allows us to push data, and `SELECT ... FROM` allows us to pull data. You are writing an entirely different language (SQL) *inside* of your Python script!
4.  **SQL Injection Protection**: You might wonder why we didn't use f-strings (`f"INSERT INTO expenses VALUES ({amount})"`) to write the query. **Never do this in professional apps!** A hacker could type `DROP TABLE expenses` into your program and delete your entire database. We use the `?` placeholder, which forces SQLite to safely sanitize the input.

### 🏃 How to Run
```bash
python expense.py
```
Try adding a few expenses. Close the script. Open it again. Notice how fast it retrieves the data from `expenses.db`!
