# Welcome to the big leagues: Level 3!
# Here, we use Object-Oriented Programming (OOP).
# Instead of just recipes, we're building a "Calculator Machine" (a Class).

# --- THE BLUEPRINT (CLASS) ---

class Calculator:
    """
    Think of a Class like a blueprint for a house. 
    You can use the blueprint to build as many houses (objects) as you want.
    """

    # Every function inside a class is called a "Method".
    # They always take 'self' as the first argument, which refers to the specific machine we're using.

    def add(self, x, y):
        return x + y

    def subtract(self, x, y):
        return x - y

    def multiply(self, x, y):
        return x * y

    def divide(self, x, y):
        # We 'raise' an error here if someone tries to divide by zero.
        # This tells the main program that something went wrong.
        if y == 0:
            raise ValueError("You can't divide by zero! That's illegal in mathland.")
        return x / y

# --- THE OPERATING ROOM ---

def main():
    # We 'instantiate' the class here. 'calc' is now a living Calculator object.
    calc = Calculator()
    
    print("========================================")
    print("   ADVANCED CALCULATOR (OOP EDITION)    ")
    print("========================================")
    print("Type your calculation like: 5 + 10")
    print("Or type 'exit' to stop the program.\n")

    # We use a 'while True' loop so the user can do multiple math problems 
    # without having to restart the script every single time.
    while True:
        try:
            user_input = input("Calc> ").strip()
            
            # Allow the user to quit gracefully.
            if user_input.lower() in ['exit', 'quit', 'stop']:
                print("Closing the machine. Goodbye!")
                break

            # Let's break the user's input (e.g., "10 + 5") into pieces.
            parts = user_input.split()
            
            if len(parts) != 3:
                print("[!] Error: Use the format 'Number Operator Number' (e.g., 2 + 2)")
                continue

            # Convert the numbers to floats.
            num1 = float(parts[0])
            operator = parts[1]
            num2 = float(parts[2])

            # Decide which method to call on our 'calc' object.
            if operator == "+":
                result = calc.add(num1, num2)
            elif operator == "-":
                result = calc.subtract(num1, num2)
            elif operator == "*":
                result = calc.multiply(num1, num2)
            elif operator == "/":
                result = calc.divide(num1, num2)
            else:
                print(f"[!] Sorry, I don't know how to do '{operator}' yet.")
                continue

            print(f" => Result: {result}")

        except ValueError as e:
            # This catches things like 'abc + 5' OR the 'divide by zero' error we raised.
            print(f"[!] Input Error: {e}")
        except Exception as e:
            # This is a catch-all for any other weird stuff that might happen.
            print(f"[!] Something went wrong: {e}")

if __name__ == "__main__":
    main()
