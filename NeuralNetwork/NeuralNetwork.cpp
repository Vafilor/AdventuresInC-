#include "NeuralNetwork.hpp"
#include "Matrix.hpp"
#include <cstdlib>
#include <iostream> //For debugging
#include <cmath>


using namespace std;


NeuralNetwork::NeuralNetwork(const vector<int>& layerSizes) //TODO variadic constructor?
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
Matrix NeuralNetwork::feedForward(const Matrix& input)
{	
	Matrix result = input;

    for(int i = 0; i < this->biases.size(); i++)
	{
		result = ((this->weights[i] * result) + this->biases[i]);
		result.applyFunctionInto(sigmoid);
	}

    return result;
}

int NeuralNetwork::evaluate(const vector< pair<const Matrix&, const Matrix& > >& testData)
{
//TODO ensure that the correct length is initially reserved
	vector<int> testResults( testData.size() );
	Matrix result;
	
	for(int i = 0; i < testData.size(); i++)
	{
		result = this->feedForward( testData[i].first );
		
		testResults.push_back( getLargestRow(result) );
	}

	int totalCorrect = 0;

	for(int i = 0; i < testData.size(); i++)
	{
		if( testResults[i] == getNonZeroRow( testData[i].second ) ) 
		{
			totalCorrect++;
		}
	}
	
	return totalCorrect;
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

Matrix NeuralNetwork::costDerivative(const Matrix& outputActivations, const Matrix& output)
{
	return outputActivations - output;
}

unsigned int NeuralNetwork::getLargestRow(const Matrix& matrix)
{
	unsigned int largest = 0;
	
	double largestValue = matrix(largest, 0);
	
	for(int i = 0; i < matrix.getRows(); i++)
	{
		if( matrix(i, 0) > largestValue ) 
		{
			largest = i;
			largestValue = matrix(i, 0);
		}
	}
	
	return largest;
}

int NeuralNetwork::getNonZeroRow(const Matrix& matrix)
{
	for(int i = matrix.getRows() - 1; i >= 0; i--)
	{
		if( matrix(i, 0) > 0.0 )
        {
                return i;
		}
    }

    return -1;
}

