import random

def choose_word():
    """Select a random word from the word list"""
    words = [
        'python', 'programming', 'computer', 'developer', 'algorithm',
        'function', 'variable', 'database', 'network', 'security',
        'artificial', 'intelligence', 'machine', 'learning', 'coding'
    ]
    return random.choice(words)

def display_hangman(attempts):
    """Display the hangman figure based on remaining attempts"""
    stages = [
        """
           -----
           |   |
               |
               |
               |
               |
        --------
        """,
        """
           -----
           |   |
           O   |
               |
               |
               |
        --------
        """,
        """
           -----
           |   |
           O   |
           |   |
               |
               |
        --------
        """,
        """
           -----
           |   |
           O   |
          /|   |
               |
               |
        --------
        """,
        """
           -----
           |   |
           O   |
          /|\\  |
               |
               |
        --------
        """,
        """
           -----
           |   |
           O   |
          /|\\  |
          /    |
               |
        --------
        """,
        """
           -----
           |   |
           O   |
          /|\\  |
          / \\  |
               |
        --------
        """
    ]
    return stages[6 - attempts]

def display_word(word, guessed_letters):
    """Display the word with guessed letters revealed"""
    display = ""
    for letter in word:
        if letter in guessed_letters:
            display += letter + " "
        else:
            display += "_ "
    return display.strip()

def hangman_game():
    """Main hangman game function"""
    print("=== HANGMAN GAME ===")
    print("Guess the word letter by letter!")
    print("You have 6 attempts to save the hangman!")
    
    word = choose_word()
    guessed_letters = []
    attempts = 6
    
    while attempts > 0:
        print(f"\n{display_hangman(attempts)}")
        print(f"Word: {display_word(word, guessed_letters)}")
        print(f"Guessed letters: {', '.join(guessed_letters)}")
        print(f"Attempts remaining: {attempts}")
        
        guess = input("Enter a letter: ").lower()
        
        if len(guess) != 1 or not guess.isalpha():
            print("Please enter a single letter!")
            continue
        
        if guess in guessed_letters:
            print("You already guessed that letter!")
            continue
        
        guessed_letters.append(guess)
        
        if guess in word:
            print(f"Good! '{guess}' is in the word!")
            
            # Check if word is complete
            if all(letter in guessed_letters for letter in word):
                print(f"\n🎉 Congratulations! You guessed the word: {word} 🎉")
                return
        else:
            print(f"Sorry! '{guess}' is not in the word.")
            attempts -= 1
    
    # Game over
    print(f"\n{display_hangman(0)}")
    print(f"💀 Game Over! The word was: {word} 💀")

def play_again():
    """Ask if player wants to play again"""
    while True:
        choice = input("\nDo you want to play again? (yes/no): ").lower()
        if choice in ['yes', 'no']:
            return choice == 'yes'
        print("Please enter 'yes' or 'no'.")

def main():
    """Main game loop"""
    print("Welcome to Hangman!")
    
    while True:
        hangman_game()
        
        if not play_again():
            print("Thanks for playing!")
            break

if __name__ == "__main__":
    main()
