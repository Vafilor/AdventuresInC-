//Matrix.cpp
//By Andrey Melnikov

#include "Matrix.h"
#include <iostream> //For debugging
#include <string>
using namespace std; //For debugging

Matrix::Matrix()
{
	this->entries = NULL;
	this->rows = 0;
	this->columns = 0;
}

Matrix::Matrix(unsigned int rows, unsigned int columns)
{
	//TODO throw exceptions for 0 by A or B by 0 matrices.
    double** data = new double*[rows];
    
    for(int i = 0; i < rows; i++) 
    {
        data[i] = new double[columns]; 
        
        for(int j = 0; j < columns; j++) 
        {
            data[i][j] = 0.0;
        }
    }
    
    this->entries = data;
    this->rows = rows;
    this->columns = columns;
}

Matrix::Matrix(const Matrix& that)
{
	this->rows = that.rows;
	this->columns = that.columns;

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

Matrix::~Matrix()
{
	this->freeEntriesMemory();
}

void Matrix::freeEntriesMemory()
{
	for(int i = 0; i < this->rows; i++) 
    {	
        delete[] this->entries[i];
    }

	if(this->rows > 0 && this->columns > 0) 
	{
		delete[] this->entries;
	}
}

Matrix Matrix::operator+(const Matrix& that) const
{
	  //TODO - if incompatible sizes, throw exception

    Matrix copy(this->rows, this->columns);
    
    for(int i = 0; i < this->getRows(); i++)
    {
        for(int j = 0; j < this->getColumns(); j++)
        {
            copy.entries[i][j] = this->entries[i][j] + that.entries[i][j];
        }
    }    
    
    return copy;  
}

Matrix Matrix::operator*(const Matrix& that) const
{
	//TODO dimension requirements (A by B) x (B by C)
    int newRows = this->getRows();
    int newColumns = that.columns;

    Matrix product( newRows, newColumns );
    
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
    
    return product;
}

Matrix Matrix::operator=(const Matrix& that) 
{
	this->rows = that.rows;
	this->columns = that.columns;

	this->freeEntriesMemory();

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

void Matrix::applyFunction(double (*function)(double entry) )
{
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->columns; j++)
		{
			this->entries[i][j] = function(this->entries[i][j]);
		}
	}
}

Matrix operator*(const Matrix& that, double scalar)
{
    Matrix copy = Matrix::createUninitializedMatrix(that.rows, that.columns);
    
    for(int i = 0; i < that.getRows(); i++)
    {
        for(int j = 0; j < that.getColumns(); j++)
        {
            copy.entries[i][j] = that.entries[i][j] * scalar;
        }
    }    
    
    return copy;
}

bool operator==(const Matrix & a, const Matrix& b)
{
	if(a.rows != b.rows || a.columns != b.columns)
	{
		return false;
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
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->columns; j++)
		{
			this->entries[i][j] *= scalar;
		}
	}
}

const Matrix& Matrix::operator+=(const Matrix& that)
{
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->columns; j++)
		{
			this->entries[i][j] += that.entries[i][j];
		}
	}
}

//TODO use this in other places
Matrix Matrix::createUninitializedMatrix(unsigned int rows, unsigned int columns)
{
	//TODO result() no work?
	Matrix result;
	
	result.rows = rows;
	result.columns = columns;

	result.entries = new double*[rows];

	for(int i = 0; i < rows; i++)
	{
		result.entries[i] = new double[columns];
	}

	return result;
}

Matrix Matrix::transpose()
{
	//TODO Spelling
	Matrix transpose = createUninitializedMatrix(this->columns, this->rows);

	for(int i = 0; i < transpose.rows; i++)
	{
		for(int j = 0; j < transpose.columns; j++)
		{
			transpose.entries[i][j] = this->entries[j][i];
		}
	}
	
	return transpose;
}

