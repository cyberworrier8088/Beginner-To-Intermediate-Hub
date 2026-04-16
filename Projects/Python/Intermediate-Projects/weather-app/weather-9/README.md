# 🌦️ Live Weather Dashboard - Level 9: The Network Call

Welcome to the **Intermediate Tier**. You are no longer writing scripts that live entirely on your computer. You are now connecting your script to the global internet. 

### 🧠 The Core Concept: Third-Party Packages
Python is famous because of its community. If you need to do something (like connect to a weather server), someone else has probably already written code to make it easy. We use `pip` (Python Package Installer) to download that code. 

For networking, the absolute gold standard library is `requests`. We installed it by typing `pip install requests` in the terminal. 

### 🛠️ Technical Deep Dive
1.  **APIs (Application Programming Interfaces)**: Think of a website like Twitter. You visit `twitter.com` in a browser, and you see visual buttons and images. An API is how *computers* visit Twitter. Instead of visual buttons, the API hands your code a raw dictionary (JSON) of data.
2.  **`requests.get()`**: This is the bread-and-butter of the internet. A "GET" request means "Hello server, please give me data." There are also "POST" requests (for submitting data, like a login form).
3.  **HTTP Status Codes**: How do we know if the server is broken? The server returns a status code!
    - **200**: OK! Perfect.
    - **401**: Unauthorized. (You need a password / API key).
    - **404**: Not Found. (The URL is wrong).
    - **500**: Internal Server Error. (The server crashed).
4.  **Graceful Catching**: We wrapped everything in a `try/except requests.exceptions.ConnectionError`. Why? Because if the user unplugs their WiFi, `requests.get()` will fail and crash the app. We catch the exact WiFi error and print a friendly message instead!

### 🏃 How to Run
Ensure you have an active internet connection, then type:
```bash
python weather.py
```
Watch as your code talks to a satellite and fetches the exact temperature in Tokyo at this very second.
