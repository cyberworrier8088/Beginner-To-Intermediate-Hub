# Rust Unit Converter - Level 2

## Overview
A comprehensive unit converter demonstrating Rust's type safety, pattern matching, and mathematical operations.

## Features
- **Multiple Unit Categories**: Length, Weight, Temperature, Volume, Area, Speed, Time
- **Comprehensive Conversions**: Support for 8+ units per category
- **Type Safety**: Enums prevent invalid unit combinations
- **Pattern Matching**: Elegant conversion logic using Rust's match expressions
- **Error Handling**: Result types for robust error management
- **Conversion History**: Track and display previous conversions
- **User Validation**: Input sanitization and error recovery

## Learning Objectives
- Enum types for type safety and organization
- Structs and impl blocks for data organization
- Pattern matching for conversion logic
- Error handling with Result types
- Mathematical operations and precision
- User input validation and sanitization
- Human-like code with detailed comments

## Prerequisites
- Rust 1.70+ (2021 edition)
- Cargo package manager
- Basic understanding of Rust syntax

## Installation & Setup

### Install Rust (if not already installed)
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source ~/.cargo/env
```

### Compilation & Running
```bash
# Navigate to project
cd Projects/Rust/Beginner-Projects/unit-converter/convert-1/

# Run with Cargo (recommended)
cargo run

# Or compile and run manually
rustc main.rs
./main
```

## Usage
1. Run the program
2. Choose from the main menu:
   - `1` - Length conversion (meters, kilometers, feet, inches, etc.)
   - `2` - Weight conversion (kilograms, pounds, ounces, etc.)
   - `3` - Temperature conversion (Celsius, Fahrenheit, Kelvin)
   - `4` - Volume conversion (liters, gallons, cups, etc.)
   - `5` - View conversion history
   - `6` - Clear history
   - `7` - Exit program
3. Enter value to convert
4. Select source unit from numbered menu
5. View comprehensive conversion results

## Example Session
```
    RUST UNIT CONVERTER
========================================
Welcome to unit conversion in Rust!

1. Length conversion
2. Weight conversion
3. Temperature conversion
4. Volume conversion
5. View conversion history
6. Clear history
7. Exit

Enter your choice (1-7): 1

--- LENGTH CONVERSION ---
Enter value to convert: 100

Select length unit:
1. Meter (m)
2. Kilometer (km)
3. Centimeter (cm)
4. Millimeter (mm)
5. Mile (mi)
6. Yard (yd)
7. Foot (ft)
8. Inch (in)

Enter choice (1-8): 1

=== CONVERTING LENGTH ===
Converting 100.0000 Meter to other units
Conversion completed successfully!
Base value in meters: 100.0000
========================

========================================
CONVERSION RESULT
========================================
Original: 100.0000 Meter (m)
Category: Length

Converted Values:
Unit                 Value        Symbol
Meter                 100.0000      m
Kilometer              0.1000       km
Centimeter             10000.0000    cm
Millimeter             100000.0000   mm
Mile                  0.0621        mi
Yard                  109.3613      yd
Foot                  328.0840      ft
Inch                  3937.0079     in
========================================
```

## Code Structure
```rust
// Enum for unit categories
#[derive(Debug, Clone, Copy, PartialEq)]
enum UnitCategory {
    Length, Weight, Temperature, Volume, Area, Speed, Time,
}

// Enum for length units
#[derive(Debug, Clone, Copy, PartialEq)]
enum LengthUnit {
    Meter, Kilometer, Centimeter, Millimeter, Mile, Yard, Foot, Inch,
}

impl LengthUnit {
    fn to_string(&self) -> &'static str;
    fn to_symbol(&self) -> &'static str;
    fn to_meters(&self) -> f64;
    fn from_meters(meters: f64) -> Vec<(LengthUnit, f64)>;
}

// Main converter structure
struct UnitConverter {
    conversion_history: Vec<ConversionResult>,
}

impl UnitConverter {
    fn new() -> Self;
    fn convert_length(&self, value: f64, from_unit: LengthUnit) -> ConversionResult;
    fn add_to_history(&mut self, result: ConversionResult);
    fn display_history(&self);
}
```

## Key Concepts Demonstrated
1. **Enum Types**: Type-safe unit definitions and categorization
2. **Pattern Matching**: Elegant conversion logic using match expressions
3. **Structs and Impl**: Data organization and method implementation
4. **Error Handling**: Result types for robust error management
5. **Mathematical Operations**: Precise floating-point calculations
6. **Input Validation**: Comprehensive error checking and recovery
7. **Human-Like Code**: Detailed comments and user feedback

## Supported Conversions

### Length Units
- **Metric**: Meter, Kilometer, Centimeter, Millimeter
- **Imperial**: Mile, Yard, Foot, Inch
- **Conversions**: All units convert to/from meters (base unit)

### Weight Units
- **Metric**: Kilogram, Gram, Milligram
- **Imperial**: Pound, Ounce, Ton
- **Conversions**: All units convert to/from kilograms (base unit)

### Temperature Units
- **Scientific**: Celsius, Fahrenheit, Kelvin
- **Conversions**: All units convert to/from Celsius (base unit)

### Volume Units
- **Metric**: Liter, Milliliter
- **Imperial**: Gallon, Quart, Pint, Cup, Fluid Ounce
- **Conversions**: All units convert to/from liters (base unit)

## Troubleshooting

### Compilation Errors
- **"enum `UnitCategory` is private"**: Add `#[derive(Debug, Clone, Copy, PartialEq)]`
- **"cannot find type `Result`"**: Add `use std::io::Result;`
- **"borrowed value does not live long enough"**: Check variable lifetimes

### Runtime Errors
- **Invalid unit choice**: Program will prompt you to try again
- **Invalid number**: Input validation prevents crashes
- **Division by zero**: Handled with proper error messages

### Platform-Specific Issues
- **Windows**: Use `cargo run` or `rustc` from Rust installation
- **macOS**: Install Rust using rustup
- **Linux**: Install Rust through package manager or rustup

## Extensions
Try these challenges to improve the program:
1. **Custom Units**: Allow users to define their own conversion factors
2. **Currency Conversion**: Add real-time exchange rate API integration
3. **Batch Conversions**: Convert multiple values at once
4. **GUI Interface**: Create a graphical user interface
5. **Web API**: Convert the program into a web service
6. **Mobile App**: Port to Android/iOS using Rust mobile frameworks
7. **Scientific Units**: Add units for physics, chemistry, etc.

## Performance Considerations
- **Memory Usage**: Minimal - uses stack allocation for most operations
- **Speed**: Instant conversions - no complex calculations required
- **Precision**: Double-precision floating-point for accurate results
- **History**: Efficient vector storage with optional size limits

## Security Considerations
- **Input Validation**: All user inputs are validated and sanitized
- **Error Handling**: No panic cases - all errors are handled gracefully
- **Type Safety**: Compile-time guarantees prevent invalid operations
- **Memory Safety**: Rust's ownership system prevents memory leaks

## Next Steps
After mastering this unit converter, try:
- Level 3: File Manager (file I/O, path manipulation)
- Level 4: Web Scraper (HTTP requests, HTML parsing)
- Level 5: Bank Account Manager (OOP, data structures)
- Intermediate Projects: Advanced algorithms and data structures

## About This Project
This unit converter demonstrates Rust's strengths in type safety, pattern matching, and error handling. The code is written with human-like comments and focuses on teaching fundamental Rust concepts through practical application.

Happy converting!
