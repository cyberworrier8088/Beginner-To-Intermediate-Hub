#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME 100
#define MAX_CONTENT 1000

void createFile() {
    char filename[MAX_FILENAME];
    char content[MAX_CONTENT];
    FILE *file;
    
    printf("Enter filename: ");
    scanf("%s", filename);
    getchar(); // Clear newline
    
    printf("Enter file content (max %d chars):\n", MAX_CONTENT);
    fgets(content, MAX_CONTENT, stdin);
    
    file = fopen(filename, "w");
    if(file == NULL) {
        printf("Error creating file!\n");
        return;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
    printf("File '%s' created successfully!\n", filename);
}

void readFile() {
    char filename[MAX_FILENAME];
    char ch;
    FILE *file;
    
    printf("Enter filename to read: ");
    scanf("%s", filename);
    
    file = fopen(filename, "r");
    if(file == NULL) {
        printf("File not found!\n");
        return;
    }
    
    printf("\n--- File Content ---\n");
    while((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n--- End of File ---\n");
    
    fclose(file);
}

void appendToFile() {
    char filename[MAX_FILENAME];
    char content[MAX_CONTENT];
    FILE *file;
    
    printf("Enter filename to append: ");
    scanf("%s", filename);
    getchar(); // Clear newline
    
    printf("Enter content to append:\n");
    fgets(content, MAX_CONTENT, stdin);
    
    file = fopen(filename, "a");
    if(file == NULL) {
        printf("File not found!\n");
        return;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content appended to '%s'!\n", filename);
}

void deleteFile() {
    char filename[MAX_FILENAME];
    int confirm;
    
    printf("Enter filename to delete: ");
    scanf("%s", filename);
    
    printf("Are you sure you want to delete '%s'? (1=Yes, 0=No): ", filename);
    scanf("%d", &confirm);
    
    if(confirm == 1) {
        if(remove(filename) == 0) {
            printf("File '%s' deleted successfully!\n", filename);
        } else {
            printf("Error deleting file!\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }
}

void displayMenu() {
    printf("\n=== FILE MANAGER ===\n");
    printf("1. Create new file\n");
    printf("2. Read file\n");
    printf("3. Append to file\n");
    printf("4. Delete file\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    
    printf("Welcome to File Manager!\n");
    printf("Learn file I/O operations in C\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch(choice) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                appendToFile();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
    } while(choice != 5);
    
    return 0;
}
