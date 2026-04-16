"""
Async Weather Dashboard - Level 10: Asynchronous Programming
Learn threading and async programming to prevent GUI freezing!
This is what separates hobbyists from professionals.
"""

import tkinter as tk
from tkinter import ttk, messagebox
import threading
import time
import json
from datetime import datetime
import queue

class WeatherAPI:
    """Mock Weather API for demonstration"""
    
    def __init__(self):
        self.cities = {
            "New York": {"temp": 72, "humidity": 65, "condition": "Partly Cloudy"},
            "London": {"temp": 59, "humidity": 70, "condition": "Rainy"},
            "Tokyo": {"temp": 68, "humidity": 55, "condition": "Sunny"},
            "Paris": {"temp": 64, "humidity": 60, "condition": "Cloudy"},
            "Sydney": {"temp": 77, "humidity": 50, "condition": "Clear"},
            "Mumbai": {"temp": 88, "humidity": 80, "condition": "Humid"},
            "Moscow": {"temp": 45, "humidity": 75, "condition": "Snowy"},
            "Dubai": {"temp": 95, "humidity": 40, "condition": "Hot & Sunny"}
        }
    
    def get_weather(self, city):
        """Simulate API call with delay"""
        print(f"API: Fetching weather for {city}...")
        
        # Simulate network delay (2-4 seconds)
        time.sleep(2)
        
        if city in self.cities:
            return {
                "city": city,
                "temperature": self.cities[city]["temp"],
                "humidity": self.cities[city]["humidity"],
                "condition": self.cities[city]["condition"],
                "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        else:
            return None

class AsyncWeatherDashboard:
    """Main dashboard application with threading"""
    
    def __init__(self, root):
        self.root = root
        self.root.title("Async Weather Dashboard - Level 10")
        self.root.geometry("800x600")
        
        # Weather API
        self.api = WeatherAPI()
        
        # Thread management
        self.threads = []
        self.thread_queue = queue.Queue()
        
        # Weather data storage
        self.weather_data = {}
        
        # Setup UI
        self.setup_ui()
        
        # Start queue checker
        self.check_queue()
        
    def setup_ui(self):
        """Setup the user interface"""
        
        # Main frame
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Title
        title_label = ttk.Label(main_frame, text="Async Weather Dashboard", 
                               font=("Arial", 16, "bold"))
        title_label.grid(row=0, column=0, columnspan=3, pady=10)
        
        # Subtitle explaining async concept
        subtitle_label = ttk.Label(main_frame, 
                                  text="Learn threading - GUI stays responsive during API calls!",
                                  font=("Arial", 10, "italic"))
        subtitle_label.grid(row=1, column=0, columnspan=3, pady=5)
        
        # City selection
        ttk.Label(main_frame, text="Select Cities:").grid(row=2, column=0, sticky=tk.W, pady=5)
        
        # City listbox with scrollbar
        list_frame = ttk.Frame(main_frame)
        list_frame.grid(row=3, column=0, columnspan=2, sticky=(tk.W, tk.E, tk.N, tk.S), pady=5)
        
        scrollbar = ttk.Scrollbar(list_frame)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        self.city_listbox = tk.Listbox(list_frame, selectmode=tk.MULTIPLE, 
                                       yscrollcommand=scrollbar.set, height=8)
        self.city_listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar.config(command=self.city_listbox.yview)
        
        # Add cities to listbox
        for city in self.api.cities.keys():
            self.city_listbox.insert(tk.END, city)
        
        # Buttons
        button_frame = ttk.Frame(main_frame)
        button_frame.grid(row=4, column=0, columnspan=3, pady=10)
        
        self.fetch_button = ttk.Button(button_frame, text="Fetch Weather (Async)", 
                                       command=self.fetch_weather_async)
        self.fetch_button.pack(side=tk.LEFT, padx=5)
        
        self.sync_button = ttk.Button(button_frame, text="Fetch Weather (Sync - DEMO)", 
                                      command=self.fetch_weather_sync)
        self.sync_button.pack(side=tk.LEFT, padx=5)
        
        self.clear_button = ttk.Button(button_frame, text="Clear", 
                                       command=self.clear_weather)
        self.clear_button.pack(side=tk.LEFT, padx=5)
        
        # Status label
        self.status_label = ttk.Label(main_frame, text="Ready", 
                                      font=("Arial", 10))
        self.status_label.grid(row=5, column=0, columnspan=3, pady=5)
        
        # Progress bar
        self.progress = ttk.Progressbar(main_frame, mode='indeterminate')
        self.progress.grid(row=6, column=0, columnspan=3, sticky=(tk.W, tk.E), pady=5)
        
        # Weather display area
        weather_frame = ttk.LabelFrame(main_frame, text="Weather Data", padding="10")
        weather_frame.grid(row=7, column=0, columnspan=3, sticky=(tk.W, tk.E, tk.N, tk.S), pady=10)
        
        # Create weather display widgets
        self.weather_widgets = {}
        
        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=1)
        main_frame.rowconfigure(7, weight=1)
        
    def fetch_weather_async(self):
        """Fetch weather using threading (NON-BLOCKING)"""
        print("\n=== ASYNC WEATHER FETCH ===")
        print("Using threading - GUI stays responsive!")
        
        # Get selected cities
        selected_indices = self.city_listbox.curselection()
        if not selected_indices:
            messagebox.showwarning("No Selection", "Please select at least one city!")
            return
        
        cities = [self.city_listbox.get(i) for i in selected_indices]
        
        print(f"Fetching weather for {len(cities)} cities using threads...")
        
        # Update status
        self.status_label.config(text="Fetching weather asynchronously...")
        self.progress.start()
        
        # Disable buttons during fetch
        self.fetch_button.config(state='disabled')
        self.sync_button.config(state='disabled')
        
        # Create and start threads for each city
        for city in cities:
            thread = threading.Thread(target=self.fetch_city_weather, args=(city,))
            thread.daemon = True  # Thread will exit when main program exits
            thread.start()
            self.threads.append(thread)
            print(f"Started thread for {city}")
        
        print(f"Started {len(cities)} threads. GUI remains responsive!")
        
    def fetch_city_weather(self, city):
        """Worker function for thread - fetches weather for one city"""
        print(f"Thread {threading.current_thread().name}: Starting fetch for {city}")
        
        try:
            # Simulate API call
            weather = self.api.get_weather(city)
            
            if weather:
                # Put result in queue for main thread to process
                self.thread_queue.put(('success', weather))
                print(f"Thread {threading.current_thread().name}: Success for {city}")
            else:
                self.thread_queue.put(('error', city))
                print(f"Thread {threading.current_thread().name}: Error for {city}")
                
        except Exception as e:
            self.thread_queue.put(('exception', city, str(e)))
            print(f"Thread {threading.current_thread().name}: Exception for {city}: {e}")
    
    def check_queue(self):
        """Check queue for thread results and update GUI"""
        try:
            while True:
                result = self.thread_queue.get_nowait()
                
                if result[0] == 'success':
                    weather = result[1]
                    self.display_weather_data(weather)
                    
                elif result[0] == 'error':
                    city = result[1]
                    self.display_error(city, "City not found")
                    
                elif result[0] == 'exception':
                    city, error = result[1], result[2]
                    self.display_error(city, error)
                    
        except queue.Empty:
            pass
        
        # Check if all threads are done
        if self.threads:
            alive_threads = [t for t in self.threads if t.is_alive()]
            if not alive_threads:
                # All threads done
                self.progress.stop()
                self.fetch_button.config(state='normal')
                self.sync_button.config(state='normal')
                self.status_label.config(text="Async fetch complete!")
                self.threads.clear()
            else:
                self.status_label.config(text=f"Fetching... {len(alive_threads)} threads active")
        
        # Schedule next check
        self.root.after(100, self.check_queue)  # Check every 100ms
    
    def fetch_weather_sync(self):
        """Fetch weather synchronously (BLOCKING - FOR DEMO PURPOSES)"""
        print("\n=== SYNC WEATHER FETCH (DEMO) ===")
        print("This will FREEZE the GUI - see why threading is important!")
        
        # Get selected cities
        selected_indices = self.city_listbox.curselection()
        if not selected_indices:
            messagebox.showwarning("No Selection", "Please select at least one city!")
            return
        
        cities = [self.city_listbox.get(i) for i in selected_indices]
        
        # Update status
        self.status_label.config(text="Fetching weather synchronously... GUI FROZEN!")
        self.progress.start()
        
        # Disable buttons
        self.fetch_button.config(state='disabled')
        self.sync_button.config(state='disabled')
        
        # Fetch weather one by one (blocking)
        for i, city in enumerate(cities):
            print(f"Sync: Fetching {city} ({i+1}/{len(cities)})...")
            
            # This blocks the main thread - GUI freezes!
            weather = self.api.get_weather(city)
            
            if weather:
                self.display_weather_data(weather)
            else:
                self.display_error(city, "City not found")
        
        # Re-enable buttons
        self.progress.stop()
        self.fetch_button.config(state='normal')
        self.sync_button.config(state='normal')
        self.status_label.config(text="Sync fetch complete! Notice GUI was frozen...")
        
        print("Sync fetch complete - GUI was frozen during API calls!")
    
    def display_weather_data(self, weather):
        """Display weather data in the GUI"""
        city = weather['city']
        
        # Create frame for this city if it doesn't exist
        if city not in self.weather_widgets:
            self.create_city_widget(city)
        
        # Update the widget
        widgets = self.weather_widgets[city]
        
        widgets['temp'].config(text=f"Temperature: {weather['temperature']}°F")
        widgets['humidity'].config(text=f"Humidity: {weather['humidity']}%")
        widgets['condition'].config(text=f"Condition: {weather['condition']}")
        widgets['timestamp'].config(text=f"Updated: {weather['timestamp']}")
        
        print(f"GUI updated with weather for {city}")
    
    def create_city_widget(self, city):
        """Create widget for displaying city weather"""
        # Create frame
        city_frame = ttk.LabelFrame(self.root, text=city, padding="10")
        
        # Find next available position
        row = 0
        col = 0
        max_cols = 4
        
        # Calculate position based on existing widgets
        widget_count = len(self.weather_widgets)
        row = 8 + (widget_count // max_cols)
        col = widget_count % max_cols
        
        city_frame.grid(row=row, column=col, padx=5, pady=5, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Create labels
        temp_label = ttk.Label(city_frame, text="Temperature: --", font=("Arial", 10, "bold"))
        temp_label.pack(anchor=tk.W)
        
        humidity_label = ttk.Label(city_frame, text="Humidity: --")
        humidity_label.pack(anchor=tk.W)
        
        condition_label = ttk.Label(city_frame, text="Condition: --")
        condition_label.pack(anchor=tk.W)
        
        timestamp_label = ttk.Label(city_frame, text="Updated: --", font=("Arial", 8))
        timestamp_label.pack(anchor=tk.W)
        
        # Store widgets
        self.weather_widgets[city] = {
            'frame': city_frame,
            'temp': temp_label,
            'humidity': humidity_label,
            'condition': condition_label,
            'timestamp': timestamp_label
        }
    
    def display_error(self, city, error):
        """Display error message"""
        if city not in self.weather_widgets:
            self.create_city_widget(city)
        
        widgets = self.weather_widgets[city]
        widgets['temp'].config(text=f"Error: {error}", foreground="red")
        widgets['humidity'].config(text="")
        widgets['condition'].config(text="")
        widgets['timestamp'].config(text="")
    
    def clear_weather(self):
        """Clear all weather data"""
        print("Clearing weather data...")
        
        # Remove all city widgets
        for widgets in self.weather_widgets.values():
            widgets['frame'].destroy()
        
        self.weather_widgets.clear()
        self.status_label.config(text="Weather data cleared")

def main():
    """Main application entry point"""
    print("=== ASYNC WEATHER DASHBOARD - LEVEL 10 ===")
    print("Learn threading and asynchronous programming!")
    print("\nKey Concepts:")
    print("- Threading prevents GUI freezing")
    print("- Queue for thread-safe communication")
    print("- Main thread handles GUI, worker threads handle I/O")
    print("- This is how professional applications work!")
    
    root = tk.Tk()
    app = AsyncWeatherDashboard(root)
    
    try:
        root.mainloop()
    except KeyboardInterrupt:
        print("\nApplication closed by user")

if __name__ == "__main__":
    main()
