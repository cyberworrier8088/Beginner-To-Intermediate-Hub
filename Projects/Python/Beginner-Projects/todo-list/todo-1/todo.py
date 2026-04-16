# 📝 To-Do List - Level 1 (Memory Track)
# Welcome to a new project! 
# A To-Do list is the classic "Hello World" of intermediate programming. 
# In Level 1, we use pure Python. ZERO imported libraries!

def main():
    # This is a Python List. It will hold our tasks in the computer's RAM (memory).
    # NOTE: Because it's just in memory, if you exit the program, the tasks vanish!
    tasks = []

    print("========================================")
    print("      📝 MY SIMPLE TO-DO LIST 📝      ")
    print("========================================")

    # We use a 'while True' loop to keep asking the user what they want to do.
    while True:
        print("\n--- Options ---")
        print("1. View Tasks")
        print("2. Add a Task")
        print("3. Complete/Remove a Task")
        print("4. Exit")
        
        choice = input("\nWhat would you like to do? (1-4): ").strip()

        if choice == '1':
            print("\n--- Your Tasks ---")
            # If the list is empty, tell them.
            if len(tasks) == 0:
                print("Your list is empty! Go relax! ☕")
            else:
                # Loop through the list and print each task.
                # 'enumerate' is a cool trick that gives us both the index (number) and the task itself!
                # We do start=1 so the list looks like [1, 2, 3] instead of Python's default [0, 1, 2]
                for index, task in enumerate(tasks, start=1):
                    print(f"[{index}] {task}")
                    
        elif choice == '2':
            # Add a new task to the end of our list using .append()
            new_task = input("Enter the new task: ").strip()
            if new_task:
                tasks.append(new_task)
                print(f"✅ Added: '{new_task}'")
            else:
                print("⚠️ You cannot add an empty task!")

        elif choice == '3':
            # To delete a task, we need to know its number.
            if len(tasks) == 0:
                print("There's nothing to cross off yet!")
                continue

            try:
                task_num = int(input("Enter the number of the task you completed: "))
                # Humans count from 1, but Python lists start at index 0.
                # So we subtract 1 to find the correct item in the list!
                index_to_remove = task_num - 1
                
                # Check if the number is valid
                if 0 <= index_to_remove < len(tasks):
                    removed_task = tasks.pop(index_to_remove)
                    print(f"🎉 Well done! You finished: '{removed_task}'")
                else:
                    print("⚠️ That number is not on the list!")
            except ValueError:
                print("⚠️ Please enter a valid number, not text.")

        elif choice == '4':
            # Break out of the infinite loop
            print("Goodbye! See you next time! 👋")
            break
            
        else:
            print("⚠️ Invalid choice. Please press 1, 2, 3, or 4.")

# Standard entry point execution
if __name__ == "__main__":
    main()
