//Matrix.cpp
//By Andrey Melnikov

#include "Matrix.h"
#include <stdexcept>
#include <iostream> //For debugging
#include <string>
using namespace std; //For debugging

//Update Matrix to be smart enough to detect mx1 or 1xm
//TODO update matrix so we can detect 0x0
// ->add method to detect 0x0?

Matrix::Matrix()
{
	this->entries = nullptr;
	this->rows = 0;
	this->columns = 0;
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
		this->vectorEntries = nullptr;
		this->entries = nullptr;
	}
	else if(that.isVector()) 
	{
		this->vectorEntries = new double[ that.vectorSize() ];
		
		for(int i = 0; i < that.vectorSize(); i++)
		{
			this->vectorEntries[i] = that.vectorEntries[i];
		}
	} 
	else 
	{
		this->entries = new double*[this->rows];
	
		for(int i = 0; i < this->rows; i++)
		{
			this->entries[i] = new double[this->columns];

			for(int j = 0; j < this->columns; j++)
			{
				this->entries[i][j] = that.entries[i][j];
			}
		}
	}
}

Matrix::Matrix(Matrix&& that)
{
	this->vectorEntries = that.vectorEntries;
	this->entries = that.entries;
	this->rows = that.rows;
	this->columns = that.columns;
	
	that.entries = nullptr;
	that.vectorEntries = nullptr;
}

Matrix::~Matrix()
{
	this->freeEntriesMemory();
}

void Matrix::freeEntriesMemory()
{
	if(this->isZeroMatrix())
	{
		return;
	}

	if(this->isVector()) 
	{
		if(this->vectorEntries == nullptr)
		{
			return;
		}
		
		delete[] this->vectorEntries;
	}
	else 
	{		
		if(this->entries == nullptr)
		{
			return;
		}

		for(int i = 0; i < this->rows; i++) 
		{	
			delete[] this->entries[i];
		}
	
		delete[] this->entries;			
	}
}

Matrix Matrix::operator+(const Matrix& that) const
{
	if(this->rows != that.rows || this->columns != that.columns)
	{
		throw invalid_argument("Matrix summation not defined for matrices");
	}

	if(this->isZeroMatrix())
	{
		return Matrix();
	}

	if(this->isVector()) 
	{
		return Matrix(this->rows, this->columns, [&](unsigned int i, unsigned int j){ return vectorEntries[i + j] + that.vectorEntries[i + j]; });
	}

    return Matrix(this->rows, this->columns, [&](unsigned int i, unsigned int j){ return entries[i][j] + that.entries[i][j]; });
}

//TODO
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
			for(int i = 0; i < this->vectorSize(); i++)
			{
				product.vectorEntries[0] += this->vectorEntries[i] * that.vectorEntries[i];
			}
		}
		else 
		{
			for(int i = 0; i < newRows; i++)
			{
				for(int j = 0; j < newColumns; j++)
				{
					product.entries[i][j] = this->vectorEntries[i] * that.vectorEntries[j];
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
				product.vectorEntries[i] += this->entries[i][j] * that.vectorEntries[j];
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
					newValue += this->entries[i][k] * that.entries[k][j];
				}
			
				product.entries[i][j] = newValue;
			
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
		this->vectorEntries = nullptr;
	} 
	else if(that.isVector()) 
	{
		this->vectorEntries = new double[ that.vectorSize() ];
		
		for(int i = 0; i < that.vectorSize(); i++)
		{
			this->vectorEntries[i] = that.vectorEntries[i];
		}
	} 
	else
	{
		this->entries = new double*[this->rows];
	
		for(int i = 0; i < this->rows; i++)
		{
			this->entries[i] = new double[this->columns];

			for(int j = 0; j < this->columns; j++)
			{
				this->entries[i][j] = that.entries[i][j];	
			}
		}
	}
	
	return *this;
}

Matrix& Matrix::operator=(Matrix&& that)
{
	this->freeEntriesMemory();

	this->entries = that.entries;
	this->vectorEntries = that.vectorEntries;
	this->rows = that.rows;
	this->columns = that.columns;
	
	that.entries = nullptr;
	that.vectorEntries = nullptr;
	
	return *this;
}

Matrix operator*(const Matrix& that, double scalar)
{
	if(that.isZeroMatrix())
	{
		return Matrix();
	}

	if(that.isVector())
	{
		if(that.rows > 1)
		{
			return Matrix(that.rows, that.columns, [&](unsigned int i, unsigned int j) { return that.vectorEntries[i] * scalar; });
		}
		
		return Matrix(that.rows, that.columns, [&](unsigned int i, unsigned int j) { return that.vectorEntries[j] * scalar; });
	}
	
	return Matrix(that.rows, that.columns, [&](unsigned int i, unsigned int j) { return that.entries[i][j] * scalar; });
}

bool operator==(const Matrix & a, const Matrix& b)
{
	if(a.rows != b.rows || a.columns != b.columns)
	{
		return false;
	}

	if(a.isZeroMatrix())
	{
		return true;
	}

	if(a.isVector())
	{
		for(int i = 0; i < a.vectorSize(); i++)
		{
			if(a.vectorEntries[i] != b.vectorEntries[i])
			{
				return false;
			}
		}
		
		return true;
	}

	for(int i = 0; i < a.rows; i++)
	{
		for(int j = 0; j < a.columns; j++)
		{
			if(a.entries[i][j] != b.entries[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

std::ostream & operator<<(std::ostream& output, const Matrix& matrix)
{
	if(matrix.isZeroMatrix())
	{
		output << "[]";
		return output;
	}

	if(matrix.isVector())
	{
		for(int i = 0; i < matrix.vectorSize(); i++)
		{
			output << matrix.vectorEntries[i];
			
			if(matrix.rows > 1)
			{
				output << "\n";
			}
			else
			{
				output << " ";
			}
		}
		
		return output;
	}

	for(int i = 0; i < matrix.rows; i++)
	{
		for(int j = 0; j < matrix.columns; j++)
		{
			output << matrix.entries[i][j] << " ";
		}

		output << endl;
	}
	
	return output;
}

const Matrix& Matrix::operator*=(double scalar)
{
	if(this->isZeroMatrix())
	{
		return *this;
	}

	if(this->isVector())
	{
		for(int i = 0; i < this->vectorSize(); i++)
		{
			this->vectorEntries[i] *= scalar;
		}
		
	}
	else 
	{
		for(int i = 0; i < this->rows; i++)
		{
			for(int j = 0; j < this->columns; j++)
			{
				this->entries[i][j] *= scalar;
			}
		}
	}
	
	return *this;
}

const Matrix& Matrix::operator+=(const Matrix& that)
{
	if(this->rows != that.rows || this->columns != that.columns)
	{
		throw invalid_argument("Matrix += not defined with incoming matrix");
	}

	if(this->isZeroMatrix())
	{
		return *this;
	}

	if(this->isVector())
	{
		for(int i = 0; i < this->vectorSize(); i++)
		{
			this->vectorEntries[i] += that.vectorEntries[i];
		}
	}
	else
	{
		for(int i = 0; i < this->rows; i++)
		{
			for(int j = 0; j < this->columns; j++)
			{
				this->entries[i][j] += that.entries[i][j];
			}
		}
	}
	
	return *this;
}

Matrix Matrix::transpose()
{
	if(this->isZeroMatrix())
	{
		return Matrix();
	}

	if(this->isVector())
	{
		return Matrix(this->columns, this->rows, [&](unsigned int i, unsigned int j) { return vectorEntries[i + j]; });
	}

	return Matrix(this->columns, this->rows, [&](unsigned int i, unsigned int j) { return entries[j][i]; });
}

Matrix Matrix::multiplyEntries(const Matrix& that) const
{
	if(this->rows != that.rows || this->columns != that.columns)
	{
		throw invalid_argument("multiplyEntry - matrices of incompatible size");
	}

	if(that.isZeroMatrix())
	{
		return Matrix();
	}

	if(this->isVector())
	{
		return Matrix(that.rows, that.columns, [&](unsigned int i, unsigned int j) { return vectorEntries[i + j] * that.vectorEntries[i + j]; });
	}

	return Matrix(that.rows, that.columns, [&](unsigned int i, unsigned int j) { return entries[i][j] * that.entries[i][j]; });
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

unsigned int Matrix::vectorSize() const
{
	if(this->rows > this->columns)
	{
		return this->rows;
	}
	
	return this->columns;
}

bool Matrix::isZeroMatrix() const
{
	//You can't have a Nx0 or 0xN matrix, so either condition below suffices.
	return this->rows == 0 || this->columns == 0;
}