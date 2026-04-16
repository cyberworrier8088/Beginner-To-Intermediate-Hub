import random

def get_user_choice():
    """Get and validate user's choice"""
    while True:
        choice = input("Choose rock, paper, or scissors: ").lower()
        if choice in ['rock', 'paper', 'scissors']:
            return choice
        print("Invalid choice! Please try again.")

def get_computer_choice():
    """Generate computer's random choice"""
    return random.choice(['rock', 'paper', 'scissors'])

def determine_winner(user, computer):
    """Determine the winner of the game"""
    if user == computer:
        return "tie"
    
    winning_combinations = {
        'rock': 'scissors',
        'paper': 'rock',
        'scissors': 'paper'
    }
    
    if winning_combinations[user] == computer:
        return "user"
    else:
        return "computer"

def play_game():
    """Main game function"""
    print("=== ROCK, PAPER, SCISSORS ===")
    print("First to win 3 rounds is the champion!")
    
    user_score = 0
    computer_score = 0
    
    while user_score < 3 and computer_score < 3:
        print(f"\nScore - You: {user_score}, Computer: {computer_score}")
        
        user_choice = get_user_choice()
        computer_choice = get_computer_choice()
        
        print(f"You chose: {user_choice}")
        print(f"Computer chose: {computer_choice}")
        
        winner = determine_winner(user_choice, computer_choice)
        
        if winner == "tie":
            print("It's a tie!")
        elif winner == "user":
            print("You win this round!")
            user_score += 1
        else:
            print("Computer wins this round!")
            computer_score += 1
    
    # Final result
    print(f"\n=== FINAL SCORE ===")
    print(f"You: {user_score}, Computer: {computer_score}")
    
    if user_score > computer_score:
        print("🎉 Congratulations! You are the champion! 🎉")
    else:
        print("💻 Computer wins! Better luck next time! 💻")

if __name__ == "__main__":
    while True:
        play_game()
        
        play_again = input("\nDo you want to play again? (yes/no): ").lower()
        if play_again != 'yes':
            print("Thanks for playing!")
            break
