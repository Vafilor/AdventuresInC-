//NeuralNetwork.h
//By Andrey Melnikov
//TODO based on

#include <vector>
#include <utility>
#include "Matrix.hpp" 


#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H


using std::vector;
using std::pair;

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
		static Matrix costDerivative(const Matrix& outputActivations, const Matrix& output);
		static unsigned int getLargestRow(const Matrix& matrix);
		static int getNonZeroRow(const Matrix& matrix);

	public:
		NeuralNetwork(const vector<int>& layerSizes);
		~NeuralNetwork();

		

		/*
			input is expected to be a rows x 1 matrix. Input to the neural network. 
			Returns the result from the network.
		*/
		Matrix feedForward(const Matrix& input);
		int evaluate(const vector< pair<const Matrix&, const Matrix&> >& testData);
		
		//pair< vector<const Matrix& >, vector<const Matrix& > > backprop(const Matrix& input, const Matrix& output);
	

//    public void SGD(List<Pair<Matrix, Matrix>> trainingData, int epochs, int miniBatchSize, double eta, List<Pair<Matrix,Matrix>> testData)
//     public void updateMiniBatch(List<Pair<Matrix,Matrix>> miniBatch, double eta)
		

		
};

double sigmoid(double value);
double sigmoidPrime(double value);

#endif
