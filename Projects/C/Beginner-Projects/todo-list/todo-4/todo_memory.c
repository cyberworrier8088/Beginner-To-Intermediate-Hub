/* 
 * To-Do List - Level 4: Memory Management Mastery
 * 
 * This is the "rite of passage" for C developers!
 * Here we learn:
 * - Dynamic memory allocation with malloc()
 * - Memory deallocation with free()
 * - Pointer arithmetic
 * - Memory leak prevention
 * - Real vs. stack memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 100
#define INITIAL_CAPACITY 10

// Task structure - now using dynamic memory
typedef struct {
    char* description;  // Dynamic string allocation
    int completed;
} Task;

// Dynamic array structure
typedef struct {
    Task* tasks;        // Dynamic array of tasks
    int capacity;      // Current allocated capacity
    int count;         // Current number of tasks
} TaskList;

// Initialize task list with dynamic memory
TaskList* create_task_list() {
    printf("=== MEMORY ALLOCATION: Creating Task List ===\n");
    
    // Allocate memory for the TaskList structure itself
    TaskList* list = (TaskList*)malloc(sizeof(TaskList));
    if (list == NULL) {
        printf("ERROR: Failed to allocate memory for TaskList!\n");
        return NULL;
    }
    
    // Allocate initial memory for tasks array
    list->tasks = (Task*)malloc(INITIAL_CAPACITY * sizeof(Task));
    if (list->tasks == NULL) {
        printf("ERROR: Failed to allocate memory for tasks array!\n");
        free(list);  // Clean up the TaskList itself
        return NULL;
    }
    
    list->capacity = INITIAL_CAPACITY;
    list->count = 0;
    
    printf("SUCCESS: Allocated memory for %d tasks\n", INITIAL_CAPACITY);
    return list;
}

// Resize the tasks array when we need more space
int resize_task_list(TaskList* list) {
    printf("\n=== MEMORY REALLOCATION: Expanding Task List ===\n");
    
    int new_capacity = list->capacity * 2;
    printf("Current capacity: %d, New capacity: %d\n", list->capacity, new_capacity);
    
    // Allocate new, larger memory block
    Task* new_tasks = (Task*)realloc(list->tasks, new_capacity * sizeof(Task));
    if (new_tasks == NULL) {
        printf("ERROR: Failed to reallocate memory!\n");
        return 0;  // Failure, but original memory is still intact
    }
    
    // Update to new memory block
    list->tasks = new_tasks;
    list->capacity = new_capacity;
    
    printf("SUCCESS: Successfully expanded to %d tasks\n", new_capacity);
    return 1;  // Success
}

// Add a task with dynamic string allocation
int add_task(TaskList* list, const char* description) {
    printf("\n=== ADDING TASK: Dynamic String Allocation ===\n");
    
    // Check if we need to expand the array
    if (list->count >= list->capacity) {
        printf("Array full! Need to resize...\n");
        if (!resize_task_list(list)) {
            return 0;  // Failed to resize
        }
    }
    
    // Allocate memory for the task description string
    char* task_desc = (char*)malloc(strlen(description) + 1);  // +1 for null terminator
    if (task_desc == NULL) {
        printf("ERROR: Failed to allocate memory for task description!\n");
        return 0;
    }
    
    // Copy the string to the allocated memory
    strcpy(task_desc, description);
    
    // Add the task to the array
    list->tasks[list->count].description = task_desc;
    list->tasks[list->count].completed = 0;
    list->count++;
    
    printf("SUCCESS: Added task '%s'\n", description);
    printf("Memory used: %zu bytes for description\n", strlen(description) + 1);
    printf("Total tasks: %d/%d\n", list->count, list->capacity);
    
    return 1;
}

// Mark task as complete
void complete_task(TaskList* list, int task_num) {
    if (task_num < 1 || task_num > list->count) {
        printf("ERROR: Invalid task number!\n");
        return;
    }
    
    list->tasks[task_num - 1].completed = 1;
    printf("Task %d marked as complete!\n", task_num);
}

// Display all tasks and memory information
void display_tasks(TaskList* list) {
    printf("\n=== TASK LIST & MEMORY INFO ===\n");
    printf("Tasks: %d/%d (used/allocated)\n", list->count, list->capacity);
    printf("Memory for array: %zu bytes\n", list->capacity * sizeof(Task));
    
    if (list->count == 0) {
        printf("No tasks yet!\n");
        return;
    }
    
    printf("\nTasks:\n");
    for (int i = 0; i < list->count; i++) {
        printf("%d. [%s] %s\n", 
               i + 1,
               list->tasks[i].completed ? "X" : " ",
               list->tasks[i].description);
        printf("   Memory for description: %zu bytes\n", 
               strlen(list->tasks[i].description) + 1);
    }
}

// Free all allocated memory - CRITICAL for preventing leaks!
void free_task_list(TaskList* list) {
    printf("\n=== MEMORY CLEANUP: Freeing All Memory ===\n");
    
    if (list == NULL) return;
    
    // Free each task description string
    for (int i = 0; i < list->count; i++) {
        if (list->tasks[i].description != NULL) {
            printf("Freeing: '%s' (%zu bytes)\n", 
                   list->tasks[i].description,
                   strlen(list->tasks[i].description) + 1);
            free(list->tasks[i].description);
            list->tasks[i].description = NULL;  // Prevent dangling pointer
        }
    }
    
    // Free the tasks array
    printf("Freeing tasks array (%d tasks)\n", list->capacity);
    free(list->tasks);
    list->tasks = NULL;
    
    // Free the TaskList structure itself
    printf("Freeing TaskList structure\n");
    free(list);
    
    printf("SUCCESS: All memory freed! No leaks!\n");
}

// Display memory usage statistics
void show_memory_stats(TaskList* list) {
    printf("\n=== MEMORY STATISTICS ===\n");
    
    size_t array_memory = list->capacity * sizeof(Task);
    size_t string_memory = 0;
    
    for (int i = 0; i < list->count; i++) {
        string_memory += strlen(list->tasks[i].description) + 1;
    }
    
    size_t total_memory = array_memory + string_memory + sizeof(TaskList);
    
    printf("Task array memory: %zu bytes\n", array_memory);
    printf("String memory: %zu bytes\n", string_memory);
    printf("TaskList structure: %zu bytes\n", sizeof(TaskList));
    printf("Total allocated memory: %zu bytes\n", total_memory);
    printf("Memory efficiency: %.1f%% used\n", 
           (double)list->count / list->capacity * 100);
}

void display_menu() {
    printf("\n" + "="*50);
    printf("MEMORY MANAGED TODO LIST - LEVEL 4");
    printf("="*50);
    printf("1. Add Task (malloc)");
    printf("2. Complete Task");
    printf("3. Show Tasks");
    printf("4. Memory Statistics");
    printf("5. Stress Test (add many tasks)");
    printf("6. Exit (free all memory)");
    printf("="*50);
    printf("Choose an option: ");
}

// Stress test to demonstrate dynamic resizing
void stress_test(TaskList* list) {
    printf("\n=== STRESS TEST: Dynamic Resizing ===\n");
    printf("Adding tasks to trigger multiple resizes...\n");
    
    for (int i = 1; i <= 25; i++) {
        char task_desc[50];
        sprintf(task_desc, "Stress test task %d", i);
        
        if (!add_task(list, task_desc)) {
            printf("Failed at task %d\n", i);
            break;
        }
        
        // Show when resizing happens
        if (i == INITIAL_CAPACITY || i == INITIAL_CAPACITY * 2) {
            printf(">>> Resized at task %d <<<\n", i);
        }
    }
    
    show_memory_stats(list);
}

int main() {
    printf("=== C MEMORY MANAGEMENT MASTERY ===\n");
    printf("Learn malloc(), free(), and pointer management!\n");
    printf("This is where C gets powerful AND dangerous!\n");
    
    // Create the task list (dynamic allocation)
    TaskList* my_tasks = create_task_list();
    if (my_tasks == NULL) {
        printf("Failed to create task list. Exiting.\n");
        return 1;
    }
    
    int choice;
    do {
        display_menu();
        scanf("%d", &choice);
        getchar();  // Clear newline
        
        switch(choice) {
            case 1: {
                char description[MAX_TASK_LENGTH];
                printf("Enter task description: ");
                fgets(description, MAX_TASK_LENGTH, stdin);
                description[strcspn(description, "\n")] = '\0';
                add_task(my_tasks, description);
                break;
            }
            case 2: {
                int task_num;
                printf("Enter task number to complete: ");
                scanf("%d", &task_num);
                complete_task(my_tasks, task_num);
                break;
            }
            case 3:
                display_tasks(my_tasks);
                break;
            case 4:
                show_memory_stats(my_tasks);
                break;
            case 5:
                stress_test(my_tasks);
                break;
            case 6:
                printf("Cleaning up memory and exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
        
    } while (choice != 6);
    
    // CRITICAL: Free all memory before exiting
    free_task_list(my_tasks);
    my_tasks = NULL;  // Prevent dangling pointer
    
    printf("\n=== PROGRAM COMPLETE ===\n");
    printf("You've mastered the basics of C memory management!\n");
    printf("Key lessons learned:\n");
    printf("- Every malloc() needs a matching free()\n");
    printf("- Check for NULL after malloc()\n");
    printf("- realloc() can expand memory safely\n");
    printf("- Memory leaks are silent but dangerous\n");
    printf("- Pointers become 'dangling' after free()\n");
    
    return 0;
}
