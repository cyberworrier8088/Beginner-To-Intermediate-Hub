"""
Personal Expense Tracker - Level 9: Fixed Pathing & Input Hardening
Learn proper file pathing, input validation, and robust error handling
This version fixes all the issues you mentioned!
"""

import os
import json
import sys
from datetime import datetime
from prettytable import PrettyTable
import re

class ExpenseTracker:
    """Robust expense tracker with proper pathing and validation"""
    
    def __init__(self):
        # PRO FIX: Use relative pathing that works from any directory
        self.base_dir = os.path.dirname(os.path.abspath(__file__))
        self.db_file = os.path.join(self.base_dir, "database.json")
        
        # Input validation patterns
        self.category_pattern = re.compile(r'^[a-zA-Z0-9\s\-_]{1,20}$')
        self.description_pattern = re.compile(r'^[a-zA-Z0-9\s\-_.,!?]{1,50}$')
        self.amount_pattern = re.compile(r'^\d+(\.\d{1,2})?$')
        
        # Initialize database
        self.expenses = []
        self.load_data()
    
    def load_data(self):
        """Load data from JSON file with proper error handling"""
        try:
            if os.path.exists(self.db_file):
                with open(self.db_file, 'r', encoding='utf-8') as f:
                    self.expenses = json.load(f)
                print(f"Loaded {len(self.expenses)} expenses from database")
            else:
                print("No existing database found. Starting fresh!")
                self.expenses = []
        except json.JSONDecodeError as e:
            print(f"Error reading database: {e}")
            print("Starting with empty database...")
            self.expenses = []
        except Exception as e:
            print(f"Unexpected error loading data: {e}")
            self.expenses = []
    
    def save_data(self):
        """Save data to JSON file with proper error handling"""
        try:
            # Ensure directory exists
            os.makedirs(self.base_dir, exist_ok=True)
            
            with open(self.db_file, 'w', encoding='utf-8') as f:
                json.dump(self.expenses, f, indent=2, ensure_ascii=False)
            print(f"Data saved to: {self.db_file}")
        except Exception as e:
            print(f"Error saving data: {e}")
    
    def validate_category(self, category):
        """Validate category input"""
        if not category or len(category.strip()) == 0:
            return False, "Category cannot be empty"
        
        if not self.category_pattern.match(category):
            return False, "Category must be 1-20 characters (letters, numbers, spaces, hyphens, underscores)"
        
        return True, "Valid category"
    
    def validate_description(self, description):
        """Validate description input"""
        if not description or len(description.strip()) == 0:
            return False, "Description cannot be empty"
        
        if not self.description_pattern.match(description):
            return False, "Description must be 1-50 characters (letters, numbers, spaces, and basic punctuation)"
        
        return True, "Valid description"
    
    def validate_amount(self, amount_str):
        """Validate amount input"""
        if not amount_str or len(amount_str.strip()) == 0:
            return False, "Amount cannot be empty", 0
        
        if not self.amount_pattern.match(amount_str):
            return False, "Amount must be a valid number (e.g., 10.50)", 0
        
        try:
            amount = float(amount_str)
            if amount <= 0:
                return False, "Amount must be greater than 0", 0
            if amount > 999999.99:
                return False, "Amount seems too large (max: 999999.99)", 0
            return True, "Valid amount", amount
        except ValueError:
            return False, "Invalid number format", 0
    
    def truncate_text(self, text, max_length=15):
        """Truncate text for table display"""
        if len(text) <= max_length:
            return text
        return text[:max_length-3] + "..."
    
    def add_expense(self):
        """Add a new expense with robust validation"""
        print("\n=== ADD NEW EXPENSE ===")
        
        # Get category with validation
        while True:
            category = input("Category (1-20 chars): ").strip()
            is_valid, message = self.validate_category(category)
            if is_valid:
                break
            print(f"Invalid category: {message}")
            print("Examples: Food, Transport, Entertainment, Bills")
        
        # Get description with validation
        while True:
            description = input("Description (1-50 chars): ").strip()
            is_valid, message = self.validate_description(description)
            if is_valid:
                break
            print(f"Invalid description: {message}")
            print("Examples: Lunch at cafe, Gas for car, Movie tickets")
        
        # Get amount with validation
        while True:
            amount_str = input("Amount (e.g., 25.50): ").strip()
            is_valid, message, amount = self.validate_amount(amount_str)
            if is_valid:
                break
            print(f"Invalid amount: {message}")
        
        # Create expense record
        expense = {
            "id": len(self.expenses) + 1,
            "category": category,
            "description": description,
            "amount": amount,
            "date": datetime.now().strftime("%Y-%m-%d"),
            "timestamp": datetime.now().isoformat()
        }
        
        self.expenses.append(expense)
        self.save_data()
        
        print(f"\nExpense added successfully!")
        print(f"Category: {category}")
        print(f"Description: {description}")
        print(f"Amount: ${amount:.2f}")
    
    def view_expenses(self):
        """View expenses with proper table formatting"""
        if not self.expenses:
            print("\nNo expenses recorded yet!")
            return
        
        print(f"\n=== EXPENSE REPORT ({len(self.expenses)} expenses) ===")
        
        # Create table with proper column widths
        table = PrettyTable()
        table.field_names = ["ID", "Category", "Description", "Amount", "Date"]
        
        # Set column widths to prevent layout breaking
        table.max_width["ID"] = 5
        table.max_width["Category"] = 12
        table.max_width["Description"] = 20
        table.max_width["Amount"] = 10
        table.max_width["Date"] = 12
        
        # Align columns properly
        table.align["ID"] = "r"
        table.align["Category"] = "l"
        table.align["Description"] = "l"
        table.align["Amount"] = "r"
        table.align["Date"] = "c"
        
        # Add expenses with truncated text
        for expense in self.expenses:
            table.add_row([
                expense["id"],
                self.truncate_text(expense["category"], 12),
                self.truncate_text(expense["description"], 20),
                f"${expense['amount']:.2f}",
                expense["date"]
            ])
        
        print(table)
        
        # Show full details for long entries
        print("\nNote: Long descriptions are truncated in table view")
        print("Use 'Search' feature to see full descriptions")
    
    def search_expenses(self):
        """Search expenses with flexible options"""
        if not self.expenses:
            print("\nNo expenses to search!")
            return
        
        print("\n=== SEARCH EXPENSES ===")
        print("1. Search by category")
        print("2. Search by description")
        print("3. Search by amount range")
        print("4. Search by date")
        print("5. Show all expenses with full details")
        
        choice = input("Search option (1-5): ").strip()
        
        if choice == "1":
            category = input("Enter category: ").strip().lower()
            results = [e for e in self.expenses if category in e["category"].lower()]
        
        elif choice == "2":
            keyword = input("Enter keyword in description: ").strip().lower()
            results = [e for e in self.expenses if keyword in e["description"].lower()]
        
        elif choice == "3":
            try:
                min_amount = float(input("Minimum amount: ") or "0")
                max_amount = float(input("Maximum amount: ") or "999999")
                results = [e for e in self.expenses if min_amount <= e["amount"] <= max_amount]
            except ValueError:
                print("Invalid amount range!")
                return
        
        elif choice == "4":
            date = input("Enter date (YYYY-MM-DD): ").strip()
            results = [e for e in self.expenses if e["date"] == date]
        
        elif choice == "5":
            results = self.expenses
        
        else:
            print("Invalid choice!")
            return
        
        if not results:
            print("\nNo expenses found matching your criteria.")
            return
        
        print(f"\n=== SEARCH RESULTS ({len(results)} expenses) ===")
        
        for expense in results:
            print(f"\nID: {expense['id']}")
            print(f"Category: {expense['category']}")
            print(f"Description: {expense['description']}")
            print(f"Amount: ${expense['amount']:.2f}")
            print(f"Date: {expense['date']}")
            print(f"Added: {expense['timestamp']}")
            print("-" * 40)
    
    def delete_expense(self):
        """Delete an expense with confirmation"""
        if not self.expenses:
            print("\nNo expenses to delete!")
            return
        
        print("\n=== DELETE EXPENSE ===")
        
        # Show recent expenses for context
        print("Recent expenses:")
        for expense in self.expenses[-5:]:
            print(f"ID {expense['id']}: {expense['category']} - {expense['description']} (${expense['amount']:.2f})")
        
        try:
            expense_id = int(input("Enter expense ID to delete: "))
            
            # Find expense
            expense_to_delete = None
            for expense in self.expenses:
                if expense["id"] == expense_id:
                    expense_to_delete = expense
                    break
            
            if not expense_to_delete:
                print(f"No expense found with ID {expense_id}")
                return
            
            # Show expense details
            print(f"\nExpense to delete:")
            print(f"Category: {expense_to_delete['category']}")
            print(f"Description: {expense_to_delete['description']}")
            print(f"Amount: ${expense_to_delete['amount']:.2f}")
            print(f"Date: {expense_to_delete['date']}")
            
            # Confirm deletion
            confirm = input("\nAre you sure you want to delete this expense? (yes/no): ").strip().lower()
            if confirm in ['yes', 'y']:
                self.expenses.remove(expense_to_delete)
                self.save_data()
                print("Expense deleted successfully!")
            else:
                print("Deletion cancelled.")
        
        except ValueError:
            print("Invalid expense ID!")
    
    def show_statistics(self):
        """Show expense statistics"""
        if not self.expenses:
            print("\nNo expenses to analyze!")
            return
        
        print("\n=== EXPENSE STATISTICS ===")
        
        # Total expenses
        total = sum(e["amount"] for e in self.expenses)
        print(f"Total expenses: ${total:.2f}")
        
        # Average expense
        average = total / len(self.expenses)
        print(f"Average expense: ${average:.2f}")
        
        # Category breakdown
        categories = {}
        for expense in self.expenses:
            cat = expense["category"]
            if cat not in categories:
                categories[cat] = {"count": 0, "total": 0}
            categories[cat]["count"] += 1
            categories[cat]["total"] += expense["amount"]
        
        print("\nCategory breakdown:")
        cat_table = PrettyTable()
        cat_table.field_names = ["Category", "Count", "Total", "Average"]
        cat_table.align["Category"] = "l"
        cat_table.align["Count"] = "r"
        cat_table.align["Total"] = "r"
        cat_table.align["Average"] = "r"
        
        for cat, data in sorted(categories.items(), key=lambda x: x[1]["total"], reverse=True):
            cat_avg = data["total"] / data["count"]
            cat_table.add_row([
                self.truncate_text(cat, 15),
                data["count"],
                f"${data['total']:.2f}",
                f"${cat_avg:.2f}"
            ])
        
        print(cat_table)
        
        # Most expensive
        most_expensive = max(self.expenses, key=lambda x: x["amount"])
        print(f"\nMost expensive: {most_expensive['description']} (${most_expensive['amount']:.2f})")
        
        # Most recent
        most_recent = max(self.expenses, key=lambda x: x["timestamp"])
        print(f"Most recent: {most_recent['description']} (${most_recent['amount']:.2f})")
    
    def export_data(self):
        """Export data to CSV format"""
        if not self.expenses:
            print("\nNo expenses to export!")
            return
        
        try:
            export_file = os.path.join(self.base_dir, "expenses_export.csv")
            
            with open(export_file, 'w', encoding='utf-8') as f:
                # Write header
                f.write("ID,Category,Description,Amount,Date,Timestamp\n")
                
                # Write expenses
                for expense in self.expenses:
                    # Escape commas in description
                    desc = expense["description"].replace('"', '""')
                    f.write(f'{expense["id"]},"{expense["category"]}","{desc}",{expense["amount"]},{expense["date"]},{expense["timestamp"]}\n')
            
            print(f"Data exported to: {export_file}")
            print(f"Exported {len(self.expenses)} expenses")
        
        except Exception as e:
            print(f"Error exporting data: {e}")
    
    def show_menu(self):
        """Display main menu"""
        print("\n" + "="*60)
        print("PERSONAL EXPENSE TRACKER - LEVEL 9")
        print("="*60)
        print("Features: Robust validation, proper pathing, input hardening")
        print("Database location:", self.db_file)
        print("-"*60)
        print("1. Add Expense")
        print("2. View Expenses")
        print("3. Search Expenses")
        print("4. Delete Expense")
        print("5. Statistics")
        print("6. Export to CSV")
        print("7. Exit")
        print("-"*60)
    
    def run(self):
        """Main application loop"""
        print("Welcome to Personal Expense Tracker!")
        print("This version demonstrates:")
        print("- Proper relative pathing with os.path.dirname(__file__)")
        print("- Input validation and hardening")
        print("- Error handling and recovery")
        print("- Table formatting with text truncation")
        
        while True:
            self.show_menu()
            choice = input("Enter your choice (1-7): ").strip()
            
            if choice == "1":
                self.add_expense()
            elif choice == "2":
                self.view_expenses()
            elif choice == "3":
                self.search_expenses()
            elif choice == "4":
                self.delete_expense()
            elif choice == "5":
                self.show_statistics()
            elif choice == "6":
                self.export_data()
            elif choice == "7":
                print("Goodbye! Thanks for using Expense Tracker!")
                break
            else:
                print("Invalid choice! Please enter 1-7.")
            
            input("\nPress Enter to continue...")

def main():
    """Main function with error handling"""
    try:
        tracker = ExpenseTracker()
        tracker.run()
    except KeyboardInterrupt:
        print("\n\nProgram interrupted by user. Goodbye!")
    except Exception as e:
        print(f"\nUnexpected error: {e}")
        print("Please report this issue to the repository maintainer.")

if __name__ == "__main__":
    main()
