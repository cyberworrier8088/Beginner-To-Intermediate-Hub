#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

void reverseString(char str[]) {
    int length = strlen(str);
    for(int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

void toUpperCase(char str[]) {
    for(int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void toLowerCase(char str[]) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int countWords(char str[]) {
    int count = 0;
    int inWord = 0;
    
    for(int i = 0; str[i]; i++) {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            if(!inWord) {
                count++;
                inWord = 1;
            }
        } else {
            inWord = 0;
        }
    }
    return count;
}

void displayMenu() {
    printf("\n=== STRING OPERATIONS ===\n");
    printf("1. Enter a string\n");
    printf("2. Display string\n");
    printf("3. Reverse string\n");
    printf("4. Convert to uppercase\n");
    printf("5. Convert to lowercase\n");
    printf("6. Count words\n");
    printf("7. Get string length\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
}

int main() {
    char text[MAX_LENGTH] = "";
    int choice;
    
    printf("Welcome to String Operations!\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch(choice) {
            case 1:
                printf("Enter a string: ");
                fgets(text, MAX_LENGTH, stdin);
                text[strcspn(text, "\n")] = '\0'; // Remove newline
                printf("String saved!\n");
                break;
                
            case 2:
                if(strlen(text) > 0) {
                    printf("Current string: \"%s\"\n", text);
                } else {
                    printf("No string entered yet!\n");
                }
                break;
                
            case 3:
                if(strlen(text) > 0) {
                    reverseString(text);
                    printf("Reversed string: \"%s\"\n", text);
                } else {
                    printf("No string entered yet!\n");
                }
                break;
                
            case 4:
                if(strlen(text) > 0) {
                    toUpperCase(text);
                    printf("Uppercase: \"%s\"\n", text);
                } else {
                    printf("No string entered yet!\n");
                }
                break;
                
            case 5:
                if(strlen(text) > 0) {
                    toLowerCase(text);
                    printf("Lowercase: \"%s\"\n", text);
                } else {
                    printf("No string entered yet!\n");
                }
                break;
                
            case 6:
                if(strlen(text) > 0) {
                    printf("Word count: %d\n", countWords(text));
                } else {
                    printf("No string entered yet!\n");
                }
                break;
                
            case 7:
                if(strlen(text) > 0) {
                    printf("String length: %zu characters\n", strlen(text));
                } else {
                    printf("No string entered yet!\n");
                }
                break;
                
            case 8:
                printf("Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
    } while(choice != 8);
    
    return 0;
}
