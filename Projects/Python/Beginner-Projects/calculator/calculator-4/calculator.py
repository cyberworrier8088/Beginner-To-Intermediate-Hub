# Welcome to Level 4: The "Elegant" Way (Mapping)
# In this version, we learn how to avoid long 'if-else' chains by using a Dictionary.
# This makes our code very easy to expand later on!

import operator

# --- THE MAPPING SYSTEM ---

# We create a dictionary that maps symbols (+, -, *, /) directly to Python functions.
# The 'operator' module contains built-in functions for basic math.
operations = {
    "+": operator.add,      # This is the same as: lambda x, y: x + y
    "-": operator.sub,      # This is the same as: lambda x, y: x - y
    "*": operator.mul,      # This is the same as: lambda x, y: x * y
    "/": operator.truediv,  # This is the same as: lambda x, y: x / y
}

def calculate(num1, op_symbol, num2):
    """
    This function looks up the math operation in our dictionary 
    and executes it instantly. No long if-elif chains required!
    """
    
    # 1. Check if the operator exists in our dictionary
    if op_symbol not in operations:
        return f"[!] Sorry, I don't know '{op_symbol}' yet."

    # 2. Safety check for division
    if op_symbol == "/" and num2 == 0:
        return "[!] Error: Math says no to division by zero!"

    # 3. Get the function from the dictionary and call it with our numbers
    func = operations[op_symbol]
    return func(num1, num2)

def main():
    print("--- 🗺️ THE MAPPING CALCULATOR 🗺️ ---")
    print("This version uses Dictionaries to map symbols to logic.\n")

    while True:
        try:
            line = input("Enter (e.g., 10 * 5) or 'q' to quit: ").strip()
            if line.lower() == 'q':
                break

            parts = line.split()
            if len(parts) != 3:
                print("Format: Number Operator Number (with spaces!)")
                continue

            n1, op, n2 = float(parts[0]), parts[1], float(parts[2])
            
            result = calculate(n1, op, n2)
            print(f"Result: {result}")

        except ValueError:
            print("Invalid numbers. Please try again.")
        except Exception as e:
            print(f"Oops: {e}")

if __name__ == "__main__":
    main()
