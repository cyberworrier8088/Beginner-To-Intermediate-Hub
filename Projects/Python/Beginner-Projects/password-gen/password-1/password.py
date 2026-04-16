# 🔐 Password Generator - Level 1 (Basic Randomization)
# Welcome to the 3rd project module!
# To generate a random password, we HAVE to use the built-in 'random' library.
# Computers are naturally deterministic (predictable), so 'random' helps us simulate chaos.

import random

# We define the "pool" of characters that our password can pick from.
# We are manually typing these strings out for Level 1.
LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
NUMBERS = "0123456789"
SYMBOLS = "!@#$%^&*()_+-=[]{}|;:,.<>?"

def main():
    print("========================================")
    print("    🔐 BASIC PASSWORD GENERATOR       ")
    print("========================================")

    # We combine all our strings into one giant pool of characters
    all_characters = LETTERS + NUMBERS + SYMBOLS

    # Ask the user how long they want the password to be
    while True:
        try:
            length_input = input("How long should the password be? (e.g., 12): ")
            length = int(length_input)
            
            # Simple security check!
            if length < 4:
                print("⚠️ A password less than 4 characters is too weak! Try again.")
                continue
            
            break # Exit the loop if they gave a nice number
            
        except ValueError:
            print("⚠️ Please type a real number!")

    # --- THE GENERATOR ENGINE ---
    
    password = ""
    # We loop exactly 'length' amount of times. 
    # The underscore '_' is a Python trick meaning "I don't care about the loop number, just do it X times."
    for _ in range(length):
        # random.choice() takes a list or string and randomly picks exactly one item from it
        random_char = random.choice(all_characters)
        
        # We stick the random character onto the end of our growing password string
        password += random_char

    # --- OUTPUT ---
    print("\n🎉 Your randomly generated password is:")
    print(f"-----------------------------------")
    print(f"  {password}")
    print(f"-----------------------------------")
    print("Warning: Do not use this for real banking apps, it's just a beginner project!")

if __name__ == "__main__":
    main()
