#include <iostream>
#include <string>
#include "Matrix.h"


using namespace std;

void printMatrix(Matrix* matrix);

int main()
{
	Matrix* matrix = new Matrix(2,2);
	Matrix* matrix2 = new Matrix(2,2);
	
	cout << "sizeof(Matrix) " << sizeof(matrix) << endl;
	Matrix matrix3 = *matrix + *matrix2;

	Matrix* matrix3Copy = &matrix3;

	delete matrix;
	delete matrix2;



	return 0;
}
