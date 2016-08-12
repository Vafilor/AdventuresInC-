#include <iostream>
#include "Timer.h"

using namespace std;

double& accessSingleArray(double array[], int columns, int row, int column);
double& accessDoubleArray(double** array, int row, int column);
long long testSingleArray(int rows, int columns, int cycles);
long long testDoubleArray(int rows, int columns, int cycles);

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

	cout << "Rows: " << rows << "\n";
	cout << "Columns: " << columns << "\n";
	cout << "Cycles: " << cycles << "\n";

	Timer timer;

	timer.mark("Single Array");
	long long singleArray = testSingleArray(rows, columns, cycles);
	timer.mark();

	timer.mark("Double Array");
	long long doubleArray = testDoubleArray(rows, columns, cycles);
	timer.mark();	
	
	cout << timer;

	cout << "Single Array Total:" << singleArray << "\n";
	cout << "Double Array Total:" << doubleArray << "\n";
}

double& accessSingleArray(double array[], int columns, int row, int column)
{
	return array[(row * columns) + column];
}

double& accessDoubleArray(double** array, int row, int column)
{
	return array[row][column];
}

long long testSingleArray(int rows, int columns, int cycles)
{
	double* array = new double[rows * columns];

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			accessSingleArray(array, columns, i, j) = 0.0;
		}
	}

	long long totalAccess = 0;

	for(int cycle = 0; cycle < cycles; cycle++)
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				accessSingleArray(array, columns, i, j);
				totalAccess++;
			}
		}
	}

	delete[] array;

	return totalAccess;
}

long long testDoubleArray(int rows, int columns, int cycles)
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

	long long totalAccess = 0;

	for(int cycle = 0; cycle < cycles; cycle++)
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				accessDoubleArray(array, i, j);
				totalAccess++;
			}
		}
	}

	for(int i = 0; i < rows; i++)
	{
		delete[] array[i];
	}

	delete[] array;

	return totalAccess;
}
