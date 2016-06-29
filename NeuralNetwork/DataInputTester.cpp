//DataInputTester.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
#include <stdexcept>
#include "Timer.hpp"

using namespace std;

void labelsToMatrices(vector<Matrix>& labels, vector<unsigned char> bytes);
void imagesToMatrices(vector<Matrix>& images, vector<unsigned char> bytes);
void loadLabelsData(vector<Matrix>& labelData, string labelsFilePath);
void loadImagesData(vector<Matrix>& imageData, string imagesFilePath);
void loadData(vector<Matrix>& labelData, vector<Matrix>& imageData, string trainingImagesFilePath, string trainingLabelsFilePath);
unsigned int bytesToInt(unsigned char input[]); //TODO built in function?

//TODO next set up test data 
//TODO also set up timer
//TODO setting up data is currently slow. We create the data, convert it, then copy it to training data class, then format it there.
//Need to look into ways to speed it up - less copying.

int main()
{
	string labelTrainingPath = "";
	string imageTrainingPath = "";
	
	vector<Matrix> labelData;
	vector<Matrix> imageData;
	
	Timer timer;
	
	timer.mark("Load Data");
		
	loadData(labelData, imageData, imageTrainingPath, labelTrainingPath);
	
	timer.mark();
	
	timer.mark("Convert to NeuralTrainingData");
	
	vector<Matrix> labelTrainingData(labelData.begin(), labelData.end() - 10000);
	vector<Matrix> imageTrainingData(imageData.begin(), imageData.end() - 10000);
	
	vector<Matrix> labelTestData(labelData.begin() + 50000, labelData.end());
	vector<Matrix> imageTestData(imageData.begin() + 50000, imageData.end());
	
	cout << "Label Training Data:" << labelTrainingData.size() << endl;
	cout << "Image Training Data:" << imageTrainingData.size() << endl;
	
	cout << "Label Test Data:" << labelTestData.size() << endl;
	cout << "Image Test Data:" << imageTestData.size() << endl;
	
	NeuralTrainingData trainingData(imageData, labelData);
	NeuralTrainingData testData(imageTestData, labelTestData);
	
	timer.mark();
	
	vector<int> neurons;
	neurons.push_back(28*28);
	neurons.push_back(10);
	neurons.push_back(10);
	
	NeuralNetwork network(neurons);
	
	
	timer.mark("Net Training");
	
	network.SGD(trainingData, 10, 10, 1.0, testData );		

	timer.mark();
	
	cout << timer << endl;
	
	return 0;
}


void loadLabelsData(vector<Matrix>& labelData, string labelsFilePath)
{
	ifstream file;
	file.open(labelsFilePath, ios::in | ios::binary | ios::ate );
	
	if( !file.is_open() ) 
	{
		throw runtime_error("Could not open trainingLabelsFile:" + labelsFilePath);
	} 

	streampos fileSize = file.tellg();
	
	unsigned char* memoryBlock = new unsigned char[fileSize];
	
	file.seekg(0, ios::beg );
	file.read((char*)memoryBlock, fileSize);
	file.close();

	unsigned int numberOfItems = bytesToInt(memoryBlock + 4);
	
	const int labelsSkip = 4 + 4; //skipping magic number, number of items
	const int labelsLimit = numberOfItems + labelsSkip;

	for(int i = labelsSkip; i < labelsLimit; i++)
	{
		Matrix newMatrix(10, 1);
		
		newMatrix(memoryBlock[i], 0) = 1.0;
		
		labelData.push_back( newMatrix );
	}
	
	cout << "Finished Loading Label Data. Size = " << labelData.size() << endl;

	delete[] memoryBlock;
}

void loadImagesData(vector<Matrix>& imageData, string imagesFilePath)
{
	ifstream file;
	file.open(imagesFilePath, ios::in | ios::binary | ios::ate );
	
	if( !file.is_open() ) 
	{
		throw runtime_error("Could not open imagesFilePath:" + imagesFilePath);
	} 

	streampos fileSize = file.tellg();
	
	unsigned char* memoryBlock = new unsigned char[fileSize];
	
	file.seekg(0, ios::beg );
	file.read((char*)memoryBlock, fileSize);
	file.close();

	const unsigned int numberOfItems = bytesToInt(memoryBlock + 4);
	const int rows = bytesToInt(memoryBlock + 8);
	const int columns = bytesToInt(memoryBlock + 12);
	
	const int imagesSkip = 4 * 4; //Skip magic number, number items, rows, columns
	const int imagesLimit = numberOfItems * rows * columns + imagesSkip;

	const int pixels = rows * columns;

	for(int i = imagesSkip; i < imagesLimit;)
	{
		//TODO - is there a more efficient way to do this? Aren't I just invoking copy constructor all the time?
		Matrix newMatrix(pixels, 1);
	
		for(int j = 0; j < pixels; j++, i++)
		{
			newMatrix(j, 0) = memoryBlock[i];
		}
				
		imageData.push_back(newMatrix);
	}
	
	cout << "Finished Loading Image Data. Size = " << imageData.size() << endl;

	delete[] memoryBlock;
}

void loadData(vector<Matrix>& labelData, vector<Matrix>& imageData, string trainingImagesFilePath, string trainingLabelsFilePath)
{	
	loadLabelsData(labelData, trainingLabelsFilePath);	
	loadImagesData(imageData, trainingImagesFilePath);
}


unsigned int bytesToInt(unsigned char input[])
{
	//char has length of 4 - assumed
	
	unsigned int result = 0;
	
	for(int i = 0; i < 4; i++)
	{
	//TODO remove commentary
		std::cout << "Input[" << i << "]:" << (int)input[i] << endl;
		result += input[i] << ( (3 - i) * 8 );
	}
	
	return result;
}
