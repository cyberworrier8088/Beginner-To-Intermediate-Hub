# 🌟 To-Do List - Level 4 (The Visual Planner)
# We are combining the JSON database from Level 3 with a Tkinter GUI!
# It features a Listbox to show tasks, an Entry box to add them, and buttons to manage them.

import tkinter as tk
from tkinter import messagebox
import json
import os

FILE_NAME = "database.json"

class TodoApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Visual To-Do Planner")
        self.root.geometry("400x550")
        self.root.configure(bg="#f4f4f9")
        
        # Load data from our JSON file!
        self.tasks = self.load_data()
        
        self.create_widgets()
        self.refresh_listbox() # Populate the visual list immediately

    def load_data(self):
        """Loads tasks from the JSON database safely."""
        if os.path.exists(FILE_NAME):
            try:
                with open(FILE_NAME, "r") as file:
                    return json.load(file)
            except json.JSONDecodeError:
                messagebox.showwarning("Warning", "Corrupted database. Starting fresh.")
                return []
        return []

    def save_data(self):
        """Saves current tasks to the JSON database."""
        with open(FILE_NAME, "w") as file:
            json.dump(self.tasks, file, indent=4)

    def create_widgets(self):
        # --- TITLE AREA ---
        title_lbl = tk.Label(self.root, text="My Tasks", font=("Helvetica", 24, "bold"), bg="#f4f4f9", fg="#333")
        title_lbl.pack(pady=15)

        # --- INPUT AREA ---
        input_frame = tk.Frame(self.root, bg="#f4f4f9")
        input_frame.pack(pady=5, padx=20, fill="x")

        self.task_entry = tk.Entry(input_frame, font=("Helvetica", 14), relief="solid", borderwidth=1)
        self.task_entry.pack(side="left", expand=True, fill="x", padx=(0, 10), ipady=5)
        # Bind the 'Enter' key so you can type and press Enter quickly
        self.task_entry.bind("<Return>", lambda event: self.add_task())

        add_btn = tk.Button(input_frame, text="Add", font=("Helvetica", 12, "bold"), bg="#4CAF50", fg="white", 
                            relief="flat", command=self.add_task)
        add_btn.pack(side="right", ipadx=10, ipady=3)

        # --- LIST AREA ---
        # A Listbox is a special Tkinter widget that holds a scrollable list of text items
        list_frame = tk.Frame(self.root)
        list_frame.pack(pady=15, padx=20, expand=True, fill="both")
        
        self.listbox = tk.Listbox(list_frame, font=("Helvetica", 14), selectbackground="#d1e7dd", 
                                  selectforeground="black", activestyle="none", relief="flat")
        self.listbox.pack(side="left", expand=True, fill="both")
        
        # Add a scrollbar just in case they have 100 tasks!
        scrollbar = tk.Scrollbar(list_frame)
        scrollbar.pack(side="right", fill="y")
        self.listbox.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=self.listbox.yview)

        # --- BUTTON AREA ---
        action_frame = tk.Frame(self.root, bg="#f4f4f9")
        action_frame.pack(pady=15, fill="x")

        toggle_btn = tk.Button(action_frame, text="Mark Done / Undone", font=("Helvetica", 12), bg="#2196F3", 
                               fg="white", relief="flat", command=self.toggle_task)
        toggle_btn.pack(side="left", expand=True, padx=5, ipady=5)

        delete_btn = tk.Button(action_frame, text="Delete Task", font=("Helvetica", 12), bg="#f44336", 
                               fg="white", relief="flat", command=self.delete_task)
        delete_btn.pack(side="right", expand=True, padx=5, ipady=5)

    def refresh_listbox(self):
        """Clears the visual listbox and redraws it from our Python list."""
        self.listbox.delete(0, tk.END)
        for task in self.tasks:
            symbol = "✓" if task["status"] == "Done" else "○"
            # We visually insert the text into the Listbox
            self.listbox.insert(tk.END, f"{symbol}  {task['name']}")
            
            # If it's done, let's color it grey so it looks 'completed'
            if task["status"] == "Done":
                self.listbox.itemconfig(tk.END, fg="#aaaaaa")

    def add_task(self):
        task_name = self.task_entry.get().strip()
        if not task_name:
            messagebox.showwarning("Oops", "Please type a task first!")
            return
            
        new_task = {"name": task_name, "status": "Pending"}
        self.tasks.append(new_task)
        self.save_data()
        
        self.task_entry.delete(0, tk.END) # Clear the exact typed text
        self.refresh_listbox()

    def toggle_task(self):
        # .curselection() returns a tuple of the highlighted indexes (e.g., (0,) or (2,))
        selected = self.listbox.curselection()
        if not selected:
            messagebox.showinfo("Select", "Please select a task from the list to toggle.")
            return
            
        index = selected[0]
        # Flip the status
        if self.tasks[index]["status"] == "Pending":
             self.tasks[index]["status"] = "Done"
        else:
             self.tasks[index]["status"] = "Pending"
             
        self.save_data()
        self.refresh_listbox()

    def delete_task(self):
        selected = self.listbox.curselection()
        if not selected:
            messagebox.showinfo("Select", "Please select a task to delete.")
            return
            
        index = selected[0]
        # Ask for confirmation - safety first!
        confirm = messagebox.askyesno("Confirm Delete", f"Are you sure you want to delete '{self.tasks[index]['name']}'?")
        if confirm:
            self.tasks.pop(index)
            self.save_data()
            self.refresh_listbox()

if __name__ == "__main__":
    print("Launching Visual To-Do Planner...")
    app_window = tk.Tk()
    app = TodoApp(app_window)
    app_window.mainloop()
