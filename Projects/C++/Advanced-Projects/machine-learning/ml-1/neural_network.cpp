/*
 * Neural Network in C++ - Level 8: Machine Learning & AI
 * 
 * Welcome to artificial intelligence in C++! This is where math meets intelligence.
 * Learn neural networks, backpropagation, and machine learning algorithms.
 * 
 * Key concepts you'll learn:
 * - Neural network architecture and layers
 * - Forward propagation and activation functions
 * - Backpropagation and gradient descent
 * - Matrix operations and linear algebra
 * - Training and optimization algorithms
 * - Human-like code with detailed explanations!
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;

// Activation functions
enum class ActivationFunction {
    SIGMOID,
    TANH,
    RELU,
    LEAKY_RELU
};

// Matrix class for neural network operations
class Matrix {
private:
    vector<vector<double>> data;
    int rows;
    int cols;
    
public:
    // Constructor
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(rows, vector<double>(cols, 0.0));
        cout << "Created matrix: " << rows << "x" << cols << endl;
    }
    
    // Constructor with initial data
    Matrix(const vector<vector<double>>& input_data) : data(input_data) {
        rows = data.size();
        cols = rows > 0 ? data[0].size() : 0;
        cout << "Created matrix from data: " << rows << "x" << cols << endl;
    }
    
    // Get dimensions
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    
    // Access elements
    double& operator()(int i, int j) { return data[i][j]; }
    const double& operator()(int i, int j) const { return data[i][j]; }
    
    // Get row
    vector<double> getRow(int i) const {
        return data[i];
    }
    
    // Get column
    vector<double> getColumn(int j) const {
        vector<double> column(rows);
        for (int i = 0; i < rows; i++) {
            column[i] = data[i][j];
        }
        return column;
    }
    
    // Matrix multiplication
    Matrix multiply(const Matrix& other) const {
        cout << "Multiplying matrices: " << rows << "x" << cols 
             << " * " << other.rows << "x" << other.cols << endl;
        
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions don't match for multiplication");
        }
        
        Matrix result(rows, other.cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                double sum = 0.0;
                for (int k = 0; k < cols; k++) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        
        cout << "Matrix multiplication completed" << endl;
        return result;
    }
    
    // Element-wise multiplication
    Matrix elementWiseMultiply(const Matrix& other) const {
        cout << "Element-wise multiplication" << endl;
        
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions don't match for element-wise multiplication");
        }
        
        Matrix result(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * other.data[i][j];
            }
        }
        
        return result;
    }
    
    // Matrix addition
    Matrix add(const Matrix& other) const {
        cout << "Adding matrices" << endl;
        
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions don't match for addition");
        }
        
        Matrix result(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        
        return result;
    }
    
    // Matrix subtraction
    Matrix subtract(const Matrix& other) const {
        cout << "Subtracting matrices" << endl;
        
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions don't match for subtraction");
        }
        
        Matrix result(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        
        return result;
    }
    
    // Transpose matrix
    Matrix transpose() const {
        cout << "Transposing matrix: " << rows << "x" << cols << " -> " << cols << "x" << rows << endl;
        
        Matrix result(cols, rows);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        
        return result;
    }
    
    // Apply activation function to all elements
    Matrix applyFunction(ActivationFunction func) const {
        cout << "Applying activation function" << endl;
        
        Matrix result(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = activate(data[i][j], func);
            }
        }
        
        return result;
    }
    
    // Apply derivative of activation function
    Matrix applyDerivative(ActivationFunction func) const {
        cout << "Applying activation function derivative" << endl;
        
        Matrix result(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = activateDerivative(data[i][j], func);
            }
        }
        
        return result;
    }
    
    // Scale matrix by scalar
    Matrix scale(double scalar) const {
        cout << "Scaling matrix by " << scalar << endl;
        
        Matrix result(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        
        return result;
    }
    
    // Random initialization
    void randomize(double min_val = -1.0, double max_val = 1.0) {
        cout << "Randomizing matrix with range [" << min_val << ", " << max_val << "]" << endl;
        
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(min_val, max_val);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = dis(gen);
            }
        }
    }
    
    // Display matrix
    void display(const string& name = "Matrix") const {
        cout << name << " (" << rows << "x" << cols << "):" << endl;
        for (int i = 0; i < rows; i++) {
            cout << "  [";
            for (int j = 0; j < cols; j++) {
                cout << setw(8) << fixed << setprecision(4) << data[i][j];
                if (j < cols - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
        cout << endl;
    }
    
    // Save matrix to file
    void saveToFile(ofstream& file) const {
        file << rows << " " << cols << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file << data[i][j];
                if (j < cols - 1) file << " ";
            }
            file << endl;
        }
    }
    
    // Load matrix from file
    void loadFromFile(ifstream& file) {
        file >> rows >> cols;
        data.resize(rows, vector<double>(cols));
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file >> data[i][j];
            }
        }
    }
    
private:
    // Activation function implementation
    double activate(double x, ActivationFunction func) const {
        switch (func) {
            case ActivationFunction::SIGMOID:
                return 1.0 / (1.0 + exp(-x));
            case ActivationFunction::TANH:
                return tanh(x);
            case ActivationFunction::RELU:
                return max(0.0, x);
            case ActivationFunction::LEAKY_RELU:
                return max(0.1 * x, x);
            default:
                return x;
        }
    }
    
    // Derivative of activation function
    double activateDerivative(double x, ActivationFunction func) const {
        switch (func) {
            case ActivationFunction::SIGMOID: {
                double sig = 1.0 / (1.0 + exp(-x));
                return sig * (1.0 - sig);
            }
            case ActivationFunction::TANH: {
                double t = tanh(x);
                return 1.0 - t * t;
            }
            case ActivationFunction::RELU:
                return x > 0 ? 1.0 : 0.0;
            case ActivationFunction::LEAKY_RELU:
                return x > 0 ? 1.0 : 0.1;
            default:
                return 1.0;
        }
    }
};

// Neural Network Layer
class Layer {
private:
    Matrix weights;
    Matrix biases;
    Matrix inputs;
    Matrix outputs;
    Matrix activation_derivatives;
    ActivationFunction activation;
    
public:
    // Constructor
    Layer(int input_size, int output_size, ActivationFunction act = ActivationFunction::SIGMOID)
        : weights(input_size, output_size), biases(1, output_size), activation(act) {
        
        cout << "Creating neural layer: " << input_size << " -> " << output_size << endl;
        
        // Initialize weights and biases
        weights.randomize(-0.5, 0.5);
        biases.randomize(-0.5, 0.5);
        
        cout << "Layer created with " << activation << " activation" << endl;
    }
    
    // Forward propagation
    Matrix forward(const Matrix& input_data) {
        cout << "\n=== FORWARD PROPAGATION ===" << endl;
        inputs = input_data;
        
        // Calculate weighted sum: inputs * weights + biases
        Matrix weighted_sum = inputs.multiply(weights);
        Matrix biased_sum = weighted_sum.add(biases);
        
        // Apply activation function
        outputs = biased_sum.applyFunction(activation);
        activation_derivatives = biased_sum.applyDerivative(activation);
        
        cout << "Forward propagation completed" << endl;
        outputs.display("Layer Output");
        
        return outputs;
    }
    
    // Backward propagation
    Matrix backward(const Matrix& output_gradient, double learning_rate) {
        cout << "\n=== BACKWARD PROPAGATION ===" << endl;
        
        // Calculate gradient for this layer
        Matrix layer_gradient = output_gradient.elementWiseMultiply(activation_derivatives);
        
        // Calculate gradients for weights and biases
        Matrix weight_gradient = inputs.transpose().multiply(layer_gradient);
        Matrix bias_gradient = layer_gradient;
        
        // Calculate gradient for previous layer
        Matrix input_gradient = layer_gradient.multiply(weights.transpose());
        
        // Update weights and biases
        weights = weights.subtract(weight_gradient.scale(learning_rate));
        biases = biases.subtract(bias_gradient.scale(learning_rate));
        
        cout << "Backward propagation completed" << endl;
        cout << "Weights updated, biases updated" << endl;
        
        return input_gradient;
    }
    
    // Get outputs
    Matrix getOutputs() const { return outputs; }
    
    // Get weights
    Matrix getWeights() const { return weights; }
    
    // Save layer to file
    void saveToFile(ofstream& file) const {
        file << static_cast<int>(activation) << endl;
        weights.saveToFile(file);
        biases.saveToFile(file);
    }
    
    // Load layer from file
    void loadFromFile(ifstream& file) {
        int activation_int;
        file >> activation_int;
        activation = static_cast<ActivationFunction>(activation_int);
        
        weights.loadFromFile(file);
        biases.loadFromFile(file);
    }
};

// Neural Network class
class NeuralNetwork {
private:
    vector<Layer> layers;
    double learning_rate;
    int epochs;
    double loss_threshold;
    
public:
    // Constructor
    NeuralNetwork(double lr = 0.01, int ep = 1000, double threshold = 0.001)
        : learning_rate(lr), epochs(ep), loss_threshold(threshold) {
        
        cout << "Creating Neural Network" << endl;
        cout << "Learning rate: " << learning_rate << endl;
        cout << "Epochs: " << epochs << endl;
        cout << "Loss threshold: " << loss_threshold << endl;
    }
    
    // Add layer to network
    void addLayer(int input_size, int output_size, ActivationFunction activation = ActivationFunction::SIGMOID) {
        cout << "\n=== ADDING LAYER ===" << endl;
        cout << "Input size: " << input_size << endl;
        cout << "Output size: " << output_size << endl;
        
        layers.emplace_back(input_size, output_size, activation);
        
        cout << "Layer added. Total layers: " << layers.size() << endl;
        cout << "==================" << endl;
    }
    
    // Forward propagation through all layers
    Matrix predict(const Matrix& input) {
        cout << "\n=== PREDICTION ===" << endl;
        cout << "Input shape: " << input.getRows() << "x" << input.getCols() << endl;
        
        Matrix current_input = input;
        
        for (size_t i = 0; i < layers.size(); i++) {
            cout << "Layer " << (i + 1) << ":" << endl;
            current_input = layers[i].forward(current_input);
        }
        
        cout << "Prediction completed" << endl;
        cout << "==================" << endl;
        
        return current_input;
    }
    
    // Train the network
    void train(const vector<Matrix>& training_inputs, const vector<Matrix>& training_targets) {
        cout << "\n=== TRAINING NEURAL NETWORK ===" << endl;
        cout << "Training samples: " << training_inputs.size() << endl;
        cout << "Epochs: " << epochs << endl;
        cout << "Learning rate: " << learning_rate << endl;
        
        for (int epoch = 1; epoch <= epochs; epoch++) {
            double total_loss = 0.0;
            
            for (size_t sample = 0; sample < training_inputs.size(); sample++) {
                // Forward propagation
                Matrix output = predict(training_inputs[sample]);
                
                // Calculate loss (mean squared error)
                Matrix target = training_targets[sample];
                Matrix error = output.subtract(target);
                double sample_loss = calculateLoss(error);
                total_loss += sample_loss;
                
                // Backward propagation
                Matrix gradient = error.scale(2.0 / output.getRows());
                
                for (int i = layers.size() - 1; i >= 0; i--) {
                    gradient = layers[i].backward(gradient, learning_rate);
                }
            }
            
            double average_loss = total_loss / training_inputs.size();
            
            // Print progress
            if (epoch % 100 == 0 || epoch == 1) {
                cout << "Epoch " << epoch << "/" << epochs 
                     << " - Loss: " << fixed << setprecision(6) << average_loss << endl;
            }
            
            // Check for convergence
            if (average_loss < loss_threshold) {
                cout << "Convergence reached at epoch " << epoch << endl;
                cout << "Final loss: " << average_loss << endl;
                break;
            }
        }
        
        cout << "Training completed!" << endl;
        cout << "========================" << endl;
    }
    
    // Test the network
    double test(const vector<Matrix>& test_inputs, const vector<Matrix>& test_targets) {
        cout << "\n=== TESTING NEURAL NETWORK ===" << endl;
        cout << "Test samples: " << test_inputs.size() << endl;
        
        double total_loss = 0.0;
        int correct_predictions = 0;
        
        for (size_t sample = 0; sample < test_inputs.size(); sample++) {
            Matrix output = predict(test_inputs[sample]);
            Matrix target = test_targets[sample];
            
            // Calculate loss
            Matrix error = output.subtract(target);
            double sample_loss = calculateLoss(error);
            total_loss += sample_loss;
            
            // Check if prediction is correct (for classification)
            if (isCorrectPrediction(output, target)) {
                correct_predictions++;
            }
        }
        
        double average_loss = total_loss / test_inputs.size();
        double accuracy = (double)correct_predictions / test_inputs.size() * 100.0;
        
        cout << "Test Results:" << endl;
        cout << "Average Loss: " << fixed << setprecision(6) << average_loss << endl;
        cout << "Accuracy: " << fixed << setprecision(2) << accuracy << "%" << endl;
        cout << "Correct Predictions: " << correct_predictions << "/" << test_inputs.size() << endl;
        cout << "============================" << endl;
        
        return accuracy;
    }
    
    // Save network to file
    void saveToFile(const string& filename) const {
        cout << "\n=== SAVING NETWORK ===" << endl;
        cout << "Saving to: " << filename << endl;
        
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file for writing!" << endl;
            return;
        }
        
        file << learning_rate << " " << epochs << " " << loss_threshold << endl;
        file << layers.size() << endl;
        
        for (const auto& layer : layers) {
            layer.saveToFile(file);
        }
        
        file.close();
        cout << "Network saved successfully!" << endl;
        cout << "====================" << endl;
    }
    
    // Load network from file
    void loadFromFile(const string& filename) {
        cout << "\n=== LOADING NETWORK ===" << endl;
        cout << "Loading from: " << filename << endl;
        
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file for reading!" << endl;
            return;
        }
        
        file >> learning_rate >> epochs >> loss_threshold;
        
        int num_layers;
        file >> num_layers;
        
        layers.clear();
        for (int i = 0; i < num_layers; i++) {
            Layer layer(1, 1); // Dummy layer, will be overwritten
            layer.loadFromFile(file);
            layers.push_back(layer);
        }
        
        file.close();
        cout << "Network loaded successfully!" << endl;
        cout << "Layers loaded: " << layers.size() << endl;
        cout << "====================" << endl;
    }
    
    // Display network architecture
    void displayArchitecture() const {
        cout << "\n=== NEURAL NETWORK ARCHITECTURE ===" << endl;
        cout << "Learning Rate: " << learning_rate << endl;
        cout << "Epochs: " << epochs << endl;
        cout << "Loss Threshold: " << loss_threshold << endl;
        cout << "Number of Layers: " << layers.size() << endl;
        
        for (size_t i = 0; i < layers.size(); i++) {
            cout << "Layer " << (i + 1) << ": ";
            // Note: In a real implementation, we'd store layer dimensions
            cout << "Neural layer with activation function" << endl;
        }
        
        cout << "====================================" << endl;
    }
    
private:
    // Calculate loss (mean squared error)
    double calculateLoss(const Matrix& error) const {
        double loss = 0.0;
        for (int i = 0; i < error.getRows(); i++) {
            for (int j = 0; j < error.getCols(); j++) {
                loss += error(i, j) * error(i, j);
            }
        }
        return loss / (error.getRows() * error.getCols());
    }
    
    // Check if prediction is correct (for classification)
    bool isCorrectPrediction(const Matrix& output, const Matrix& target) const {
        // Find the index of maximum value in output and target
        int output_max = 0, target_max = 0;
        double output_val = output(0, 0), target_val = target(0, 0);
        
        for (int i = 0; i < output.getRows(); i++) {
            for (int j = 0; j < output.getCols(); j++) {
                if (output(i, j) > output_val) {
                    output_val = output(i, j);
                    output_max = i * output.getCols() + j;
                }
                if (target(i, j) > target_val) {
                    target_val = target(i, j);
                    target_max = i * target.getCols() + j;
                }
            }
        }
        
        return output_max == target_max;
    }
};

// XOR problem dataset generator
vector<pair<Matrix, Matrix>> generateXORDataset() {
    cout << "\n=== GENERATING XOR DATASET ===" << endl;
    
    vector<pair<Matrix, Matrix>> dataset;
    
    // XOR truth table
    vector<vector<double>> inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<vector<double>> targets = {{0}, {1}, {1}, {0}};
    
    for (size_t i = 0; i < inputs.size(); i++) {
        Matrix input_matrix({inputs[i]});
        Matrix target_matrix({targets[i]});
        
        cout << "Input: [" << inputs[i][0] << ", " << inputs[i][1] << "] -> Target: " << targets[i][0] << endl;
        
        dataset.emplace_back(input_matrix, target_matrix);
    }
    
    cout << "Generated " << dataset.size() << " training samples" << endl;
    cout << "=============================" << endl;
    
    return dataset;
}

// Iris dataset (simplified version)
vector<pair<Matrix, Matrix>> generateIrisDataset() {
    cout << "\n=== GENERATING IRIS DATASET ===" << endl;
    
    vector<pair<Matrix, Matrix>> dataset;
    
    // Simplified Iris dataset (3 classes, 4 features)
    vector<vector<double>> inputs = {
        {5.1, 3.5, 1.4, 0.2}, // Setosa
        {4.9, 3.0, 1.4, 0.2}, // Setosa
        {7.0, 3.2, 4.7, 1.4}, // Versicolor
        {6.4, 3.2, 4.5, 1.5}, // Versicolor
        {6.3, 3.3, 6.0, 2.5}, // Virginica
        {5.8, 2.7, 5.1, 1.9}  // Virginica
    };
    
    vector<vector<double>> targets = {
        {1, 0, 0}, // Setosa
        {1, 0, 0}, // Setosa
        {0, 1, 0}, // Versicolor
        {0, 1, 0}, // Versicolor
        {0, 0, 1}, // Virginica
        {0, 0, 1}  // Virginica
    };
    
    for (size_t i = 0; i < inputs.size(); i++) {
        Matrix input_matrix({inputs[i]});
        Matrix target_matrix({targets[i]});
        
        cout << "Sample " << (i + 1) << ": Features [";
        for (size_t j = 0; j < inputs[i].size(); j++) {
            cout << inputs[i][j];
            if (j < inputs[i].size() - 1) cout << ", ";
        }
        cout << "] -> Class [" << targets[i][0] << ", " << targets[i][1] << ", " << targets[i][2] << "]" << endl;
        
        dataset.emplace_back(input_matrix, target_matrix);
    }
    
    cout << "Generated " << dataset.size() << " training samples" << endl;
    cout << "=============================" << endl;
    
    return dataset;
}

// Input validation functions
int getValidInteger(const string& prompt, int min_val = 0, int max_val = 1000000) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            int value = stoi(input);
            
            if (value >= min_val && value <= max_val) {
                return value;
            }
            
            cout << "Error: Please enter a number between " << min_val << " and " << max_val << "." << endl;
        } catch (...) {
            cout << "Error: Please enter a valid integer." << endl;
        }
    }
}

double getValidDouble(const string& prompt, double min_val = 0.0, double max_val = 1.0) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            double value = stod(input);
            
            if (value >= min_val && value <= max_val) {
                return value;
            }
            
            cout << "Error: Please enter a number between " << min_val << " and " << max_val << "." << endl;
        } catch (...) {
            cout << "Error: Please enter a valid number." << endl;
        }
    }
}

// Display program introduction
void displayIntroduction() {
    cout << "========================================" << endl;
    cout << "    C++ NEURAL NETWORK - LEVEL 8" << endl;
    cout << "========================================" << endl;
    cout << "Welcome to artificial intelligence in C++!" << endl;
    cout << "This program demonstrates:" << endl;
    cout << "- Neural network architecture and layers" << endl;
    cout << "- Forward propagation and activation functions" << endl;
    cout << "- Backpropagation and gradient descent" << endl;
    cout << "- Matrix operations and linear algebra" << endl;
    cout << "- Training and optimization algorithms" << endl;
    cout << "- Human-like code with detailed comments!" << endl;
    cout << "========================================" << endl;
}

// Display main menu
void displayMenu() {
    cout << "\n=== NEURAL NETWORK MENU ===" << endl;
    cout << "1. Create XOR Network" << endl;
    cout << "2. Create Iris Classification Network" << endl;
    cout << "3. Load Network from File" << endl;
    cout << "4. Train Network" << endl;
    cout << "5. Test Network" << endl;
    cout << "6. Save Network" << endl;
    cout << "7. Display Architecture" << endl;
    cout << "8. Make Prediction" << endl;
    cout << "9. Exit" << endl;
    cout << "=============================" << endl;
}

// Main program loop
int main() {
    displayIntroduction();
    
    NeuralNetwork network;
    vector<pair<Matrix, Matrix>> training_data;
    vector<pair<Matrix, Matrix>> test_data;
    bool network_created = false;
    
    while (true) {
        displayMenu();
        
        int choice = getValidInteger("Enter your choice (1-9): ", 1, 9);
        
        switch (choice) {
            case 1: {
                cout << "\n=== CREATING XOR NETWORK ===" << endl;
                
                // Create network for XOR problem
                network = NeuralNetwork(0.1, 10000, 0.001);
                network.addLayer(2, 4, ActivationFunction::SIGMOID);  // Hidden layer
                network.addLayer(4, 1, ActivationFunction::SIGMOID);  // Output layer
                
                // Generate XOR dataset
                training_data = generateXORDataset();
                test_data = training_data; // Use same data for testing
                
                network_created = true;
                cout << "XOR Network created successfully!" << endl;
                cout << "=============================" << endl;
                break;
            }
            
            case 2: {
                cout << "\n=== CREATING IRIS CLASSIFICATION NETWORK ===" << endl;
                
                // Create network for Iris classification
                network = NeuralNetwork(0.01, 5000, 0.001);
                network.addLayer(4, 8, ActivationFunction::RELU);       // Hidden layer 1
                network.addLayer(8, 6, ActivationFunction::RELU);       // Hidden layer 2
                network.addLayer(6, 3, ActivationFunction::SIGMOID);   // Output layer
                
                // Generate Iris dataset
                training_data = generateIrisDataset();
                test_data = training_data; // Use same data for testing
                
                network_created = true;
                cout << "Iris Classification Network created successfully!" << endl;
                cout << "=============================================" << endl;
                break;
            }
            
            case 3: {
                if (!network_created) {
                    cout << "Please create a network first!" << endl;
                    break;
                }
                
                string filename;
                cout << "Enter filename to load network: ";
                getline(cin, filename);
                
                network.loadFromFile(filename);
                break;
            }
            
            case 4: {
                if (!network_created || training_data.empty()) {
                    cout << "Please create a network and load training data first!" << endl;
                    break;
                }
                
                // Convert training data to separate vectors
                vector<Matrix> inputs, targets;
                for (const auto& pair : training_data) {
                    inputs.push_back(pair.first);
                    targets.push_back(pair.second);
                }
                
                network.train(inputs, targets);
                break;
            }
            
            case 5: {
                if (!network_created || test_data.empty()) {
                    cout << "Please create a network and load test data first!" << endl;
                    break;
                }
                
                // Convert test data to separate vectors
                vector<Matrix> inputs, targets;
                for (const auto& pair : test_data) {
                    inputs.push_back(pair.first);
                    targets.push_back(pair.second);
                }
                
                network.test(inputs, targets);
                break;
            }
            
            case 6: {
                if (!network_created) {
                    cout << "Please create a network first!" << endl;
                    break;
                }
                
                string filename;
                cout << "Enter filename to save network: ";
                getline(cin, filename);
                
                network.saveToFile(filename);
                break;
            }
            
            case 7: {
                if (!network_created) {
                    cout << "Please create a network first!" << endl;
                    break;
                }
                
                network.displayArchitecture();
                break;
            }
            
            case 8: {
                if (!network_created) {
                    cout << "Please create and train a network first!" << endl;
                    break;
                }
                
                cout << "\n=== MAKING PREDICTION ===" << endl;
                cout << "Enter input values (comma-separated): ";
                string input_str;
                getline(cin, input_str);
                
                // Parse input
                vector<double> input_values;
                stringstream ss(input_str);
                string value;
                
                while (getline(ss, value, ',')) {
                    try {
                        input_values.push_back(stod(value));
                    } catch (...) {
                        cout << "Invalid input value: " << value << endl;
                    }
                }
                
                if (input_values.empty()) {
                    cout << "No valid input values provided!" << endl;
                    break;
                }
                
                Matrix input({input_values});
                Matrix prediction = network.predict(input);
                
                cout << "Prediction result:" << endl;
                prediction.display("Prediction");
                cout << "====================" << endl;
                break;
            }
            
            case 9:
                cout << "\nThank you for using C++ Neural Network!" << endl;
                cout << "You've learned:" << endl;
                cout << "- Neural network architecture and layers" << endl;
                cout << "- Forward propagation and activation functions" << endl;
                cout << "- Backpropagation and gradient descent" << endl;
                cout << "- Matrix operations and linear algebra" << endl;
                cout << "- Training and optimization algorithms" << endl;
                cout << "- Human-readable, maintainable code!" << endl;
                return 0;
                
            default:
                cout << "Error: Invalid choice! Please enter 1-9." << endl;
        }
        
        // Add a small pause for better user experience
        if (choice != 9) {
            cout << "\nPress Enter to continue...";
            string pause;
            getline(cin, pause);
        }
    }
    
    return 0;
}
