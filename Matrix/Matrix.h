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
        
    public:

		//Constructors & Destructor

		Matrix();
        Matrix(unsigned int rows, unsigned int columns);
        
        template<typename Function>
        Matrix(unsigned int rows, unsigned int columns, Function initializer) 
        {
			if(rows == 0 || columns == 0)
			{
				throw invalid_argument("rows or columns is 0");
			}

			this->entries = new double*[rows];

			for(int i = 0; i < rows; i++) 
			{
				this->entries[i] = new double[columns]; 
	
				for(int j = 0; j < columns; j++) 
				{
					this->entries[i][j] = initializer(i, j);
				}
			}

			this->rows = rows;
			this->columns = columns;
        }
        
        Matrix(const Matrix& that);
        Matrix(Matrix&& that);
        ~Matrix();
        

		//Getters & Setters
        unsigned int getRows() const;
        unsigned int getColumns() const;
		double & operator()(unsigned int row, unsigned int column);
		double operator()(unsigned int row, unsigned int column) const;

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
		Matrix operator+(const Matrix& that) const;
        Matrix operator-(const Matrix& that) const;
		Matrix operator*(const Matrix& that) const;
		Matrix& operator=(const Matrix& that);
		Matrix& operator=(Matrix&& that);

		const Matrix& operator*=(double scalar);
		const Matrix& operator/=(double scalar);
		const Matrix& operator+=(const Matrix& that);
		const Matrix& operator-=(const Matrix& that);

		/**
		 * Multiplies each entry of this matrix by each entry of that matrix, entry by entry.
		 * Result(i,j) = this(i,j) * that(i,j)
		 */
		Matrix multiplyEntries(const Matrix& that) const;

		//Friend Functions

		friend Matrix operator*(const Matrix& that, double scalar);
		friend Matrix operator*(double scalar, const Matrix& that);

		friend bool operator==(const Matrix & a, const Matrix & b);
		//TODO can ostream not be const input and output? Either?
		friend std::ostream & operator<<(std::ostream & output, const Matrix & matrix);


		/*
		 *Replace each entry in the matrix with the result of the 
		 *passed in functor where the argument to the functor is the matrix entry 
		*/
		//TODO can I move these definitions into .cpp file?
		template<typename Function>		
		void applyFunctionInto(Function function )
		{
			for(int i = 0; i < this->rows; i++)
			{
				for(int j = 0; j < this->columns; j++)
				{
					this->entries[i][j] = function(this->entries[i][j]);
				}
			}
		}

		template<typename Function>	
		Matrix applyFunction( Function function )
		{
			Matrix copy(*this);

			copy.applyFunctionInto(function);

			return copy;
		}
};
#endif