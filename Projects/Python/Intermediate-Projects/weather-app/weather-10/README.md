# 🌤️ Live Weather Dashboard - Method 10: The Interactive Network GUI

Welcome to **Level 10**, the absolute peak of the Weather App series! We have combined the graphical interface tricks from `tkinter` with the real-world network requests of `pip install requests`. 

### 🧠 The Core Concept: Asynchronous Threading
If you run a network request (`requests.get`) inside a Graphical User Interface, you will encounter a massive problem: **Freezing**.
Python runs on a "Single Thread" by default. If Python stops to ask the Open-Meteo server for the weather, it stops updating the screen. Your Mac/Windows OS will think the app crashed and might display the "Spinning Wheel of Death" or "(Not Responding)".

### 🛠️ Technical Deep Dive
1.  **`import threading`**: This is a powerful standard library. We use `threading.Thread(target=...)` to spawn a "background worker". The main thread keeps the GUI alive and rotating, while the background thread quietly communicates with the satellite.
2.  **Thread-Safe UI Updates**: A background thread is NOT allowed to touch the GUI directly. If it does, the app will crash mysteriously. We use a neat trick `self.root.after(0, update)` to pass messages from the background thread safely back to the main thread.
3.  **Network Timeouts**: Notice `requests.get(url, timeout=5)`? If the API server crashes, the connection will hang indefinitely forever. Adding a `timeout` explicitly forces the script to give up after 5 seconds and show the user a friendly "Error" instead of hanging. 

### 🏃 How to Run
Ensure you have an active internet connection, then type:
```bash
python weather.py
```
Type different Latitudes and Longitudes (for example, `40.7128` and `-74.0060` for New York City) and hit Fetch!
