//DataInputTester.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>

#include "Matrix.h"
#include "NeuralNetwork.h"
#include "HandWriting.h"
#include "Timer.h"
#include "HandWritingDataInput.h"

using namespace std;


//TODO - rename this to ImageData tester or similar - this is a specific use of Neural Network. Classes for this purpose are defined in a header 
//and defined - this "controller" makes use of them
int main(int argc, char* argv[])
{
	if(argc < 5) 
	{
		cout << "Expected \"Label Training File Path\", \"Image Training Path\", \"Image Testing Path\", \"Label Testing Path\"\n";
		return 1;
	}
	
	string labelTrainingPath = argv[1];
	string imageTrainingPath = argv[2];
	string imageTestingPath = argv[3];
	string labelTestingPath = argv[4];
		
	Timer timer;
	timer.setVerbose(true, &cout);
	
	timer.mark("Load Data");
	
	NeuralNetworkData trainingData( HandWritingDataInput(imageTrainingPath, labelTrainingPath) );
	NeuralNetworkData testingData ( HandWritingDataInput(imageTestingPath, labelTestingPath) );
	
	timer.mark();
	
	vector<int> neurons;
	neurons.push_back(28*28);
	neurons.push_back(10);
	neurons.push_back(10);
	
	NeuralNetwork network(neurons);	
	
	timer.mark("Net Training");
		
	network.SGD(trainingData, 30, 10, 3.0, testingData );		

	timer.mark();

	cout << "Program Done" << endl;	 
	
	return 0;
}
