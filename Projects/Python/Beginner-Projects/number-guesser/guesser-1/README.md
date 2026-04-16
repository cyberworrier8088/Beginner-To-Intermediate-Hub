# 🎲 Number Guesser - Level 1: The Basic Loop

Welcome to the **Number Guesser** series. A classic beginner project that teaches basic game loops and control flow!

### 🧠 The Core Concept: Tracking State
In an application like a calculator, the user enters math, and the script exits. 
In a game, the terminal runs a continuous loop (`while True`) and must "remember" how many times the user has tried to guess. We use external variables (like `attempts`) that exist outside of the loop so they aren't reset to zero every time the loop cycles!

### 🛠️ Technical Deep Dive
1.  **State Tracking**: Notice how `attempts = 0` is placed *above* the `while` loop. If we accidentally put it inside the `while` loop, every single guess would set `attempts` back to 0. A very common beginner mistake!
2.  **`int()` Conversion**: Terminals talk purely in text. If the user types `42`, the computer sees `"42"` (A collection of letters, not a piece of math). We must wrap their input in `int()` to force Python to treat it as a mathematical concept.
3.  **Fatal Weakness**: If a user runs your script and types the letter `"A"` instead of a number, your script will try to calculate `int("A")`. Since `"A"` is not a math sequence, the entire script will crash and output a scary red traceback error. We will fix this in Level 2!

### 🏃 How to Run
```bash
python guesser.py
```
Try running the script and intentionally type "Hello" instead of a number to witness what a terminal crash looks like!
