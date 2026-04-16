/*
 * Linked List - Level 5: Dynamic Data Structures
 * 
 * Master linked lists - the foundation of complex data structures!
 * Learn:
 * - Dynamic node creation with malloc
 * - Pointer manipulation and linking
 * - Memory management for data structures
 * - Common linked list operations
 * - The difference between array and linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Node structure - the building block of linked lists
typedef struct Node {
    int data;                    // The actual data
    char name[MAX_NAME_LENGTH];  // Additional data
    struct Node* next;          // Pointer to next node
} Node;

// Linked list structure - manages the entire list
typedef struct {
    Node* head;                 // Pointer to first node
    Node* tail;                 // Pointer to last node
    int count;                  // Number of nodes
} LinkedList;

// Create a new node with dynamic memory allocation
Node* create_node(int data, const char* name) {
    printf("Creating node: data=%d, name=%s\n", data, name);
    
    // Allocate memory for the node
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("ERROR: Failed to allocate memory for new node!\n");
        return NULL;
    }
    
    // Initialize the node
    new_node->data = data;
    strncpy(new_node->name, name, MAX_NAME_LENGTH - 1);
    new_node->name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null termination
    new_node->next = NULL;
    
    printf("SUCCESS: Node created at memory address %p\n", (void*)new_node);
    return new_node;
}

// Initialize an empty linked list
LinkedList* create_linked_list() {
    printf("Creating empty linked list...\n");
    
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("ERROR: Failed to allocate memory for linked list!\n");
        return NULL;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    
    printf("SUCCESS: Linked list created\n");
    return list;
}

// Add node to the beginning of the list
void add_front(LinkedList* list, int data, const char* name) {
    printf("\n=== ADDING TO FRONT ===\n");
    
    Node* new_node = create_node(data, name);
    if (new_node == NULL) return;
    
    // Link the new node
    new_node->next = list->head;
    list->head = new_node;
    
    // If list was empty, update tail
    if (list->tail == NULL) {
        list->tail = new_node;
    }
    
    list->count++;
    printf("Node added to front. List now has %d nodes\n", list->count);
}

// Add node to the end of the list
void add_back(LinkedList* list, int data, const char* name) {
    printf("\n=== ADDING TO BACK ===\n");
    
    Node* new_node = create_node(data, name);
    if (new_node == NULL) return;
    
    // If list is empty, new node becomes both head and tail
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        // Link the new node to the current tail
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    list->count++;
    printf("Node added to back. List now has %d nodes\n", list->count);
}

// Find a node by data value
Node* find_node(LinkedList* list, int data) {
    printf("\n=== SEARCHING FOR DATA %d ===\n", data);
    
    Node* current = list->head;
    int position = 0;
    
    while (current != NULL) {
        position++;
        printf("Checking node %d: data=%d\n", position, current->data);
        
        if (current->data == data) {
            printf("FOUND: Node with data %d at position %d\n", data, position);
            return current;
        }
        
        current = current->next;
    }
    
    printf("NOT FOUND: No node with data %d\n", data);
    return NULL;
}

// Remove a node by data value
int remove_node(LinkedList* list, int data) {
    printf("\n=== REMOVING NODE WITH DATA %d ===\n", data);
    
    if (list->head == NULL) {
        printf("List is empty - nothing to remove\n");
        return 0;
    }
    
    Node* current = list->head;
    Node* previous = NULL;
    
    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Node not found - cannot remove\n");
        return 0;
    }
    
    // Remove the node
    if (previous == NULL) {
        // Removing the head
        list->head = current->next;
        printf("Removed head node\n");
    } else {
        // Removing from middle or end
        previous->next = current->next;
        printf("Removed node from middle/end\n");
    }
    
    // Update tail if we removed the last node
    if (current == list->tail) {
        list->tail = previous;
        printf("Updated tail pointer\n");
    }
    
    // Free the memory
    printf("Freeing node at address %p\n", (void*)current);
    free(current);
    list->count--;
    
    printf("Node removed successfully. List now has %d nodes\n", list->count);
    return 1;
}

// Display the entire linked list
void display_list(LinkedList* list) {
    printf("\n=== LINKED LIST CONTENTS ===\n");
    printf("Head: %p, Tail: %p, Count: %d\n", 
           (void*)list->head, (void*)list->tail, list->count);
    
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    Node* current = list->head;
    int position = 0;
    
    printf("Nodes:\n");
    while (current != NULL) {
        position++;
        printf("%d. [Address: %p] Data: %d, Name: %s, Next: %p\n",
               position,
               (void*)current,
               current->data,
               current->name,
               (void*)current->next);
        
        current = current->next;
    }
    
    printf("End of list\n");
}

// Display memory usage
void show_memory_usage(LinkedList* list) {
    printf("\n=== MEMORY USAGE ===\n");
    
    size_t node_memory = list->count * sizeof(Node);
    size_t list_memory = sizeof(LinkedList);
    size_t total_memory = node_memory + list_memory;
    
    printf("Memory for nodes: %zu bytes (%d nodes × %zu bytes)\n",
           node_memory, list->count, sizeof(Node));
    printf("Memory for list structure: %zu bytes\n", list_memory);
    printf("Total memory: %zu bytes\n", total_memory);
    
    if (list->count > 0) {
        printf("Average per node: %.1f bytes\n", (double)total_memory / list->count);
    }
}

// Free all memory in the linked list
void free_linked_list(LinkedList* list) {
    printf("\n=== FREEING ALL MEMORY ===\n");
    
    if (list == NULL) return;
    
    Node* current = list->head;
    int freed_count = 0;
    
    while (current != NULL) {
        Node* next = current->next;  // Save next pointer
        printf("Freeing node: data=%d, address=%p\n", current->data, (void*)current);
        free(current);
        current = next;
        freed_count++;
    }
    
    // Free the list structure itself
    printf("Freeing list structure\n");
    free(list);
    
    printf("SUCCESS: Freed %d nodes and list structure\n", freed_count);
    printf("No memory leaks!\n");
}

// Demonstrate linked list operations
void demonstrate_linked_list() {
    printf("\n" + "="*60);
    printf("LINKED LIST DEMONSTRATION");
    printf("="*60);
    
    // Create a new linked list
    LinkedList* my_list = create_linked_list();
    
    // Add some nodes
    add_back(my_list, 10, "Alice");
    add_back(my_list, 20, "Bob");
    add_back(my_list, 30, "Charlie");
    add_front(my_list, 5, "David");
    
    // Display the list
    display_list(my_list);
    show_memory_usage(my_list);
    
    // Search for a node
    find_node(my_list, 20);
    find_node(my_list, 99);
    
    // Remove some nodes
    remove_node(my_list, 20);
    display_list(my_list);
    
    remove_node(my_list, 5);  // Remove head
    display_list(my_list);
    
    remove_node(my_list, 30);  // Remove tail
    display_list(my_list);
    
    // Clean up
    free_linked_list(my_list);
}

void display_menu() {
    printf("\n" + "="*50);
    printf("LINKED LIST - LEVEL 5");
    printf("="*50);
    printf("1. Demonstrate Linked List");
    printf("2. Create Custom List");
    printf("3. Add Node to Front");
    printf("4. Add Node to Back");
    printf("5. Find Node");
    printf("6. Remove Node");
    printf("7. Display List");
    printf("8. Show Memory Usage");
    printf("9. Free List");
    printf("10. Exit");
    printf("="*50);
    printf("Choose an option: ");
}

int main() {
    printf("=== C LINKED LIST MASTERY ===\n");
    printf("Learn dynamic data structures and pointer management!\n");
    printf("Linked lists are the foundation of many advanced data structures.\n");
    
    LinkedList* current_list = NULL;
    int choice;
    
    do {
        display_menu();
        scanf("%d", &choice);
        getchar();  // Clear newline
        
        switch(choice) {
            case 1:
                demonstrate_linked_list();
                break;
                
            case 2:
                if (current_list != NULL) {
                    printf("Freeing existing list first...\n");
                    free_linked_list(current_list);
                }
                current_list = create_linked_list();
                printf("New empty list created\n");
                break;
                
            case 3:
                if (current_list == NULL) {
                    printf("Create a list first (option 2)\n");
                    break;
                }
                {
                    int data;
                    char name[MAX_NAME_LENGTH];
                    printf("Enter data (number): ");
                    scanf("%d", &data);
                    getchar();
                    printf("Enter name: ");
                    fgets(name, MAX_NAME_LENGTH, stdin);
                    name[strcspn(name, "\n")] = '\0';
                    add_front(current_list, data, name);
                }
                break;
                
            case 4:
                if (current_list == NULL) {
                    printf("Create a list first (option 2)\n");
                    break;
                }
                {
                    int data;
                    char name[MAX_NAME_LENGTH];
                    printf("Enter data (number): ");
                    scanf("%d", &data);
                    getchar();
                    printf("Enter name: ");
                    fgets(name, MAX_NAME_LENGTH, stdin);
                    name[strcspn(name, "\n")] = '\0';
                    add_back(current_list, data, name);
                }
                break;
                
            case 5:
                if (current_list == NULL) {
                    printf("Create a list first (option 2)\n");
                    break;
                }
                {
                    int data;
                    printf("Enter data to find: ");
                    scanf("%d", &data);
                    find_node(current_list, data);
                }
                break;
                
            case 6:
                if (current_list == NULL) {
                    printf("Create a list first (option 2)\n");
                    break;
                }
                {
                    int data;
                    printf("Enter data to remove: ");
                    scanf("%d", &data);
                    remove_node(current_list, data);
                }
                break;
                
            case 7:
                if (current_list == NULL) {
                    printf("Create a list first (option 2)\n");
                    break;
                }
                display_list(current_list);
                break;
                
            case 8:
                if (current_list == NULL) {
                    printf("Create a list first (option 2)\n");
                    break;
                }
                show_memory_usage(current_list);
                break;
                
            case 9:
                if (current_list != NULL) {
                    free_linked_list(current_list);
                    current_list = NULL;
                    printf("List freed\n");
                } else {
                    printf("No list to free\n");
                }
                break;
                
            case 10:
                if (current_list != NULL) {
                    printf("Cleaning up before exit...\n");
                    free_linked_list(current_list);
                }
                printf("Goodbye! Master linked lists and you'll master data structures!\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
        
    } while (choice != 10);
    
    return 0;
}
