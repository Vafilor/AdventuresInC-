#include "Matrix.h"
#include <iostream> //For debugging
using namespace std; //For debugging

Matrix::Matrix(unsigned int rows, unsigned int columns)
{
	double** data = new double*[rows];
	
	for(int i = 0; i < columns; i++) 
	{
		data[i] = new double[columns]; //TODO can you auto initialize dynamic arrays?
		
		for(int j = 0; j < columns; j++) 
		{
			data[i][j] = 0.0;
		}
	}
	
	this->entries = data;
	this->rows = rows;
	this->columns = columns;
}

Matrix::Matrix(Matrix* matrix)
{
	double** data = new double*[matrix->getRows()];
	
	for(int i = 0; i < matrix->getRows(); i++)
	{
		data[i] = new double[matrix->getColumns()];
		
		for(int j = 0; j < matrix->getColumns(); j++)
		{
			data[i][j] = matrix->getEntry(i,j);
		}
	}
	
	this->entries = data;
	this->rows = matrix->getRows();
	this->columns = matrix->getColumns();
}

//TODO make sure all data is dealloced
Matrix::~Matrix()
{
	for(int i = 0; i < this->rows; i++) 
	{
		delete[] this->entries[i];
	}
}

unsigned int Matrix::getRows()
{
	return this->rows;
}

unsigned int Matrix::getColumns()
{
	return this->columns;
}

double Matrix::getEntry(int row, int column)
{
	return this->entries[row][column];
}


void Matrix::setEntry(int row, int column, double value)
{
	this->entries[row][column] = value;
}

Matrix* Matrix::add(Matrix* that)
{
	//TODO - if incompatible sizes, throw exception

	Matrix* copy = new Matrix(this);
	
	for(int i = 0; i < this->getRows(); i++)
	{
		for(int j = 0; j < this->getColumns(); j++)
		{
			copy->setEntry(i, j, this->getEntry(i, j) + that->getEntry(i,j) );
		}
	}	
	
	return copy;	
}

//TODO make sure you mark what's const and what's not
Matrix* Matrix::subtract(Matrix* that)
{
	//TODO - if incompatible sizes, throw exception
	Matrix* temp = that->scale(-1.0);
	Matrix* result = this->add(temp);
	
	delete temp;
	
	return result;
	
	
	//Is there performance penalty vs below?
// 	Matrix* copy = new Matrix(this);
// 	
// 	for(int i = 0; i < this->getRows(); i++)
// 	{
// 		for(int j = 0; j < this->getColumns(); j++)
// 		{
// 			copy->setEntry(i, j, this->getEntry(i, j) - that->getEntry(i,j) );
// 		}
// 	}	
// 	
// 	return copy;	
}

Matrix* Matrix::scale(double scalar)
{
	//TODO - if incompatible sizes, throw exception

	Matrix* copy = new Matrix(this);
	
	for(int i = 0; i < this->getRows(); i++)
	{
		for(int j = 0; j < this->getColumns(); j++)
		{
			copy->setEntry(i, j,  this->getEntry(i, j) * scalar );
		}
	}	
	
	return copy;
}

std::string Matrix::toString()
{
	std::string result = "";
	
	for(int i = 0; i < this->getRows(); i++)
	{
		for(int j = 0; j < this->getColumns(); j++)
		{
			result += std::to_string(this->getEntry(i,j)) + " ";
		}
		
		result += "\n";
	}
	
	return result;
}

//Private Methods
void Matrix::scaleInPlace(double scalar)
{
	for(int i = 0; i < this->getRows(); i++)
	{
		for(int j = 0; j < this->getColumns(); j++)
		{
			this->setEntry(i, j,  this->getEntry(i, j) * scalar );
		}
	}		
}