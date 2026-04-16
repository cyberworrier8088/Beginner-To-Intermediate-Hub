/*
 * Bank Account Manager in Rust - Level 2: Object-Oriented Programming
 * 
 * Welcome to financial programming in Rust! This is where safety meets money.
 * Learn OOP concepts, data structures, and business logic with Rust's type system.
 * 
 * Key concepts you'll learn:
 * - Structs and impl blocks (Rust's version of classes)
 * - Enum for account types and transaction types
 * - Error handling with Result and Option
 * - Vector operations and data management
 * - Input validation and sanitization
 * - Human-like code with detailed explanations!
 */

use std::io::{self, Write};
use std::collections::HashMap;

// Account type enumeration
#[derive(Debug, Clone, Copy, PartialEq)]
enum AccountType {
    Checking,
    Savings,
    Credit,
}

impl AccountType {
    fn from_str(s: &str) -> Option<Self> {
        match s.to_lowercase().as_str() {
            "checking" => Some(AccountType::Checking),
            "savings" => Some(AccountType::Savings),
            "credit" => Some(AccountType::Credit),
            _ => None,
        }
    }
    
    fn to_string(&self) -> &'static str {
        match self {
            AccountType::Checking => "Checking",
            AccountType::Savings => "Savings",
            AccountType::Credit => "Credit",
        }
    }
}

// Transaction type enumeration
#[derive(Debug, Clone)]
enum TransactionType {
    Deposit,
    Withdrawal,
    Transfer,
    Interest,
    Fee,
}

impl TransactionType {
    fn to_string(&self) -> &'static str {
        match self {
            TransactionType::Deposit => "Deposit",
            TransactionType::Withdrawal => "Withdrawal",
            TransactionType::Transfer => "Transfer",
            TransactionType::Interest => "Interest",
            TransactionType::Fee => "Fee",
        }
    }
}

// Transaction structure
#[derive(Debug, Clone)]
struct Transaction {
    id: u32,
    transaction_type: TransactionType,
    amount: f64,
    description: String,
    timestamp: String,
    balance_after: f64,
}

impl Transaction {
    fn new(id: u32, transaction_type: TransactionType, amount: f64, 
            description: String, balance_after: f64) -> Self {
        Transaction {
            id,
            transaction_type,
            amount,
            description,
            timestamp: chrono::Utc::now().to_rfc3339(),
            balance_after,
        }
    }
    
    fn display(&self) {
        println!("ID: {} | Type: {} | Amount: ${:.2} | Balance: ${:.2}", 
                self.id, self.transaction_type.to_string(), self.amount, self.balance_after);
        println!("Description: {} | Time: {}", self.description, self.timestamp);
        println!("{}", "-".repeat(60));
    }
}

// Bank account structure
#[derive(Debug)]
struct BankAccount {
    account_number: String,
    account_holder: String,
    account_type: AccountType,
    balance: f64,
    transactions: Vec<Transaction>,
    next_transaction_id: u32,
    interest_rate: f64,
    overdraft_limit: f64,
    is_active: bool,
}

impl BankAccount {
    // Create new account
    fn new(account_number: String, account_holder: String, 
            account_type: AccountType, initial_deposit: f64) -> Self {
        let mut account = BankAccount {
            account_number,
            account_holder,
            account_type,
            balance: initial_deposit,
            transactions: Vec::new(),
            next_transaction_id: 1,
            interest_rate: match account_type {
                AccountType::Savings => 0.02,      // 2% interest
                AccountType::Checking => 0.001,    // 0.1% interest
                AccountType::Credit => 0.18,       // 18% APR
            },
            overdraft_limit: match account_type {
                AccountType::Checking => 500.0,
                AccountType::Savings => 0.0,
                AccountType::Credit => 1000.0,
            },
            is_active: true,
        };
        
        // Add initial deposit transaction
        if initial_deposit > 0.0 {
            account.add_transaction(TransactionType::Deposit, initial_deposit, 
                                  "Initial deposit".to_string());
        }
        
        account
    }
    
    // Add transaction
    fn add_transaction(&mut self, transaction_type: TransactionType, 
                      amount: f64, description: String) {
        let transaction = Transaction::new(
            self.next_transaction_id,
            transaction_type,
            amount,
            description,
            self.balance
        );
        
        self.transactions.push(transaction);
        self.next_transaction_id += 1;
    }
    
    // Deposit money
    fn deposit(&mut self, amount: f64, description: String) -> Result<(), String> {
        if amount <= 0.0 {
            return Err("Deposit amount must be positive".to_string());
        }
        
        if !self.is_active {
            return Err("Account is not active".to_string());
        }
        
        self.balance += amount;
        self.add_transaction(TransactionType::Deposit, amount, description);
        
        println!("Successfully deposited ${:.2} to account {}", amount, self.account_number);
        Ok(())
    }
    
    // Withdraw money
    fn withdraw(&mut self, amount: f64, description: String) -> Result<(), String> {
        if amount <= 0.0 {
            return Err("Withdrawal amount must be positive".to_string());
        }
        
        if !self.is_active {
            return Err("Account is not active".to_string());
        }
        
        let available_balance = self.balance + self.overdraft_limit;
        
        if amount > available_balance {
            return Err(format!("Insufficient funds. Available: ${:.2}, Requested: ${:.2}", 
                            available_balance, amount));
        }
        
        self.balance -= amount;
        self.add_transaction(TransactionType::Withdrawal, amount, description);
        
        println!("Successfully withdrew ${:.2} from account {}", amount, self.account_number);
        Ok(())
    }
    
    // Transfer money to another account
    fn transfer(&mut self, amount: f64, description: String) -> Result<(), String> {
        if amount <= 0.0 {
            return Err("Transfer amount must be positive".to_string());
        }
        
        if !self.is_active {
            return Err("Account is not active".to_string());
        }
        
        // For this demo, we'll just withdraw with transfer description
        // In a real system, this would involve another account
        self.withdraw(amount, format!("Transfer: {}", description))
    }
    
    // Apply interest
    fn apply_interest(&mut self) -> Result<(), String> {
        if !self.is_active {
            return Err("Account is not active".to_string());
        }
        
        if self.account_type != AccountType::Savings && self.account_type != AccountType::Credit {
            return Err("Interest only applies to savings and credit accounts".to_string());
        }
        
        let interest_amount = self.balance * self.interest_rate / 12.0; // Monthly interest
        
        if interest_amount.abs() < 0.01 {
            return Err("Interest amount too small to apply".to_string());
        }
        
        self.balance += interest_amount;
        self.add_transaction(TransactionType::Interest, interest_amount, 
                           format!("Monthly interest at {:.2}% APR", self.interest_rate * 100.0));
        
        println!("Applied ${:.2} interest to account {}", interest_amount, self.account_number);
        Ok(())
    }
    
    // Apply monthly fee
    fn apply_monthly_fee(&mut self, fee: f64) -> Result<(), String> {
        if !self.is_active {
            return Err("Account is not active".to_string());
        }
        
        if fee <= 0.0 {
            return Err("Fee must be positive".to_string());
        }
        
        self.balance -= fee;
        self.add_transaction(TransactionType::Fee, fee, "Monthly maintenance fee".to_string());
        
        println!("Applied ${:.2} monthly fee to account {}", fee, self.account_number);
        Ok(())
    }
    
    // Get balance
    fn get_balance(&self) -> f64 {
        self.balance
    }
    
    // Check if account is active
    fn is_active(&self) -> bool {
        self.is_active
    }
    
    // Activate/deactivate account
    fn set_active(&mut self, active: bool) {
        self.is_active = active;
        println!("Account {} is now {}", self.account_number, 
                if active { "active" } else { "inactive" });
    }
    
    // Display account information
    fn display_info(&self) {
        println!("{}", "=".repeat(60));
        println!("ACCOUNT INFORMATION");
        println!("{}", "=".repeat(60));
        println!("Account Number: {}", self.account_number);
        println!("Account Holder: {}", self.account_holder);
        println!("Account Type: {}", self.account_type.to_string());
        println!("Balance: ${:.2}", self.balance);
        println!("Interest Rate: {:.2}% APR", self.interest_rate * 100.0);
        println!("Overdraft Limit: ${:.2}", self.overdraft_limit);
        println!("Status: {}", if self.is_active { "Active" } else { "Inactive" });
        println!("Transactions: {}", self.transactions.len());
        println!("{}", "=".repeat(60));
    }
    
    // Display recent transactions
    fn display_recent_transactions(&self, limit: usize) {
        println!("\n{}", "=".repeat(60));
        println!("RECENT TRANSACTIONS (Last {})", limit);
        println!("{}", "=".repeat(60));
        
        if self.transactions.is_empty() {
            println!("No transactions found.");
            return;
        }
        
        let start = if self.transactions.len() > limit {
            self.transactions.len() - limit
        } else {
            0
        };
        
        for transaction in &self.transactions[start..] {
            transaction.display();
        }
    }
    
    // Display all transactions
    fn display_all_transactions(&self) {
        println!("\n{}", "=".repeat(60));
        println!("ALL TRANSACTIONS");
        println!("{}", "=".repeat(60));
        
        if self.transactions.is_empty() {
            println!("No transactions found.");
            return;
        }
        
        for transaction in &self.transactions {
            transaction.display();
        }
    }
}

// Bank manager structure
struct BankManager {
    accounts: HashMap<String, BankAccount>,
    next_account_number: u32,
}

impl BankManager {
    // Create new bank manager
    fn new() -> Self {
        BankManager {
            accounts: HashMap::new(),
            next_account_number: 1001,
        }
    }
    
    // Generate account number
    fn generate_account_number(&mut self) -> String {
        let account_number = format!("ACC{:06}", self.next_account_number);
        self.next_account_number += 1;
        account_number
    }
    
    // Create new account
    fn create_account(&mut self, account_holder: String, account_type: AccountType, 
                      initial_deposit: f64) -> Result<String, String> {
        if account_holder.trim().is_empty() {
            return Err("Account holder name cannot be empty".to_string());
        }
        
        if initial_deposit < 0.0 {
            return Err("Initial deposit cannot be negative".to_string());
        }
        
        let account_number = self.generate_account_number();
        let account = BankAccount::new(account_number.clone(), account_holder, 
                                      account_type, initial_deposit);
        
        self.accounts.insert(account_number.clone(), account);
        
        println!("Successfully created account {} for {}", account_number, account_holder);
        Ok(account_number)
    }
    
    // Get account
    fn get_account(&self, account_number: &str) -> Option<&BankAccount> {
        self.accounts.get(account_number)
    }
    
    // Get mutable account
    fn get_account_mut(&mut self, account_number: &str) -> Option<&mut BankAccount> {
        self.accounts.get_mut(account_number)
    }
    
    // List all accounts
    fn list_accounts(&self) {
        println!("\n{}", "=".repeat(60));
        println!("ALL BANK ACCOUNTS");
        println!("{}", "=".repeat(60));
        
        if self.accounts.is_empty() {
            println!("No accounts found.");
            return;
        }
        
        for (account_number, account) in &self.accounts {
            println!("Account: {} | Holder: {} | Type: {} | Balance: ${:.2} | Status: {}",
                    account_number, account.account_holder, account.account_type.to_string(),
                    account.balance, if account.is_active { "Active" } else { "Inactive" });
        }
        
        println!("Total accounts: {}", self.accounts.len());
        println!("{}", "=".repeat(60));
    }
    
    // Get bank statistics
    fn get_statistics(&self) {
        println!("\n{}", "=".repeat(60));
        println!("BANK STATISTICS");
        println!("{}", "=".repeat(60));
        
        if self.accounts.is_empty() {
            println!("No accounts to analyze.");
            return;
        }
        
        let mut total_balance = 0.0;
        let mut active_accounts = 0;
        let mut checking_accounts = 0;
        let mut savings_accounts = 0;
        let mut credit_accounts = 0;
        
        for account in self.accounts.values() {
            total_balance += account.balance;
            if account.is_active {
                active_accounts += 1;
            }
            
            match account.account_type {
                AccountType::Checking => checking_accounts += 1,
                AccountType::Savings => savings_accounts += 1,
                AccountType::Credit => credit_accounts += 1,
            }
        }
        
        println!("Total Accounts: {}", self.accounts.len());
        println!("Active Accounts: {}", active_accounts);
        println!("Inactive Accounts: {}", self.accounts.len() - active_accounts);
        println!("Total Balance: ${:.2}", total_balance);
        println!("Average Balance: ${:.2}", total_balance / self.accounts.len() as f64);
        println!("Checking Accounts: {}", checking_accounts);
        println!("Savings Accounts: {}", savings_accounts);
        println!("Credit Accounts: {}", credit_accounts);
        println!("{}", "=".repeat(60));
    }
}

// Input validation functions
fn get_valid_string(prompt: &str) -> String {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        let trimmed = input.trim();
        if !trimmed.is_empty() {
            return trimmed.to_string();
        }
        
        println!("Input cannot be empty. Please try again.");
    }
}

fn get_valid_number(prompt: &str) -> f64 {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim().parse::<f64>() {
            Ok(num) => return num,
            Err(_) => println!("Invalid number. Please try again."),
        }
    }
}

fn get_valid_positive_number(prompt: &str) -> f64 {
    loop {
        let num = get_valid_number(prompt);
        if num > 0.0 {
            return num;
        }
        println!("Number must be positive. Please try again.");
    }
}

fn get_account_type() -> AccountType {
    loop {
        println!("Select account type:");
        println!("1. Checking");
        println!("2. Savings");
        println!("3. Credit");
        
        let choice = get_valid_string("Enter choice (1-3): ");
        
        match choice.as_str() {
            "1" => return AccountType::Checking,
            "2" => return AccountType::Savings,
            "3" => return AccountType::Credit,
            _ => println!("Invalid choice. Please enter 1, 2, or 3."),
        }
    }
}

// Main menu
async fn main_menu(bank: &mut BankManager) {
    loop {
        println!("\n{}", "=".repeat(60));
        println!("RUST BANK ACCOUNT MANAGER");
        println!("{}", "=".repeat(60));
        println!("1. Create new account");
        println!("2. List all accounts");
        println!("3. Account operations");
        println!("4. Bank statistics");
        println!("5. Exit");
        
        let choice = get_valid_string("Enter choice (1-5): ");
        
        match choice.as_str() {
            "1" => create_account_menu(bank),
            "2" => bank.list_accounts(),
            "3" => account_operations_menu(bank),
            "4" => bank.get_statistics(),
            "5" => {
                println!("Thank you for using Rust Bank Manager!");
                break;
            }
            _ => println!("Invalid choice. Please enter 1-5."),
        }
    }
}

// Create account menu
fn create_account_menu(bank: &mut BankManager) {
    println!("\n{}", "-".repeat(40));
    println!("CREATE NEW ACCOUNT");
    println!("{}", "-".repeat(40));
    
    let account_holder = get_valid_string("Enter account holder name: ");
    let account_type = get_account_type();
    let initial_deposit = get_valid_positive_number("Enter initial deposit: $");
    
    match bank.create_account(account_holder, account_type, initial_deposit) {
        Ok(account_number) => {
            if let Some(account) = bank.get_account(&account_number) {
                account.display_info();
            }
        }
        Err(e) => println!("Error creating account: {}", e),
    }
}

// Account operations menu
fn account_operations_menu(bank: &mut BankManager) {
    if bank.accounts.is_empty() {
        println!("No accounts available. Please create an account first.");
        return;
    }
    
    println!("\n{}", "-".repeat(40));
    println!("ACCOUNT OPERATIONS");
    println!("{}", "-".repeat(40));
    
    // List accounts for selection
    bank.list_accounts();
    
    let account_number = get_valid_string("Enter account number: ");
    
    if let Some(account) = bank.get_account(&account_number) {
        account.display_info();
        
        loop {
            println!("\nAccount Operations:");
            println!("1. Deposit");
            println!("2. Withdraw");
            println!("3. Transfer");
            println!("4. Apply interest");
            println!("5. Apply monthly fee");
            println!("6. View transactions");
            println!("7. Activate/Deactivate account");
            println!("8. Back to main menu");
            
            let choice = get_valid_string("Enter choice (1-8): ");
            
            match choice.as_str() {
                "1" => deposit_menu(bank, &account_number),
                "2" => withdraw_menu(bank, &account_number),
                "3" => transfer_menu(bank, &account_number),
                "4" => apply_interest_menu(bank, &account_number),
                "5" => apply_fee_menu(bank, &account_number),
                "6" => view_transactions_menu(bank, &account_number),
                "7" => toggle_account_status(bank, &account_number),
                "8" => break,
                _ => println!("Invalid choice. Please enter 1-8."),
            }
        }
    } else {
        println!("Account not found.");
    }
}

// Deposit menu
fn deposit_menu(bank: &mut BankManager, account_number: &str) {
    let amount = get_valid_positive_number("Enter deposit amount: $");
    let description = get_valid_string("Enter description: ");
    
    if let Some(account) = bank.get_account_mut(account_number) {
        match account.deposit(amount, description) {
            Ok(_) => println!("Deposit successful! New balance: ${:.2}", account.get_balance()),
            Err(e) => println!("Deposit failed: {}", e),
        }
    }
}

// Withdraw menu
fn withdraw_menu(bank: &mut BankManager, account_number: &str) {
    let amount = get_valid_positive_number("Enter withdrawal amount: $");
    let description = get_valid_string("Enter description: ");
    
    if let Some(account) = bank.get_account_mut(account_number) {
        match account.withdraw(amount, description) {
            Ok(_) => println!("Withdrawal successful! New balance: ${:.2}", account.get_balance()),
            Err(e) => println!("Withdrawal failed: {}", e),
        }
    }
}

// Transfer menu
fn transfer_menu(bank: &mut BankManager, account_number: &str) {
    let amount = get_valid_positive_number("Enter transfer amount: $");
    let description = get_valid_string("Enter transfer description: ");
    
    if let Some(account) = bank.get_account_mut(account_number) {
        match account.transfer(amount, description) {
            Ok(_) => println!("Transfer successful! New balance: ${:.2}", account.get_balance()),
            Err(e) => println!("Transfer failed: {}", e),
        }
    }
}

// Apply interest menu
fn apply_interest_menu(bank: &mut BankManager, account_number: &str) {
    if let Some(account) = bank.get_account_mut(account_number) {
        match account.apply_interest() {
            Ok(_) => println!("Interest applied successfully! New balance: ${:.2}", account.get_balance()),
            Err(e) => println!("Failed to apply interest: {}", e),
        }
    }
}

// Apply fee menu
fn apply_fee_menu(bank: &mut BankManager, account_number: &str) {
    let fee = get_valid_positive_number("Enter monthly fee amount: $");
    
    if let Some(account) = bank.get_account_mut(account_number) {
        match account.apply_monthly_fee(fee) {
            Ok(_) => println!("Fee applied successfully! New balance: ${:.2}", account.get_balance()),
            Err(e) => println!("Failed to apply fee: {}", e),
        }
    }
}

// View transactions menu
fn view_transactions_menu(bank: &BankManager, account_number: &str) {
    if let Some(account) = bank.get_account(account_number) {
        println!("\nTransaction Options:");
        println!("1. View recent transactions (last 10)");
        println!("2. View all transactions");
        
        let choice = get_valid_string("Enter choice (1-2): ");
        
        match choice.as_str() {
            "1" => account.display_recent_transactions(10),
            "2" => account.display_all_transactions(),
            _ => println!("Invalid choice."),
        }
    }
}

// Toggle account status
fn toggle_account_status(bank: &mut BankManager, account_number: &str) {
    if let Some(account) = bank.get_account_mut(account_number) {
        let new_status = !account.is_active();
        account.set_active(new_status);
    }
}

#[tokio::main]
async fn main() {
    println!("========================================");
    println!("    RUST BANK ACCOUNT MANAGER");
    println!("========================================");
    println!("Welcome to safe banking in Rust!");
    println!("This program demonstrates:");
    println!("- Object-oriented programming with structs");
    println!("- Enum for type safety");
    println!("- Error handling with Result types");
    println!("- Data structures and collections");
    println!("- Input validation and sanitization");
    println!("- Human-like code with personality!");
    println!("========================================");
    
    let mut bank = BankManager::new();
    
    // Add some demo accounts
    println!("Creating demo accounts...");
    
    if let Ok(_) = bank.create_account("John Doe".to_string(), AccountType::Checking, 1000.0) {
        println!("Demo account created for John Doe");
    }
    
    if let Ok(_) = bank.create_account("Jane Smith".to_string(), AccountType::Savings, 5000.0) {
        println!("Demo account created for Jane Smith");
    }
    
    if let Ok(_) = bank.create_account("Bob Johnson".to_string(), AccountType::Credit, 0.0) {
        println!("Demo account created for Bob Johnson");
    }
    
    // Run main menu
    main_menu(&mut bank).await;
    
    println!("\nYou've learned:");
    println!("- Object-oriented programming in Rust");
    println!("- Structs and impl blocks");
    println!("- Enum for type safety");
    println!("- Error handling with Result types");
    println!("- Vector operations and data management");
    println!("- Input validation and sanitization");
    println!("- Human-readable, maintainable code!");
    
    println!("\nKey takeaways:");
    println!("- Rust prevents entire classes of bugs at compile time");
    println!("- Type system ensures data integrity");
    println!("- Error handling prevents crashes");
    println!("- Memory safety without garbage collection");
    println!("- Human-like code makes maintenance easier!");
}
