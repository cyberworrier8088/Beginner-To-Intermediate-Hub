# 🔬 Calculator - Method 6: Precision & Scientific (Standard Library)

Welcome to **Level 6**! Until now, we wrote our logic using raw Python syntax. But what happens when native Python fails us?

### 🧠 The Problem: Floating Point Errors
Did you know that computers struggle with decimals? If you ask a raw Python script to calculate `0.1 + 0.2`, it won't say `0.3`. It will say `0.30000000000000004`! 
Because computers calculate in Binary (1s and 0s), they can't perfectly represent base-10 decimals. If you are building a calculator for a bank, losing that `0.00000000000000004` matters!

### 🛠️ The Solution: Built-in Libraries
We don't need to reinvent the wheel or download third-party software. Python comes with a "Standard Library"—a toolkit that's pre-installed. We will `import` two of these tools:

1.  **`decimal` Module**: We use `from decimal import Decimal`. This tells Python to forget binary math and calculate exactly like a human would on a piece of paper.
2.  **`math` Module**: We use `import math`. This gives us incredibly fast C-level code for things like Square Roots (`math.sqrt`), Trigonometry, and Pi.

*Note: Because these are "built-in", you don't need an internet connection to use them. No `pip install` required!*

### 🏃 How to Run
```bash
python calculator.py
```
Try running `0.1 + 0.2` and see how perfectly it outputs `0.3`!

---
### 🌟 Why this matters
Knowing when to use raw code (Levels 1-3) and when to reach for the Standard Library (Level 6+) is what separates a beginner from an intermediate developer. Let Python do the heavy lifting!
