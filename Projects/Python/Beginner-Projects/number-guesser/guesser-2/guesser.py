# 🎲 Number Guesser - Level 2 (Bulletproof Code)
# In Level 1, our users could accidentally crash the program by typing letters instead of numbers.
# In professional development, we never trust the user! We must anticipate human error.
# We do this using Exception Handling (try/except blocks).

import random

def main():
    print("========================================")
    print("    🛡️ BULLETPROOF NUMBER GUESSER     ")
    print("========================================")
    print("I am thinking of a number between 1 and 100.")
    print("Try typing a word like 'Banana' instead of a number!\n")
    
    secret_number = random.randint(1, 100)
    attempts = 0 
    
    while True:
        user_input = input("Enter your guess: ")
        
        # --- EXCEPTION HANDLING MAGIC ---
        # We wrap the dangerous calculation inside a 'try' block.
        # This tells Python: "Try to do this, but if it fails, DON'T crash!"
        try:
            guess = int(user_input)
        except ValueError:
            # If the ValueError triggers, Python immediately jumps here instead of crashing the app.
            print("⚠️ ERROR: You didn't type a number! Try again.")
            
            # The 'continue' keyword skips the rest of the loop and starts back at the top!
            # Therefore, we don't accidentally count this as a valid attempt.
            continue
            
        # If we made it here, it means 'guess' is a valid number, so we add an attempt
        attempts += 1

        if guess < secret_number:
            print("Too low! ⬆️ Try going higher.")
        elif guess > secret_number:
            print("Too high! ⬇️ Try going lower.")
        else:
            print(f"\n🎉 WINNER! You guessed the secret number ({secret_number})!")
            print(f"It took you {attempts} valid attempts to win.")
            break

if __name__ == "__main__":
    main()
