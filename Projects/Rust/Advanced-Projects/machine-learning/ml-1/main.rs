/*
 * Machine Learning in Rust - Level 8: AI & Neural Networks
 * 
 * Welcome to artificial intelligence in Rust! This is where safety meets intelligence.
 * Learn neural networks, backpropagation, and machine learning algorithms.
 * 
 * Key concepts you'll learn:
 * - Neural network architecture with ndarray
 * - Forward propagation and activation functions
 * - Backpropagation and gradient descent
 * - Matrix operations and linear algebra
 * - Training optimization and regularization
 * - Human-like code with detailed explanations!
 */

use ndarray::prelude::*;
use ndarray_rand::rand::Rng;
use ndarray_rand::rand_distr::Uniform;
use serde::{Deserialize, Serialize};
use std::fs::File;
use std::io::{self, Write};
use rand::Rng as StdRng;

// Activation function types
#[derive(Debug, Clone, Copy, Serialize, Deserialize)]
pub enum ActivationFunction {
    Sigmoid,
    Tanh,
    ReLU,
    LeakyReLU,
}

// Neural network layer
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Layer {
    weights: Array2<f64>,
    biases: Array1<f64>,
    activation: ActivationFunction,
    last_input: Option<Array2<f64>>,
    last_output: Option<Array2<f64>>,
    last_activation_derivative: Option<Array2<f64>>,
}

impl Layer {
    // Create new layer
    pub fn new(input_size: usize, output_size: usize, activation: ActivationFunction) -> Self {
        println!("Creating neural layer: {} -> {}", input_size, output_size);
        
        // Initialize weights with Xavier initialization
        let mut rng = rand::thread_rng();
        let limit = (6.0 / (input_size as f64 + output_size as f64)).sqrt();
        
        let weights = Array2::random_using(
            (input_size, output_size),
            Uniform::new(-limit, limit),
            &mut rng,
        );
        
        let biases = Array1::zeros(output_size);
        
        println!("Layer created with {:?} activation", activation);
        
        Layer {
            weights,
            biases,
            activation,
            last_input: None,
            last_output: None,
            last_activation_derivative: None,
        }
    }
    
    // Forward propagation
    pub fn forward(&mut self, input: &Array2<f64>) -> Array2<f64> {
        println!("\n=== FORWARD PROPAGATION ===");
        println!("Input shape: {:?}", input.shape());
        
        // Store input for backpropagation
        self.last_input = Some(input.clone());
        
        // Calculate weighted sum: input * weights + biases
        let weighted_sum = input.dot(&self.weights);
        let biased_sum = weighted_sum + &self.biases.view().insert_axis(Axis(0));
        
        // Apply activation function
        let output = self.apply_activation(&biased_sum);
        let activation_derivative = self.apply_activation_derivative(&biased_sum);
        
        // Store for backpropagation
        self.last_output = Some(output.clone());
        self.last_activation_derivative = Some(activation_derivative);
        
        println!("Forward propagation completed");
        println!("Output shape: {:?}", output.shape());
        
        output
    }
    
    // Backward propagation
    pub fn backward(&mut self, output_gradient: &Array2<f64>, learning_rate: f64) -> Array2<f64> {
        println!("\n=== BACKWARD PROPAGATION ===");
        println!("Output gradient shape: {:?}", output_gradient.shape());
        
        // Calculate gradient for this layer
        let activation_derivative = self.last_activation_derivative.as_ref().unwrap();
        let layer_gradient = output_gradient * activation_derivative;
        
        // Calculate gradients for weights and biases
        let input = self.last_input.as_ref().unwrap();
        let weight_gradient = input.t().dot(&layer_gradient);
        let bias_gradient = layer_gradient.sum_axis(Axis(0));
        
        // Calculate gradient for previous layer
        let input_gradient = layer_gradient.dot(&self.weights.t());
        
        // Update weights and biases
        self.weights = &self.weights - &(weight_gradient * learning_rate);
        self.biases = &self.biases - &(bias_gradient * learning_rate);
        
        println!("Backward propagation completed");
        println!("Weights updated, biases updated");
        
        input_gradient
    }
    
    // Get last output
    pub fn get_last_output(&self) -> Option<&Array2<f64>> {
        self.last_output.as_ref()
    }
    
    // Apply activation function
    fn apply_activation(&self, x: &Array2<f64>) -> Array2<f64> {
        match self.activation {
            ActivationFunction::Sigmoid => {
                x.mapv(|v| 1.0 / (1.0 + (-v).exp()))
            }
            ActivationFunction::Tanh => {
                x.mapv(|v| v.tanh())
            }
            ActivationFunction::ReLU => {
                x.mapv(|v| v.max(0.0))
            }
            ActivationFunction::LeakyReLU => {
                x.mapv(|v| v.max(0.1 * v))
            }
        }
    }
    
    // Apply activation function derivative
    fn apply_activation_derivative(&self, x: &Array2<f64>) -> Array2<f64> {
        match self.activation {
            ActivationFunction::Sigmoid => {
                x.mapv(|v| {
                    let sig = 1.0 / (1.0 + (-v).exp());
                    sig * (1.0 - sig)
                })
            }
            ActivationFunction::Tanh => {
                x.mapv(|v| {
                    let t = v.tanh();
                    1.0 - t * t
                })
            }
            ActivationFunction::ReLU => {
                x.mapv(|v| if v > 0.0 { 1.0 } else { 0.0 })
            }
            ActivationFunction::LeakyReLU => {
                x.mapv(|v| if v > 0.0 { 1.0 } else { 0.1 })
            }
        }
    }
}

// Neural network structure
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct NeuralNetwork {
    layers: Vec<Layer>,
    learning_rate: f64,
    epochs: usize,
    loss_threshold: f64,
}

impl NeuralNetwork {
    // Create new neural network
    pub fn new(learning_rate: f64, epochs: usize, loss_threshold: f64) -> Self {
        println!("Creating Neural Network");
        println!("Learning rate: {}", learning_rate);
        println!("Epochs: {}", epochs);
        println!("Loss threshold: {}", loss_threshold);
        
        NeuralNetwork {
            layers: Vec::new(),
            learning_rate,
            epochs,
            loss_threshold,
        }
    }
    
    // Add layer to network
    pub fn add_layer(&mut self, input_size: usize, output_size: usize, activation: ActivationFunction) {
        println!("\n=== ADDING LAYER ===");
        println!("Input size: {}", input_size);
        println!("Output size: {}", output_size);
        
        self.layers.push(Layer::new(input_size, output_size, activation));
        
        println!("Layer added. Total layers: {}", self.layers.len());
        println!("==================");
    }
    
    // Forward propagation through all layers
    pub fn predict(&mut self, input: &Array2<f64>) -> Array2<f64> {
        println!("\n=== PREDICTION ===");
        println!("Input shape: {:?}", input.shape());
        
        let mut current_input = input.clone();
        
        for (i, layer) in self.layers.iter_mut().enumerate() {
            println!("Layer {}:", i + 1);
            current_input = layer.forward(&current_input);
        }
        
        println!("Prediction completed");
        println!("==================");
        
        current_input
    }
    
    // Train the network
    pub fn train(&mut self, training_inputs: &[Array2<f64>], training_targets: &[Array2<f64>]) {
        println!("\n=== TRAINING NEURAL NETWORK ===");
        println!("Training samples: {}", training_inputs.len());
        println!("Epochs: {}", self.epochs);
        println!("Learning rate: {}", self.learning_rate);
        
        for epoch in 1..=self.epochs {
            let mut total_loss = 0.0;
            
            for (sample_idx, (input, target)) in training_inputs.iter().zip(training_targets.iter()).enumerate() {
                // Forward propagation
                let output = self.predict(input);
                
                // Calculate loss (mean squared error)
                let error = &output - target;
                let sample_loss = self.calculate_loss(&error);
                total_loss += sample_loss;
                
                // Backward propagation
                let gradient = &error * (2.0 / output.len() as f64);
                
                let mut current_gradient = gradient.clone();
                for layer in self.layers.iter_mut().rev() {
                    current_gradient = layer.backward(&current_gradient, self.learning_rate);
                }
                
                if sample_idx % 100 == 0 {
                    println!("Sample {}: Loss = {:.6}", sample_idx + 1, sample_loss);
                }
            }
            
            let average_loss = total_loss / training_inputs.len() as f64;
            
            // Print progress
            if epoch % 100 == 0 || epoch == 1 {
                println!("Epoch {}/{} - Loss: {:.6}", epoch, self.epochs, average_loss);
            }
            
            // Check for convergence
            if average_loss < self.loss_threshold {
                println!("Convergence reached at epoch {}", epoch);
                println!("Final loss: {:.6}", average_loss);
                break;
            }
        }
        
        println!("Training completed!");
        println!("========================");
    }
    
    // Test the network
    pub fn test(&mut self, test_inputs: &[Array2<f64>], test_targets: &[Array2<f64>]) -> (f64, f64) {
        println!("\n=== TESTING NEURAL NETWORK ===");
        println!("Test samples: {}", test_inputs.len());
        
        let mut total_loss = 0.0;
        let mut correct_predictions = 0;
        
        for (input, target) in test_inputs.iter().zip(test_targets.iter()) {
            let output = self.predict(input);
            let error = &output - target;
            let sample_loss = self.calculate_loss(&error);
            total_loss += sample_loss;
            
            // Check if prediction is correct (for classification)
            if self.is_correct_prediction(&output, target) {
                correct_predictions += 1;
            }
        }
        
        let average_loss = total_loss / test_inputs.len() as f64;
        let accuracy = (correct_predictions as f64 / test_inputs.len() as f64) * 100.0;
        
        println!("Test Results:");
        println!("Average Loss: {:.6}", average_loss);
        println!("Accuracy: {:.2}%", accuracy);
        println!("Correct Predictions: {}/{}", correct_predictions, test_inputs.len());
        println!("============================");
        
        (average_loss, accuracy)
    }
    
    // Save network to file
    pub fn save_to_file(&self, filename: &str) -> io::Result<()> {
        println!("\n=== SAVING NETWORK ===");
        println!("Saving to: {}", filename);
        
        let json_data = serde_json::to_string_pretty(self)?;
        std::fs::write(filename, json_data)?;
        
        println!("Network saved successfully!");
        println!("====================");
        
        Ok(())
    }
    
    // Load network from file
    pub fn load_from_file(filename: &str) -> io::Result<Self> {
        println!("\n=== LOADING NETWORK ===");
        println!("Loading from: {}", filename);
        
        let json_data = std::fs::read_to_string(filename)?;
        let network: NeuralNetwork = serde_json::from_str(&json_data)?;
        
        println!("Network loaded successfully!");
        println!("Layers loaded: {}", network.layers.len());
        println!("====================");
        
        Ok(network)
    }
    
    // Display network architecture
    pub fn display_architecture(&self) {
        println!("\n=== NEURAL NETWORK ARCHITECTURE ===");
        println!("Learning Rate: {}", self.learning_rate);
        println!("Epochs: {}", self.epochs);
        println!("Loss Threshold: {}", self.loss_threshold);
        println!("Number of Layers: {}", self.layers.len());
        
        for (i, layer) in self.layers.iter().enumerate() {
            println!("Layer {}: {} -> {} ({:?})", 
                    i + 1, 
                    layer.weights.shape()[0], 
                    layer.weights.shape()[1], 
                    layer.activation);
        }
        
        println!("====================================");
    }
    
    // Calculate loss (mean squared error)
    fn calculate_loss(&self, error: &Array2<f64>) -> f64 {
        error.mapv(|v| v * v).mean().unwrap()
    }
    
    // Check if prediction is correct (for classification)
    fn is_correct_prediction(&self, output: &Array2<f64>, target: &Array2<f64>) -> bool {
        // Find the index of maximum value in output and target
        let output_max = output.iter().enumerate()
            .max_by(|a, b| a.1.partial_cmp(b.1).unwrap())
            .map(|(idx, _)| idx)
            .unwrap_or(0);
        
        let target_max = target.iter().enumerate()
            .max_by(|a, b| a.1.partial_cmp(b.1).unwrap())
            .map(|(idx, _)| idx)
            .unwrap_or(0);
        
        output_max == target_max
    }
}

// XOR problem dataset
pub fn generate_xor_dataset() -> (Vec<Array2<f64>>, Vec<Array2<f64>>) {
    println!("\n=== GENERATING XOR DATASET ===");
    
    let inputs = vec![
        arr2(&[[0.0, 0.0]]),
        arr2(&[[0.0, 1.0]]),
        arr2(&[[1.0, 0.0]]),
        arr2(&[[1.0, 1.0]]),
    ];
    
    let targets = vec![
        arr2(&[[0.0]]),
        arr2(&[[1.0]]),
        arr2(&[[1.0]]),
        arr2(&[[0.0]]),
    ];
    
    for (i, (input, target)) in inputs.iter().zip(targets.iter()).enumerate() {
        println!("Input: [{}, {}] -> Target: {}", 
                input[[0, 0]], input[[0, 1]], target[[0, 0]]);
    }
    
    println!("Generated {} training samples", inputs.len());
    println!("=============================");
    
    (inputs, targets)
}

// Iris dataset (simplified version)
pub fn generate_iris_dataset() -> (Vec<Array2<f64>>, Vec<Array2<f64>>) {
    println!("\n=== GENERATING IRIS DATASET ===");
    
    let inputs = vec![
        arr2(&[[5.1, 3.5, 1.4, 0.2]]), // Setosa
        arr2(&[[4.9, 3.0, 1.4, 0.2]]), // Setosa
        arr2(&[[7.0, 3.2, 4.7, 1.4]]), // Versicolor
        arr2(&[[6.4, 3.2, 4.5, 1.5]]), // Versicolor
        arr2(&[[6.3, 3.3, 6.0, 2.5]]), // Virginica
        arr2(&[[5.8, 2.7, 5.1, 1.9]]), // Virginica
    ];
    
    let targets = vec![
        arr2(&[[1.0, 0.0, 0.0]]), // Setosa
        arr2(&[[1.0, 0.0, 0.0]]), // Setosa
        arr2(&[[0.0, 1.0, 0.0]]), // Versicolor
        arr2(&[[0.0, 1.0, 0.0]]), // Versicolor
        arr2(&[[0.0, 0.0, 1.0]]), // Virginica
        arr2(&[[0.0, 0.0, 1.0]]), // Virginica
    ];
    
    for (i, (input, target)) in inputs.iter().zip(targets.iter()).enumerate() {
        println!("Sample {}: Features [{}, {}, {}, {}] -> Class [{}, {}, {}]", 
                i + 1,
                input[[0, 0]], input[[0, 1]], input[[0, 2]], input[[0, 3]],
                target[[0, 0]], target[[0, 1]], target[[0, 2]]);
    }
    
    println!("Generated {} training samples", inputs.len());
    println!("=============================");
    
    (inputs, targets)
}

// Input validation functions
fn get_valid_integer(prompt: &str, min_val: usize, max_val: usize) -> usize {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim().parse::<usize>() {
            Ok(value) if value >= min_val && value <= max_val => return value,
            Ok(_) => println!("Error: Please enter a number between {} and {}.", min_val, max_val),
            Err(_) => println!("Error: Please enter a valid integer."),
        }
    }
}

fn get_valid_double(prompt: &str, min_val: f64, max_val: f64) -> f64 {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        match input.trim().parse::<f64>() {
            Ok(value) if value >= min_val && value <= max_val => return value,
            Ok(_) => println!("Error: Please enter a number between {} and {}.", min_val, max_val),
            Err(_) => println!("Error: Please enter a valid number."),
        }
    }
}

// Display program introduction
fn display_introduction() {
    println!("========================================");
    println!("    RUST MACHINE LEARNING - LEVEL 8");
    println!("========================================");
    println!("Welcome to artificial intelligence in Rust!");
    println!("This program demonstrates:");
    println!("- Neural network architecture with ndarray");
    println!("- Forward propagation and activation functions");
    println!("- Backpropagation and gradient descent");
    println!("- Matrix operations and linear algebra");
    println!("- Training optimization and regularization");
    println!("- Human-like code with detailed comments!");
    println!("========================================");
}

// Display main menu
fn display_menu() {
    println!("\n=== MACHINE LEARNING MENU ===");
    println!("1. Create XOR Network");
    println!("2. Create Iris Classification Network");
    println!("3. Load Network from File");
    println!("4. Train Network");
    println!("5. Test Network");
    println!("6. Save Network");
    println!("7. Display Architecture");
    println!("8. Make Prediction");
    println!("9. Exit");
    println!("=============================");
}

// Main program
fn main() -> io::Result<()> {
    display_introduction();
    
    let mut network: Option<NeuralNetwork> = None;
    let mut training_inputs: Vec<Array2<f64>> = Vec::new();
    let mut training_targets: Vec<Array2<f64>> = Vec::new();
    let mut test_inputs: Vec<Array2<f64>> = Vec::new();
    let mut test_targets: Vec<Array2<f64>> = Vec::new();
    
    loop {
        display_menu();
        
        let choice = get_valid_integer("Enter your choice (1-9): ", 1, 9);
        
        match choice {
            1 => {
                println!("\n=== CREATING XOR NETWORK ===");
                
                // Create network for XOR problem
                let mut nn = NeuralNetwork::new(0.1, 10000, 0.001);
                nn.add_layer(2, 4, ActivationFunction::Sigmoid);  // Hidden layer
                nn.add_layer(4, 1, ActivationFunction::Sigmoid);  // Output layer
                
                // Generate XOR dataset
                let (inputs, targets) = generate_xor_dataset();
                training_inputs = inputs.clone();
                training_targets = targets.clone();
                test_inputs = inputs;
                test_targets = targets;
                
                network = Some(nn);
                println!("XOR Network created successfully!");
                println!("=============================");
            }
            
            2 => {
                println!("\n=== CREATING IRIS CLASSIFICATION NETWORK ===");
                
                // Create network for Iris classification
                let mut nn = NeuralNetwork::new(0.01, 5000, 0.001);
                nn.add_layer(4, 8, ActivationFunction::ReLU);       // Hidden layer 1
                nn.add_layer(8, 6, ActivationFunction::ReLU);       // Hidden layer 2
                nn.add_layer(6, 3, ActivationFunction::Sigmoid);   // Output layer
                
                // Generate Iris dataset
                let (inputs, targets) = generate_iris_dataset();
                training_inputs = inputs.clone();
                training_targets = targets.clone();
                test_inputs = inputs;
                test_targets = targets;
                
                network = Some(nn);
                println!("Iris Classification Network created successfully!");
                println!("=============================================");
            }
            
            3 => {
                print!("Enter filename to load network: ");
                io::stdout().flush().unwrap();
                
                let mut filename = String::new();
                io::stdin().read_line(&mut filename)?;
                
                network = Some(NeuralNetwork::load_from_file(filename.trim())?);
            }
            
            4 => {
                if let Some(ref mut nn) = network {
                    if training_inputs.is_empty() {
                        println!("Please load training data first!");
                    } else {
                        nn.train(&training_inputs, &training_targets);
                    }
                } else {
                    println!("Please create a network first!");
                }
            }
            
            5 => {
                if let Some(ref mut nn) = network {
                    if test_inputs.is_empty() {
                        println!("Please load test data first!");
                    } else {
                        nn.test(&test_inputs, &test_targets);
                    }
                } else {
                    println!("Please create a network first!");
                }
            }
            
            6 => {
                if let Some(ref nn) = network {
                    print!("Enter filename to save network: ");
                    io::stdout().flush().unwrap();
                    
                    let mut filename = String::new();
                    io::stdin().read_line(&mut filename)?;
                    
                    nn.save_to_file(filename.trim())?;
                } else {
                    println!("Please create a network first!");
                }
            }
            
            7 => {
                if let Some(ref nn) = network {
                    nn.display_architecture();
                } else {
                    println!("Please create a network first!");
                }
            }
            
            8 => {
                if let Some(ref mut nn) = network {
                    println!("\n=== MAKING PREDICTION ===");
                    print!("Enter input values (comma-separated): ");
                    io::stdout().flush().unwrap();
                    
                    let mut input_str = String::new();
                    io::stdin().read_line(&mut input_str)?;
                    
                    // Parse input
                    let input_values: Result<Vec<f64>, _> = input_str
                        .trim()
                        .split(',')
                        .map(|s| s.trim().parse::<f64>())
                        .collect();
                    
                    match input_values {
                        Ok(values) if !values.is_empty() => {
                            let input = arr2(&[values]);
                            let prediction = nn.predict(&input);
                            
                            println!("Prediction result:");
                            println!("{:?}", prediction);
                            println!("====================");
                        }
                        Ok(_) => {
                            println!("No valid input values provided!");
                        }
                        Err(_) => {
                            println!("Invalid input format!");
                        }
                    }
                } else {
                    println!("Please create and train a network first!");
                }
            }
            
            9 => {
                println!("\nThank you for using Rust Machine Learning!");
                println!("You've learned:");
                println!("- Neural network architecture with ndarray");
                println!("- Forward propagation and activation functions");
                println!("- Backpropagation and gradient descent");
                println!("- Matrix operations and linear algebra");
                println!("- Training optimization and regularization");
                println!("- Human-readable, maintainable code!");
                break;
            }
            
            _ => {
                println!("Error: Invalid choice! Please enter 1-9.");
            }
        }
        
        // Add a small pause for better user experience
        if choice != 9 {
            println!("\nPress Enter to continue...");
            let mut _pause = String::new();
            io::stdin().read_line(&mut _pause)?;
        }
    }
    
    Ok(())
}
