#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix
{
    private:
        double** entries;
        unsigned int rows;
        unsigned int columns;
        
        //TODO static method that determines if matrix sizes match

        
    public:
        Matrix(unsigned int rows, unsigned int columns);
        Matrix(Matrix* that);
        ~Matrix();
        
        //TODO make a public static method to generate identity matrix for some size and fill with random
        //values - one where random values are provided by some generator too.
        unsigned int getRows() const;
        unsigned int getColumns() const;
        double getEntry(int row, int column) const; 
        void setEntry(int row, int column, double value);
        //Make operator versions of these. Want A + B, A - B
		Matrix operator+(const Matrix& that);
        Matrix operator-(const Matrix& that);
		Matrix operator*(const Matrix& that);
		double operator()(int row, int column) const;
        std::string toString();

};

Matrix operator*(const Matrix& that, double scalar);
Matrix operator*(double scalar, const Matrix& that);

#endif
