#include "HandWriting.hpp"
#include <fstream>
#include <string>
#include "Timer.hpp"
#include <iostream>

using namespace std;

HandWriting::HandWriting(string imageDataFilePath, string labelDataFilePath)
{
	unsigned char* imageData = loadFileData(imageDataFilePath);
	unsigned char* labelData = loadFileData(labelDataFilePath);
	
	this->formatAndStoreImageData(imageData);	
	this->formatAndStoreLabelData(labelData);

	this->wrapData();

	delete[] imageData;
	delete[] labelData;
}

HandWriting::~HandWriting()
{
}

unsigned char* HandWriting::loadFileData(string fileName)
{
	ifstream file;
	file.open(fileName, ios::in | ios::binary | ios::ate );
	
	if( !file.is_open() ) 
	{
		throw runtime_error("Could not open file:" + fileName);
	} 

	streampos fileSize = file.tellg();
	
	unsigned char* memoryBlock = new unsigned char[fileSize];
	
	file.seekg(0, ios::beg );
	file.read((char*)memoryBlock, fileSize);
	file.close();

	return memoryBlock;
}

void HandWriting::formatAndStoreImageData(unsigned char* data)
{
	const unsigned int numberOfItems = bytesToInt(data + 4);
	const int rows = bytesToInt(data + 8);
	const int columns = bytesToInt(data + 12);
	
	const int imagesSkip = 4 * 4; //Skip magic number, number items, rows, columns
	const int imagesLimit = numberOfItems * rows * columns + imagesSkip;

	const int pixels = rows * columns;

	this->inputs.reserve(numberOfItems);

	for(int i = imagesSkip; i < imagesLimit;)
	{
		//TODO - is there a more efficient way to do this? Aren't I just invoking copy constructor all the time?
		this->inputs.push_back(Matrix(pixels, 1));

		for(int j = 0; j < pixels; j++, i++)
		{
			this->inputs.back()(j, 0) = (double)data[i] / 255.0;
		}
	}
}

void HandWriting::formatAndStoreLabelData(unsigned char* data)
{
	unsigned int numberOfItems = bytesToInt(data + 4);
	
	const int labelsSkip = 4 + 4; //skipping magic number, number of items
	const int labelsLimit = numberOfItems + labelsSkip;

	this->outputs.reserve(numberOfItems);

	for(int i = labelsSkip; i < labelsLimit; i++)
	{
		this->outputs.push_back(Matrix(10,1));
			
		this->outputs.back()(data[i], 0) = 1.0;
	}
}

unsigned int HandWriting::bytesToInt(unsigned char input[])
{
	//Assumed char is 4 bytes
	unsigned int result = 0;
	
	for(int i = 0; i < 4; i++)
	{
		result += input[i] << ( (3 - i) * 8 );
	}
	
	return result;
}
