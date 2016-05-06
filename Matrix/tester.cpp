#include <iostream>
#include <string>
#include "Matrix.h"


using namespace std;

void printMatrix(Matrix* matrix);

int main()
{
	Matrix* matrix = new Matrix(3,4);
	Matrix* matrix2 = new Matrix(4,5);
	
	
	for(int i = 0; i < matrix->getRows(); i++)
	{
		for(int j = 0; j < matrix->getColumns(); j++)
		{
			matrix->setEntry(i,j, i+j);
		}	
	}

	for(int i = 0; i < matrix2->getRows(); i++)
	{
		for(int j = 0; j < matrix2->getColumns(); j++)
		{
			matrix2->setEntry(i,j, i+j);
		}	
	}

	cout << matrix->toString() << endl;
	cout << matrix2->toString() << endl;
	cout << endl;
	Matrix* result = matrix->multiply(matrix2);
	cout << result->toString() << endl;
	cout << endl;

	delete matrix;
	delete matrix2;
	delete result;

	return 0;
}
