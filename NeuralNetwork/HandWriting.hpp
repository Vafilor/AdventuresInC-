//Implement training data class (also rename the parent first)
//This class will load the data from a file. The types are specific - labels vs image data. The amount of data is not specific 
//e.g. 10,000 images? 60,0000? How many rows x columns? 

#include "NeuralNetwork.hpp"
#include <string>

#ifndef HAND_WRITING_H
#define HAND_WRITING_H

class HandWriting : public NeuralNetworkData
{
	private:
		static unsigned char* loadFileData(string fileName);
		static unsigned int bytesToInt(unsigned char[] bytes);
		
		void formatAndStoreLabelData(unsigned char* data);
		void formatAndStoreImageData(unsigned char* data);
		
	public:
		HandWriting(string imageDataFilePath, string labelDataFilePath);
		~HandWriting();
};

#endif