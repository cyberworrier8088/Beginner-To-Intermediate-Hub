/*
 * Unity Testing Framework - Level 6: Professional C Testing
 * 
 * This is what separates hobbyists from professionals in C!
 * Learn:
 * - Unit testing with Unity framework
 * - Test-driven development
 * - Assertion macros and test organization
 * - Professional code quality practices
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple Unity-like testing framework for demonstration
#define TEST_ASSERT(condition) \
    do { \
        test_count++; \
        if (!(condition)) { \
            printf("FAIL: %s:%d - %s\n", __FILE__, __LINE__, #condition); \
            failed_count++; \
        } else { \
            printf("PASS: %s\n", #condition); \
        } \
    } while(0)

#define TEST_ASSERT_EQUAL(expected, actual) \
    do { \
        test_count++; \
        if ((expected) != (actual)) { \
            printf("FAIL: %s:%d - Expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
            failed_count++; \
        } else { \
            printf("PASS: Expected %d, got %d\n", (expected), (actual)); \
        } \
    } while(0)

#define TEST_ASSERT_NOT_NULL(ptr) \
    do { \
        test_count++; \
        if ((ptr) == NULL) { \
            printf("FAIL: %s:%d - Pointer is NULL\n", __FILE__, __LINE__); \
            failed_count++; \
        } else { \
            printf("PASS: Pointer is not NULL\n"); \
        } \
    } while(0)

#define TEST_ASSERT_NULL(ptr) \
    do { \
        test_count++; \
        if ((ptr) != NULL) { \
            printf("FAIL: %s:%d - Pointer is not NULL\n", __FILE__, __LINE__); \
            failed_count++; \
        } else { \
            printf("PASS: Pointer is NULL\n"); \
        } \
    } while(0)

// Global test counters
static int test_count = 0;
static int failed_count = 0;

// Test setup and teardown functions
void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

// Calculator functions to test
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) {
        return 0; // Simple error handling for demo
    }
    return a / b;
}

// String functions to test
int string_length(const char* str) {
    if (str == NULL) return 0;
    
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char* string_copy(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return NULL;
    
    char* original_dest = dest;
    while ((*dest++ = *src++) != '\0') {
        // Copy character by character
    }
    
    return original_dest;
}

// Array functions to test
int find_max(int arr[], int size) {
    if (arr == NULL || size <= 0) return 0;
    
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Memory functions to test
int* create_array(int size) {
    if (size <= 0) return NULL;
    
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) return NULL;
    
    // Initialize array
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
    
    return arr;
}

void free_array(int** arr) {
    if (arr != NULL && *arr != NULL) {
        free(*arr);
        *arr = NULL;
    }
}

// Test functions
void test_calculator_addition(void) {
    printf("\n=== Testing Calculator Addition ===\n");
    
    setUp();
    TEST_ASSERT_EQUAL(5, add(2, 3));
    TEST_ASSERT_EQUAL(0, add(0, 0));
    TEST_ASSERT_EQUAL(-1, add(-2, 1));
    TEST_ASSERT_EQUAL(100, add(50, 50));
    tearDown();
}

void test_calculator_subtraction(void) {
    printf("\n=== Testing Calculator Subtraction ===\n");
    
    setUp();
    TEST_ASSERT_EQUAL(2, subtract(5, 3));
    TEST_ASSERT_EQUAL(0, subtract(5, 5));
    TEST_ASSERT_EQUAL(-3, subtract(2, 5));
    tearDown();
}

void test_calculator_multiplication(void) {
    printf("\n=== Testing Calculator Multiplication ===\n");
    
    setUp();
    TEST_ASSERT_EQUAL(6, multiply(2, 3));
    TEST_ASSERT_EQUAL(0, multiply(5, 0));
    TEST_ASSERT_EQUAL(-6, multiply(-2, 3));
    tearDown();
}

void test_calculator_division(void) {
    printf("\n=== Testing Calculator Division ===\n");
    
    setUp();
    TEST_ASSERT_EQUAL(2, divide(6, 3));
    TEST_ASSERT_EQUAL(1, divide(5, 4));
    TEST_ASSERT_EQUAL(0, divide(5, 0)); // Division by zero case
    tearDown();
}

void test_string_functions(void) {
    printf("\n=== Testing String Functions ===\n");
    
    setUp();
    
    // Test string_length
    TEST_ASSERT_EQUAL(5, string_length("Hello"));
    TEST_ASSERT_EQUAL(0, string_length(""));
    TEST_ASSERT_EQUAL(0, string_length(NULL));
    
    // Test string_copy
    char dest[100];
    const char* src = "Test String";
    char* result = string_copy(dest, src);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(0, strcmp(dest, src));
    
    tearDown();
}

void test_array_functions(void) {
    printf("\n=== Testing Array Functions ===\n");
    
    setUp();
    
    int test_array[] = {1, 5, 3, 9, 2};
    int size = sizeof(test_array) / sizeof(test_array[0]);
    
    TEST_ASSERT_EQUAL(9, find_max(test_array, size));
    TEST_ASSERT_EQUAL(0, find_max(NULL, 5));
    TEST_ASSERT_EQUAL(0, find_max(test_array, 0));
    
    tearDown();
}

void test_memory_functions(void) {
    printf("\n=== Testing Memory Functions ===\n");
    
    setUp();
    
    // Test array creation
    int* arr = create_array(5);
    TEST_ASSERT_NOT_NULL(arr);
    
    if (arr != NULL) {
        // Check if array is initialized
        TEST_ASSERT_EQUAL(0, arr[0]);
        TEST_ASSERT_EQUAL(0, arr[4]);
        
        // Test array freeing
        free_array(&arr);
        TEST_ASSERT_NULL(arr);
    }
    
    // Test edge cases
    TEST_ASSERT_NULL(create_array(0));
    TEST_ASSERT_NULL(create_array(-1));
    
    tearDown();
}

void test_edge_cases(void) {
    printf("\n=== Testing Edge Cases ===\n");
    
    setUp();
    
    // Test integer overflow (simple check)
    int result = add(2147483647, 1);
    printf("Overflow test: 2147483647 + 1 = %d\n", result);
    
    // Test with negative numbers
    TEST_ASSERT_EQUAL(-10, add(-5, -5));
    TEST_ASSERT_EQUAL(15, subtract(5, -10));
    
    // Test with maximum values
    TEST_ASSERT_EQUAL(1000000, multiply(1000, 1000));
    
    tearDown();
}

// Integration test
void test_calculator_integration(void) {
    printf("\n=== Testing Calculator Integration ===\n");
    
    setUp();
    
    // Test complex calculation: (5 + 3) * 2 - 4 / 2 = 14
    int step1 = add(5, 3);    // 8
    int step2 = multiply(step1, 2); // 16
    int step3 = subtract(step2, 4); // 12
    int result = divide(step3, 2); // 6
    
    TEST_ASSERT_EQUAL(6, result);
    
    printf("Integration test: (5 + 3) * 2 - 4 / 2 = %d\n", result);
    
    tearDown();
}

// Performance test
void test_performance(void) {
    printf("\n=== Testing Performance ===\n");
    
    setUp();
    
    // Test with large array
    const int large_size = 100000;
    int* large_array = create_array(large_size);
    TEST_ASSERT_NOT_NULL(large_array);
    
    if (large_array != NULL) {
        // Fill array with test data
        for (int i = 0; i < large_size; i++) {
            large_array[i] = i;
        }
        
        // Find max in large array
        int max_val = find_max(large_array, large_size);
        TEST_ASSERT_EQUAL(large_size - 1, max_val);
        
        printf("Performance test: Found max %d in array of %d elements\n", 
               max_val, large_size);
        
        free_array(&large_array);
    }
    
    tearDown();
}

// Run all tests
void run_all_tests(void) {
    printf("=== C UNITY TESTING FRAMEWORK DEMO ===\n");
    printf("Professional unit testing in C!\n");
    printf("=====================================\n");
    
    // Reset counters
    test_count = 0;
    failed_count = 0;
    
    // Run individual test suites
    test_calculator_addition();
    test_calculator_subtraction();
    test_calculator_multiplication();
    test_calculator_division();
    test_string_functions();
    test_array_functions();
    test_memory_functions();
    test_edge_cases();
    test_calculator_integration();
    test_performance();
    
    // Print results
    printf("\n" + "="*60);
    printf("TEST RESULTS SUMMARY");
    printf("="*60);
    printf("Total tests run: %d\n", test_count);
    printf("Tests passed: %d\n", test_count - failed_count);
    printf("Tests failed: %d\n", failed_count);
    
    if (failed_count == 0) {
        printf("🎉 ALL TESTS PASSED! 🎉\n");
        printf("Code quality: EXCELLENT\n");
    } else {
        printf("❌ %d TESTS FAILED ❌\n", failed_count);
        printf("Code quality: NEEDS IMPROVEMENT\n");
    }
    
    printf("Success rate: %.1f%%\n", 
           ((float)(test_count - failed_count) / test_count) * 100);
    printf("="*60);
}

// Interactive test runner
void interactive_test_runner(void) {
    printf("\n=== INTERACTIVE TEST RUNNER ===\n");
    printf("Choose what to test:\n");
    printf("1. Calculator Tests\n");
    printf("2. String Tests\n");
    printf("3. Array Tests\n");
    printf("4. Memory Tests\n");
    printf("5. All Tests\n");
    printf("6. Exit\n");
    
    int choice;
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    test_count = 0;
    failed_count = 0;
    
    switch(choice) {
        case 1:
            test_calculator_addition();
            test_calculator_subtraction();
            test_calculator_multiplication();
            test_calculator_division();
            break;
        case 2:
            test_string_functions();
            break;
        case 3:
            test_array_functions();
            break;
        case 4:
            test_memory_functions();
            break;
        case 5:
            run_all_tests();
            return;
        case 6:
            printf("Goodbye!\n");
            return;
        default:
            printf("Invalid choice!\n");
            return;
    }
    
    // Print results for individual test
    printf("\nResults: %d tests, %d passed, %d failed\n", 
           test_count, test_count - failed_count, failed_count);
}

int main() {
    printf("=== C UNIT TESTING FRAMEWORK ===\n");
    printf("Learn professional testing practices!\n");
    printf("This is what separates hobbyists from pros.\n\n");
    
    printf("Key concepts:\n");
    printf("- Test assertions and macros\n");
    printf("- Setup and teardown functions\n");
    printf("- Test organization and suites\n");
    printf("- Edge case testing\n");
    printf("- Integration testing\n");
    printf("- Performance testing\n\n");
    
    int mode;
    printf("Choose mode:\n");
    printf("1. Run all tests automatically\n");
    printf("2. Interactive test runner\n");
    printf("Enter choice: ");
    scanf("%d", &mode);
    
    if (mode == 1) {
        run_all_tests();
    } else if (mode == 2) {
        interactive_test_runner();
    } else {
        printf("Invalid choice. Running all tests...\n");
        run_all_tests();
    }
    
    printf("\n=== LEARNING POINTS ===\n");
    printf("You've learned professional C testing!\n");
    printf("Next steps:\n");
    printf("- Use real Unity framework\n");
    printf("- Add mock objects\n");
    printf("- Test-driven development\n");
    printf("- Continuous integration\n");
    
    return (failed_count == 0) ? 0 : 1;
}
