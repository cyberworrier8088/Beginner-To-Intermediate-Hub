class BankAccount:
    """Simple bank account class for learning OOP"""
    
    def __init__(self, owner_name, initial_balance=0):
        """Initialize bank account with owner name and balance"""
        self.owner_name = owner_name
        self.balance = initial_balance
        self.transaction_history = []
        
        if initial_balance > 0:
            self.transaction_history.append(f"Initial deposit: ${initial_balance:.2f}")
    
    def deposit(self, amount):
        """Add money to the account"""
        if amount <= 0:
            print("Deposit amount must be positive!")
            return False
        
        self.balance += amount
        self.transaction_history.append(f"Deposit: +${amount:.2f}")
        print(f"Successfully deposited ${amount:.2f}")
        return True
    
    def withdraw(self, amount):
        """Remove money from the account"""
        if amount <= 0:
            print("Withdrawal amount must be positive!")
            return False
        
        if amount > self.balance:
            print(f"Insufficient funds! Available balance: ${self.balance:.2f}")
            return False
        
        self.balance -= amount
        self.transaction_history.append(f"Withdrawal: -${amount:.2f}")
        print(f"Successfully withdrew ${amount:.2f}")
        return True
    
    def check_balance(self):
        """Display current balance"""
        print(f"Current balance: ${self.balance:.2f}")
        return self.balance
    
    def display_account_info(self):
        """Display complete account information"""
        print("\n" + "="*40)
        print(f"Account Holder: {self.owner_name}")
        print(f"Current Balance: ${self.balance:.2f}")
        print("="*40)
    
    def show_transaction_history(self):
        """Display all transactions"""
        print("\n--- Transaction History ---")
        if not self.transaction_history:
            print("No transactions yet.")
        else:
            for i, transaction in enumerate(self.transaction_history, 1):
                print(f"{i}. {transaction}")
        print("--------------------------\n")

def display_menu():
    """Display banking menu options"""
    print("\n=== BANKING SYSTEM ===")
    print("1. Check Balance")
    print("2. Deposit Money")
    print("3. Withdraw Money")
    print("4. View Account Info")
    print("5. Transaction History")
    print("6. Exit")
    print("======================")

def get_positive_amount(prompt):
    """Get and validate positive amount from user"""
    while True:
        try:
            amount = float(input(prompt))
            if amount > 0:
                return amount
            print("Amount must be positive!")
        except ValueError:
            print("Please enter a valid number!")

def main():
    """Main banking application"""
    print("Welcome to Simple Banking System!")
    print("================================")
    
    # Create account
    name = input("Enter account holder name: ")
    initial_deposit = get_positive_amount("Enter initial deposit amount (or 0): ")
    
    account = BankAccount(name, initial_deposit)
    account.display_account_info()
    
    while True:
        display_menu()
        choice = input("Enter your choice (1-6): ")
        
        if choice == '1':
            account.check_balance()
        
        elif choice == '2':
            amount = get_positive_amount("Enter deposit amount: $")
            account.deposit(amount)
        
        elif choice == '3':
            amount = get_positive_amount("Enter withdrawal amount: $")
            account.withdraw(amount)
        
        elif choice == '4':
            account.display_account_info()
        
        elif choice == '5':
            account.show_transaction_history()
        
        elif choice == '6':
            print(f"\nThank you for banking with us, {account.owner_name}!")
            print("Goodbye!")
            break
        
        else:
            print("Invalid choice! Please enter a number between 1 and 6.")
        
        input("\nPress Enter to continue...")

if __name__ == "__main__":
    main()
