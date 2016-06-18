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

int NeuralNetwork::evaluate(const NeuralTrainingData& data)
{
//TODO ensure that the correct length is initially reserved

	//TODO - can be for each loop - order doesn't matter either.

//	Matrix result;

//	for(int i = 0; i < data.size(); i++)
//	{
//		result = this->feedForward( data[i].input );
//		
//		if( getLargestRow(result) == getNonZeroRow() )	
//	}

//	vector<int> testResults( data.size() );
//	Matrix result;
//	
//	for(int i = 0; i < data.size(); i++)
//	{
//		result = this->feedForward( data[i].first );
//		
//		testResults.push_back( getLargestRow(result) );
//	}

//	int totalCorrect = 0;

//	for(int i = 0; i < testData.size(); i++)
//	{
//		if( testResults[i] == getNonZeroRow( testData[i].second ) ) 
//		{
//			totalCorrect++;
//		}
//	}
//	
//	return totalCorrect;
return 0;
}

//pair<vector<Matrix>, vector<Matrix>> NeuralNetwork::backprop(const Matrix& input, const Matrix& output)
//{
	
	
//        ArrayList<Matrix> nabla_b = this.createBlankCopy(this.biases);
//		ArrayList<Matrix> nabla_w = this.createBlankCopy(this.weights);
//		
//		Pair<ArrayList<Matrix>, ArrayList<Matrix>> zsAndActivations = this.calculateActivations(input);

//		ArrayList<Matrix> zs = zsAndActivations.getFirstElement();
//		ArrayList<Matrix> activations = zsAndActivations.getSecondElement();
//        

//        //Backward pass
//        Matrix delta = this.costDerivative(activations.get(activations.size() - 1), output).
//                            multiplyEntries(
//                                    zs.get(zs.size()-1).
//                                    applyFunction(NeuralNetwork::sigmoidPrime)
//                            );


//        nabla_b.set(nabla_b.size()-1, delta);
//        nabla_w.set(nabla_w.size()-1,  delta.multiply(activations.get(activations.size() - 2).transpose()) );

//        Matrix z = null;
//        Matrix sp = null;

//        for(int i = 2; i < this.sizes.length; i++)
//        {
//            z = zs.get(zs.size() - i);
//            sp = z.applyFunction(NeuralNetwork::sigmoidPrime);

//            delta = this.weights.get(this.weights.size() - i + 1).transpose().multiply(delta).multiplyEntries(sp);
//            nabla_b.set(nabla_b.size() - i, delta);
//            nabla_w.set(nabla_w.size() - i, delta.multiply(activations.get(activations.size() - i - 1).transpose()) );
//        }

//		return new Pair<ArrayList<Matrix>, ArrayList<Matrix>>( nabla_b, nabla_w );
//}

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

void NeuralNetwork::createBlankCopy(vector<Matrix>& matrices, const vector<Matrix> original)
{
	for(int i = 0; i < original.size(); i++)
	{
		matrices.push_back(Matrix( original[i].getRows(), original[i].getColumns() ));
	}
}



NeuralTrainingData::NeuralTrainingData(const vector<Matrix>& inputs, const vector<Matrix>& outputs)
{
	//TODO make sure this is being copied correctly
	this->inputs = inputs;
	this->outputs = outputs;

	for(int i = 0; i < this->inputs.size(); i++)
	{
		this->wrappedData.push_back(Datum(inputs[i], outputs[i]));
	}
}

unsigned int NeuralTrainingData::MatrixWrapper::largestRow() const
{
	unsigned int largest = 0;
	
	double largestValue = this->matrix(largest, 0);
	
	for(int i = 0; i < this->matrix.getRows(); i++)
	{
		if( this->matrix(i, 0) > largestValue ) 
		{
			largest = i;
			largestValue = this->matrix(i, 0);
		}
	}
	
	return largest;
}

int NeuralTrainingData::MatrixWrapper::firstNonZeroRow() const
{
	for(int i = 0; i < this->matrix.getRows(); i++)
	{		
		if( this->matrix(i,0) > 0.0)
		{
			return i;
		}
	}

	return -1;
}

int NeuralTrainingData::MatrixWrapper::lastNonZeroRow() const
{
	for(int i = this->matrix.getRows() - 1; i >= 0; i--)
	{
		if( this->matrix(i, 0) > 0.0 )
        {
                return i;
		}
    }

    return -1;
}

