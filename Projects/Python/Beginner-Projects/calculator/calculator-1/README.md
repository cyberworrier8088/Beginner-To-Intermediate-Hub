# 🧮 Calculator - Method 1: The Simplest Way

Hey there! If you're just starting your coding journey, this is the perfect place to begin. This project builds a basic calculator using "Straight-Line" logic — which means the code runs from top to bottom without jumping around too much.

### 🧠 What you'll learn here
By reading and running this code, you'll understand four big concepts in Python:

1.  **Variables**: Think of these as little boxes where we store data (`num1`, `num2`).
2.  **Data Types**: We use `float()` because Python needs to know if a number is a whole number (Integer) or has decimals (Float). Calculators work best with Floats!
3.  **Inputs**: How to use the `input()` function to let a human talk to the computer.
4.  **Conditionals (If/Else)**: This is how the computer makes decisions. "If the user typed '+', then do addition."

### 🛠️ Technical Breakdown
- **String to Float**: When you type a number in the console, Python sees it as text (e.g., `"10"`). We convert it using `float("10")` so we can actually add it.
- **Error Handling (Basic)**: We added a small check for **Division by Zero**. In math, dividing by zero is undefined, and in Python, it usually crashes the program. We handle it with a simple `if` check to keep things smooth.
- **F-Strings**: Notice the `f"Result: {result}"` part? That's a modern Python feature called an "f-string" (formatted string). it lets us put variables directly inside a sentence.

### 🏃 How to Run
1. Open your terminal or command prompt.
2. Navigate to this folder.
3. Run the following command:
   ```bash
   python calculator.py
   ```

---
### 💡 Pro Tip for Beginners
Try changing the words inside the `print()` functions or adding a new operator like `%` (modulo) to see what happens. Breaking and fixing code is the best way to learn!
