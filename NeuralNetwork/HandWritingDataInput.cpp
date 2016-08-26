#include <fstream>
#include "HandWritingDataInput.h"
		
HandWritingDataInput::HandWritingDataInput(string imageDataFilePath, string labelDataFilePath)
{
	this->currentImageIndex = 0;
	this->currentLabelIndex = 0;
		
	this->imageData = this->loadFileData(imageDataFilePath);
	this->labelData = this->loadFileData(labelDataFilePath);

	this->totalItems = this->getTotalItems();
	
	//TODO on destruction, make sure to free memory!
}

unsigned char* HandWritingDataInput::loadFileData(string fileName)
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

unsigned int HandWritingDataInput::getTotalItems()
{
	return bytesToInt(this-imageData + 4);
}

Matrix HandWritingDataInput::getNextInput()
{
	if(!this->hasNextInput)
	{
		throw out_of_range("HandWritingDataInput has no more inputs");
	}

	//Rows x Columns are known in advance to be 28x28
	const int pixels = 28 * 28;
	
	//Skip magic number, number items, rows, columns, and the already calculated image data
	const int imagesSkip = 4 * 4 + (this->currentImageIndex * pixels); 

	Matrix input;
	
	for(int i = imagesSkip; i < (imagesSkip + pixels); i++)
	{
		input(i, 0) = (double)this->imageData[i] / 255.0;
	}

	this->currentImageIndex++;
	
	return input;
}

Matrix HandWritingDataInput::getNextOutput()
{	
	if(!this->hasNextOutput)
	{
		throw out_of_range("HandWritingDataInput has no more outputs");
	}

	//skipping magic number, number of items, items processed
	const int labelsSkip = 4 + 4 + (this->currentLabelIndex);

	Matrix output(10,1);

	output( this->labelData[labelsSkip], 0 ) = 1.0;
	
	this->currentLabelIndex++;
	
	return output;
}

bool HandWritingDataInput::hasNextInput() const 
{
	return this->currentImageIndex < this->totalItems;	
}

Matrix HandWritingDataInput::getNextOutput()
{
	return this->currentLabelIndex < this->totalItems;
}

unsigned int DataInput::bytesToInt(unsigned char input[])
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