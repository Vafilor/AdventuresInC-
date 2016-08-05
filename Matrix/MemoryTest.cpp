//MemoryTest.cpp - runs through a variety of methods and creation of Matrix class.
//To be used by Valgrind to ensure no memory leaks happen.
//This file assumes unit tests have been run so everything is working as intended, with, perhaps, memory leaks.
#include "Matrix.h"
#include <vector>

using namespace std;
//TODO - test constructors, and all operations and methods. True, some shouldn't change memory (eg. getter/setter) but we have no knowledge of internal implementation. Only the interface and we want to make sure that works.

void constructors();
void operatorAddition();
void operatorMultiplication();
void operatorsInto();
void operatorsScalar();
void operatorsFunctions();


int main()
{
	 constructors();
	 operatorAddition();
	 operatorMultiplication();
	 operatorsInto();
	 operatorsScalar();
	 operatorsFunctions();
}

void constructors()
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(2,2);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);
	
	Matrix functionCall(5,5, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	vector<Matrix> matrices;
	matrices.reserve(7);
	
	//Move constructor
	matrices.push_back(zero);
	matrices.push_back(single);
	matrices.push_back(row);
	matrices.push_back(column);
	matrices.push_back(square);
	matrices.push_back(rectangle);
	matrices.push_back(rectangle2);
	
	matrices.clear();
	
	Matrix blank;
	
	//Move Assignment
	blank = Matrix(3,3);
	
	//Copy Constructor
	Matrix rectangleCopy = rectangle;
	
	//Operator assignment
	rectangleCopy = row;
	
	//Setting all to 0 matrix
	single = zero;
	row = Matrix();
	column = Matrix(0,0);
	square = zero;
	rectangle = zero;
	rectangle2 = rectangle = zero;
}

void operatorAddition()
{
}

void operatorMultiplication()
{
}

void operatorsInto()
{
}

void operatorsScalar()
{
}

void operatorsFunctions()
{
}