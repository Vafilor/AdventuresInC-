#include "HandWriting.hpp"
#include <ifstream>

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

unsigned char* HandWriting::loadFileData(string fileName)
{
	ifstream file;
	file.open(labelsFilePath, ios::in | ios::binary | ios::ate );
	
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

	for(int i = imagesSkip; i < imagesLimit;)
	{
		//TODO - is there a more efficient way to do this? Aren't I just invoking copy constructor all the time?
		Matrix newMatrix(pixels, 1);
	
		for(int j = 0; j < pixels; j++, i++)
		{
			newMatrix(j, 0) = data[i];
		}
				
		this->inputs.push_back(newMatrix);
	}
}

void HandWriting::formatAndStoreLabelData(unsigned char* data)
{
	unsigned int numberOfItems = bytesToInt(data + 4);
	
	const int labelsSkip = 4 + 4; //skipping magic number, number of items
	const int labelsLimit = numberOfItems + labelsSkip;

	for(int i = labelsSkip; i < labelsLimit; i++)
	{
		Matrix newMatrix(10, 1);
		
		newMatrix(data[i], 0) = 1.0;
		
		//TODO - maybe pointer to matrix to avoid duplication?
		this->outputs.push_back(newMatrix);
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