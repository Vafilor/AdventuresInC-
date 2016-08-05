//MemoryTest.cpp - runs through a variety of methods and creation of Matrix class.
//To be used by Valgrind to ensure no memory leaks happen.
//This file assumes unit tests have been run so everything is working as intended, with, perhaps, memory leaks.
#include "Matrix.h"
#include <vector>

using namespace std;

void constructors();
void operatorAddition();
void operatorMultiplication();
void operatorsInto();
void operatorsScalar();
void operatorsFunctions();
void getters();
void setters();

int main()
{
	 constructors();
	 operatorAddition();
	 operatorMultiplication();
	 operatorsScalar();
	 operatorsFunctions();
	 getters();
	 setters();	 
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
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(2,2);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);
	
	zero + zero;
	zero += zero;
	
	single + single;
	single += single;
	
	row + row;
	row += row;
	
	column + column;
	column += column;
	
	square + square;
	square += square;
	
	rectangle + rectangle;
	rectangle += rectangle;
	
	rectangle2 + rectangle2;
	rectangle2 += rectangle2;
}

void operatorMultiplication()
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(2,2);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);
	
	zero * zero;
	single * single;
	
	row * column;
	column * row;
	
	square * square;
	
	rectangle * rectangle2;
	rectangle2 * rectangle;
}

void operatorsScalar()
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(2,2);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);
	
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
	
	for(Matrix& matrix : matrices) 
	{
		matrix *= 1.0;
		matrix *= 2.2;
		matrix /= 1.0;
		matrix /= 5.3;
	}
	
	matrices.clear();
}

void operatorsFunctions()
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(2,2);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);
	
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
	
	for(Matrix& matrix : matrices) 
	{
		matrix.applyFunction( [](double entry){
			return entry * entry;
		});
		
		matrix.applyFunctionInto( [](double entry){
			return entry * entry;
		});
	}
	
	matrices.clear();
}

void getters()
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(2,2);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);
	
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
	
	for(Matrix& matrix : matrices) 
	{
		for(int row = 0; row < matrix.getRows(); row++)
		{
			for(int column = 0; column < matrix.getColumns(); column++)
			{
				double result = matrix(row, column);
			}
		}
	}
	
	matrices.clear();
}

void setters()
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(2,2);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);
	
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
	
	for(Matrix& matrix : matrices) 
	{
		for(int row = 0; row < matrix.getRows(); row++)
		{
			for(int column = 0; column < matrix.getColumns(); column++)
			{
				matrix(row, column) = 0.245;
			}
		}
	}
	
	matrices.clear();
}