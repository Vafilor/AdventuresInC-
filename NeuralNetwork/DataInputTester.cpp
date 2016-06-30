//DataInputTester.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>

#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
#include "HandWriting.hpp"
#include "Timer.hpp"

using namespace std;



//TODO - rename this to ImageData tester or similar - this is a specific use of Neural Network. Classes for this purpose are defined in a header 
//and defined - this "controller" makes use of them
int main()
{
	string labelTrainingPath = "";
	string imageTrainingPath = "";
	string imageTestingPath = "";
	string labelTestingPath = "";
		
	Timer timer;
	
	timer.mark("Load Data");
		
	HandWriting trainingData(imageTrainingPath, labelTrainingPath);
	HandWriting testingData(imageTestingPath, labelTestingPath);
	
	timer.mark();
	
	
	vector<int> neurons;
	neurons.push_back(28*28);
	neurons.push_back(10);
	neurons.push_back(10);
	
	NeuralNetwork network(neurons);
	
	
	timer.mark("Net Training");
	
// 	network.SGD(trainingData, 1, 10, 1.0, testData );		

	timer.mark();
	
	cout << timer << endl;
	
	return 0;
}
