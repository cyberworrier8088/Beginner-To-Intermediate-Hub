# 🌤️ Intermediate Dashboard - Level 10 (Live GUI Dashboard)
# In Level 9, we fetched API data in the terminal.
# Now, we combine the 'requests' library with 'tkinter' to build a real Weather Desktop App!

import tkinter as tk
from tkinter import messagebox
import requests
import threading # We use this to prevent the GUI from freezing during network calls!

class WeatherApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Live Weather Station")
        self.root.geometry("400x450")
        self.root.configure(bg="#87CEEB") # Sky blue background!
        self.root.resizable(False, False)

        self.setup_ui()

    def setup_ui(self):
        # --- TITLE ---
        tk.Label(self.root, text="🌤️ Weather Dashboard", font=("Helvetica", 20, "bold"), 
                 bg="#87CEEB", fg="white").pack(pady=20)

        # --- INPUT FIELDS ---
        input_frame = tk.Frame(self.root, bg="#87CEEB")
        input_frame.pack(pady=10)

        # We need Latitude and Longitude to talk to Open-Meteo
        tk.Label(input_frame, text="Latitude:", bg="#87CEEB", font=("Arial", 12, "bold")).grid(row=0, column=0, padx=5, pady=5)
        self.lat_entry = tk.Entry(input_frame, font=("Arial", 12), width=10)
        self.lat_entry.grid(row=0, column=1, padx=5, pady=5)
        self.lat_entry.insert(0, "35.6895") # Default to Tokyo

        tk.Label(input_frame, text="Longitude:", bg="#87CEEB", font=("Arial", 12, "bold")).grid(row=1, column=0, padx=5, pady=5)
        self.lon_entry = tk.Entry(input_frame, font=("Arial", 12), width=10)
        self.lon_entry.grid(row=1, column=1, padx=5, pady=5)
        self.lon_entry.insert(0, "139.6917") # Default to Tokyo

        # --- FETCH BUTTON ---
        self.fetch_btn = tk.Button(self.root, text="Fetch Live Weather", font=("Helvetica", 14, "bold"), 
                                   bg="#FFD700", fg="#333", relief="flat", command=self.start_fetch_thread)
        self.fetch_btn.pack(pady=20, ipadx=10, ipady=5)

        # --- RESULT DISPLAY ---
        self.result_label = tk.Label(self.root, text="Awaiting data...", font=("Courier", 18, "bold"), 
                                     bg="#87CEEB", fg="#333")
        self.result_label.pack(pady=20)

    def start_fetch_thread(self):
        """
        If we do a network request on the main GUI thread, the whole app freezes until the internet responds!
        To fix this, we create a 'Thread' (a background worker) that fetches the data secretly.
        """
        # Change the label so the user knows we are trying
        self.result_label.config(text="Fetching from Satellite... 📡")
        self.fetch_btn.config(state="disabled") # Stop them from clicking 100 times!

        # Start the background worker!
        worker = threading.Thread(target=self.fetch_weather_data)
        worker.start()

    def fetch_weather_data(self):
        """This runs in the background. It safely talks to the API."""
        lat = self.lat_entry.get().strip()
        lon = self.lon_entry.get().strip()

        # Basic input validation
        try:
             float(lat)
             float(lon)
        except ValueError:
             self.update_ui_with_error("Please enter valid numbers.")
             return

        url = f"https://api.open-meteo.com/v1/forecast?latitude={lat}&longitude={lon}&current_weather=true"

        try:
            # The magical request call
            response = requests.get(url, timeout=5) # 5 second timeout limit!
            
            if response.status_code == 200:
                data = response.json()
                current = data.get("current_weather", {})
                temp = current.get("temperature", "N/A")
                wind = current.get("windspeed", "N/A")
                
                # We format the success message
                success_text = f"🌡️ Temp: {temp}°C\n💨 Wind: {wind} km/h"
                self.update_ui_with_success(success_text)
            else:
                self.update_ui_with_error(f"Server Error: {response.status_code}")
                
        except requests.exceptions.ConnectionError:
            self.update_ui_with_error("No Internet Connection.")
        except requests.exceptions.Timeout:
            self.update_ui_with_error("The server took too long to reply.")
        except Exception as e:
            self.update_ui_with_error("An unknown error occurred.")

    # --- THREAD-SAFE UI UPDATERS ---
    # We use .after(0, ...) to force the main GUI thread to safely update the text.

    def update_ui_with_error(self, error_msg):
        def update():
            self.result_label.config(text=f"❌ {error_msg}")
            self.fetch_btn.config(state="normal")
            messagebox.showerror("Weather API Error", error_msg)
        self.root.after(0, update)

    def update_ui_with_success(self, text):
        def update():
            self.result_label.config(text=text)
            self.fetch_btn.config(state="normal")
        self.root.after(0, update)

if __name__ == "__main__":
    print("Launching Live Weather Dashboard...")
    root = tk.Tk()
    app = WeatherApp(root)
    root.mainloop()
