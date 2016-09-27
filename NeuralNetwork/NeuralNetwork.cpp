#include "NeuralNetwork.h"
#include "Matrix.h"
#include <stdexcept>
#include <cstdlib>
#include <iostream> //For debugging
#include <cmath>
#include <algorithm>
#include <random>
#include "Timer.h"

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
		result.applyFunctionInto(this->sigmoid);
	}

    return result;
}

int NeuralNetwork::evaluate(const NeuralNetworkData& data)
{
	unsigned int totalCorrect = 0;
	Matrix result;
	//TODO - can be for each loop - order doesn't matter either.
	for(int i = 0; i < data.size(); i++)
	{
		result = this->feedForward( data[i].getInput() );

		if( NeuralNetwork::getLargestRow(result) == NeuralNetwork::getLastNonZeroRow(data[i].getOutput()) )
		{
			totalCorrect++;
		}	
	}

	return totalCorrect;
}

void NeuralNetwork::SGD(const NeuralNetworkData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta)
{
	this->SGD(trainingData, epochs, miniBatchSize, eta, NeuralNetworkData());
}

void NeuralNetwork::SGD(const NeuralNetworkData& trainingData, unsigned int epochs, unsigned int miniBatchSize, double eta, const NeuralNetworkData& testData )		
{	
	vector <pair<int,int> > trainingDataPartition;
    partition(0, trainingData.size(), miniBatchSize, trainingDataPartition);

	Timer timer;
	timer.setVerbose(true, &cout);

	for(int i = 1; i <= epochs; i++)
	{
		random_shuffle(trainingDataPartition.begin(), trainingDataPartition.end() );
		
		timer.mark("Epoch");
		
		for( pair<int,int> subset : trainingDataPartition )
		{
			this->updateMiniBatch(trainingData, subset, eta);
		}
		
		timer.mark();
	
		if(testData.size() > 0)
		{
			cout << "Epoch " << i << "/" << epochs << ": " << this->evaluate(testData) << "/" << testData.size() << " correct." << endl;
		}
	}
}

void NeuralNetwork::backprop(const Matrix& input, const Matrix& output, vector<Matrix>& outputWeights, vector<Matrix>& outputBiases)
{
	createBlankCopy(this->weights, outputWeights);
	createBlankCopy(this->biases, outputBiases);
	
	vector<Matrix> zs;
	vector<Matrix> activations;

	calculateZsAndActivations(input, zs, activations);
	//Backward pass
	Matrix delta = costDerivative( activations.back(), output ).multiplyEntries( zs.back().applyFunction(this->sigmoidPrime) );

	outputBiases.back() = delta;
	outputWeights.back() = delta * ( activations[ activations.size() - 2 ].transpose() );

	Matrix sp;

	for(v_int i = 2; i < this->sizes.size(); i++)
	{
		sp = (zs[zs.size() - i]).applyFunction(this->sigmoidPrime);
		
		delta = (this->weights[this->weights.size() - i + 1].transpose() * delta).multiplyEntries(sp);
		outputBiases[outputBiases.size() - i] = delta;
		outputWeights[outputWeights.size() - i] = delta * ( activations[activations.size() - i - 1].transpose() ); 
	}
}

void NeuralNetwork::partition(int start, int end, int size, vector <pair<int,int> >& pairs)
{
	pairs.clear();

	int endOfRange = 0;
	
	for(int i = start; i < end; i += size)
	{
		endOfRange = i + size;
		
		if(endOfRange > end)
		{
			endOfRange = end;
		}

		pairs.push_back( pair<int,int>(i, endOfRange) );
	}
}

Matrix NeuralNetwork::gaussianDistribution(unsigned rows, unsigned columns)
{
	default_random_engine generator;
	normal_distribution<double> distribution(0.0, 1.0);

	Matrix matrix(rows, columns);

	double value = 0.0;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			value = distribution(generator);
			matrix(i, j) = value;
		}
	}	

	return matrix;
}

Matrix NeuralNetwork::costDerivative(const Matrix& outputActivations, const Matrix& output)
{
	return outputActivations - output;
}

void NeuralNetwork::addInto(vector<Matrix>& matrices, const vector<Matrix>& delta)
{
	if(matrices.size() != delta.size())
	{
		throw invalid_argument("AddInto - different size of matrix lists");
	}

	for(vector<Matrix>::size_type i = 0; i < matrices.size(); i++)
	{
		matrices[i] += delta[i];
	}
}

void NeuralNetwork::updateMiniBatch(const NeuralNetworkData& trainingData, pair<v_int, v_int> limits, double eta)
{
	vector<Matrix> nabla_b;
	vector<Matrix> delta_nabla_b;
	vector<Matrix> nabla_w;
	vector<Matrix> delta_nabla_w;

	createBlankCopy(this->biases, nabla_b);
	createBlankCopy(this->weights, nabla_w);


	for(v_int i = limits.first; i < limits.second; i++)
	{
		this->backprop(trainingData[i].getInput(), trainingData[i].getOutput(), delta_nabla_w, delta_nabla_b);
	
		addInto(nabla_b, delta_nabla_b);
		addInto(nabla_w, delta_nabla_w);

		delta_nabla_b.clear();
		delta_nabla_w.clear();
	}

	v_int limitRange = limits.second - limits.first;
	
	double learningScale = eta / limitRange;

	for( m_int i = 0; i < this->weights.size(); i++) 
	{
		this->weights[i] -= nabla_w[i] * learningScale;
	}

	for( m_int i = 0; i < this->biases.size(); i++)
	{
		this->biases[i] -= nabla_b[i] * learningScale;
	}
}

void NeuralNetwork::createBlankCopy(const vector<Matrix> original, vector<Matrix>& destination)
{
	destination.clear();
	destination.reserve(original.size());

	for(int i = 0; i < original.size(); i++)
	{
		destination.push_back(Matrix( original[i].getRows(), original[i].getColumns() ));
	}
}

void NeuralNetwork::calculateZsAndActivations(const Matrix& input, vector<Matrix>& zs, vector<Matrix>& activations)
{
	zs.clear();
	activations.clear();
	
	zs.reserve(this->biases.size());
	activations.reserve(this->biases.size());

	Matrix z;
	Matrix activation = input;

	activations.push_back(activation);

	for(m_int i = 0; i < this->biases.size(); i++)
	{
		z = (this->weights[i] * activation) + this->biases[i];
		zs.push_back(z);

		activation = z.applyFunction(this->sigmoid);
	
		activations.push_back(activation);	
	}
}

NeuralNetworkData::Datum::Datum(Matrix&& inputData, Matrix&& outputData)
{				
	this->input = std::move(inputData);
	this->output = std::move(outputData);
}

NeuralNetworkData::Datum::Datum(Datum&& that)
{
	this->input = std::move(that.input);
	this->output = std::move(that.output);
}

NeuralNetworkData::NeuralNetworkData()
{
}

NeuralNetworkData::NeuralNetworkData(NeuralNetworkDataLoader&& dataLoader)
{
	while(dataLoader.hasNextInput())
	{
		this->wrappedData.push_back( Datum(dataLoader.getNextInput(), dataLoader.getNextOutput()) );
	}
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


int NeuralNetwork::getLastNonZeroRow(const Matrix& matrix)
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

ostream& operator<<(ostream& os, NeuralNetwork& network)
{
	os << "Weights" << endl << endl;

	for(Matrix& matrix : network.weights)
	{
		os << matrix << endl << endl;
	}

	os << "Biases" << endl << endl;

	for(Matrix& matrix : network.biases)
	{
		os << matrix << endl << endl;
	}

	return os;
}


double sigmoid(double value)
{
	return 1.0 / ( 1.0 + exp(-value) );
}

double Sigmoid::operator()(double value)
{
	return sigmoid(value);
}

double SigmoidPrime::operator()(double value)
{
	
	return sigmoid(value) * (1.0 - sigmoid(value) );
}
