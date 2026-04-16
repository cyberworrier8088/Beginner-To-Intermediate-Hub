# 🖥️ Calculator - Method 7: The Pro GUI Edition

Welcome to **Level 7**, the final boss of the Calculator series! We are returning to graphical interfaces (`tkinter`), but this time, we are building it like a true professional.

### 🧠 The Goal: Building a Real Application
In Level 5, our GUI was cool, but it had issues:
1. No keyboard support (you had to click with a mouse).
2. Looked a bit gray and boring.
3. Used the dangerous `eval()` function without any checks.

### 🛠️ Technical Masterclass
1.  **State Management**: Notice how we store `self.current_expression` and `self.total_expression`? We are maintaining the "state" of the app. This is how React.js and modern Web Apps work conceptually!
2.  **Keyboard Binding (`.bind()`)**: A huge feature of `tkinter`. We attached functions to the physics keys on your keyboard (`<Return>`, `<BackSpace>`). 
3.  **Input Sanitization**: We still use `eval()`, because building a custom math parser is an advanced College-level Computer Science topic. *However*, we added a **Sanitization Check**: 
    `allowed_chars = set("0123456789/*-+.()")`
    Before `eval()` runs, we check if the math string contains *only* those characters. If a hacker tries to inject `os.system("hack_computer")`, the app will reject it instantly!
4.  **UI Styling (Dark Mode)**: We customized fonts, removed ugly borders (`relief="flat"`), and assigned distinct background colors (`bg`) to numbers vs. operators.

### 🏃 How to Run
```bash
python calculator.py
```
*Try typing 2+2 on your physical keyboard and hitting Enter!*

---
### 🎓 Calculator Series Complete!
You did it. You went from a 10-line basic script to a fully secure, object-oriented, styled desktop application. **You are ready for the real world.**
