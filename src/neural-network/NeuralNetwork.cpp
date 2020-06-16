#include "neural-network/NeuralNetwork.hpp"

// Constructor for Any NeuralNetwork
NeuralNetwork::NeuralNetwork(unsigned input, unsigned hidden, unsigned output) {
    input_nodes = input;
    hidden_nodes = hidden;
    output_nodes = output;

    weights_ih = Matrix(hidden, input, 0);
    weights_ho = Matrix(output, hidden, 0);

    bias_h = Matrix(hidden, 1, 0);
    bias_o = Matrix(output, 1, 0);

    weights_ih.randomize();
    weights_ho.randomize();

    bias_h.randomize();
    bias_o.randomize();
}

// Copy Constructor
NeuralNetwork::NeuralNetwork(const NeuralNetwork &n) {
    input_nodes = n.input_nodes;
    hidden_nodes = n.hidden_nodes;
    output_nodes = n.output_nodes;

    weights_ih = Matrix(n.weights_ih);
    weights_ho = Matrix(n.weights_ho);

    bias_h = Matrix(n.bias_h);
    bias_o = Matrix(n.bias_o);
}

// Default Constructor
NeuralNetwork::NeuralNetwork() {
}

// Set the learning rate
void NeuralNetwork::setLearningRate(double rate) {
    this->learningRate = rate; // default 0.1
}

// Train the neural network
// args: Array with inputs, Array with the results
void NeuralNetwork::train(vector<double> input_array, vector<double> target_array) {
    Matrix inputs = Matrix(input_array);
    Matrix hidden = this->weights_ih * inputs;
    hidden = hidden + this->bias_h;
    // activation function!
    hidden.sigmod();
    // Generating the output's output!
    Matrix outputs = this->weights_ho * hidden;
    outputs = outputs + this->bias_o;
    outputs.sigmod();

    // Convert array to matrix object
    Matrix targets = Matrix(target_array);

    // Calculate the error
    // ERROR = TARGETS - OUTPUTS
    Matrix output_errors = targets - outputs;

    // Calculate gradient
    Matrix gradients = outputs.dSigmod();
    gradients = gradients * output_errors;
    gradients = gradients * this->learningRate;

    // Calculate Deltas
    Matrix hidden_transpose = hidden.transpose();
    Matrix weights_ho_deltas = gradients * hidden_transpose;

    // Adjust the weights by deltas
    this->weights_ho = this->weights_ho + weights_ho_deltas;
    // Adujust bias by its deltas (which is just the gradient)
    this->bias_o = this->bias_o + gradients;

    // Calculate the hidden layer errors
    Matrix weights_ho_transpose = this->weights_ho.transpose();
    Matrix hidden_errors = weights_ho_transpose * output_errors;

    // Calculate hidden gradient
    Matrix hidden_gradient = hidden.dSigmod();
    hidden_gradient = hidden_gradient * hidden_errors;
    hidden_gradient = hidden_gradient * this->learningRate;

    // Calculate input->hidden deltas
    Matrix inputs_transpose = inputs.transpose();
    Matrix weights_ih_deltas = hidden_gradient * inputs_transpose;

    // Adjust the weights by deltas
    this->weights_ih = this->weights_ih + weights_ih_deltas;
    // Adjust the bias by its deltas (which is just the gradients)
    this->bias_h = this->bias_h + hidden_gradient;
}

// Predict a output
// args: Array of inputs
// return: Array of outputs to given inputs 
vector<double> NeuralNetwork::predict(vector<double> input_array) {
    // Generating the hidden outputs
    Matrix inputs = Matrix(input_array);
    Matrix hidden = this->weights_ih * inputs;
    hidden = hidden + this->bias_h;
    
    // Activation function
    hidden = hidden.sigmod();

    // Generating the ouput's output!
    Matrix output = this->weights_ho * hidden;
    Matrix out = output + this->bias_o;
    output = output.sigmod();

    return output.toArray();
}

// Make a copy of this NeuralNetwork
NeuralNetwork &NeuralNetwork::copy() {
    return *this;
}

// Apply a mutate function in weights and bias
void NeuralNetwork::mutate(functioncall func) {
    this->weights_ih.map(func);
    this->weights_ho.map(func);
    this->bias_h.map(func);
    this->bias_o.map(func);
}

// Fancy print all weights and bias
void NeuralNetwork::print() {
    std::cout << "Weights_HO\n";
    this->weights_ho.print();
    std::cout << "Weights_IH\n";
    this->weights_ih.print();
    std::cout << "Bias_H\n";
    this->bias_h.print();
    std::cout << "Bias_O\n";
    this->bias_o.print();
}

// Get inputs #
unsigned NeuralNetwork::getInputNodes() {
    return this->input_nodes;
}

// Get hidden #
unsigned NeuralNetwork::getHiddenNodes() {
    return this->hidden_nodes;
}

// Get ouputs #
unsigned NeuralNetwork::getOutputNodes() {
    return this->output_nodes;
}

// Get input-hidden weights Matrix
Matrix NeuralNetwork::getWeightsIh() {
    return this->weights_ih;
}

// Get hiden-outputs weights Matrix
Matrix NeuralNetwork::getWeightsHo() {
    return this->weights_ho;
}

// Get hidden bias Matrix
Matrix NeuralNetwork::getHiddenBias() {
    return this->bias_h;
}

// Get output bias Matrix
Matrix NeuralNetwork::getOutputBias() {
    return this->bias_o;
}