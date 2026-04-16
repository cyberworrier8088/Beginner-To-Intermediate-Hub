# 🎲 Number Guesser - Level 3 (File I/O High Scores)
# In Level 2, our code was secure, but once the game closed, the score was lost.
# Here we add a "High Score" tracking system using basic File Input/Output (I/O).
# Remember: In golf and this game, a LOWER score is better (fewer attempts!).

import random
import os

SCORE_FILE = "highscore.txt"

def load_high_score():
    """Reads the high score from our text file on the hard drive."""
    if os.path.exists(SCORE_FILE):
        try:
            with open(SCORE_FILE, "r") as file:
                # Read the file and convert the text into an integer
                return int(file.read().strip())
        except ValueError:
            # If the file exists but has weird text inside, just return None
            return None
    return None

def save_high_score(score):
    """Saves a new best score to the text file."""
    # Using 'w' mode deletes whatever was in the file and overwrites it
    with open(SCORE_FILE, "w") as file:
        file.write(str(score))
    print(f"💾 NEW HIGH SCORE SAVED: {score} attempts!")

def main():
    print("========================================")
    print("    🏆 CHAMPIONSHIP NUMBER GUESSER    ")
    print("========================================")
    
    # Load the current high score before the game starts
    current_best = load_high_score()
    if current_best:
        print(f"👑 Current High Score: {current_best} attempts.")
    else:
        print("👑 No High Score set yet. Try to set the record!")
        
    print("----------------------------------------\n")
    
    secret_number = random.randint(1, 100)
    attempts = 0 
    
    while True:
        user_input = input("Enter your guess (1-100): ")
        
        try:
            guess = int(user_input)
        except ValueError:
            print("⚠️ ERROR: You didn't type a number! Try again.")
            continue
            
        attempts += 1

        if guess < secret_number:
            print("Too low! ⬆️ Try going higher.")
        elif guess > secret_number:
            print("Too high! ⬇️ Try going lower.")
        else:
            print(f"\n🎉 WINNER! You guessed the secret number ({secret_number})!")
            print(f"It took you {attempts} attempts to win.")
            
            # --- HIGH SCORE LOGIC ---
            # If they don't have a high score yet, OR they beat the old score
            if current_best is None or attempts < current_best:
                print("🌟 AMAZING! YOU BEAT THE HIGH SCORE! 🌟")
                save_high_score(attempts) # Save to the hard drive!
            else:
                print(f"Good job, but the high score is still {current_best} attempts. Try again!")
                
            break

if __name__ == "__main__":
    main()
