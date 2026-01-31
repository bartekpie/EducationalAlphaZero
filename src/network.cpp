#include "network.hpp"

NeuralNetwork::NeuralNetwork(int64_t input_size, int64_t output_size, int neuronsInLayer, float learningPace): learningPace_(learningPace){
        if (neuronsInLayer < input_size || neuronsInLayer < output_size) {
          throw std::invalid_argument("Hidden layer too small");
        }
        layer1_ = register_module("layer1", torch::nn::Linear(input_size, neuronsInLayer));
        layer2_ = register_module("layer2", torch::nn::Linear(neuronsInLayer,neuronsInLayer));
        layer3_ = register_module("layer3", torch::nn::Linear(neuronsInLayer,output_size));
    }

torch::Tensor NeuralNetwork::forward(torch::Tensor x) {
        x = torch::relu(layer1_->forward(x));
        x = torch::relu(layer2_->forward(x));
        x = layer3_->forward(x);
        return x;
    
    }
//template<typename T>
void NeuralNetwork::train(std::vector<std::vector<double>> inputs, std::vector<std::vector<double>> outputs ) {
        if (inputs.size() != outputs.size())
          throw std::invalid_argument( "Inputs and Outputs size should be the same");
        torch::optim::Adam optimizer(parameters(), torch::optim::AdamOptions(learningPace_));
        for (auto i{0}; i < 100; i++) {
            for(auto dataIndex{0}; dataIndex < inputs.size(); dataIndex++) {
                torch::Tensor X = torch::tensor(inputs[dataIndex]);
                torch::Tensor Y = torch::tensor(outputs[dataIndex]);
                torch::Tensor nnet_output = this->forward(X);
                torch::Tensor loss = criterion_(nnet_output, Y);
                optimizer.zero_grad();
                loss.backward();
                optimizer.step();
            }
        }
    }
std::pair<double, double> NeuralNetwork::TensorToPair(torch::Tensor t) {
    auto cpu_output = t.to(torch::kCPU);

    return std::make_pair(
        cpu_output[0].item<double>(),
        cpu_output[1].item<double>()
    );
}

torch::Tensor NeuralNetwork::vecToTensor(const std::vector<int>& i)
{
    return torch::tensor(i).clone();
}
