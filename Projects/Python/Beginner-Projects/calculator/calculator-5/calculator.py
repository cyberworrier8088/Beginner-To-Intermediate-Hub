# Welcome to Level 5: The "Visual" Way (GUI)
# In this final level, we build a real desktop application with buttons and a window!
# We use 'tkinter', which is Python's built-in library for creating interfaces.

import tkinter as tk
from tkinter import messagebox

# --- THE APP SETUP ---

def on_click(button_text):
    """
    This function handles what happens when any button is clicked.
    """
    current_text = entry.get()
    
    if button_text == "=":
        try:
            # 'eval' is a powerful but dangerous tool that calculates strings.
            # In a real app, we'd use a safer way, but for a beginner GUI, it's perfect!
            result = eval(current_text)
            entry.delete(0, tk.END)
            entry.insert(tk.END, str(result))
        except ZeroDivisionError:
            messagebox.showerror("Error", "You can't divide by zero!")
            entry.delete(0, tk.END)
        except Exception:
            messagebox.showerror("Error", "Invalid Input")
            entry.delete(0, tk.END)
            
    elif button_text == "C":
        # Clear the display
        entry.delete(0, tk.END)
    else:
        # Append the button text to the current entry
        entry.insert(tk.END, button_text)

# --- CREATING THE WINDOW ---

# 1. Initialize the main window
root = tk.Tk()
root.title("Python Pro Calculator")
root.geometry("300x400")
root.resizable(False, False)

# 2. The Display Screen
# This is where the numbers show up.
entry = tk.Entry(root, font=("Arial", 24), borderwidth=5, relief="flat", justify="right")
entry.grid(row=0, column=0, columnspan=4, padx=10, pady=20, sticky="nsew")

# 3. Defining the Buttons
# We list them out in a grid pattern.
buttons = [
    '7', '8', '9', '/',
    '4', '5', '6', '*',
    '1', '2', '3', '-',
    'C', '0', '=', '+'
]

# 4. Building the Buttons on the Screen
row_val = 1
col_val = 0

for button in buttons:
    # We use a 'lambda' here to pass the specific button text to the function.
    action = lambda x=button: on_click(x)
    
    tk.Button(root, text=button, width=5, height=2, font=("Arial", 14),
              command=action).grid(row=row_val, column=col_val, padx=5, pady=5, sticky="nsew")
    
    col_val += 1
    if col_val > 3:
        col_val = 0
        row_val += 1

# 5. Make the grid expand nicely
for i in range(4):
    root.grid_columnconfigure(i, weight=1)
for i in range(1, 5):
    root.grid_rowconfigure(i, weight=1)

# --- START THE APP ---
print("Opening the GUI Calculator window...")
root.mainloop()

# Note: If you're running this on a server without a screen, it might not open.
# But on your personal computer, a real window will pop up!
