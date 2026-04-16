# 🌦️ Intermediate Dashboard - Level 9 (The Raw API Call)
# Welcome to Intermediate territory! Here we start using 'Third-Party' libraries.
# We ran `pip install requests` to install a library made by the Python community.
# Why? Because talking to the internet using built-in methods takes 20 lines of messy code.
# The `requests` library does it in 1 line!

import requests # External third-party library
import time

def get_live_weather(latitude, longitude):
    """
    Sends a request to the Open-Meteo server and fetches live JSON data.
    """
    url = f"https://api.open-meteo.com/v1/forecast?latitude={latitude}&longitude={longitude}&current_weather=true"
    
    print(f"[*] Dispatching network request to: {url}")
    print("[*] Waiting for server response...")
    
    # We add a tiny delay just to make it feel like real networking!
    time.sleep(1)

    try:
        # Boom! This ONE line reaches out to a satellite/server thousands of miles away!
        response = requests.get(url)
        
        # We check the HTTP Status Code. 200 means "OK! Everything worked."
        # 404 means "Not Found", 500 means "Server Error".
        if response.status_code == 200:
            # Another magic feature of 'requests': it converts the raw JSON byte data 
            # straight into a Python Dictionary automatically!
            weather_data = response.json()
            return weather_data
        else:
            print(f"[!] Server returned a bad status code: {response.status_code}")
            return None
            
    except requests.exceptions.ConnectionError:
        # What if the user's WiFi is turned off? We catch the connection error!
        print("[!] Critical Error: Could not connect to the internet. Check your WiFi.")
        return None

def main():
    print("========================================")
    print("      🌦️ TERMINAL WEATHER STATION      ")
    print("========================================")
    print("Let's fetch the weather for Tokyo, Japan (Lat: 35.6895, Lon: 139.6917)\n")

    tokyo_lat = 35.6895
    tokyo_lon = 139.6917

    # Fetch the data
    data = get_live_weather(tokyo_lat, tokyo_lon)

    if data:
        print("\n--- SERVER REPLIED WITH SUCCESS (200 OK) ---")
        
        # The server sends back a massive dictionary. We "parse" it to find exactly what we want.
        # It looks like: {"current_weather": {"temperature": 15.2, "windspeed": 10.4}}
        
        current = data.get("current_weather", {})
        temp = current.get("temperature", "Unknown")
        wind = current.get("windspeed", "Unknown")
        
        print(f"🌡️ Temperature in Tokyo: {temp}°C")
        print(f"💨 Wind Speed: {wind} km/h")
        print("\nNotice how we pulled real-world data directly into our app? You're an engineer now!")

if __name__ == "__main__":
    main()
