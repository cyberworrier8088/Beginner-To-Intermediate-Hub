# 🚀 Calculator - Method 3: The "Pro" Way (OOP)

Welcome to the final level! This is where we stop thinking about code as a list of tasks and start thinking about it as **Systems and Objects**. This version uses **Object-Oriented Programming (OOP)**.

### 🧠 The Big Shift: What is OOP?
Imagine you are building a robot. 
- In Level 1, you just gave the robot a list of commands.
- In Level 2, you gave the robot "skills" (functions).
- In **Level 3**, you are actually building the **Robot Factory** (the Class). Once you have the factory, you can create as many Calculator-Robots as you want!

### 🛠️ Technical Deep-Dive
1.  **Classes & Objects**: The `class Calculator` is the blueprint. When we do `calc = Calculator()`, we are creating an "instance" (the actual machine).
2.  **Methods**: Functions inside a class are called methods. They represent the "behaviors" of the object.
3.  **The `self` Keyword**: This is how the object refers to itself. It's like the robot saying, "I'm using *my own* internal math processor."
4.  **Advanced Error Handling**: We use `raise ValueError` to manually trigger an error if something impossible happens (like division by zero). Then, the `main()` function "catches" it. This keeps the logic (math) and the UI (printing errors) separate. 
5.  **Infinite Loops**: We use `while True` to keep the calculator running. This turns our script into a real "application" rather than a one-off tool.

### 💡 Why do people use OOP?
It's all about **Organization** and **Scalability**. If you wanted to add a "History" feature to the calculator, you could just add a list called `self.history` inside the class, and every operation would automatically track itself!

### 🏃 How to Run
```bash
python calculator.py
```
Type `exit` to turn off the machine.

---
### 🏆 You've reached the end!
You now understand how the same problem (a calculator) can be solved in three increasingly powerful ways. Which one is your favorite?
