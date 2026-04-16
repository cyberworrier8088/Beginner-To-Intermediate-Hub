"""
Unit Testing - Level 10: Professional Testing Practices
This separates hobbyists from professionals!
Learn pytest, test-driven development, and code quality.
"""

import pytest
import calculator

class TestCalculator:
    """Test suite for calculator functions"""
    
    def test_add_positive_numbers(self):
        """Test adding positive numbers"""
        result = calculator.add(5, 3)
        assert result == 8, f"Expected 8, got {result}"
    
    def test_add_negative_numbers(self):
        """Test adding negative numbers"""
        result = calculator.add(-5, -3)
        assert result == -8, f"Expected -8, got {result}"
    
    def test_add_mixed_numbers(self):
        """Test adding positive and negative numbers"""
        result = calculator.add(10, -4)
        assert result == 6, f"Expected 6, got {result}"
    
    def test_add_zero(self):
        """Test adding zero"""
        result = calculator.add(5, 0)
        assert result == 5, f"Expected 5, got {result}"
    
    def test_subtract_positive_numbers(self):
        """Test subtracting positive numbers"""
        result = calculator.subtract(10, 3)
        assert result == 7, f"Expected 7, got {result}"
    
    def test_subtract_negative_result(self):
        """Test subtraction resulting in negative"""
        result = calculator.subtract(3, 10)
        assert result == -7, f"Expected -7, got {result}"
    
    def test_multiply_positive_numbers(self):
        """Test multiplying positive numbers"""
        result = calculator.multiply(4, 5)
        assert result == 20, f"Expected 20, got {result}"
    
    def test_multiply_by_zero(self):
        """Test multiplying by zero"""
        result = calculator.multiply(5, 0)
        assert result == 0, f"Expected 0, got {result}"
    
    def test_multiply_negative_numbers(self):
        """Test multiplying negative numbers"""
        result = calculator.multiply(-3, -4)
        assert result == 12, f"Expected 12, got {result}"
    
    def test_divide_positive_numbers(self):
        """Test dividing positive numbers"""
        result = calculator.divide(15, 3)
        assert result == 5, f"Expected 5, got {result}"
    
    def test_divide_by_zero(self):
        """Test division by zero should raise exception"""
        with pytest.raises(ValueError, match="Cannot divide by zero"):
            calculator.divide(5, 0)
    
    def test_divide_negative_numbers(self):
        """Test dividing negative numbers"""
        result = calculator.divide(-10, 2)
        assert result == -5, f"Expected -5, got {result}"
    
    def test_divide_with_remainder(self):
        """Test division with remainder"""
        result = calculator.divide(7, 2)
        assert result == 3.5, f"Expected 3.5, got {result}"
    
    @pytest.mark.parametrize("a,b,expected", [
        (1, 1, 2),
        (0, 0, 0),
        (-1, 1, 0),
        (100, 200, 300),
        (-50, -25, -75),
    ])
    def test_add_parametrized(self, a, b, expected):
        """Test add function with multiple inputs"""
        result = calculator.add(a, b)
        assert result == expected, f"Expected {expected}, got {result}"
    
    def test_calculator_integration(self):
        """Test calculator with complex operations"""
        # (10 + 5) * 2 / 3 = 10
        step1 = calculator.add(10, 5)  # 15
        step2 = calculator.multiply(step1, 2)  # 30
        result = calculator.divide(step2, 3)  # 10
        
        assert result == 10, f"Expected 10, got {result}"

class TestEdgeCases:
    """Test edge cases and boundary conditions"""
    
    def test_large_numbers(self):
        """Test with very large numbers"""
        result = calculator.add(1000000, 2000000)
        assert result == 3000000, f"Expected 3000000, got {result}"
    
    def test_decimal_numbers(self):
        """Test with decimal numbers"""
        result = calculator.add(1.5, 2.7)
        assert abs(result - 4.2) < 0.0001, f"Expected 4.2, got {result}"
    
    def test_very_small_numbers(self):
        """Test with very small numbers"""
        result = calculator.multiply(0.001, 0.002)
        assert abs(result - 0.000002) < 0.0000001, f"Expected 0.000002, got {result}"

if __name__ == "__main__":
    print("Run tests with: pytest test_calculator.py -v")
    print("This demonstrates professional testing practices!")
