#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secretNumber, guess, attempts = 0;
    
    // Seed the random number generator
    srand(time(0));
    
    // Generate random number between 1 and 100
    secretNumber = rand() % 100 + 1;
    
    printf("=== NUMBER GUESSING GAME ===\n");
    printf("I'm thinking of a number between 1 and 100.\n");
    printf("Can you guess what it is?\n\n");
    
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;
        
        if(guess > secretNumber) {
            printf("Too high! Try again.\n");
        } else if(guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else {
            printf("Congratulations! You guessed it!\n");
            printf("It took you %d attempts.\n", attempts);
        }
        
    } while(guess != secretNumber);
    
    return 0;
}
