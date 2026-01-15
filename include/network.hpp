#pragma once

#include <iostream>
#include <torch/torch.h>
#include <stdexcept>
#include <vector>

class NeuralNetwork : public torch::nn::Module {
private:
    torch::nn::Linear layer1_{nullptr};
    torch::nn::Linear layer2_{nullptr};
    torch::nn::Linear layer3_{nullptr};
    torch::nn::MSELoss criterion_;
    float learningPace_;

public:
    NeuralNetwork(int64_t input_size, int64_t output_size, int neuronsInLayer, float learningPace);
    torch::Tensor forward(torch::Tensor x);
    //template<typename T>
    void train(std::vector<std::vector<double>> inputs, std::vector<std::vector<double>> outputs);
};
