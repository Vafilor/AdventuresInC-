#include "NeuralNetwork.hpp"
#include "Matrix.hpp"
#include <cstdlib>
#include <iostream> //For debugging
#include <cmath>


using namespace std;

NeuralNetwork::NeuralNetwork(vector<int> layerSizes) //TODO variadic constructor?
{
	for(int i = 0; i < layerSizes.size(); i++)
	{
		this->sizes.push_back(layerSizes[i]); //TODO deep copy instead? STL?
	}

	for(int i = 1; i < this->sizes.size(); i++)
	{
		this->biases.push_back( this->gaussianDistribution(this->sizes[i], 1 ) );
	}

    for (int i = 0; i < this->sizes.size() - 1; i++)
    {
		this->weights.push_back( this->gaussianDistribution( this->sizes[i + 1], this->sizes[i] ) );
    }
}

NeuralNetwork::~NeuralNetwork()
{
	this->biases.clear();
	this->weights.clear();
}


//TODO note exceptions thrown
Matrix NeuralNetwork::feedForward(Matrix input)
{	
	Matrix result = input;

    for(int i = 0; i < this->biases.size(); i++)
	{
		result = ((this->weights[i] * result) + this->biases[i]);
		result.applyFunctionInto(sigmoid);
	}

    return result;



	//TODO problem area
	//for(int i = 0; i < this->biases.size(); i++)
	//{
	//	cout << "Input:\n" << input->toString() << endl;
	//	cout << "Weights:\n" << this->weights[i]->toString() << endl;
	//	input = (*this->weights[i]) * (*input);

	//}

//	return input;

        //for b, w in zip(self.biases, self.weights):
        //    a = sigmoid(np.dot(w, a)+b)
        //return a
}

double sigmoid(double value)
{
	return 1.0 / ( 1.0 + exp(-value) );
}

double sigmoidPrime(double value)
{
	return sigmoid(value) * (1.0 - sigmoid(value) );
}

Matrix NeuralNetwork::gaussianDistribution(unsigned rows, unsigned columns)
{
	Matrix matrix(rows, columns);

	double value = 0.0;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			value = 2;//(double)rand() / (double)RAND_MAX;
			matrix(i, j) = value;
		}
	}	

	return matrix;
}
