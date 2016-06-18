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

class NeuralTrainingData;

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

		/**
		 * Modifies incoming matrices container to have 0 filled matrices, where each matrix has the same size as a matrix in orignal, done in order. 
		*/
		static void createBlankCopy(vector<Matrix>& matrices, const vector<Matrix> original);

	public:
		NeuralNetwork(const vector<int>& layerSizes);
		~NeuralNetwork();

		

		/*
			input is expected to be a rows x 1 matrix. Input to the neural network. 
			Returns the result from the network.
		*/
		Matrix feedForward(const Matrix& input);
		int evaluate(const NeuralTrainingData& data);
		
//		pair<vector<const Matrix&>, vector<const Matrix&>> backprop(const Matrix& input, const Matrix& output);
	

//    public void SGD(List<Pair<Matrix, Matrix>> trainingData, int epochs, int miniBatchSize, double eta, List<Pair<Matrix,Matrix>> testData)
//     public void updateMiniBatch(List<Pair<Matrix,Matrix>> miniBatch, double eta)
		

		
};

double sigmoid(double value);
double sigmoidPrime(double value);

/*
 * Utility class to help interact with Neural Network Training Data.
 *
*/
class NeuralTrainingData
{
	private:
		class MatrixWrapper 
		{	
			private:
				const Matrix& matrix;

			public:
				MatrixWrapper(const Matrix& newMatrix) : matrix(newMatrix)
				{
				}

				const Matrix& rawMatrix() const { return this->matrix; };
				unsigned int largestRow() const;
				int firstNonZeroRow() const;
				int lastNonZeroRow() const;
		};

		struct Datum
		{
			MatrixWrapper input;
			MatrixWrapper output;

			Datum(const Matrix& inputData, const Matrix& outputData) : input(inputData), output(outputData)
			{
			}
		};

		vector<Matrix> inputs;
		vector<Matrix> outputs;
		vector<Datum> wrappedData;
		
	public:
		NeuralTrainingData(const vector<Matrix>& inputs, const vector<Matrix>& outputs);
		~NeuralTrainingData();

		const Datum& operator[](int i) const { return this->wrappedData[i]; };
		const vector<Matrix>& getInputs() const { return this->inputs; };
		const vector<Matrix>& getOutputs() const { return this->outputs; };	
		vector<Matrix>::size_type size() { return this->inputs.size(); };
};

#endif
