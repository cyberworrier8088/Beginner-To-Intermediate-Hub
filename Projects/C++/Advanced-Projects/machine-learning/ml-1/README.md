# C++ Neural Network - Level 8

## Overview
A comprehensive neural network implementation demonstrating advanced C++ programming, machine learning algorithms, and artificial intelligence concepts.

## Features
- **Neural Network Architecture**: Multi-layer perceptron with customizable layers
- **Activation Functions**: Sigmoid, Tanh, ReLU, Leaky ReLU
- **Forward Propagation**: Matrix operations and activation function application
- **Backpropagation**: Gradient descent and weight optimization
- **Training Algorithms**: Mean squared error loss, convergence detection
- **Matrix Operations**: Custom matrix class with linear algebra operations
- **Dataset Support**: XOR problem and Iris classification
- **Model Persistence**: Save and load trained networks

## Learning Objectives
- Neural network architecture and layer design
- Forward propagation and activation functions
- Backpropagation and gradient descent algorithms
- Matrix operations and linear algebra implementation
- Training optimization and convergence criteria
- Machine learning model persistence
- Human-like code with detailed explanations

## Prerequisites
- C++17 compatible compiler (g++, clang++, or MSVC)
- Basic understanding of linear algebra and calculus
- Familiarity with machine learning concepts
- Mathematical background in neural networks

## Compilation & Running

### Linux/macOS
```bash
# Compile
g++ -std=c++17 -O3 -o neural_network neural_network.cpp

# Run
./neural_network

# Run with specific dataset
./neural_network
```

### Windows (with g++)
```bash
# Compile
g++ -std=c++17 -O3 -o neural_network.exe neural_network.cpp

# Run
neural_network.exe
```

### Windows (Visual Studio)
1. Open Visual Studio
2. Create new C++ project
3. Add neural_network.cpp to project
4. Configure project properties:
   - C++ Language Standard: ISO C++17
   - Optimization: /O2 or /O3
5. Build and run

## Usage Examples

### Interactive Mode
```bash
# Start interactive mode
./neural_network

=== NEURAL NETWORK MENU ===
1. Create XOR Network
2. Create Iris Classification Network
3. Load Network from File
4. Train Network
5. Test Network
6. Save Network
7. Display Architecture
8. Make Prediction
9. Exit

Choice: 1

=== CREATING XOR NETWORK ===
Creating Neural Network
Learning rate: 0.1
Epochs: 10000
Loss threshold: 0.001

=== ADDING LAYER ===
Input size: 2
Output size: 4
Creating neural layer: 2 -> 4
Layer created with SIGMOID activation
Layer added. Total layers: 1
==================

=== ADDING LAYER ===
Input size: 4
Output size: 1
Creating neural layer: 4 -> 1
Layer created with SIGMOID activation
Layer added. Total layers: 2
==================

=== GENERATING XOR DATASET ===
Input: [0, 0] -> Target: 0
Input: [0, 1] -> Target: 1
Input: [1, 0] -> Target: 1
Input: [1, 1] -> Target: 0
Generated 4 training samples
=============================

XOR Network created successfully!
=============================
```

### Training Example
```bash
Choice: 4

=== TRAINING NEURAL NETWORK ===
Training samples: 4
Epochs: 10000
Learning rate: 0.1

Epoch 1/10000 - Loss: 0.562500
Epoch 100/10000 - Loss: 0.456789
Epoch 200/10000 - Loss: 0.345678
...
Epoch 1000/10000 - Loss: 0.012345
Epoch 2000/10000 - Loss: 0.006789
...
Convergence reached at epoch 3456
Final loss: 0.000987
Training completed!
========================
```

### Testing Example
```bash
Choice: 5

=== TESTING NEURAL NETWORK ===
Test samples: 4

=== PREDICTION ===
Input shape: 1x2
Layer 1:
=== FORWARD PROPAGATION ===
Input shape: 1x2
Multiplying matrices: 1x2 * 2x4
Matrix multiplication completed
Forward propagation completed
Layer Output (1x4):
  [  0.6234,  0.7891,  0.4567,  0.2345]

Layer 2:
=== FORWARD PROPAGATION ===
Input shape: 1x4
Multiplying matrices: 1x4 * 4x1
Matrix multiplication completed
Forward propagation completed
Layer Output (1x1):
  [  0.0123]

Prediction completed
==================

Test Results:
Average Loss: 0.000987
Accuracy: 100.00%
Correct Predictions: 4/4
============================
```

## Code Structure
```cpp
class Matrix {
private:
    vector<vector<double>> data;
    int rows;
    int cols;
    
public:
    // Core matrix operations
    Matrix multiply(const Matrix& other) const;
    Matrix elementWiseMultiply(const Matrix& other) const;
    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    Matrix transpose() const;
    
    // Neural network operations
    Matrix applyFunction(ActivationFunction func) const;
    Matrix applyDerivative(ActivationFunction func) const;
    Matrix scale(double scalar) const;
    
    // Utility methods
    void randomize(double min_val = -1.0, double max_val = 1.0);
    void display(const string& name = "Matrix") const;
};

class Layer {
private:
    Matrix weights;
    Matrix biases;
    Matrix inputs;
    Matrix outputs;
    Matrix activation_derivatives;
    ActivationFunction activation;
    
public:
    // Forward and backward propagation
    Matrix forward(const Matrix& input_data);
    Matrix backward(const Matrix& output_gradient, double learning_rate);
    
    // Utility methods
    Matrix getOutputs() const;
    Matrix getWeights() const;
};

class NeuralNetwork {
private:
    vector<Layer> layers;
    double learning_rate;
    int epochs;
    double loss_threshold;
    
public:
    // Core network operations
    void addLayer(int input_size, int output_size, ActivationFunction activation);
    Matrix predict(const Matrix& input);
    void train(const vector<Matrix>& training_inputs, const vector<Matrix>& training_targets);
    double test(const vector<Matrix>& test_inputs, const vector<Matrix>& test_targets);
    
    // Utility methods
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
    void displayArchitecture() const;
};
```

## Key Concepts Demonstrated
1. **Neural Network Architecture**: Multi-layer perceptron design
2. **Matrix Operations**: Custom implementation of linear algebra
3. **Forward Propagation**: Activation function application
4. **Backpropagation**: Gradient calculation and weight updates
5. **Training Algorithms**: Loss calculation and optimization
6. **Activation Functions**: Sigmoid, Tanh, ReLU, Leaky ReLU
7. **Model Persistence**: Save and load trained networks
8. **Human-Like Code**: Detailed comments and user feedback

## Mathematical Foundations

### Forward Propagation
```
Z = X · W + b
A = f(Z)
```
Where:
- X = Input matrix
- W = Weight matrix
- b = Bias vector
- f = Activation function
- Z = Weighted sum
- A = Activated output

### Backpropagation
```
Loss = MSE(Y, A)
Gradient = 2 * (A - Y) / n
Weight Update: W = W - learning_rate * gradient
```

### Activation Functions
- **Sigmoid**: f(x) = 1 / (1 + e^(-x))
- **Tanh**: f(x) = tanh(x)
- **ReLU**: f(x) = max(0, x)
- **Leaky ReLU**: f(x) = max(0.1x, x)

## Datasets Included

### XOR Problem
- **Input**: 2 binary features
- **Output**: 1 binary target
- **Samples**: 4 training examples
- **Purpose**: Demonstrate non-linear classification

### Iris Classification
- **Input**: 4 numeric features (sepal/petal length/width)
- **Output**: 3 one-hot encoded classes
- **Samples**: 6 simplified examples
- **Purpose**: Multi-class classification

## Performance Considerations
- **Time Complexity**: O(n²) for matrix multiplication
- **Space Complexity**: O(n²) for weight storage
- **Training Speed**: Depends on epochs and learning rate
- **Memory Usage**: Efficient matrix operations
- **Optimization**: Vectorized operations where possible

## Troubleshooting

### Compilation Errors
- **"cmath was not declared"**: Add `#include <cmath>`
- **"random was not declared"**: Add `#include <random>`
- **"algorithm was not declared"**: Add `#include <algorithm>`
- **"chrono was not declared"**: Add `#include <chrono>`

### Runtime Errors
- **Matrix dimension mismatch**: Check matrix multiplication compatibility
- **Division by zero**: Ensure proper loss calculation
- **Memory issues**: Monitor with system tools
- **Convergence problems**: Adjust learning rate and epochs

### Training Issues
- **No convergence**: Increase epochs or adjust learning rate
- **Overfitting**: Add regularization or reduce network size
- **Local minima**: Try different weight initialization
- **Gradient vanishing**: Use appropriate activation functions

## Extensions and Enhancements
Try these challenges to improve the neural network:
1. **More Activation Functions**: Add Swish, Mish, GELU
2. **Regularization**: Implement L1/L2 regularization and dropout
3. **Optimization Algorithms**: Add Adam, RMSprop, Adagrad
4. **Convolutional Layers**: Add CNN support for image processing
5. **Recurrent Layers**: Add RNN/LSTM for sequence data
6. **Batch Processing**: Implement mini-batch training
7. **Early Stopping**: Add validation-based early stopping
8. **Learning Rate Scheduling**: Implement adaptive learning rates
9. **GPU Acceleration**: Add CUDA/OpenCL support
10. **Visualization**: Add training progress graphs

## Real-World Applications
- **Image Classification**: Computer vision tasks
- **Natural Language Processing**: Text analysis and generation
- **Time Series Prediction**: Stock market, weather forecasting
- **Recommendation Systems**: Product recommendations
- **Anomaly Detection**: Fraud detection, system monitoring
- **Game AI**: Game playing agents and NPCs

## Next Steps
After mastering this neural network, try:
- Level 9: Computer Vision (OpenCV, image processing)
- Level 10: Advanced AI (transformers, GANs, reinforcement learning)
- Level 11: Cloud ML (AWS SageMaker, Google AI Platform)
- Level 12: Production ML (MLOps, model deployment)

## About This Project
This neural network implementation demonstrates advanced C++ programming through practical machine learning. The code includes detailed explanations of mathematical concepts, algorithmic implementations, and optimization techniques, making it perfect for learning AI and deep learning fundamentals.

Happy coding and happy learning!
