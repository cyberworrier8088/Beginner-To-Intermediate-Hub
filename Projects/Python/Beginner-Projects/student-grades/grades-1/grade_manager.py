class Student:
    """Student class to manage student information and grades"""
    
    def __init__(self, name, student_id):
        self.name = name
        self.student_id = student_id
        self.grades = []
    
    def add_grade(self, grade):
        """Add a grade to the student's record"""
        if 0 <= grade <= 100:
            self.grades.append(grade)
            return True
        else:
            print("Grade must be between 0 and 100!")
            return False
    
    def calculate_average(self):
        """Calculate the average grade"""
        if not self.grades:
            return 0
        return sum(self.grades) / len(self.grades)
    
    def get_letter_grade(self):
        """Convert average to letter grade"""
        average = self.calculate_average()
        
        if average >= 90:
            return 'A'
        elif average >= 80:
            return 'B'
        elif average >= 70:
            return 'C'
        elif average >= 60:
            return 'D'
        else:
            return 'F'
    
    def display_info(self):
        """Display student information"""
        print(f"\n--- Student Information ---")
        print(f"Name: {self.name}")
        print(f"ID: {self.student_id}")
        print(f"Grades: {self.grades}")
        print(f"Average: {self.calculate_average():.2f}")
        print(f"Letter Grade: {self.get_letter_grade()}")
        print("-------------------------")

class GradeManager:
    """Grade management system for multiple students"""
    
    def __init__(self):
        self.students = []
    
    def add_student(self):
        """Add a new student to the system"""
        name = input("Enter student name: ").strip()
        student_id = input("Enter student ID: ").strip()
        
        # Check if student ID already exists
        for student in self.students:
            if student.student_id == student_id:
                print("Student ID already exists!")
                return
        
        student = Student(name, student_id)
        self.students.append(student)
        print(f"Student '{name}' added successfully!")
    
    def find_student(self, student_id):
        """Find student by ID"""
        for student in self.students:
            if student.student_id == student_id:
                return student
        return None
    
    def add_grade_to_student(self):
        """Add grade to a specific student"""
        if not self.students:
            print("No students in the system!")
            return
        
        student_id = input("Enter student ID: ").strip()
        student = self.find_student(student_id)
        
        if student:
            try:
                grade = float(input(f"Enter grade for {student.name}: "))
                student.add_grade(grade)
            except ValueError:
                print("Invalid grade! Please enter a number.")
        else:
            print("Student not found!")
    
    def display_all_students(self):
        """Display all students and their information"""
        if not self.students:
            print("No students in the system!")
            return
        
        print(f"\n{'='*60}")
        print("ALL STUDENTS")
        print(f"{'='*60}")
        
        for student in self.students:
            student.display_info()
    
    def display_class_statistics(self):
        """Display class-wide statistics"""
        if not self.students:
            print("No students in the system!")
            return
        
        total_students = len(self.students)
        total_grades = 0
        grade_count = 0
        highest_average = 0
        highest_student = None
        
        for student in self.students:
            if student.grades:
                avg = student.calculate_average()
                total_grades += sum(student.grades)
                grade_count += len(student.grades)
                
                if avg > highest_average:
                    highest_average = avg
                    highest_student = student
        
        class_average = total_grades / grade_count if grade_count > 0 else 0
        
        print(f"\n{'='*50}")
        print("CLASS STATISTICS")
        print(f"{'='*50}")
        print(f"Total Students: {total_students}")
        print(f"Class Average: {class_average:.2f}")
        print(f"Total Grades Entered: {grade_count}")
        
        if highest_student:
            print(f"Highest Performing Student: {highest_student.name} ({highest_average:.2f})")
        print(f"{'='*50}")
    
    def display_menu(self):
        """Display the main menu"""
        print("\n" + "="*50)
        print("STUDENT GRADE MANAGEMENT SYSTEM")
        print("="*50)
        print("1. Add New Student")
        print("2. Add Grade to Student")
        print("3. View All Students")
        print("4. Class Statistics")
        print("5. Exit")
        print("="*50)
        print("Choose an option: ", end="")

def main():
    """Main grade management application"""
    print("Welcome to Student Grade Management System!")
    print("====================================")
    
    manager = GradeManager()
    
    while True:
        manager.display_menu()
        choice = input().strip()
        
        if choice == '1':
            manager.add_student()
        
        elif choice == '2':
            manager.add_grade_to_student()
        
        elif choice == '3':
            manager.display_all_students()
        
        elif choice == '4':
            manager.display_class_statistics()
        
        elif choice == '5':
            print("\nThank you for using Grade Management System!")
            print("Goodbye!")
            break
        
        else:
            print("Invalid choice! Please enter a number between 1 and 5.")
        
        input("\nPress Enter to continue...")

if __name__ == "__main__":
    main()
