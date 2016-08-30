#ifndef HANDWRITING_DATA_INPUT_H
#define HANDWRITING_DATA_INPUT_H

#include <string>
#include "Matrix.h"
#include "NeuralNetwork.h"

using std::string;

class HandWritingDataInput : public NeuralNetworkDataLoader
{
	private:
		static unsigned int bytesToInt(unsigned char bytes[] );
	
		unsigned char* imageData;
		unsigned char* labelData;
		
		unsigned int currentImageIndex;
		unsigned int currentLabelIndex;
		
		unsigned int totalItems;
		
		unsigned char* loadFileData(string fileName);
		unsigned int getTotalItems();	

	public:
		HandWritingDataInput(string imageDataFilePath, string labelDataFilePath);
		~HandWritingDataInput();
		
		virtual Matrix getNextInput();
		virtual Matrix getNextOutput();
		virtual bool hasNextInput() const;
		virtual bool hasNextOutput() const;
};

#endif