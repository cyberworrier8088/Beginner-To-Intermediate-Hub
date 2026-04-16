/*
 * Sorting Algorithms - Level 2: Algorithm Implementation
 * 
 * Learn fundamental sorting algorithms in C:
 * - Bubble Sort (simple but inefficient)
 * - Selection Sort (find minimum, swap)
 * - Insertion Sort (build sorted portion)
 * - Array manipulation and swapping
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10
#define MAX_VALUE 100

// Function prototypes
void print_array(int arr[], int size, const char* title);
void bubble_sort(int arr[], int size);
void selection_sort(int arr[], int size);
void insertion_sort(int arr[], int size);
void swap(int* a, int* b);
void fill_random_array(int arr[], int size);
void copy_array(int source[], int dest[], int size);
void demonstrate_sorting();

void print_array(int arr[], int size, const char* title) {
    printf("%s: [", title);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void fill_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % MAX_VALUE + 1;
    }
}

void copy_array(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

// Bubble Sort: Compare adjacent elements and swap if wrong order
void bubble_sort(int arr[], int size) {
    printf("\n=== BUBBLE SORT ===\n");
    printf("Idea: Bubble up largest elements to the end\n");
    printf("Complexity: O(n²) - Slow but easy to understand\n\n");
    
    int comparisons = 0;
    int swaps = 0;
    
    for (int pass = 0; pass < size - 1; pass++) {
        printf("Pass %d: ", pass + 1);
        
        int swapped = 0;
        for (int i = 0; i < size - pass - 1; i++) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swaps++;
                swapped = 1;
            }
        }
        
        print_array(arr, size, "Array");
        
        // If no swaps occurred, array is sorted
        if (!swapped) {
            printf("No swaps - array is sorted early!\n");
            break;
        }
    }
    
    printf("Bubble Sort completed: %d comparisons, %d swaps\n", comparisons, swaps);
}

// Selection Sort: Find minimum and place at beginning
void selection_sort(int arr[], int size) {
    printf("\n=== SELECTION SORT ===\n");
    printf("Idea: Select minimum element and place at start\n");
    printf("Complexity: O(n²) - Always makes same comparisons\n\n");
    
    int comparisons = 0;
    int swaps = 0;
    
    for (int i = 0; i < size - 1; i++) {
        printf("Position %d: ", i);
        
        int min_index = i;
        
        // Find minimum in unsorted portion
        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        
        // Swap minimum with current position
        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
            swaps++;
            printf("Swapped %d with %d\n", arr[i], arr[min_index]);
        } else {
            printf("Already in position\n");
        }
        
        print_array(arr, size, "Array");
    }
    
    printf("Selection Sort completed: %d comparisons, %d swaps\n", comparisons, swaps);
}

// Insertion Sort: Build sorted portion one element at a time
void insertion_sort(int arr[], int size) {
    printf("\n=== INSERTION SORT ===\n");
    printf("Idea: Insert each element into its correct position\n");
    printf("Complexity: O(n²) - Fast for nearly sorted arrays\n\n");
    
    int comparisons = 0;
    int shifts = 0;
    
    for (int i = 1; i < size; i++) {
        printf("Inserting element %d (%d): ", i, arr[i]);
        
        int key = arr[i];
        int j = i - 1;
        
        // Shift elements greater than key to the right
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            shifts++;
            j--;
        }
        
        // Place key in correct position
        arr[j + 1] = key;
        shifts++;
        
        print_array(arr, size, "Array");
        printf("Key %d inserted at position %d\n", key, j + 1);
    }
    
    printf("Insertion Sort completed: %d comparisons, %d shifts\n", comparisons, shifts);
}

void demonstrate_sorting() {
    int original[ARRAY_SIZE];
    int bubble_array[ARRAY_SIZE];
    int selection_array[ARRAY_SIZE];
    int insertion_array[ARRAY_SIZE];
    
    // Generate random array
    fill_random_array(original, ARRAY_SIZE);
    
    printf("=== SORTING ALGORITHM DEMONSTRATION ===\n");
    print_array(original, ARRAY_SIZE, "Original array");
    
    // Test each sorting algorithm
    printf("\n" + "="*60);
    printf("TESTING ALL SORTING ALGORITHMS");
    printf("="*60);
    
    // Bubble Sort
    copy_array(original, bubble_array, ARRAY_SIZE);
    bubble_sort(bubble_array, ARRAY_SIZE);
    print_array(bubble_array, ARRAY_SIZE, "Bubble sort result");
    
    // Selection Sort
    copy_array(original, selection_array, ARRAY_SIZE);
    selection_sort(selection_array, ARRAY_SIZE);
    print_array(selection_array, ARRAY_SIZE, "Selection sort result");
    
    // Insertion Sort
    copy_array(original, insertion_array, ARRAY_SIZE);
    insertion_sort(insertion_array, ARRAY_SIZE);
    print_array(insertion_array, ARRAY_SIZE, "Insertion sort result");
    
    // Verify all results are the same
    int all_same = 1;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (bubble_array[i] != selection_array[i] || 
            bubble_array[i] != insertion_array[i]) {
            all_same = 0;
            break;
        }
    }
    
    printf("\n" + "="*60);
    if (all_same) {
        printf("SUCCESS: All algorithms produced the same result!");
    } else {
        printf("ERROR: Algorithms produced different results!");
    }
    printf("="*60);
}

void display_menu() {
    printf("\n" + "="*50);
    printf("SORTING ALGORITHMS - LEVEL 2");
    printf("="*50);
    printf("1. Demonstrate All Algorithms");
    printf("2. Custom Bubble Sort");
    printf("3. Custom Selection Sort");
    printf("4. Custom Insertion Sort");
    printf("5. Algorithm Comparison");
    printf("6. Exit");
    printf("="*50);
    printf("Choose an option: ");
}

void algorithm_comparison() {
    int sizes[] = {10, 50, 100};
    int num_sizes = 3;
    
    printf("\n=== ALGORITHM PERFORMANCE COMPARISON ===\n");
    printf("Testing with different array sizes...\n");
    
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        int test_array[size];
        int bubble_array[size];
        int selection_array[size];
        int insertion_array[size];
        
        printf("\nTesting with %d elements:\n", size);
        
        // Generate test data
        fill_random_array(test_array, size);
        
        // Time each algorithm (simple counting)
        clock_t start, end;
        
        // Bubble Sort
        copy_array(test_array, bubble_array, size);
        start = clock();
        bubble_sort(bubble_array, size);
        end = clock();
        double bubble_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Selection Sort
        copy_array(test_array, selection_array, size);
        start = clock();
        selection_sort(selection_array, size);
        end = clock();
        double selection_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Insertion Sort
        copy_array(test_array, insertion_array, size);
        start = clock();
        insertion_sort(insertion_array, size);
        end = clock();
        double insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("Performance for %d elements:\n", size);
        printf("Bubble Sort:    %.6f seconds\n", bubble_time);
        printf("Selection Sort: %.6f seconds\n", selection_time);
        printf("Insertion Sort: %.6f seconds\n", insertion_time);
        
        // Find fastest
        if (bubble_time <= selection_time && bubble_time <= insertion_time) {
            printf("Fastest: Bubble Sort\n");
        } else if (selection_time <= insertion_time) {
            printf("Fastest: Selection Sort\n");
        } else {
            printf("Fastest: Insertion Sort\n");
        }
    }
}

int main() {
    printf("=== C SORTING ALGORITHMS ===\n");
    printf("Learn fundamental sorting techniques!\n");
    printf("Understanding sorting is key to algorithm thinking.\n");
    
    // Seed random number generator
    srand(time(NULL));
    
    int choice;
    do {
        display_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                demonstrate_sorting();
                break;
            case 2: {
                int custom_array[ARRAY_SIZE];
                fill_random_array(custom_array, ARRAY_SIZE);
                print_array(custom_array, ARRAY_SIZE, "Custom array");
                bubble_sort(custom_array, ARRAY_SIZE);
                break;
            }
            case 3: {
                int custom_array[ARRAY_SIZE];
                fill_random_array(custom_array, ARRAY_SIZE);
                print_array(custom_array, ARRAY_SIZE, "Custom array");
                selection_sort(custom_array, ARRAY_SIZE);
                break;
            }
            case 4: {
                int custom_array[ARRAY_SIZE];
                fill_random_array(custom_array, ARRAY_SIZE);
                print_array(custom_array, ARRAY_SIZE, "Custom array");
                insertion_sort(custom_array, ARRAY_SIZE);
                break;
            }
            case 5:
                algorithm_comparison();
                break;
            case 6:
                printf("Goodbye! Keep practicing algorithms!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
        
    } while (choice != 6);
    
    return 0;
}
