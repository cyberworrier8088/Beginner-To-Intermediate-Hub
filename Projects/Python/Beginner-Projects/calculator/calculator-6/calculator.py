# 🔬 Level 6: The Precision & Scientific Calculator
# Welcome to the big leagues of math!
# 
# Why are we here? Try opening a normal Python terminal and do: 0.1 + 0.2
# Python will say: 0.30000000000000004
# WHAT!? Why? Because computers use "floating point binary math" which isn't perfect.
#
# To fix this, we introduce built-in libraries! 
# We don't need to pip install them; they come with Python.

import math       # This gives us advanced math like square roots and pi.
from decimal import Decimal, getcontext # This gives us PERFECT precision.

# Set the precision for our Decimals (how many digits after the dot)
getcontext().prec = 10 

def advanced_calculator():
    print("========================================")
    print(" 🔬 PRECISION SCIENTIFIC CALCULATOR     ")
    print("========================================")
    print("Available Operations:")
    print(" +, -, *, /  : Basic Logic")
    print(" sqrt        : Square Root (e.g., 'sqrt 16')")
    print(" power       : Exponents (e.g., '2 power 3' for 2^3)")
    print(" Type 'quit' to exit.\n")
    
    while True:
        try:
            user_input = input("Calc> ").strip().lower()
            
            if user_input in ['quit', 'exit', 'q']:
                print("Turning off the scientific module...")
                break
                
            parts = user_input.split()
            
            # --- Handle Single Number Operations (like Square Root) ---
            if len(parts) == 2 and parts[0] == 'sqrt':
                # Convert the input to a highly precise Decimal instead of a normal float
                num = Decimal(parts[1])
                if num < 0:
                    print("[!] Error: You cannot find the square root of a negative number here.")
                    continue
                # Use the built-in math module for the heavy lifting
                result = math.sqrt(float(num))
                print(f" Result: {result}")
                continue
                
            # --- Handle Two Number Operations ---
            if len(parts) != 3:
                print("[!] Error: Format needed -> 'Number Operator Number'")
                continue
                
            # Notice we wrap inputs in Decimal('') to keep them perfectly exact
            n1 = Decimal(parts[0])
            op = parts[1]
            n2 = Decimal(parts[2])
            
            if op == '+':
                result = n1 + n2
            elif op == '-':
                result = n1 - n2
            elif op == '*':
                result = n1 * n2
            elif op == '/':
                if n2 == 0:
                    print("[!] Error: Division by zero is mathematically undefined.")
                    continue
                result = n1 / n2
            elif op == 'power' or op == '^':
                result = n1 ** n2
            else:
                print(f"[!] Error: Unknown operator '{op}'")
                continue
                
            print(f" Result (Exact): {result}")
            
        except ImportError:
             print("Wait, this shouldn't happen! The math module is built-in.")
        except Exception as e:
            # We catch the broad 'Exception' to stop crashes, and print the exact error message
            print(f"[!] Math Error: {e}")

if __name__ == "__main__":
    advanced_calculator()
