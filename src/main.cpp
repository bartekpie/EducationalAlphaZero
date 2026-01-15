#include <iostream>
#include "network.hpp"

int main() {

    std::vector<double> inputs = {0.33,0.26, 0.91, 0.84, 0.33, 0.19, 0.47, 0.74};
    std::vector<double> outputs = {0.22,0.43,0.11,0.83};
    
    

    std::vector<double> inputs1 = {1.1, 4, 5, 88, 90, 12.3, 1.4, 5.6};
    std::vector<double> outputs1 = {20,12,40,80};


    std::vector<std::vector<double>> trainingInputs {inputs, inputs1};
    std::vector<std::vector<double>> trainingOutputs {outputs, outputs1};


    
    NeuralNetwork net(trainingInputs[0].size(), trainingOutputs[0].size(), 8, 0.1);
    net.train(trainingInputs, trainingOutputs);

    torch::Tensor inputsTen = torch::tensor(inputs);
    torch::Tensor inputs1Ten = torch::tensor(inputs1);

    std::cout<< net.forward(inputsTen) << std::endl;
    std::cout<< net.forward(inputs1Ten) << std::endl;



    

}