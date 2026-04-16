# 🎲 Number Guesser - Level 1 (The Basic Loop)
# Welcome to a new Beginner project!
# We are making a game where the computer thinks of a number between 1 and 100.
# We will use the built-in 'random' library to make the computer's choice unpredictable.

import random

def main():
    print("========================================")
    print("      🎲 THE NUMBER GUESSER GAME      ")
    print("========================================")
    
    # The computer secretly picks a number!
    secret_number = random.randint(1, 100)
    attempts = 0 # We keep track of how many tries it takes
    
    print("I am thinking of a number between 1 and 100.")
    print("Can you guess it?\n")

    # We use a 'while True' infinite loop.
    # The game keeps asking for a guess forever until the user wins.
    while True:
        # We ask for a string from the terminal
        user_input = input("Enter your guess: ")
        
        # In Level 1, we assume the user is smart and actually types a number.
        # If they type the word 'banana' here, the program will instantly crash!
        # We convert their string text into an integer (a whole math number)
        guess = int(user_input)
        
        # Every time they guess, we add 1 to their attempt count
        attempts += 1

        # We use simple If/Elif logic to guide them
        if guess < secret_number:
            print("Too low! ⬆️ Try going higher.")
        elif guess > secret_number:
            print("Too high! ⬇️ Try going lower.")
        else:
            # If it's not too low, and not too high, it must be the exact number!
            print(f"\n🎉 WINNER! You guessed the secret number ({secret_number})!")
            print(f"It took you {attempts} attempts to win.")
            
            # Since they won, we use 'break' to snap out of the infinite 'while True' loop
            break

if __name__ == "__main__":
    main()
