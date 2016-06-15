//NeuralNetwork.h
//By Andrey Melnikov
//TODO based on

#include <vector>
#include "Matrix.hpp" 

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H


using std::vector;

class NeuralNetwork
{
	private:
		vector<int> sizes;
		vector<Matrix> biases;
		vector<Matrix> weights;

		/*
			Creates a rows x columns matrix where each entry is initialized randomly via a Gaussian distribution with mean 0 and variance 1. 
			At least, it will be eventually, for now its just a random double in range [0,1]
		*/
		static Matrix gaussianDistribution(unsigned int rows, unsigned int columns);


	public:
		NeuralNetwork(vector<int> layerSizes);
		~NeuralNetwork();

		

		/*
			input is expected to be a rows x 1 matrix. Input to the neural network. 
			Returns the result from the network.
		*/
		Matrix feedForward(Matrix input);

//    public void SGD(List<Pair<Matrix, Matrix>> trainingData, int epochs, int miniBatchSize, double eta, List<Pair<Matrix,Matrix>> testData)
//     public void updateMiniBatch(List<Pair<Matrix,Matrix>> miniBatch, double eta)
//    public Pair<ArrayList<Matrix>, ArrayList<Matrix>> backprop(Matrix input, Matrix output)
//    public int evaluate(List<Pair<Matrix, Matrix>> testData)
//    private Matrix costDerivative(Matrix outputActiviations, Matrix output)
};

double sigmoid(double value);
double sigmoidPrime(double value);

#endif
