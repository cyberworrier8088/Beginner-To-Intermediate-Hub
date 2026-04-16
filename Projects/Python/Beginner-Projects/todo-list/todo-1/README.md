# 📝 To-Do List - Method 1: The Memory Track

Welcome to the To-Do List project series! A To-Do list is the perfect project to learn about applications that manage data. This specific app relies entirely on **Core Python**—there are absolutely zero libraries imported!

### 🧠 The Core Concept: CRUD Operations
In the software engineering world, almost everything is a "CRUD" application:
*   **C**reate (Adding a task)
*   **R**ead (Viewing your tasks)
*   **U**pdate (Changing a task - *Skipped in this basic version*)
*   **D**elete (Removing a task)

If you can build a CRUD application, you can build Twitter, a Bank, or Facebook (they just have larger databases!).

### 🛠️ Technical Deep Dive
1.  **RAM vs. Storage (The Problem)**: Right now, we store our tasks in a Python `list`. Lists live in your computer's RAM. RAM is ephemeral (temporary). If you close the terminal or turn off your computer, the list resets. We will solve this in Level 2!
2.  **User Input Loops**: How do we keep a menu open forever until the user says stop? We wrap everything in a `while True:` loop. The only way out is if they select the 'Exit' option, which triggers the `break` command to snap out of the loop.
3.  **The `.pop()` Method**: When a user wants to delete a task, we use Python's built-in `.remove()` or `.pop()`. We used `.pop(index)`. It removes the item at that specific position in the list and gives it back to us so we can print a nice congratulations message!

### 🏃 How to Run
```bash
python todo.py
```
Try adding 3 tasks, then completely closing your terminal. Open it again and run the script. Notice how the tasks are gone? Let's move to Level 2 to fix that!
