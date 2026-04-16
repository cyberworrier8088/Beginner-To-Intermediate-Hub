# 🗄️ To-Do List - Level 3 (The JSON Database)
# In Level 2, we saved data to a basic text file. That works for simple strings!
# But what if our tasks have BOTH a "name" AND a "status" (Done/Pending)?
# Plain text files get messy when saving complex dictionaries. 
# So, we introduce our first Standard Library tool: the 'json' module.

import json # Built-in library to format data exactly like web servers do!
import os

FILE_NAME = "database.json"

def load_data():
    """Loads a JSON file and turns it into a Python List of Dictionaries."""
    if os.path.exists(FILE_NAME):
        # We wrap this in a 'try' block just in case the JSON file got corrupted by a human
        try:
            with open(FILE_NAME, "r") as file:
                return json.load(file) # The magic happens here!
        except json.JSONDecodeError:
            print("[!] Warning: Database corrupted. Starting fresh.")
            return []
    return []

def save_data(tasks):
    """Takes our List of Dictionaries and saves it cleanly to a JSON file."""
    with open(FILE_NAME, "w") as file:
        # indent=4 makes the file look pretty and readable to humans!
        json.dump(tasks, file, indent=4) 

def main():
    print("========================================")
    print("        🗄️ JSON TO-DO DATABASE        ")
    print("========================================")
    
    # In this level, 'tasks' is a list of DICTIONARIES.
    # Example format: [{"name": "Buy milk", "status": "Pending"}, {"name": "Read book", "status": "Done"}]
    tasks = load_data()

    while True:
        print("\n--- Command Center ---")
        print("1. View Dashboard")
        print("2. Add Task")
        print("3. Toggle Task Status (Done/Pending)")
        print("4. Delete Task")
        print("5. Exit")
        
        choice = input("\nAction (1-5): ").strip()

        if choice == '1':
            print("\n--- Status Dashboard ---")
            if not tasks:
                print("Everything is empty. 🛸")
            else:
                for index, item in enumerate(tasks, start=1):
                    # We check the status to print a nice visual emoji
                    symbol = "✅" if item["status"] == "Done" else "⏳"
                    print(f"[{index}] {symbol} {item['name']}")
                    
        elif choice == '2':
            name = input("Task Name: ").strip()
            if name:
                # Notice we are adding a DICTIONARY to the list, not just a string!
                new_task = {"name": name, "status": "Pending"}
                tasks.append(new_task)
                save_data(tasks)
                print(f"[*] Task '{name}' injected into database.")

        elif choice == '3':
            try:
                task_num = int(input("Enter Task Number to Toggle Status: "))
                index = task_num - 1
                if 0 <= index < len(tasks):
                    # Flip the status depending on what it currently is
                    current_status = tasks[index]["status"]
                    if current_status == "Pending":
                        tasks[index]["status"] = "Done"
                    else:
                        tasks[index]["status"] = "Pending"
                        
                    save_data(tasks)
                    print(f"[*] Task '{tasks[index]['name']}' updated to: {tasks[index]['status']}")
                else:
                    print("[!] Invalid Task ID.")
            except ValueError:
                print("[!] Please type a number.")

        elif choice == '4':
            try:
                task_num = int(input("Enter Task Number to DELETE forever: "))
                index = task_num - 1
                if 0 <= index < len(tasks):
                    deleted = tasks.pop(index)
                    save_data(tasks)
                    print(f"[*] PERMANENTLY REMOVED: '{deleted['name']}'")
                else:
                    print("[!] Invalid Task ID.")
            except ValueError:
                print("[!] Please type a number.")

        elif choice == '5':
            print("System shutting down... Data securely saved as JSON.")
            break

if __name__ == "__main__":
    main()
