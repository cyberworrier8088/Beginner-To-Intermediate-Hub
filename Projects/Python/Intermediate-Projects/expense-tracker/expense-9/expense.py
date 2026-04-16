# 💸 Intermediate Expense Tracker - Level 9 (The SQLite Database)
# In Level 3 (To-Do List), we saved data as JSON. That's fine for small lists.
# But what if you have 100,000 credit card transactions? JSON would crash your computer.
# Enter SQLite3! A built-in Relational Database used by actual mobile apps (iOS/Android).

import sqlite3 # Standard Library Database Engine
from datetime import datetime

DB_NAME = "expenses.db"

def init_db():
    """
    Creates the database file if it doesn't exist, and sets up our 'Table'.
    A Table is like a spreadsheet with strict columns.
    """
    # 1. Connect to the database (creates the file if missing)
    conn = sqlite3.connect(DB_NAME)
    
    # 2. Extract a 'Cursor' (the tool we use to send SQL commands)
    cursor = conn.cursor()
    
    # 3. Write raw SQL to create our 'expenses' table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS expenses (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL,
            category TEXT NOT NULL,
            amount REAL NOT NULL,
            description TEXT
        )
    ''')
    
    # 4. Save (Commit) the changes and close the connection!
    conn.commit()
    conn.close()

def add_expense(category, amount, description):
    """Inserts a new row into the database."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    
    # Grab today's date automatically
    today = datetime.now().strftime("%Y-%m-%d")
    
    # ⚠️ Security Notice: We NEVER use f-strings to build SQL queries! It allows 'SQL Injection' attacks.
    # We use '?' placeholders, and let the library insert the variables safely.
    cursor.execute('''
        INSERT INTO expenses (date, category, amount, description) 
        VALUES (?, ?, ?, ?)
    ''', (today, category, amount, description))
    
    conn.commit()
    conn.close()
    print(f"✅ Saved ${amount:.2f} for {category} into the database.")

def view_expenses():
    """Fetches all rows from the database and prints them."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    
    # Pull everything from the table
    cursor.execute('SELECT id, date, category, amount, description FROM expenses')
    rows = cursor.fetchall()
    
    if not rows:
        print("📭 No expenses logged yet.")
    else:
        print("\n--- 💸 EXPENSE HISTORY ---")
        for row in rows:
            # row is a 'Tuple': (id, date, category, amount, description)
            print(f"[{row[0]}] {row[1]} | {row[2].upper()} | ${row[3]:.2f} | {row[4]}")
            
    conn.close()

def main():
    print("========================================")
    print("      💸 SQLITE EXPENSE MANAGER        ")
    print("========================================")
    
    # Always ensure the table exists before we try doing anything!
    init_db()

    while True:
        print("\nOptions: (1) Add Expense  (2) View All  (3) Exit")
        choice = input("Choice: ").strip()

        if choice == '1':
            cat = input("Category (e.g., Food, Rent, Fun): ").strip()
            # Error checking on the money input!
            try:
                amt = float(input("Amount ($): "))
            except ValueError:
                print("❌ Invalid amount. Use numbers like 15.50")
                continue
                
            desc = input("Description (optional): ").strip()
            add_expense(cat, amt, desc)
            
        elif choice == '2':
            view_expenses()
            
        elif choice == '3':
            print("Database connection closed. Goodbye! 👋")
            break
        else:
            print("Invalid option.")

if __name__ == "__main__":
    main()
