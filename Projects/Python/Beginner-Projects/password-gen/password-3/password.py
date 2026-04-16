# 🛡️ Password Generator - Level 3 (The Visual Generator)
# We are converting our OOP logic from Level 2 into a full Tkinter Desktop App.
# This app features Checkbuttons for configuration and a visual Slider for length!

import tkinter as tk
from tkinter import messagebox
import random
import string

class PasswordApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Visual Generator V3")
        self.root.geometry("400x500")
        self.root.configure(bg="#1e1e24")
        self.root.resizable(False, False)

        # variables attached to Tkinter checkboxes
        self.var_upper = tk.BooleanVar(value=True)
        self.var_number = tk.BooleanVar(value=True)
        self.var_symbol = tk.BooleanVar(value=True)

        self.setup_ui()

    def setup_ui(self):
        # --- TITLE ---
        tk.Label(self.root, text="Password Generator", font=("Helvetica", 22, "bold"), 
                 bg="#1e1e24", fg="#fb3640").pack(pady=20)

        # --- THE OUTPUT DISPLAY ---
        self.display_var = tk.StringVar(value="Click Generate 👇")
        # We use an Entry box set to 'readonly' so the user can highlight and copy the password!
        self.display = tk.Entry(self.root, textvariable=self.display_var, font=("Courier", 18), 
                                bg="#2b2b36", fg="#ffffff", justify="center", state="readonly", relief="flat")
        self.display.pack(fill="x", padx=30, ipady=15)

        # --- LENGTH SLIDER ---
        tk.Label(self.root, text="Password Length:", bg="#1e1e24", fg="#ffffff", font=("Helvetica", 12)).pack(pady=(20, 5))
        # A Scale widget lets users drag a slider instead of typing numbers
        self.length_slider = tk.Scale(self.root, from_=4, to_=64, orient="horizontal", 
                                      bg="#1e1e24", fg="#ffffff", highlightthickness=0, length=250)
        self.length_slider.set(16) # Default length
        self.length_slider.pack()

        # --- SETTINGS (CHECKBOXES) ---
        check_frame = tk.Frame(self.root, bg="#1e1e24")
        check_frame.pack(pady=20)

        # Styling dict to keep things DRY
        cb_style = {"bg": "#1e1e24", "fg": "#ffffff", "selectcolor": "#2b2b36", "activebackground": "#1e1e24", "font": ("Helvetica", 11)}

        tk.Checkbutton(check_frame, text="Include UPPERCASE (A-Z)", variable=self.var_upper, **cb_style).pack(anchor="w", pady=2)
        tk.Checkbutton(check_frame, text="Include Numbers (0-9)", variable=self.var_number, **cb_style).pack(anchor="w", pady=2)
        tk.Checkbutton(check_frame, text="Include Symbols (!@#)", variable=self.var_symbol, **cb_style).pack(anchor="w", pady=2)

        # --- GENERATE BUTTON ---
        btn = tk.Button(self.root, text="⚡ GENERATE ⚡", font=("Helvetica", 16, "bold"), 
                        bg="#fb3640", fg="white", activebackground="#d92e35", relief="flat", 
                        command=self.generate_password)
        btn.pack(pady=20, ipadx=20, ipady=10)

    def _build_pool(self):
        """Internal logic function to build the character pool based on checkboxes."""
        pool = string.ascii_lowercase
        if self.var_upper.get():
            pool += string.ascii_uppercase
        if self.var_number.get():
            pool += string.digits
        if self.var_symbol.get():
            pool += string.punctuation
        return pool

    def generate_password(self):
        """Action attached to the big red button!"""
        pool = self._build_pool()
        length = self.length_slider.get()

        if not pool:
            # If they unchecked everything except lowercase, and we removed lowercase (not possible in this UI, but good safety)
            # Actually, standard lowercase is always on in this design.
            pass 

        # Generate!
        pw_list = [random.choice(pool) for _ in range(length)]
        final_password = "".join(pw_list)

        # Update the read-only display
        self.display.config(state="normal")
        self.display.delete(0, tk.END)
        self.display.insert(0, final_password)
        self.display.config(state="readonly")
        
if __name__ == "__main__":
    print("Launching Visual Password Generator...")
    root = tk.Tk()
    app = PasswordApp(root)
    root.mainloop()
