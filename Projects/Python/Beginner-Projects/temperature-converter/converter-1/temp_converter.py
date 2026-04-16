def celsius_to_fahrenheit(celsius):
    """Convert Celsius to Fahrenheit"""
    return (celsius * 9/5) + 32

def fahrenheit_to_celsius(fahrenheit):
    """Convert Fahrenheit to Celsius"""
    return (fahrenheit - 32) * 5/9

def celsius_to_kelvin(celsius):
    """Convert Celsius to Kelvin"""
    return celsius + 273.15

def kelvin_to_celsius(kelvin):
    """Convert Kelvin to Celsius"""
    return kelvin - 273.15

def fahrenheit_to_kelvin(fahrenheit):
    """Convert Fahrenheit to Kelvin"""
    celsius = fahrenheit_to_celsius(fahrenheit)
    return celsius_to_kelvin(celsius)

def kelvin_to_fahrenheit(kelvin):
    """Convert Kelvin to Fahrenheit"""
    celsius = kelvin_to_celsius(kelvin)
    return celsius_to_fahrenheit(celsius)

def display_menu():
    """Display conversion menu"""
    print("\n" + "="*50)
    print("TEMPERATURE CONVERTER")
    print("="*50)
    print("1. Celsius to Fahrenheit")
    print("2. Fahrenheit to Celsius")
    print("3. Celsius to Kelvin")
    print("4. Kelvin to Celsius")
    print("5. Fahrenheit to Kelvin")
    print("6. Kelvin to Fahrenheit")
    print("7. Exit")
    print("="*50)

def get_temperature():
    """Get temperature input from user"""
    while True:
        try:
            temp = float(input("Enter temperature: "))
            return temp
        except ValueError:
            print("Please enter a valid number!")

def main():
    """Main temperature converter application"""
    print("Welcome to Temperature Converter!")
    print("Convert between Celsius, Fahrenheit, and Kelvin")
    
    while True:
        display_menu()
        choice = input("Enter your choice (1-7): ")
        
        if choice == '7':
            print("Goodbye!")
            break
        
        if choice in ['1', '2', '3', '4', '5', '6']:
            temp = get_temperature()
            
            if choice == '1':
                result = celsius_to_fahrenheit(temp)
                print(f"{temp}°C = {result:.2f}°F")
                
            elif choice == '2':
                result = fahrenheit_to_celsius(temp)
                print(f"{temp}°F = {result:.2f}°C")
                
            elif choice == '3':
                result = celsius_to_kelvin(temp)
                print(f"{temp}°C = {result:.2f}K")
                
            elif choice == '4':
                result = kelvin_to_celsius(temp)
                print(f"{temp}K = {result:.2f}°C")
                
            elif choice == '5':
                result = fahrenheit_to_kelvin(temp)
                print(f"{temp}°F = {result:.2f}K")
                
            elif choice == '6':
                result = kelvin_to_fahrenheit(temp)
                print(f"{temp}K = {result:.2f}°F")
        else:
            print("Invalid choice! Please enter a number between 1 and 7.")
        
        input("\nPress Enter to continue...")

if __name__ == "__main__":
    main()
