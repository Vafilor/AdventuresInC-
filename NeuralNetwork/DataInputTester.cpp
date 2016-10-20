//DataInputTester.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <string>
#include <unordered_map>

#include "Matrix.h"
#include "NeuralNetwork.h"
#include "HandWriting.h"
#include "Timer.h"
#include "HandWritingDataInput.h"

using namespace std;

//TODO allow exiting from any command, maybe make a menu class? A menu is composed of menus?
//TODO output what's going on at any time  - e.g. failed to load file, could not load key of file, etc.

class TrainingParameters
{
	private:
		unsigned int epochs;
		unsigned int miniBatchSize;
		double eta;
		
	public:
		TrainingParameters(unsigned int epochs = 0, unsigned int miniBatchSize = 0, double eta = 0.0);
		
		unsigned int getEpochs() const;
		unsigned int getMiniBatchSize() const;
		double getEta() const;
		
		friend istream& operator>>(istream& input, TrainingParameters& trainingParameters);
		friend ostream& operator<<(ostream& output, const TrainingParameters& trainingParameters);
};

TrainingParameters::TrainingParameters(unsigned int epochs, unsigned int miniBatchSize, double eta)
{
	this->epochs = epochs;
	this->miniBatchSize = miniBatchSize;
	this->eta = eta;
}

unsigned int TrainingParameters::getEpochs() const
{
	return this->epochs;
}

unsigned int TrainingParameters::getMiniBatchSize() const
{
	return this->miniBatchSize;
}

double TrainingParameters::getEta() const
{
	return this->eta;
}

istream& operator>>(istream& input, TrainingParameters& trainingParameters)
{
	input >> trainingParameters.epochs;
	input >> trainingParameters.miniBatchSize;
	input >> trainingParameters.eta;
	
	return input;
}

ostream& operator<<(ostream& output, const TrainingParameters& trainingParameters)
{
	output << trainingParameters.getEpochs() << " ";
	output << trainingParameters.getMiniBatchSize() << " ";
	output << trainingParameters.getEta();
	
	return output;
}

enum MenuChoice 
{
	LoadDataFilePaths = 1,
	Create,
	Load,
	Save,
	TrainWithoutUpdates,
	TrainWithUpdates,
	Evaluate,
	Quit
};

/*
 * Prints the options to interact with a NeuralNetwork, and returns a user's choice. 
 */
MenuChoice printMenu();

string getDataPathFileName();
void loadDataFilePaths(string fileName, string& inputTraining, string& outputTraining, string& inputTesting, string& outputTesting);

NeuralNetwork createNeuralNetwork();
NeuralNetwork loadNeuralNetwork();
void evaluateNeuralNetwork(string inputTestingPath, string outputTestingPath);
void trainWithoutUpdates(NeuralNetwork& neuralNetwork, const string& inputTraining, const string& outputTraining);
void trainWithUpdates(NeuralNetwork& neuralNetwork, const string& inputTraining, const string& outputTraining, const string& inputTesting, const string& outputTesting);
void saveNeuralNetwork(const NeuralNetwork& neuralNetwork);
void evaluateNeuralNetwork(const NeuralNetwork& neuralNetwork, const string& inputTestingPath, const string& outputTestingPath);


//Look through file for keys and set values.
//TODO - rename this to ImageData tester or similar - this is a specific use of Neural Network. Classes for this purpose are defined in a header 
//and defined - this "controller" makes use of them
int main()
{

	string inputTrainingPath;
	string outputTrainingPath;
	string inputTestingPath;
	string outputTestingPath;
	
	NeuralNetwork neuralNetwork;

	MenuChoice userChoice = printMenu();
	
	while(userChoice != Quit) 
	{
		cout << "|" << userChoice << "|\n";


		
		switch( userChoice )
		{	
			case LoadDataFilePaths:
			{
				string fileName = getDataPathFileName();
				
				try 
				{
					loadDataFilePaths(fileName, inputTrainingPath, outputTrainingPath, inputTestingPath, outputTestingPath);
				} 
				catch( out_of_range& exception ) 
				{
					cerr << "File Path " << exception.what() << " not found in " << fileName << "\n";
				}
				catch( runtime_error& exception)
				{
					cerr << exception.what() << "\n";
				}
								
				break;
			}
			case Create:
			{
				neuralNetwork = createNeuralNetwork();
				break;
			}
			case Load:
			{
				neuralNetwork = loadNeuralNetwork();
				break;
			}
			case Save:
			{
				saveNeuralNetwork(neuralNetwork);
				break;
			}
			case TrainWithoutUpdates:
			{
				trainWithoutUpdates(neuralNetwork, inputTrainingPath, outputTrainingPath);
				break;
			}
			case TrainWithUpdates:
			{
				trainWithUpdates(neuralNetwork, inputTrainingPath, outputTrainingPath, inputTestingPath, outputTestingPath);
				break;
			}
			case Evaluate:
			{
				evaluateNeuralNetwork(neuralNetwork, inputTestingPath, outputTestingPath);
				break;
			}
			default:
				cout << "That is not a valid choice\n";
				break;
		}
		
		userChoice = printMenu();
	}

	return 0;
}

NeuralNetwork loadNeuralNetwork()
{	
	cout << "Enter name of file containing Neural Network data:";
	cin.get();
	
	string fileName;
	
	getline(cin, fileName);
	
	ifstream inputFile(fileName, ios::in);
	
	if(!inputFile.is_open() )
	{
		cout << "Could not open " << fileName << "\n";
		throw runtime_error("Unable to open file " + fileName);
	}
	
	NeuralNetwork network;
	
	inputFile >> network;

	inputFile.close();
	
	return network;
}

NeuralNetwork createNeuralNetwork()
{
	cout << "Number of Layers:";
	
	unsigned int numberOfLayers = 0;
	
	cin >> numberOfLayers;
	
	vector<int> layers;
	
	unsigned int layerSize = 0;
	
	for(unsigned int i = 0; i < numberOfLayers; i++) 
	{
		cout << "Layer " << (i+1);
		
		if(i == 0) 
		{
			cout << " (input)";
		} 
		else if(i == (numberOfLayers - 1))
		{
			cout << " (output)";
		}
		
		cout << ":";
		
		cin >> layerSize;
		cout << "|" << layerSize << "|";
		
		layers.push_back(layerSize);
	}
	
	cout << "Neural Network Created\n";
	
	return NeuralNetwork(layers);
}

MenuChoice printMenu()
{	
	bool repeatMenu = true;
		 
	unsigned short choice = 0;
	
	while( repeatMenu ) 
	{
		cout << "\n"
		 << "-------------Menu----------------\n"
		 << "1. Load Data File Paths From File\n"
		 << "2. Create Neural Network\n"
		 << "3. Load Neural Network from file\n"
		 << "4. Save Neural Network to file\n"
		 << "5. Train Neural Network without updates\n"
		 << "6. Train Neural Network with updates\n"
		 << "7. Evaluate Neural Network\n"
		 << "8. Quit\n"
		 << "\n"
		 << "Choice:";
		 
		cin >> choice;
		
		if( choice < 1 || choice > 8 ) 
		{
			cout << "That is not a valid choice\n";
		} else 
		{
			repeatMenu = false;
		}
	}
	
	return (MenuChoice)choice;
}

//TODO make sure to catch exception when calling this!
void loadDataFilePaths(string fileName, string& inputTraining, string& outputTraining, string& inputTesting, string& outputTesting)
{
	ifstream input(fileName);
	
	if(!input.is_open())
	{
		throw runtime_error("Unable to open file " + fileName);
	}
	

	//Read file, and store values into a map, then read values from map. 
	//make sure to close file pointer when done.
	
	string key;
	string value;
	
	unordered_map<string, string> fileLocations;
	
	//TODO does testing input as a boolean cover all error conditions?
	while( input ) 
	{
		input >> key;
		input >> value;
		
		fileLocations[key] = value;
	}
	
	input.close();
	
	inputTraining  = fileLocations.at("inputTraining");
	outputTraining = fileLocations.at("outputTraining");
	inputTesting   = fileLocations.at("inputTesting");
	outputTesting  = fileLocations.at("outputTesting");
}

string getDataPathFileName()
{
	cout << "Enter the name of the file that contains file paths\n"
		 << "File Name:";
		 
	string fileName;
	
	cin.get();
	
	//TODO check errors
	getline(cin, fileName);
	
	return fileName;
}

void trainWithUpdates(NeuralNetwork& neuralNetwork, const string& inputTraining, const string& outputTraining, const string& inputTesting, const string& outputTesting)
{	
	try 
	{
		NeuralNetworkData trainingData( HandWritingDataInput(inputTraining, outputTraining) );
		NeuralNetworkData testingData ( HandWritingDataInput(inputTesting, outputTesting) );
		
		TrainingParameters trainingParameters;
		
		cout << "Enter Epochs MiniBatchSize Eta:";
		
		cin >> trainingParameters;
		
		cout << "Training Parameters:";
		cout << trainingParameters;
		
		neuralNetwork.SGD(trainingData, trainingParameters.getEpochs(), trainingParameters.getMiniBatchSize(), trainingParameters.getEta(), testingData);		
		
		cout << "\nDone Training\n";
	}
	catch( runtime_error& exception)
	{
		cerr << exception.what() << "\n";
	}
}

void saveNeuralNetwork(const NeuralNetwork& neuralNetwork)
{
	cout << "Enter File to save to\n"
		 << "(CAREFUL - THIS FILE WILL BE WIPED CLEAN)\n"
		 << "File Name:";
		 
	string fileName;
	
	cin >> fileName;
	
	ofstream output;
	output.open(fileName, ios::trunc);
	
	if(!output.is_open())
	{
		cerr << "Unable to open " << fileName << "\n";
		
		return;
	}
	
	output << neuralNetwork;
	
	output.close();
	
	cout << "Neural Network saved to " << fileName << "\n";
}

void evaluateNeuralNetwork(const NeuralNetwork& neuralNetwork, const string& inputTestingPath, const string& outputTestingPath)
{	
	try 
	{
		NeuralNetworkData testingData( HandWritingDataInput(inputTestingPath, outputTestingPath) );
		
		int numberCorrect = neuralNetwork.evaluate(testingData);
		int totalData = testingData.size();
		
		cout << "Neural Network:" << numberCorrect << "/" << totalData << "\n";
	}
	catch( runtime_error& exception )
	{
		cerr << exception.what() << "\n";
	}
}

void trainWithoutUpdates(NeuralNetwork& neuralNetwork, const string& inputTraining, const string& outputTraining)
{
	try 
	{
		NeuralNetworkData trainingData( HandWritingDataInput(inputTraining, outputTraining) );
		
		TrainingParameters trainingParameters;
		
		cout << "Enter Epochs MiniBatchSize Eta:";
		
		cin >> trainingParameters;
		
		cout << "Training Parameters:";
		cout << trainingParameters;
		
		neuralNetwork.SGD(trainingData, trainingParameters.getEpochs(), trainingParameters.getMiniBatchSize(), trainingParameters.getEta());		
		
		cout << "\nDone Training\n";
	}
	catch( runtime_error& exception)
	{
		cerr << exception.what() << "\n";
	}
}
