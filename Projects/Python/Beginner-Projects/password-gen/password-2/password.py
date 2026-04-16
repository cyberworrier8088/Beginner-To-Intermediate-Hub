# ⚙️ Password Generator - Level 2 (Configurable OOP)
# In Level 1, we hardcoded our strings.
# But what if a website says: "No special symbols allowed!"?
# In Level 2, we build a configurable "Class" to let the user decide exactly what they want.
# We also use the built-in 'string' library to avoid typing the alphabet ourselves!

import random
import string # This library contains pre-made strings of the alphabet!

class PasswordGenerator:
    """A Class that acts as a customizable password factory."""
    
    def __init__(self, length=12, use_upper=True, use_numbers=True, use_symbols=True):
        self.length = length
        self.use_upper = use_upper
        self.use_numbers = use_numbers
        self.use_symbols = use_symbols

    def _build_character_pool(self):
        """Internal method to assemble exactly which characters we are allowed to use."""
        # We always start with lowercase letters
        pool = string.ascii_lowercase
        
        if self.use_upper:
            pool += string.ascii_uppercase
        if self.use_numbers:
            pool += string.digits
        if self.use_symbols:
            pool += string.punctuation # Contains !@#$%^&* etc.
            
        return pool

    def generate(self):
        """Generates the actual password based on the rules we set."""
        pool = self._build_character_pool()
        
        if not pool:
             return "[!] Error: Character pool is empty!"

        # Let's use a Python "List Comprehension" to make it in one elegant line!
        # This is the advanced way of writing the 'for _ in range()' loop from Level 1.
        password_list = [random.choice(pool) for _ in range(self.length)]
        
        # .join() squishes a list of characters into one continuous string
        return "".join(password_list)

def ask_yes_no(question):
    """Helper function to cleanly ask the user yes/no questions."""
    while True:
        ans = input(question + " (y/n): ").strip().lower()
        if ans in ['y', 'yes']:
            return True
        if ans in ['n', 'no']:
            return False
        print("⚠️ Please type 'y' or 'n'.")

def main():
    print("========================================")
    print("      ⚙️ CUSTOM PASSWORD FACTORY      ")
    print("========================================")

    # Gather settings from the user
    try:
        length = int(input("Enter desired password length (e.g. 16): "))
    except ValueError:
        print("Invalid number. Defaulting to 12.")
        length = 12

    # Ask exactly what they want inside
    use_up = ask_yes_no("Include UPPERCASE letters?")
    use_num = ask_yes_no("Include Numbers (0-9)?")
    use_sym = ask_yes_no("Include Symbols (!@#)?")

    # Instantiate our "Factory" with the user's custom settings
    factory = PasswordGenerator(
        length=length, 
        use_upper=use_up, 
        use_numbers=use_num, 
        use_symbols=use_sym
    )

    print("\n[ Generating... ]")
    # Tell the factory to make 5 different passwords to give the user options!
    for i in range(1, 6):
        print(f" Option {i}: {factory.generate()}")

if __name__ == "__main__":
    main()
