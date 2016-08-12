#include <iostream>
#include "Timer.h"

using namespace std;

double& accessSingleArray(double array[], int columns, int row, int column);
double& accessDoubleArray(double** array, int row, int column);
void testSingleArray(int rows, int columns, int cycles);
void testDoubleArray(int rows, int columns, int cycles);

int main(int argc, char* argv[])
{
	if( argc != 4 )
	{
		cout << "Usage: rows columns cycles\n";
		return 0;
	}

	int rows = atoi(argv[1]);
	int columns = atoi(argv[2]);
	int cycles = atoi(argv[3]);

	Timer timer;

	timer.mark("Single Array");
	testSingleArray(rows, columns, cycles);
	timer.mark();

	timer.mark("Double Array");
	testDoubleArray(rows, columns, cycles);
	timer.mark();	
	
	cout << timer;
}

double& accessSingleArray(double array[], int columns, int row, int column)
{
	return array[(row * columns) + column];
}

double& accessDoubleArray(double** array, int row, int column)
{
	return array[row][column];
}

void testSingleArray(int rows, int columns, int cycles)
{
	double* array = new double[rows * columns];

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			accessSingleArray(array, columns, i, j) = 0.0;
		}
	}

	for(int cycle = 0; cycle < cycles; cycle++)
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				accessSingleArray(array, columns, i, j);
			}
		}
	}
}

void testDoubleArray(int rows, int columns, int cycles)
{
	double** array = new double*[rows];

	for(int i = 0; i < rows; i++)
	{
		array[i] = new double[columns];

		for(int j = 0; j < columns; j++)
		{
			accessDoubleArray(array, i, j) = 0.0;
		}
	}

	for(int cycle = 0; cycle < cycles; cycle++)
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				accessDoubleArray(array, i, j);
			}
		}
	}
}
