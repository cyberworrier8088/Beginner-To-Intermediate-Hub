#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

struct Task {
    char description[MAX_LENGTH];
    int completed;
};

struct Task todoList[MAX_TASKS];
int taskCount = 0;

void addTask() {
    if(taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }
    
    printf("Enter task description: ");
    getchar(); // Clear newline character
    fgets(todoList[taskCount].description, MAX_LENGTH, stdin);
    
    // Remove newline character
    todoList[taskCount].description[strcspn(todoList[taskCount].description, "\n")] = '\0';
    
    todoList[taskCount].completed = 0;
    taskCount++;
    
    printf("Task added successfully!\n");
}

void displayTasks() {
    if(taskCount == 0) {
        printf("No tasks to display.\n");
        return;
    }
    
    printf("\n=== YOUR TASKS ===\n");
    for(int i = 0; i < taskCount; i++) {
        printf("%d. [%s] %s\n", 
               i + 1, 
               todoList[i].completed ? "X" : " ", 
               todoList[i].description);
    }
    printf("==================\n\n");
}

void markComplete() {
    int taskNum;
    
    if(taskCount == 0) {
        printf("No tasks to complete.\n");
        return;
    }
    
    printf("Enter task number to mark complete: ");
    scanf("%d", &taskNum);
    
    if(taskNum >= 1 && taskNum <= taskCount) {
        todoList[taskNum - 1].completed = 1;
        printf("Task marked as complete!\n");
    } else {
        printf("Invalid task number!\n");
    }
}

void displayMenu() {
    printf("=== TODO LIST MANAGER ===\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Mark Task Complete\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    
    printf("Welcome to TODO List Manager!\n\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                markComplete();
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        printf("\n");
    } while(choice != 4);
    
    return 0;
}
