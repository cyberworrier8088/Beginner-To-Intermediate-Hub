# 📊 Expense Tracker - Method 10: Advanced Reporting

Welcome to **Level 10**, the final frontier of our Expense Tracker series. You've graduated from saving flat text files to writing raw SQL logic. Now, we introduce advanced data presentation and SQL analytics!

### 🧠 The Core Concept: Analytics & Rendering
Having a giant database of 10,000 credit card swipes doesn't help anyone if you can't read it. Data Science is all about taking raw data and converting it into human-readable insights. 

### 🛠️ Technical Deep Dive
1.  **The `prettytable` Library**: Instead of writing 100 lines of messy `print()` formatting with invisible spaces to try and make a perfect grid, we installed the third-party `prettytable` package (`pip install prettytable`). We feed it our SQL rows, and it automatically draws stunning, aligned ASCII tables directly into our terminal.
2.  **Advanced SQL `SUM()`**: If we wanted to know our total expenses, we *could* ask SQL for every single row, put it in a Python array, and loop through them to add them up. **Don't do that!** It's extremely slow. We use SQL's built in `SELECT SUM(amount)` to make the database engine do the math instantly.
3.  **Advanced SQL `GROUP BY`**: Finding out how much we spent on 'Food' vs 'Rent' is tricky. We use `GROUP BY category` to tell the SQL engine: "Squish all the rows with the exact same category together, and SUM up their amounts."
4.  **Formatting Metrics**: We use `%` calculations and Python's string formatting `:.2f` to ensure money always prints like `$10.50` instead of `$10.5`.

### 🏃 How to Run
First, ensure you have the required library installed:
```bash
pip install prettytable
```
Then, execute the application:
```bash
python expense.py
```
Add a few expenses (e.g., $15.00 for 'Food', $10.00 for 'Food', $100.00 for 'Rent'). Then select option 3 (Financial Summary) to watch the SQL Analytics engine perfectly group and tally your spending!
