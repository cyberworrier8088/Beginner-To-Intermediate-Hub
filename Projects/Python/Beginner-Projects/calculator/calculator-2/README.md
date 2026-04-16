# 🧱 Calculator - Method 2: Modular (Functions)

Welcome to **Level 2**! You've graduated from basic scripts to something more professional. This version is all about **Functions**—which are essentially reusable blocks of code.

### 🧠 Why move to Level 2?
In the first version, we just wrote code in a single long list. That's fine for tiny scripts, but imagine building a huge app like Instagram or YouTube! You can't just have one million lines of code in a row. You need to break it down.

### 🛠️ Technical Concepts
1.  **DRY (Don't Repeat Yourself)**: By putting the math logic into functions (`add`, `subtract`), we only write the math once. If we want to change how addition works later, we only have to change it in one place!
2.  **Scope**: Notice how the variables `x` and `y` are only inside the functions? That's called "local scope." It means variables inside a function don't mess with variables outside.
3.  **The Entry Point (`if __name__ == "__main__":`)**: This is a classic Python trick. It ensures that the `main()` function only runs when you execute this specific file. If another script "imports" this one, it won't start the calculator automatically.
4.  **Error Handling (`try/except`)**: We've added a basic safety net. If you type letters instead of numbers, Python will "catch" that error (`ValueError`) and show a friendly message instead of crashing with a scary red text block.

### 🏃 How to Run
```bash
python calculator.py
```

---
### 💡 Challenge
Can you add a new function for "Power" (squaring a number)?
*Hint: Use `return x ** y`!*
