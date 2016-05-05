#include <iostream>
#include <string>
#include "Matrix.h"


using namespace std;

void printMatrix(Matrix* matrix);

int main()
{
	Matrix* matrix = new Matrix(3,4);
	
	
	for(int i = 0; i < matrix->getRows(); i++)
	{
		for(int j = 0; j < matrix->getColumns(); j++)
		{
			matrix->setEntry(i,j, i+j);
		}	
	}

	cout << matrix->toString() << endl;

	Matrix* temp = matrix->scale(10);

	cout << temp->toString() << endl;
	
	Matrix* sum = matrix->subtract(temp);
	
	cout << sum->toString() << endl;

	cout << endl;

	//delete matrix;

	return 0;
}
