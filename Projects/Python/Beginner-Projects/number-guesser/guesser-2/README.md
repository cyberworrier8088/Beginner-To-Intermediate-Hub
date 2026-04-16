# 🎲 Number Guesser - Level 2: Bulletproof Code

Welcome to **Level 2**. By now, you are realizing that human users are unpredictable. If you build a calculator, someone will type their name into the math field. If your program doesn't handle it gracefully, it crashes. In Python, we fix this with Exception Handling.

### 🧠 The Core Concept: Try / Except Blocks
If you do dangerous logic (like reading a file that might not exist, or converting letters into math), you wrap it in a `try` block. If the computer experiences a fatal error, instead of shutting down, it jumps straight to the `except` block. 

### 🛠️ Technical Deep Dive
1.  **`ValueError`**: Python specifically categorizes its errors. Trying to math-ify the word "Banana" triggers a `ValueError`. If we wrote `except:`, it would catch *every* error (even pressing Ctrl-C to quit!). By writing `except ValueError:`, we are being perfectly precise.
2.  **The `continue` Keyword**: If the user makes an error, we don't want to add `+ 1` to their attempt count. By using `continue`, we force the loop to abandon everything below it and restart from the absolute top immediately. (This is different from `break`, which destroys the loop entirely!).

### 🏃 How to Run
```bash
python guesser.py
```
Run the game, and attempt to break it by typing random letters, symbols, or leaving it blank! Notice how robust the program feels when it elegantly handles your mistakes instead of spitting out scary red text.
