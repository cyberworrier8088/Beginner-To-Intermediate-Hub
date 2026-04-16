# 🗃️ To-Do List - Level 2 (File Keeper)
# In Level 1, we lost our data every time the app closed.
# Here, we fix that using pure Python File I/O (Input/Output).
# No libraries needed! We are just reading and writing to a standard Text File.

import os  # We only import this to check if the file exists when the app starts.

FILE_NAME = "my_database.txt"

def load_tasks():
    """Reads the tasks from the text file into a Python list."""
    tasks = []
    # Check if the file exists before trying to open it!
    if os.path.exists(FILE_NAME):
        # 'r' means Read mode
        with open(FILE_NAME, "r") as file:
            for line in file:
                # .strip() removes the invisible 'newline' character at the end of each line
                tasks.append(line.strip())
    return tasks

def save_tasks(tasks):
    """Writes the current list to the text file, replacing what was there before."""
    # 'w' means Write mode. Be careful, 'w' deletes everything in the file and starts fresh!
    with open(FILE_NAME, "w") as file:
        for task in tasks:
            file.write(task + "\n") # We manually add \n so every task is on a new line

def main():
    print("========================================")
    print("      🗃️ PERSISTENT TO-DO LIST       ")
    print("========================================")
    
    # Load any existing tasks from the hard drive into RAM when the app starts
    tasks = load_tasks()
    print(f"[*] Loaded {len(tasks)} tasks from the hard drive.")

    while True:
        print("\n--- Options ---")
        print("1. View Tasks")
        print("2. Add a Task")
        print("3. Complete/Remove a Task")
        print("4. Exit")
        
        choice = input("\nWhat would you like to do? (1-4): ").strip()

        if choice == '1':
            print("\n--- Your Tasks ---")
            if not tasks:
                print("Your list is empty! Go relax! ☕")
            else:
                for index, task in enumerate(tasks, start=1):
                    print(f"[{index}] {task}")
                    
        elif choice == '2':
            new_task = input("Enter the new task: ").strip()
            if new_task:
                tasks.append(new_task)
                # SAVE IMMEDITELY AFTER CHANGING THE LIST
                save_tasks(tasks)
                print(f"✅ Added & Saved: '{new_task}'")
            else:
                print("⚠️ You cannot add an empty task!")

        elif choice == '3':
            if not tasks:
                print("There's nothing to cross off yet!")
                continue

            try:
                task_num = int(input("Enter the number of the task you completed: "))
                index = task_num - 1
                
                if 0 <= index < len(tasks):
                    removed_task = tasks.pop(index)
                    # SAVE AGAIN because the list changed
                    save_tasks(tasks)
                    print(f"🎉 Well done! You finished: '{removed_task}'")
                else:
                    print("⚠️ That number is not on the list!")
            except ValueError:
                print("⚠️ Please enter a valid number.")

        elif choice == '4':
            print("Goodbye! Your tasks are safely saved on your hard drive! 💾")
            break
            
        else:
            print("⚠️ Invalid choice. Please press 1, 2, 3, or 4.")

if __name__ == "__main__":
    main()
