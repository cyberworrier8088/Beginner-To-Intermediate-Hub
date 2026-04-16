# 🗺️ Calculator - Method 4: The Dictionary Map

Welcome to **Level 4**! This is a "pro tip" version of the calculator. Instead of using a long list of `if-elif` checks, we use a **Dictionary** to map symbols directly to the math they perform.

### 🧠 The Logic: Data as Control
In previous levels, we used code structure (`if/else`) to decide what to do. In Level 4, we use **Data** (a Dictionary) to control the program. This is a very common pattern in high-level programming.

### 🛠️ Technical Breakdown
1.  **The `operator` Module**: Python has a built-in library called `operator` that provides functions for all the basics. `operator.add(a, b)` is exactly the same as `a + b`, but it's a function we can store in a variable!
2.  **Mapping**: We create a dictionary where the "Key" is the symbol (like `"+"`) and the "Value" is the function itself.
3.  **Lookup**: When a user types `*`, we just ask the dictionary: "What function do you have for `*`?" and then we run it.
4.  **Extensibility**: This is the best part! If you want to add a "Modulo" (`%`) operator, you don't need to add new `elif` lines. You just add one single line to the dictionary: `"%": operator.mod`.

### 💡 Why learn this?
Professional developers hate long `if-else` chains. They are hard to read and hard to maintain. Using a "Map" pattern makes your code cleaner, faster, and much easier to grow in the future.

### 🏃 How to Run
```bash
python calculator.py
```
Type `q` to quit.

---
### 🌟 Congratulations!
You've explored the same problem from 4 different angles. You've seen the Simplest way, the Modular way, the Object-Oriented way, and the Elegant-Data way. You're well on your way to becoming a Python Master!
