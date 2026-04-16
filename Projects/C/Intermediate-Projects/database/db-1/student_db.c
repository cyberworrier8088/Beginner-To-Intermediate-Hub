#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_ID 20

typedef struct {
    char name[MAX_NAME];
    char id[MAX_ID];
    int age;
    double gpa;
} Student;

Student database[MAX_STUDENTS];
int student_count = 0;

void add_student() {
    if(student_count >= MAX_STUDENTS) {
        printf("Database is full! Maximum %d students.\n", MAX_STUDENTS);
        return;
    }
    
    Student new_student;
    
    printf("Enter student name: ");
    getchar(); // Clear newline
    fgets(new_student.name, MAX_NAME, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = '\0';
    
    printf("Enter student ID: ");
    fgets(new_student.id, MAX_ID, stdin);
    new_student.id[strcspn(new_student.id, "\n")] = '\0';
    
    printf("Enter student age: ");
    scanf("%d", &new_student.age);
    
    printf("Enter student GPA: ");
    scanf("%lf", &new_student.gpa);
    
    // Check for duplicate ID
    for(int i = 0; i < student_count; i++) {
        if(strcmp(database[i].id, new_student.id) == 0) {
            printf("Student ID already exists!\n");
            return;
        }
    }
    
    database[student_count] = new_student;
    student_count++;
    printf("Student added successfully!\n");
}

void display_all_students() {
    if(student_count == 0) {
        printf("No students in database!\n");
        return;
    }
    
    printf("\n=== ALL STUDENTS ===\n");
    printf("%-5s %-20s %-15s %-5s %-6s\n", "No.", "Name", "ID", "Age", "GPA");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < student_count; i++) {
        printf("%-5d %-20s %-15s %-5d %-6.2f\n", 
               i + 1, 
               database[i].name, 
               database[i].id, 
               database[i].age, 
               database[i].gpa);
    }
    printf("------------------------------------------------\n");
}

void search_student() {
    if(student_count == 0) {
        printf("No students in database!\n");
        return;
    }
    
    char search_id[MAX_ID];
    printf("Enter student ID to search: ");
    getchar(); // Clear newline
    fgets(search_id, MAX_ID, stdin);
    search_id[strcspn(search_id, "\n")] = '\0';
    
    for(int i = 0; i < student_count; i++) {
        if(strcmp(database[i].id, search_id) == 0) {
            printf("\n--- STUDENT FOUND ---\n");
            printf("Name: %s\n", database[i].name);
            printf("ID: %s\n", database[i].id);
            printf("Age: %d\n", database[i].age);
            printf("GPA: %.2f\n", database[i].gpa);
            printf("---------------------\n");
            return;
        }
    }
    
    printf("Student with ID '%s' not found!\n", search_id);
}

void update_student() {
    if(student_count == 0) {
        printf("No students in database!\n");
        return;
    }
    
    char search_id[MAX_ID];
    printf("Enter student ID to update: ");
    getchar(); // Clear newline
    fgets(search_id, MAX_ID, stdin);
    search_id[strcspn(search_id, "\n")] = '\0';
    
    for(int i = 0; i < student_count; i++) {
        if(strcmp(database[i].id, search_id) == 0) {
            printf("Current information:\n");
            printf("Name: %s\n", database[i].name);
            printf("Age: %d\n", database[i].age);
            printf("GPA: %.2f\n", database[i].gpa);
            
            printf("\nEnter new information:\n");
            
            printf("New name (or press Enter to keep current): ");
            char new_name[MAX_NAME];
            fgets(new_name, MAX_NAME, stdin);
            if(strlen(new_name) > 1) {
                new_name[strcspn(new_name, "\n")] = '\0';
                strcpy(database[i].name, new_name);
            }
            
            printf("New age (or 0 to keep current): ");
            int new_age;
            scanf("%d", &new_age);
            if(new_age > 0) {
                database[i].age = new_age;
            }
            
            printf("New GPA (or 0 to keep current): ");
            double new_gpa;
            scanf("%lf", &new_gpa);
            if(new_gpa > 0) {
                database[i].gpa = new_gpa;
            }
            
            printf("Student information updated!\n");
            return;
        }
    }
    
    printf("Student with ID '%s' not found!\n", search_id);
}

void delete_student() {
    if(student_count == 0) {
        printf("No students in database!\n");
        return;
    }
    
    char search_id[MAX_ID];
    printf("Enter student ID to delete: ");
    getchar(); // Clear newline
    fgets(search_id, MAX_ID, stdin);
    search_id[strcspn(search_id, "\n")] = '\0';
    
    for(int i = 0; i < student_count; i++) {
        if(strcmp(database[i].id, search_id) == 0) {
            printf("Student found: %s (%s)\n", database[i].name, database[i].id);
            printf("Are you sure you want to delete? (1=Yes, 0=No): ");
            
            int confirm;
            scanf("%d", &confirm);
            
            if(confirm == 1) {
                // Shift all students left
                for(int j = i; j < student_count - 1; j++) {
                    database[j] = database[j + 1];
                }
                student_count--;
                printf("Student deleted successfully!\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            return;
        }
    }
    
    printf("Student with ID '%s' not found!\n", search_id);
}

void save_to_file() {
    FILE *file = fopen("students.dat", "wb");
    if(file == NULL) {
        printf("Error saving to file!\n");
        return;
    }
    
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(database, sizeof(Student), student_count, file);
    
    fclose(file);
    printf("Database saved to file successfully!\n");
}

void load_from_file() {
    FILE *file = fopen("students.dat", "rb");
    if(file == NULL) {
        printf("No saved database file found.\n");
        return;
    }
    
    fread(&student_count, sizeof(int), 1, file);
    fread(database, sizeof(Student), student_count, file);
    
    fclose(file);
    printf("Database loaded from file successfully!\n");
}

void display_statistics() {
    if(student_count == 0) {
        printf("No students in database!\n");
        return;
    }
    
    double total_gpa = 0;
    int total_age = 0;
    double highest_gpa = 0;
    double lowest_gpa = 4.0;
    
    for(int i = 0; i < student_count; i++) {
        total_gpa += database[i].gpa;
        total_age += database[i].age;
        
        if(database[i].gpa > highest_gpa) {
            highest_gpa = database[i].gpa;
        }
        
        if(database[i].gpa < lowest_gpa) {
            lowest_gpa = database[i].gpa;
        }
    }
    
    printf("\n=== DATABASE STATISTICS ===\n");
    printf("Total Students: %d\n", student_count);
    printf("Average Age: %.1f\n", (double)total_age / student_count);
    printf("Average GPA: %.2f\n", total_gpa / student_count);
    printf("Highest GPA: %.2f\n", highest_gpa);
    printf("Lowest GPA: %.2f\n", lowest_gpa);
    printf("==========================\n");
}

void display_menu() {
    printf("\n=== STUDENT DATABASE SYSTEM ===\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Save to File\n");
    printf("7. Load from File\n");
    printf("8. Statistics\n");
    printf("9. Exit\n");
    printf("Choose an option: ");
}

int main() {
    printf("Welcome to Student Database System!\n");
    printf("Learn file I/O and data structures in C\n");
    
    load_from_file(); // Try to load existing data
    
    int choice;
    do {
        display_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_all_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                update_student();
                break;
            case 5:
                delete_student();
                break;
            case 6:
                save_to_file();
                break;
            case 7:
                load_from_file();
                break;
            case 8:
                display_statistics();
                break;
            case 9:
                save_to_file(); // Auto-save before exit
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
    } while(choice != 9);
    
    return 0;
}
