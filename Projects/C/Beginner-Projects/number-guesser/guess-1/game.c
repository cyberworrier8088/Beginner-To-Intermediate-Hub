/* 🎲 Number Guesser - C Level 1: Loops & Randomness */
/* In C, random numbers are "Pseudo-Random". */
/* We must 'seed' the computer's clock so the number is different every time! */

#include <stdio.h>
#include <stdlib.h> // Required for rand() and srand()
#include <time.h>   // Required for time()

int main() {
    int secret, guess, attempts = 0;

    /* ⏱️ Seeding the Random Number Generator */
    /* This tells C: "Use the current exact millisecond of the clock to pick a starting point." */
    srand(time(NULL));

    /* Pick a number between 1 and 100 */
    /* % 100 gives a number between 0-99. We add 1 to get 1-100. */
    secret = (rand() % 100) + 1;

    printf("========================================\n");
    printf("     🎲 THE C NUMBER GUESSER GAME     \n");
    printf("========================================\n");
    printf("I'm thinking of a number between 1 and 100...\n");

    /* 🔄 The game loop */
    while (1) {
        printf("Enter your guess: ");
        
        /* If user types letters, scanf fails and will loop forever. */
        /* To keep Level 1 simple, we'll just check for numbers. */
        if (scanf("%d", &guess) != 1) {
            printf("⚠️ Numbers only please!\n");
            fflush(stdin);
            continue;
        }

        attempts++;

        if (guess < secret) {
            printf("Too low! ⬆️\n");
        } else if (guess > secret) {
            printf("Too high! ⬇️\n");
        } else {
            printf("\n🎉 CONGRATULATIONS! 🎉\n");
            printf("You found the number %d in %d tries!\n", secret, attempts);
            break;
        }
    }

    return 0;
}
