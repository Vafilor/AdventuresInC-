//Matrix.h
//By Andrey Melnikov

#include <string>
#include <stdexcept>

#ifndef MATRIX_H
#define MATRIX_H

//TODO indicate exceptions thrown - including for methods that call other methods

using std::invalid_argument;

class Matrix
{
    private:
        double** entries;
        unsigned int rows;
        unsigned int columns;
        
		void freeEntriesMemory();

		//Static Utilities
		//Helper method that creates a matrix of rows x columns size, but where each value is not initialized to save precious cpu cycles
		static Matrix createUninitializedMatrix(unsigned int rows, unsigned int columns);
        
    public:

		//Constructors & Destructor

		Matrix();
        Matrix(unsigned int rows, unsigned int columns) throw(invalid_argument);
        Matrix(const Matrix& that);
        ~Matrix();
        

		//Getters & Setters
        inline unsigned int getRows() const;
        inline unsigned int getColumns() const;
		inline double & operator()(unsigned int row, unsigned int column);
		inline const double & operator()(unsigned int row, unsigned int column) const;

		//Unary Operators & Methods
		
		//Returns a matrix where each entry is the negative of the current matrix entry
		//i.e New(i,j) = -Old(i,j)
		inline Matrix operator-() const;

		//Returns a transpose of the current matrix.
		//i.e. New(i,j) = Old(j,i)
		Matrix transpose();

		//Binary Operators & Methods

		//Returns a matrix where each entry is the sum of this and that matrices
		//i.e. New(i,j) = this(i,j) + that(i,j)
		Matrix operator+(const Matrix& that) const throw(invalid_argument);
        inline Matrix operator-(const Matrix& that) const;
		Matrix operator*(const Matrix& that) const throw(invalid_argument);
		Matrix operator=(const Matrix& that);

		const Matrix& operator*=(double scalar);
		inline const Matrix& operator/=(double scalar);
		const Matrix& operator+=(const Matrix& that) throw(invalid_argument);
		inline const Matrix& operator-=(const Matrix& that) throw(invalid_argument);

		//Friend Functions

		friend Matrix operator*(const Matrix& that, double scalar);
		inline friend Matrix operator*(double scalar, const Matrix& that);

		friend bool operator==(const Matrix & a, const Matrix & b);
		//TODO can ostream not be const input and output? Either?
		friend std::ostream & operator<<(std::ostream & output, const Matrix & matrix);


		/*
		 *Replace each entry in the matrix with the result of the 
		 *passed in function where the argument to the function is the matrix entry 
		*/
		void applyFunctionInto(double (*function)(double entry) );
		//TODO add new applyFunction version - one that changes entries inline, the other that creates a new object.
};

//Inline functions

Matrix Matrix::operator-(const Matrix& that) const
{
	return (*this) + (-that);
}

double& Matrix::operator()(unsigned int row, unsigned int column) 
{
	//TODO bounds checking?
	return this->entries[row][column];
}

const double& Matrix::operator()(unsigned int row, unsigned int column) const 
{
	//TODO bounds checking?
	return this->entries[row][column];
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

const Matrix& Matrix::operator-=(const Matrix& that) throw(invalid_argument)
{
	return (*this) += -that; 
}

Matrix operator*(double scalar, const Matrix& that)
{
	return that * scalar;
}

#endif
