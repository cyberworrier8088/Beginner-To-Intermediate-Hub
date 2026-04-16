/*
 * Unit Converter in Rust - Level 2: Data Structures & Business Logic
 * 
 * Welcome to utility programming in Rust! This is where precision meets safety.
 * Learn data structures, mathematical operations, and user interface design.
 * 
 * Key concepts you'll learn:
 * - Enum for unit types and categories
 * - Structs and impl blocks for data organization
 * - Pattern matching for conversion logic
 * - Error handling with Result types
 * - User input validation and sanitization
 * - Mathematical operations and precision
 * - Human-like code with detailed explanations!
 */

use std::io::{self, Write};
use std::collections::HashMap;

// Unit categories for organization
#[derive(Debug, Clone, Copy, PartialEq)]
enum UnitCategory {
    Length,
    Weight,
    Temperature,
    Volume,
    Area,
    Speed,
    Time,
}

// Length units
#[derive(Debug, Clone, Copy, PartialEq)]
enum LengthUnit {
    Meter,
    Kilometer,
    Centimeter,
    Millimeter,
    Mile,
    Yard,
    Foot,
    Inch,
}

impl LengthUnit {
    fn to_string(&self) -> &'static str {
        match self {
            LengthUnit::Meter => "Meter",
            LengthUnit::Kilometer => "Kilometer",
            LengthUnit::Centimeter => "Centimeter",
            LengthUnit::Millimeter => "Millimeter",
            LengthUnit::Mile => "Mile",
            LengthUnit::Yard => "Yard",
            LengthUnit::Foot => "Foot",
            LengthUnit::Inch => "Inch",
        }
    }
    
    fn to_symbol(&self) -> &'static str {
        match self {
            LengthUnit::Meter => "m",
            LengthUnit::Kilometer => "km",
            LengthUnit::Centimeter => "cm",
            LengthUnit::Millimeter => "mm",
            LengthUnit::Mile => "mi",
            LengthUnit::Yard => "yd",
            LengthUnit::Foot => "ft",
            LengthUnit::Inch => "in",
        }
    }
    
    fn to_meters(&self) -> f64 {
        match self {
            LengthUnit::Meter => 1.0,
            LengthUnit::Kilometer => 1000.0,
            LengthUnit::Centimeter => 0.01,
            LengthUnit::Millimeter => 0.001,
            LengthUnit::Mile => 1609.344,
            LengthUnit::Yard => 0.9144,
            LengthUnit::Foot => 0.3048,
            LengthUnit::Inch => 0.0254,
        }
    }
    
    fn from_meters(meters: f64) -> Vec<(LengthUnit, f64)> {
        vec![
            (LengthUnit::Meter, meters),
            (LengthUnit::Kilometer, meters / 1000.0),
            (LengthUnit::Centimeter, meters * 100.0),
            (LengthUnit::Millimeter, meters * 1000.0),
            (LengthUnit::Mile, meters / 1609.344),
            (LengthUnit::Yard, meters / 0.9144),
            (LengthUnit::Foot, meters / 0.3048),
            (LengthUnit::Inch, meters / 0.0254),
        ]
    }
}

// Weight units
#[derive(Debug, Clone, Copy, PartialEq)]
enum WeightUnit {
    Kilogram,
    Gram,
    Milligram,
    Pound,
    Ounce,
    Ton,
}

impl WeightUnit {
    fn to_string(&self) -> &'static str {
        match self {
            WeightUnit::Kilogram => "Kilogram",
            WeightUnit::Gram => "Gram",
            WeightUnit::Milligram => "Milligram",
            WeightUnit::Pound => "Pound",
            WeightUnit::Ounce => "Ounce",
            WeightUnit::Ton => "Ton",
        }
    }
    
    fn to_symbol(&self) -> &'static str {
        match self {
            WeightUnit::Kilogram => "kg",
            WeightUnit::Gram => "g",
            WeightUnit::Milligram => "mg",
            WeightUnit::Pound => "lb",
            WeightUnit::Ounce => "oz",
            WeightUnit::Ton => "t",
        }
    }
    
    fn to_kilograms(&self) -> f64 {
        match self {
            WeightUnit::Kilogram => 1.0,
            WeightUnit::Gram => 0.001,
            WeightUnit::Milligram => 0.000001,
            WeightUnit::Pound => 0.453592,
            WeightUnit::Ounce => 0.0283495,
            WeightUnit::Ton => 1000.0,
        }
    }
    
    fn from_kilograms(kilograms: f64) -> Vec<(WeightUnit, f64)> {
        vec![
            (WeightUnit::Kilogram, kilograms),
            (WeightUnit::Gram, kilograms * 1000.0),
            (WeightUnit::Milligram, kilograms * 1000000.0),
            (WeightUnit::Pound, kilograms / 0.453592),
            (WeightUnit::Ounce, kilograms / 0.0283495),
            (WeightUnit::Ton, kilograms / 1000.0),
        ]
    }
}

// Temperature units
#[derive(Debug, Clone, Copy, PartialEq)]
enum TemperatureUnit {
    Celsius,
    Fahrenheit,
    Kelvin,
}

impl TemperatureUnit {
    fn to_string(&self) -> &'static str {
        match self {
            TemperatureUnit::Celsius => "Celsius",
            TemperatureUnit::Fahrenheit => "Fahrenheit",
            TemperatureUnit::Kelvin => "Kelvin",
        }
    }
    
    fn to_symbol(&self) -> &'static str {
        match self {
            TemperatureUnit::Celsius => "°C",
            TemperatureUnit::Fahrenheit => "°F",
            TemperatureUnit::Kelvin => "K",
        }
    }
    
    fn to_celsius(&self, value: f64) -> f64 {
        match self {
            TemperatureUnit::Celsius => value,
            TemperatureUnit::Fahrenheit => (value - 32.0) * 5.0 / 9.0,
            TemperatureUnit::Kelvin => value - 273.15,
        }
    }
    
    fn from_celsius(celsius: f64) -> Vec<(TemperatureUnit, f64)> {
        vec![
            (TemperatureUnit::Celsius, celsius),
            (TemperatureUnit::Fahrenheit, celsius * 9.0 / 5.0 + 32.0),
            (TemperatureUnit::Kelvin, celsius + 273.15),
        ]
    }
}

// Volume units
#[derive(Debug, Clone, Copy, PartialEq)]
enum VolumeUnit {
    Liter,
    Milliliter,
    Gallon,
    Quart,
    Pint,
    Cup,
    FluidOunce,
}

impl VolumeUnit {
    fn to_string(&self) -> &'static str {
        match self {
            VolumeUnit::Liter => "Liter",
            VolumeUnit::Milliliter => "Milliliter",
            VolumeUnit::Gallon => "Gallon",
            VolumeUnit::Quart => "Quart",
            VolumeUnit::Pint => "Pint",
            VolumeUnit::Cup => "Cup",
            VolumeUnit::FluidOunce => "Fluid Ounce",
        }
    }
    
    fn to_symbol(&self) -> &'static str {
        match self {
            VolumeUnit::Liter => "L",
            VolumeUnit::Milliliter => "mL",
            VolumeUnit::Gallon => "gal",
            VolumeUnit::Quart => "qt",
            VolumeUnit::Pint => "pt",
            VolumeUnit::Cup => "cup",
            VolumeUnit::FluidOunce => "fl oz",
        }
    }
    
    fn to_liters(&self) -> f64 {
        match self {
            VolumeUnit::Liter => 1.0,
            VolumeUnit::Milliliter => 0.001,
            VolumeUnit::Gallon => 3.78541,
            VolumeUnit::Quart => 0.946353,
            VolumeUnit::Pint => 0.473176,
            VolumeUnit::Cup => 0.236588,
            VolumeUnit::FluidOunce => 0.0295735,
        }
    }
    
    fn from_liters(liters: f64) -> Vec<(VolumeUnit, f64)> {
        vec![
            (VolumeUnit::Liter, liters),
            (VolumeUnit::Milliliter, liters * 1000.0),
            (VolumeUnit::Gallon, liters / 3.78541),
            (VolumeUnit::Quart, liters / 0.946353),
            (VolumeUnit::Pint, liters / 0.473176),
            (VolumeUnit::Cup, liters / 0.236588),
            (VolumeUnit::FluidOunce, liters / 0.0295735),
        ]
    }
}

// Conversion result structure
#[derive(Debug)]
struct ConversionResult {
    original_value: f64,
    original_unit: String,
    original_symbol: String,
    converted_values: Vec<(String, f64, String)>, // (unit_name, value, symbol)
    category: UnitCategory,
}

impl ConversionResult {
    fn new(original_value: f64, original_unit: String, original_symbol: String, 
              category: UnitCategory) -> Self {
        ConversionResult {
            original_value,
            original_unit,
            original_symbol,
            converted_values: Vec::new(),
            category,
        }
    }
    
    fn display(&self) {
        println!("\n{}", "=".repeat(60));
        println!("CONVERSION RESULT");
        println!("{}", "=".repeat(60));
        println!("Original: {:.4} {} ({})", self.original_value, 
                self.original_unit, self.original_symbol);
        println!("Category: {:?}", self.category);
        println!();
        
        println!("Converted Values:");
        println!("{}", "-".repeat(60));
        println!("{:<20} {:>15} {:>10}", "Unit", "Value", "Symbol");
        println!("{}", "-".repeat(60));
        
        for (unit_name, value, symbol) in &self.converted_values {
            println!("{:<20} {:>15.4} {:>10}", unit_name, value, symbol);
        }
        
        println!("{}", "=".repeat(60));
    }
}

// Unit converter structure
struct UnitConverter {
    conversion_history: Vec<ConversionResult>,
}

impl UnitConverter {
    fn new() -> Self {
        UnitConverter {
            conversion_history: Vec::new(),
        }
    }
    
    // Convert length units
    fn convert_length(&self, value: f64, from_unit: LengthUnit) -> ConversionResult {
        println!("\n=== CONVERTING LENGTH ===");
        println!("Converting {:.4} {} to other units", value, from_unit.to_string());
        
        // Convert to base unit (meters)
        let meters = value * from_unit.to_meters();
        
        // Convert from base unit to all other units
        let conversions = LengthUnit::from_meters(meters);
        
        let mut result = ConversionResult::new(
            value,
            from_unit.to_string().to_string(),
            from_unit.to_symbol().to_string(),
            UnitCategory::Length,
        );
        
        for (unit, converted_value) in conversions {
            result.converted_values.push((
                unit.to_string().to_string(),
                converted_value,
                unit.to_symbol().to_string(),
            ));
        }
        
        println!("Conversion completed successfully!");
        println!("Base value in meters: {:.4}", meters);
        println!("========================");
        
        result
    }
    
    // Convert weight units
    fn convert_weight(&self, value: f64, from_unit: WeightUnit) -> ConversionResult {
        println!("\n=== CONVERTING WEIGHT ===");
        println!("Converting {:.4} {} to other units", value, from_unit.to_string());
        
        // Convert to base unit (kilograms)
        let kilograms = value * from_unit.to_kilograms();
        
        // Convert from base unit to all other units
        let conversions = WeightUnit::from_kilograms(kilograms);
        
        let mut result = ConversionResult::new(
            value,
            from_unit.to_string().to_string(),
            from_unit.to_symbol().to_string(),
            UnitCategory::Weight,
        );
        
        for (unit, converted_value) in conversions {
            result.converted_values.push((
                unit.to_string().to_string(),
                converted_value,
                unit.to_symbol().to_string(),
            ));
        }
        
        println!("Conversion completed successfully!");
        println!("Base value in kilograms: {:.4}", kilograms);
        println!("========================");
        
        result
    }
    
    // Convert temperature units
    fn convert_temperature(&self, value: f64, from_unit: TemperatureUnit) -> ConversionResult {
        println!("\n=== CONVERTING TEMPERATURE ===");
        println!("Converting {:.4} {} to other units", value, from_unit.to_string());
        
        // Convert to base unit (celsius)
        let celsius = from_unit.to_celsius(value);
        
        // Convert from base unit to all other units
        let conversions = TemperatureUnit::from_celsius(celsius);
        
        let mut result = ConversionResult::new(
            value,
            from_unit.to_string().to_string(),
            from_unit.to_symbol().to_string(),
            UnitCategory::Temperature,
        );
        
        for (unit, converted_value) in conversions {
            result.converted_values.push((
                unit.to_string().to_string(),
                converted_value,
                unit.to_symbol().to_string(),
            ));
        }
        
        println!("Conversion completed successfully!");
        println!("Base value in celsius: {:.4}", celsius);
        println!("===========================");
        
        result
    }
    
    // Convert volume units
    fn convert_volume(&self, value: f64, from_unit: VolumeUnit) -> ConversionResult {
        println!("\n=== CONVERTING VOLUME ===");
        println!("Converting {:.4} {} to other units", value, from_unit.to_string());
        
        // Convert to base unit (liters)
        let liters = value * from_unit.to_liters();
        
        // Convert from base unit to all other units
        let conversions = VolumeUnit::from_liters(liters);
        
        let mut result = ConversionResult::new(
            value,
            from_unit.to_string().to_string(),
            from_unit.to_symbol().to_string(),
            UnitCategory::Volume,
        );
        
        for (unit, converted_value) in conversions {
            result.converted_values.push((
                unit.to_string().to_string(),
                converted_value,
                unit.to_symbol().to_string(),
            ));
        }
        
        println!("Conversion completed successfully!");
        println!("Base value in liters: {:.4}", liters);
        println!("========================");
        
        result
    }
    
    // Add conversion to history
    fn add_to_history(&mut self, result: ConversionResult) {
        self.conversion_history.push(result);
        println!("Conversion added to history. Total conversions: {}", 
                self.conversion_history.len());
    }
    
    // Display conversion history
    fn display_history(&self) {
        println!("\n{}", "=".repeat(60));
        println!("CONVERSION HISTORY");
        println!("{}", "=".repeat(60));
        
        if self.conversion_history.is_empty() {
            println!("No conversions in history yet.");
            return;
        }
        
        for (i, result) in self.conversion_history.iter().enumerate() {
            println!("Conversion {}: {:.4} {} ({})", 
                    i + 1, result.original_value, result.original_unit);
            println!("  Category: {:?}", result.category);
            println!("  Converted to {} different units", result.converted_values.len());
        }
        
        println!("Total conversions: {}", self.conversion_history.len());
        println!("{}", "=".repeat(60));
    }
    
    // Clear conversion history
    fn clear_history(&mut self) {
        self.conversion_history.clear();
        println!("Conversion history cleared.");
    }
}

// Input validation functions
fn get_valid_number(prompt: &str) -> f64 {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim().parse::<f64>() {
            Ok(num) => {
                if num >= 0.0 {
                    return num;
                } else {
                    println!("Error: Please enter a positive number!");
                }
            }
            Err(_) => {
                println!("Error: Please enter a valid number!");
            }
        }
    }
}

fn get_valid_string(prompt: &str) -> String {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        let trimmed = input.trim();
        if !trimmed.is_empty() {
            return trimmed.to_string();
        }
        
        println!("Error: Input cannot be empty. Please try again.");
    }
}

// Length unit selection
fn get_length_unit() -> LengthUnit {
    println!("\nSelect length unit:");
    println!("1. Meter (m)");
    println!("2. Kilometer (km)");
    println!("3. Centimeter (cm)");
    println!("4. Millimeter (mm)");
    println!("5. Mile (mi)");
    println!("6. Yard (yd)");
    println!("7. Foot (ft)");
    println!("8. Inch (in)");
    
    loop {
        print!("Enter choice (1-8): ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim() {
            "1" => return LengthUnit::Meter,
            "2" => return LengthUnit::Kilometer,
            "3" => return LengthUnit::Centimeter,
            "4" => return LengthUnit::Millimeter,
            "5" => return LengthUnit::Mile,
            "6" => return LengthUnit::Yard,
            "7" => return LengthUnit::Foot,
            "8" => return LengthUnit::Inch,
            _ => println!("Error: Please enter a number between 1 and 8!"),
        }
    }
}

// Weight unit selection
fn get_weight_unit() -> WeightUnit {
    println!("\nSelect weight unit:");
    println!("1. Kilogram (kg)");
    println!("2. Gram (g)");
    println!("3. Milligram (mg)");
    println!("4. Pound (lb)");
    println!("5. Ounce (oz)");
    println!("6. Ton (t)");
    
    loop {
        print!("Enter choice (1-6): ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim() {
            "1" => return WeightUnit::Kilogram,
            "2" => return WeightUnit::Gram,
            "3" => return WeightUnit::Milligram,
            "4" => return WeightUnit::Pound,
            "5" => return WeightUnit::Ounce,
            "6" => return WeightUnit::Ton,
            _ => println!("Error: Please enter a number between 1 and 6!"),
        }
    }
}

// Temperature unit selection
fn get_temperature_unit() -> TemperatureUnit {
    println!("\nSelect temperature unit:");
    println!("1. Celsius (°C)");
    println!("2. Fahrenheit (°F)");
    println!("3. Kelvin (K)");
    
    loop {
        print!("Enter choice (1-3): ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim() {
            "1" => return TemperatureUnit::Celsius,
            "2" => return TemperatureUnit::Fahrenheit,
            "3" => return TemperatureUnit::Kelvin,
            _ => println!("Error: Please enter a number between 1 and 3!"),
        }
    }
}

// Volume unit selection
fn get_volume_unit() -> VolumeUnit {
    println!("\nSelect volume unit:");
    println!("1. Liter (L)");
    println!("2. Milliliter (mL)");
    println!("3. Gallon (gal)");
    println!("4. Quart (qt)");
    println!("5. Pint (pt)");
    println!("6. Cup (cup)");
    println!("7. Fluid Ounce (fl oz)");
    
    loop {
        print!("Enter choice (1-7): ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim() {
            "1" => return VolumeUnit::Liter,
            "2" => return VolumeUnit::Milliliter,
            "3" => return VolumeUnit::Gallon,
            "4" => return VolumeUnit::Quart,
            "5" => return VolumeUnit::Pint,
            "6" => return VolumeUnit::Cup,
            "7" => return VolumeUnit::FluidOunce,
            _ => println!("Error: Please enter a number between 1 and 7!"),
        }
    }
}

// Length conversion menu
fn length_conversion_menu(converter: &mut UnitConverter) {
    println!("\n--- LENGTH CONVERSION ---");
    
    let value = get_valid_number("Enter value to convert: ");
    let from_unit = get_length_unit();
    
    let result = converter.convert_length(value, from_unit);
    result.display();
    
    converter.add_to_history(result);
}

// Weight conversion menu
fn weight_conversion_menu(converter: &mut UnitConverter) {
    println!("\n--- WEIGHT CONVERSION ---");
    
    let value = get_valid_number("Enter value to convert: ");
    let from_unit = get_weight_unit();
    
    let result = converter.convert_weight(value, from_unit);
    result.display();
    
    converter.add_to_history(result);
}

// Temperature conversion menu
fn temperature_conversion_menu(converter: &mut UnitConverter) {
    println!("\n--- TEMPERATURE CONVERSION ---");
    
    let value = get_valid_number("Enter temperature to convert: ");
    let from_unit = get_temperature_unit();
    
    let result = converter.convert_temperature(value, from_unit);
    result.display();
    
    converter.add_to_history(result);
}

// Volume conversion menu
fn volume_conversion_menu(converter: &mut UnitConverter) {
    println!("\n--- VOLUME CONVERSION ---");
    
    let value = get_valid_number("Enter volume to convert: ");
    let from_unit = get_volume_unit();
    
    let result = converter.convert_volume(value, from_unit);
    result.display();
    
    converter.add_to_history(result);
}

// Main menu
fn display_main_menu() {
    println!("\n{}", "=".repeat(60));
    println!("    RUST UNIT CONVERTER");
    println!("{}", "=".repeat(60));
    println!("1. Length conversion");
    println!("2. Weight conversion");
    println!("3. Temperature conversion");
    println!("4. Volume conversion");
    println!("5. View conversion history");
    println!("6. Clear history");
    println!("7. Exit");
    println!("{}", "=".repeat(60));
}

fn main() {
    println!("========================================");
    println!("    RUST UNIT CONVERTER");
    println!("========================================");
    println!("Welcome to unit conversion in Rust!");
    println!("This program demonstrates:");
    println!("- Enum for type safety and organization");
    println!("- Structs and impl blocks for data organization");
    println!("- Pattern matching for conversion logic");
    println!("- Error handling with Result types");
    println!("- Mathematical operations and precision");
    println!("- User input validation and sanitization");
    println!("- Human-like code with detailed comments!");
    println!("========================================");
    
    let mut converter = UnitConverter::new();
    
    loop {
        display_main_menu();
        
        print!("Enter your choice (1-7): ");
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim() {
            "1" => length_conversion_menu(&mut converter),
            "2" => weight_conversion_menu(&mut converter),
            "3" => temperature_conversion_menu(&mut converter),
            "4" => volume_conversion_menu(&mut converter),
            "5" => converter.display_history(),
            "6" => converter.clear_history(),
            "7" => {
                println!("\nThank you for using Rust Unit Converter!");
                println!("You've learned:");
                println!("- Enum for type safety and organization");
                println!("- Structs and impl blocks for data organization");
                println!("- Pattern matching for conversion logic");
                println!("- Error handling with Result types");
                println!("- Mathematical operations and precision");
                println!("- User input validation and sanitization");
                println!("- Human-readable, maintainable code!");
                break;
            }
            _ => println!("Error: Invalid choice! Please enter 1-7."),
        }
        
        // Add a small pause for better user experience
        if input.trim() != "7" {
            println!("\nPress Enter to continue...");
            let mut _pause = String::new();
            io::stdin().read_line(&mut _pause).unwrap();
        }
    }
}
