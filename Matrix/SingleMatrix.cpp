//Matrix.cpp
//By Andrey Melnikov

#include "Matrix.h"
#include <stdexcept>
#include <iostream> //For debugging
#include <string>
using namespace std; //For debugging

Matrix::Matrix() : Matrix(0,0)
{
}

Matrix::Matrix(unsigned int rows, unsigned int columns) : Matrix(rows, columns, [](unsigned int i, unsigned int j) { return 0.0; } )
{
}

Matrix::Matrix(const Matrix& that)
{
	this->rows = that.rows;
	this->columns = that.columns;

	if(that.isZeroMatrix())
	{
		this->entries = nullptr;
	}
	else 
	{
		this->entries = new double[ that.length() ];
		
		for(int i = 0; i < that.length(); i++)
		{
			this->entries[i] = that.entries[i];
		}
	}
}

Matrix::Matrix(Matrix&& that)
{
	this->rows = that.rows;
	this->columns = that.columns;
	this->entries = that.entries;

	that.entries = nullptr;
}

Matrix::~Matrix()
{
	this->freeEntriesMemory();
}

void Matrix::freeEntriesMemory()
{
	delete[] this->entries;
}

Matrix Matrix::operator+(const Matrix& that) const
{
	if(this->rows != that.rows || this->columns != that.columns)
	{
		throw invalid_argument("Matrix summation not defined for matrices");
	}

	//TODO - addition is actually simpler - add each entry by entry. 
	//Need to see if can simply do this.
    	return Matrix(this->rows, this->columns, [&](unsigned int i, unsigned int j){ return (*this)(i,j) + that(i,j); });
}

Matrix Matrix::operator*(const Matrix& that) const
{
	if(this->columns != that.rows)
	{
		throw invalid_argument("Matrix Multiplication not defined for incoming matrix");
	}	

	if(this->isZeroMatrix()) 
	{
		return Matrix();
	}

    int newRows = this->getRows();
    int newColumns = that.columns;

    Matrix product( newRows, newColumns );

	if(this->isVector())
	{
		if(this->rows == 1)
		{
			for(int i = 0; i < this->length(); i++)
			{
				product.entries[0] += this->entries[i] * that.entries[i];
			}
		}
		else 
		{
			for(int i = 0; i < newRows; i++)
			{
				for(int j = 0; j < newColumns; j++)
				{
					product(i,j) = this->entries[i] * that.entries[j];
				}
			}
		}
	}
	else if(that.isVector())
	{
		for(int i = 0; i < this->rows; i++)
		{
			for(int j = 0; j < this->columns; j++)
			{
				product.entries[i] += (*this)(i,j) * that.entries[j];
			}
		}
	}
	else 
	{
		double newValue = 0.0;
	
		for(int i = 0; i < newRows; i++) 
		{
			for(int j = 0; j < newColumns; j++)
			{
				for(int k = 0; k < this->getColumns(); k++)
				{
					newValue += (*this)(i,k) * that(k,j);
				}
			
				product(i,j) = newValue;
			
				newValue = 0.0;
			}    
		}
    }
    
    return product;
}

Matrix& Matrix::operator=(const Matrix& that) 
{
	this->freeEntriesMemory();

	this->rows = that.rows;
	this->columns = that.columns;

	if(that.isZeroMatrix())
	{
		this->entries = nullptr;
	} 
	else
	{
		this->entries = new double[ that.length() ];
		
		for(int i = 0; i < that.length(); i++)
		{
			this->entries[i] = that.entries[i];
		}
	} 

	
	return *this;
}

Matrix& Matrix::operator=(Matrix&& that)
{
	this->freeEntriesMemory();

	this->entries = that.entries;
	this->rows = that.rows;
	this->columns = that.columns;
	
	that.entries = nullptr;
	
	return *this;
}

Matrix operator*(const Matrix& that, double scalar)
{
	//TODO - can this be simplified?
	return Matrix(that.rows, that.columns, [&](unsigned int i, unsigned int j) { return that(i,j) * scalar; });
}

bool operator==(const Matrix & a, const Matrix& b)
{
	if(a.rows != b.rows || a.columns != b.columns)
	{
		return false;
	}

	for(int i = 0; i < a.length(); i++)
	{
		if(a.entries[i] != b.entries[i])
		{
			return false;
		}
	}

	return true;
}

std::ostream & operator<<(std::ostream& output, const Matrix& matrix)
{
	output << "[";

	for(int i = 0; i < matrix.rows; i++)
	{
		output << "[";

		for(int j = 0; j < matrix.columns; j++)
		{
			output << matrix(i,j) << " ";
		}

		output << "]\n";
	}
	
	output << "]";

	return output;
}

const Matrix& Matrix::operator*=(double scalar)
{
	for(int i = 0; i < this->length(); i++)
	{
		this->entries[i] *= scalar;
	}
	
	return *this;
}

const Matrix& Matrix::operator+=(const Matrix& that)
{
	if(this->rows != that.rows || this->columns != that.columns)
	{
		throw invalid_argument("Matrix += not defined with incoming matrix");
	}

	for(int i = 0; i < this->length(); i++)
	{
		this->entries[i] += that.entries[i];
	}
	
	return *this;
}

Matrix Matrix::transpose()
{
	return Matrix(this->columns, this->rows, [&](unsigned int i, unsigned int j) { return (*this)(j,i); });
}

Matrix Matrix::multiplyEntries(const Matrix& that) const
{
	if(this->rows != that.rows || this->columns != that.columns)
	{
		throw invalid_argument("multiplyEntry - matrices of incompatible size");
	}

	return Matrix(that.getRows(), that.getColumns(), [&](unsigned int i, unsigned int j) { return (*this)(i,j) * that(i,j); });
}

Matrix Matrix::operator-(const Matrix& that) const
{
	return (*this) + (-that);
}

double& Matrix::operator()(unsigned int row, unsigned int column)
{
	if(row >= this->rows || column >= this->columns) 
	{
		throw invalid_argument("Access out of bounds");
	}

	return this->entries[(row * this->columns) + column];
}

double Matrix::operator()(unsigned int row, unsigned int column) const
{
	if(row >= this->rows || column >= this->columns) 
	{
		throw invalid_argument("Access out of bounds");
	}

	return this->entries[(row * this->columns) + column];
}

unsigned int Matrix::getRows() const 
{	
	return this->rows;
}

unsigned int Matrix::getColumns() const 
{
	return this->columns;
}

Matrix Matrix::operator-() const 
{ 
	return (*this) * -1.0; 
}

const Matrix& Matrix::operator/=(double scalar) 
{
	return (*this) *= 1.0/scalar; 
}

const Matrix& Matrix::operator-=(const Matrix& that)
{
	return (*this) += -that; 
}

Matrix operator*(double scalar, const Matrix& that)
{
	return that * scalar;
}

bool Matrix::isVector() const
{
	return this->rows == 1 || this->columns == 1;
}

unsigned int Matrix::length() const
{
	return this->rows * this->columns;
}

bool Matrix::isZeroMatrix() const
{
	//You can't have a Nx0 or 0xN matrix, so either condition below suffices.
	return this->rows == 0 || this->columns == 0;
}
