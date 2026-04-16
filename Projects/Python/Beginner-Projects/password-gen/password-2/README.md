# ⚙️ Password Generator - Method 2: Configurable OOP

Welcome to **Level 2** of the Password Generator! This time, instead of dictating one static rule for password creation, we give the power to the user. Different websites have different rules, so our generator needs to be flexible.

### 🧠 The Core Concept: Object-Oriented Configs
By using a `class` (Object-Oriented Programming), we can create a "Factory" state. We instantiate the object with specific settings (e.g., `use_numbers = False`). From then on, every password that object generates will strictly obey those rules.

### 🛠️ Technical Deep Dive
1.  **The `string` Library**: Instead of physically typing `"abcdefghijklmnopqrstuvwxyz..."`, we import `string` and just call `string.ascii_lowercase`. It's safer, quicker, and built directly into Python.
2.  **Helper Functions**: Notice `def ask_yes_no()`? Validating user input (making sure they type 'y' or 'n' instead of 'potato') takes a lot of code. Instead of repeating that `while True` loop 3 times, we write it *once* as a function and call it 3 times. DRY principle in action!
3.  **List Comprehensions**: The line `[random.choice(pool) for _ in range(self.length)]` is a Python superpower. It is a `for` loop crushed down into a single, highly-optimized line that outputs an array of characters.
4.  **The `.join()` Method**: We use `"".join()` to glue all those loose characters back into a single strong string.

### 🏃 How to Run
```bash
python password.py
```
Try running it and asking for only symbols and numbers, with no uppercase letters. The factory will output exactly what you configure!
