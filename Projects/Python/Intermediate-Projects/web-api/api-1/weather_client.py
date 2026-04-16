import requests
import json
from datetime import datetime

class WeatherAPI:
    """Simple weather API client for learning API integration"""
    
    def __init__(self, api_key=None):
        """Initialize with API key (free tier available)"""
        # Using OpenWeatherMap API (free tier available)
        self.api_key = api_key or "demo_key"  # Replace with actual key
        self.base_url = "https://api.openweathermap.org/data/2.5"
    
    def get_weather_by_city(self, city_name):
        """Get weather data for a specific city"""
        try:
            url = f"{self.base_url}/weather"
            params = {
                'q': city_name,
                'appid': self.api_key,
                'units': 'metric'  # Celsius
            }
            
            response = requests.get(url, params=params)
            response.raise_for_status()  # Raise exception for bad status
            
            return response.json()
            
        except requests.exceptions.RequestException as e:
            print(f"Error fetching weather data: {e}")
            return None
        except json.JSONDecodeError as e:
            print(f"Error parsing weather data: {e}")
            return None
    
    def get_forecast_by_city(self, city_name, days=5):
        """Get weather forecast for a city"""
        try:
            url = f"{self.base_url}/forecast"
            params = {
                'q': city_name,
                'appid': self.api_key,
                'units': 'metric',
                'cnt': days * 8  # 8 forecasts per day (3-hour intervals)
            }
            
            response = requests.get(url, params=params)
            response.raise_for_status()
            
            return response.json()
            
        except requests.exceptions.RequestException as e:
            print(f"Error fetching forecast data: {e}")
            return None
    
    def format_weather_data(self, weather_data):
        """Format weather data for display"""
        if not weather_data:
            return "No weather data available"
        
        try:
            city = weather_data['name']
            country = weather_data['sys']['country']
            temp = weather_data['main']['temp']
            feels_like = weather_data['main']['feels_like']
            humidity = weather_data['main']['humidity']
            description = weather_data['weather'][0]['description']
            wind_speed = weather_data['wind']['speed']
            
            formatted = f"""
{'='*50}
WEATHER REPORT FOR {city.upper()}, {country}
{'='*50}
🌡️  Temperature: {temp}°C (feels like {feels_like}°C)
💧 Humidity: {humidity}%
🌤️  Conditions: {description.title()}
💨 Wind Speed: {wind_speed} m/s
{'='*50}
            """
            
            return formatted.strip()
            
        except KeyError as e:
            return f"Error formatting weather data: Missing key {e}"
    
    def format_forecast_data(self, forecast_data):
        """Format forecast data for display"""
        if not forecast_data:
            return "No forecast data available"
        
        try:
            city = forecast_data['city']['name']
            country = forecast_data['city']['country']
            
            formatted = f"""
{'='*60}
5-DAY FORECAST FOR {city.upper()}, {country}
{'='*60}
            """
            
            # Group forecasts by day
            daily_forecasts = {}
            for item in forecast_data['list']:
                date = datetime.fromtimestamp(item['dt']).strftime('%Y-%m-%d')
                if date not in daily_forecasts:
                    daily_forecasts[date] = []
                daily_forecasts[date].append(item)
            
            for date, forecasts in list(daily_forecasts.items())[:5]:
                avg_temp = sum(f['main']['temp'] for f in forecasts) / len(forecasts)
                main_condition = forecasts[0]['weather'][0]['description']
                
                formatted += f"""
📅 {date}
🌡️  Avg Temp: {avg_temp:.1f}°C
🌤️  Conditions: {main_condition.title()}
"""
            
            formatted += f"{'='*60}"
            return formatted.strip()
            
        except KeyError as e:
            return f"Error formatting forecast data: Missing key {e}"

def display_menu():
    """Display weather API menu"""
    print("\n" + "="*50)
    print("WEATHER API CLIENT")
    print("="*50)
    print("1. Get Current Weather")
    print("2. Get 5-Day Forecast")
    print("3. Weather History (Demo)")
    print("4. API Information")
    print("5. Exit")
    print("="*50)
    print("Choose an option: ", end="")

def get_city_name():
    """Get city name from user"""
    city = input("Enter city name: ").strip()
    if not city:
        print("City name cannot be empty!")
        return None
    return city

def demo_api_info():
    """Display API information for learning"""
    print(f"""
{'='*60}
API INFORMATION - LEARNING RESOURCES
{'='*60}

🔗 FREE API PROVIDERS:
1. OpenWeatherMap (openweathermap.org)
   - Free tier: 1000 calls/day
   - Sign up required for API key
   
2. WeatherAPI (weatherapi.com)
   - Free tier: 1,000,000 calls/month
   - No sign up required for demo

📚 LEARNING CONCEPTS:
• HTTP Requests (GET, POST, PUT, DELETE)
• API Keys & Authentication
• JSON Data Parsing
• Error Handling
• Rate Limiting
• Response Status Codes

🔧 PYTHON LIBRARIES USED:
• requests - HTTP library
• json - JSON parsing
• datetime - Date/time handling

💡 TIPS FOR REAL USAGE:
1. Replace 'demo_key' with real API key
2. Add proper error handling
3. Implement caching to reduce API calls
4. Add input validation
5. Consider rate limiting
{'='*60}
    """)

def main():
    """Main weather API application"""
    print("Welcome to Weather API Client!")
    print("Learn API integration with real weather data")
    print("\nNote: Using demo mode. Get free API key from openweathermap.org")
    
    weather_api = WeatherAPI()
    
    while True:
        display_menu()
        choice = input().strip()
        
        if choice == '1':
            city = get_city_name()
            if city:
                print(f"\nFetching weather for {city}...")
                weather_data = weather_api.get_weather_by_city(city)
                
                if weather_data and 'weather' in weather_data:
                    print(weather_api.format_weather_data(weather_data))
                else:
                    # Demo data for learning
                    print(f"""
{'='*50}
DEMO WEATHER DATA FOR {city.upper()}
{'='*50}
🌡️  Temperature: 22°C (feels like 24°C)
💧 Humidity: 65%
🌤️  Conditions: Partly Cloudy
💨 Wind Speed: 3.5 m/s
{'='*50}
Note: Get real API key for live data!
                    """)
        
        elif choice == '2':
            city = get_city_name()
            if city:
                print(f"\nFetching forecast for {city}...")
                forecast_data = weather_api.get_forecast_by_city(city)
                
                if forecast_data and 'list' in forecast_data:
                    print(weather_api.format_forecast_data(forecast_data))
                else:
                    print("Demo forecast data would appear here with real API key!")
        
        elif choice == '3':
            print("\nWeather History Feature:")
            print("This would store and display historical weather data")
            print("Implementation requires database integration (SQLite)")
            print("See database projects for learning this concept!")
        
        elif choice == '4':
            demo_api_info()
        
        elif choice == '5':
            print("\nThank you for using Weather API Client!")
            print("Keep learning API integration!")
            break
        
        else:
            print("Invalid choice! Please enter a number between 1 and 5.")
        
        input("\nPress Enter to continue...")

if __name__ == "__main__":
    main()
