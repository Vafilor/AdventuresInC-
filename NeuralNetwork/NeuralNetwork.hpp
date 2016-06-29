//NeuralNetwork.h
//By Andrey Melnikov
//TODO based on

#include <vector>
#include <utility>
#include "Matrix.hpp" 
#include <stdexcept>

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H


using std::vector;
using std::pair;

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
		void wrapData() = 0;

		
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

		/**
		 * Modifies incoming matrices container to have 0 filled matrices, where each matrix has the same size as a matrix in orignal, done in order. 
		*/
		static void createBlankCopy(vector<Matrix>& matrices, const vector<Matrix> original);
		static unsigned int getLargestRow(const Matrix& matrix);
		static int getLastNonZeroRow(const Matrix& matrix);

		/*
		 * Returns a collection of pairs of ints such that the range from [start, end) is split up into ranges of size length, that is [i, i + size).
		 * If size is greater than the incoming range, a pair that spans the whole range is returned as the single element of the collection.
		 * If the range can't be split up evenly, the last span will be shorter than all the other spans.
		*/
		static void partition(int start, int end, int size, vector< pair<int,int> >& pairs);

		//outputWeights and biases are expected to be empty.
		void backprop(const Matrix& input, const Matrix& output, vector<Matrix>& outputWeights, vector<Matrix>& outputBiases);
		void updateMiniBatch(const NeuralNetworkData& trainingData, pair<v_int, v_int> limits, double eta); 
		static void addInto(vector<Matrix>& matrices, const vector<Matrix>& delta) throw(invalid_argument);
	
		//zs and activations are expected to be empty.
		void calculateZsAndActivations(const Matrix& input, vector<Matrix>& zs, vector<Matrix>& activations);
		
	public:
		NeuralNetwork(const vector<int>& layerSizes);
		~NeuralNetwork();

	
		/*
			input is expected to be a rows x 1 matrix. Input to the neural network. 
			Returns the result from the network.
		*/
		Matrix feedForward(const Matrix& input);
		int evaluate(const NeuralNetworkData& data);
		

		inline void SGD(const NeuralNetworkData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta);
		void SGD(const NeuralNetworkData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta, const NeuralNetworkData& testData );		
};

void NeuralNetwork::SGD(const NeuralNetworkData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta)
{
	this->SGD(trainingData, epochs, miniBatchSize, eta, NeuralNetworkData());
}

double sigmoid(double value);
double sigmoidPrime(double value);


#endif
