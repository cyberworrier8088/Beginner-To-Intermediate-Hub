# Welcome to Level 2! 
# Now that you know the basics, we're going to organize our code better.
# In professional coding, we don't just write one big list of instructions. 
# We group them into "Functions" (like recipes) that we can call whenever we need them.

# --- THE RECIPES (FUNCTIONS) ---

# This function takes two numbers (x and y) and returns their sum.
def add(x, y):
    return x + y

# Subtraction recipe
def subtract(x, y):
    return x - y

# Multiplication recipe
def multiply(x, y):
    return x * y

# Division recipe - notice we're still checking for that pesky zero!
def divide(x, y):
    if y == 0:
        return "[E] Cannot divide by zero!"
    return x / y

# --- THE MAIN BRAIN ---

def main():
    # This is where our program actually 'starts'. 
    # By putting it in a function called main(), we keep things tidy.
    
    print("=== THE MODULAR CALCULATOR ===")
    print("This version uses FUNCTIONS to do the hard work.\n")

    # Let's try to get numbers, but we'll use a 'try' block.
    # If a user types 'abc' instead of a number, the program won't crash!
    try:
        num1 = float(input("First number: "))
        num2 = float(input("Second number: "))
    except ValueError:
        print("Wait! That's not a number. Please try again with actual numbers.")
        return # This stops the function right here.

    print("Pick one: +, -, *, /")
    op = input("Operation: ")

    # Now we call our 'recipes' based on what the user picked.
    if op == "+":
        print(f"Result: {add(num1, num2)}")
    elif op == "-":
        print(f"Result: {subtract(num1, num2)}")
    elif op == "*":
        print(f"Result: {multiply(num1, num2)}")
    elif op == "/":
        print(f"Result: {divide(num1, num2)}")
    else:
        print("Invalid choice. Please run me again and use +, -, *, or /.")

# This bit at the bottom is very important in Python.
# it basically says: "Only run main() if this file is the one we clicked 'Run' on."
# It stops the program from running automatically if we try to 'import' this file elsewhere.
if __name__ == "__main__":
    main()
