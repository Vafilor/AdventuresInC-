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
//TODO rename to NeuralNetworkData - as it can be both test or training data.
class NeuralTrainingData
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

		vector<Matrix> inputs;
		vector<Matrix> outputs;
		vector<Datum> wrappedData;
		
	public:
		NeuralTrainingData();
		NeuralTrainingData(const vector<Matrix>& inputs, const vector<Matrix>& outputs);
		~NeuralTrainingData();

		const Datum& operator[](int i) const { return this->wrappedData[i]; };
		const vector<Matrix>& getInputs() const { return this->inputs; };
		const vector<Matrix>& getOutputs() const { return this->outputs; };	
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
		void updateMiniBatch(const NeuralTrainingData& trainingData, pair<v_int, v_int> limits, double eta); 
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
		int evaluate(const NeuralTrainingData& data);
		

		inline void SGD(const NeuralTrainingData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta);
		void SGD(const NeuralTrainingData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta, const NeuralTrainingData& testData );		
};

void NeuralNetwork::SGD(const NeuralTrainingData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta)
{
	this->SGD(trainingData, epochs, miniBatchSize, eta, NeuralTrainingData());
}

double sigmoid(double value);
double sigmoidPrime(double value);


#endif
