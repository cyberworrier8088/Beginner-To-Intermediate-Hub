# 📊 Advanced Tracker - Level 10 (Data Analysis & Reporting)
# In Level 9, we created a database but printing raw rows to a terminal is ugly and hard to read.
# Here we use an external Third-Party library called 'prettytable' to render beautiful
# visual tables right in your terminal. We also use Advanced SQL to calculate totals!

import sqlite3
from prettytable import PrettyTable # pip install prettytable
from datetime import datetime

DB_NAME = "expenses.db"

def init_db():
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS expenses (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date TEXT NOT NULL,
            category TEXT NOT NULL,
            amount REAL NOT NULL,
            description TEXT
        )
    ''')
    conn.commit()
    conn.close()

def add_expense(category, amount, description):
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    today = datetime.now().strftime("%Y-%m-%d")
    cursor.execute('INSERT INTO expenses (date, category, amount, description) VALUES (?, ?, ?, ?)', 
                   (today, category, amount, description))
    conn.commit()
    conn.close()
    print(f"✅ Logged ${amount:.2f} to {category}.")

def render_table_report():
    """Fetches data and uses PrettyTable to draw a beautiful ASCII grid."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute('SELECT id, date, category, amount, description FROM expenses')
    rows = cursor.fetchall()
    conn.close()

    if not rows:
        print("📭 Database is empty.")
        return

    # Initialize the Pretty Table
    table = PrettyTable()
    
    # Define our Column Headers
    table.field_names = ["ID", "Date", "Category", "Amount ($)", "Description"]
    
    # Align the Amount column to the right, because numbers look much better that way!
    table.align["Amount ($)"] = "r"
    table.align["Description"] = "l"

    for row in rows:
        # We beautifully format the amount with 2 decimal places before adding the row
        formatted_amount = f"{row[3]:.2f}"
        table.add_row([row[0], row[1], row[2].capitalize(), formatted_amount, row[4]])

    print("\n" + str(table) + "\n")

def generate_financial_summary():
    """Uses advanced SQL to do the math for us, rather than calculating it in Python!"""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    # We ask the SQL Engine to figure out the SUM of all amounts
    cursor.execute('SELECT SUM(amount) FROM expenses')
    total_spent = cursor.fetchone()[0] # fetchone() returns a tuple, [0] gets the actual number
    
    # If the database is empty, total_spent will be None
    if total_spent is None:
        print("💡 No financial data to summarize yet.")
        conn.close()
        return

    print("========================================")
    print("      💰 FINANCIAL SUMMARY REPORT     ")
    print("========================================")
    print(f"💵 Total Money Spent: ${total_spent:.2f}\n")

    # Group By Category: This asks SQL to add up the money, but grouped into categories!
    cursor.execute('SELECT category, SUM(amount) FROM expenses GROUP BY category ORDER BY SUM(amount) DESC')
    category_totals = cursor.fetchall()

    print("📈 Spending by Category:")
    for cat in category_totals:
        category_name = cat[0]
        category_amount = cat[1]
        
        # Calculate what percentage of our total spending went to this category
        percentage = (category_amount / total_spent) * 100
        print(f"   - {category_name.capitalize()}: ${category_amount:.2f} ({percentage:.1f}%)")

    conn.close()

def main():
    init_db()

    while True:
        print("\n--- 🏦 TERMINAL WEALTH DASHBOARD ---")
        print("1. Add New Expense")
        print("2. View Expense Table (PrettyTable)")
        print("3. Generate Financial Summary (SQL Analytics)")
        print("4. Exit")
        
        choice = input("\nSelect an action (1-4): ").strip()

        if choice == '1':
            cat = input("Category: ").strip()
            try:
                amt = float(input("Amount: $"))
            except ValueError:
                print("❌ Invalid amount.")
                continue
            desc = input("Description: ").strip()
            add_expense(cat, amt, desc)
            
        elif choice == '2':
            render_table_report()
            
        elif choice == '3':
            generate_financial_summary()
            
        elif choice == '4':
            print("Shutting down terminal dashboard...")
            break
        else:
            print("Invalid selection.")

if __name__ == "__main__":
    main()
