//NeuralNetwork.h
//By Andrey Melnikov
//TODO based on

#include <vector>
#include <utility>
#include "Matrix.h" 
#include <stdexcept>
#include <iostream>

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H


using std::vector;
using std::pair;
using std::ostream;

typedef vector<int>::size_type v_int;
typedef vector<Matrix>::size_type m_int;


/*
 * Utility class to help interact with Neural Network Training Data.
 *
*/
class NeuralNetworkData
{
	private:
		struct Datum
		{
			const Matrix* input;
			const Matrix* output;

			Datum(const Matrix& inputData, const Matrix& outputData) : input(&inputData), output(&outputData)
			{
			}
			
			const Matrix& getInput() const { return *this->input; };
			const Matrix& getOutput() const { return *this->output; };
		};
		
		vector<Datum> wrappedData;

	protected:
		vector<Matrix> inputs;
		vector<Matrix> outputs;
		
		//Populates the vector<Datum>, providing convient access to NeuralNetwork 
		//TODO make this abstract class
		void wrapData();

		
	public:
		NeuralNetworkData() {};
		~NeuralNetworkData() {};

		//Create a method to convert inputs/outputs into wrapped data - protected
		//Make sure this isn't virtual - no need to override
		const Datum& operator[](int i) const { return this->wrappedData[i]; };
		vector<Matrix>::size_type size() const { return this->inputs.size(); };
};

class NeuralNetwork
{
	//TODO pair<v_int,v_int> is [a,b)
	private:
		vector<int> sizes;
		vector<Matrix> biases;
		vector<Matrix> weights;

		/*	Matrix z;
			Creates a rows x columns matrix where each entry is initialized randomly via a Gaussian distribution with mean 0 and variance 1. 
			At least, it will be eventually, for now its just a random double in range [0,1]
		*/
		static Matrix gaussianDistribution(unsigned int rows, unsigned int columns);
		static Matrix costDerivative(const Matrix& outputActivations, const Matrix& output);

		/*
		 * Input: A Mx1 sized matrix. Can be MxN but only the first row will be considered.
		 * returns: The index of the largest value in the row, or 0 if the values are all the same.
		 */
		static unsigned int getLargestRow(const Matrix& matrix);

		/*
		 * Input: A Mx1 sized matrix. Can be MxN but only the first row will be considered.
	     * returns: The index of the first greater than zero entry, starting from the end of the row. 
		 *			-1 if all entries are less than or equal to 0.
		 */
		static int getLastNonZeroRow(const Matrix& matrix);

		/**
		 * Modifies destination to be of the same size as original and have 0 filled matrices, 
		 * where each matrix has the same size as a matrix in orignal, done in order. 
		*/
		static void createBlankCopy(const vector<Matrix> original, vector<Matrix>& destination);


		/*
		 * Returns a collection of pairs of ints such that the range from [start, end) is split up into ranges of size length, that is [i, i + size).
		 * If size is greater than the incoming range, a pair that spans the whole range is returned as the single element of the collection.
		 * If the range can't be split up evenly, the last span will be shorter than all the other spans.
		*/
		static void partition(int start, int end, int size, vector< pair<int,int> >& pairs);

		//outputWeights and biases are expected to be empty.
		void backprop(const Matrix& input, const Matrix& output, vector<Matrix>& outputWeights, vector<Matrix>& outputBiases);
		//TODO pair pass by reference?
		void updateMiniBatch(const NeuralNetworkData& trainingData, pair<v_int, v_int> limits, double eta); 
		static void addInto(vector<Matrix>& matrices, const vector<Matrix>& delta);
	
		/*
		 * Note: a z is the value of a layer in the Neural Network before it has had the Sigmoid function applied. 	
		 *
		 * Give the input matrix, populates zs with the z-value of each layer in the NeuralNetwork.
		 * Also populates activations with the activation of each layer in the NeuralNetwork.
		 * 
		 * Incoming zs and activations are wiped of the original data.
		*/
		void calculateZsAndActivations(const Matrix& input, vector<Matrix>& zs, vector<Matrix>& activations);
		
	public:
		NeuralNetwork(const vector<int>& layerSizes);
		~NeuralNetwork();
	
		/*
		 * input is expected to be a rows x 1 matrix. Input to the neural network. 
		 * Returns the result from the network.
		*/
		Matrix feedForward(const Matrix& input);
		int evaluate(const NeuralNetworkData& data);
		
		void SGD(const NeuralNetworkData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta);
		void SGD(const NeuralNetworkData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta, const NeuralNetworkData& testData );		

		friend ostream& operator<<(ostream& os, NeuralNetwork& network);
};


double sigmoid(double value);

struct Sigmoid
{
	double operator()(double value);
};

struct SigmoidPrime
{
	double operator()(double value);
};

#endif
