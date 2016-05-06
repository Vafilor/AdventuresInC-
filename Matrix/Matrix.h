//TODO ifndef

#include <string>

class Matrix
{
    private:
        double** entries;
        unsigned int rows;
        unsigned int columns;
        
        void    scaleInPlace(double scalar);
        //TODO static method that determines if matrix sizes match
        
    public:
        Matrix(unsigned int rows, unsigned int columns);
        Matrix(Matrix* matrix);
        ~Matrix();
        
        //TODO make a public static method to generate identity matrix for some size and fill with random
        //values - one where random values are provided by some generator too.
        unsigned int getRows();
        unsigned int getColumns();
        double getEntry(int row, int column); //TODO make double array accessor?
        void setEntry(int row, int column, double value);
        //Make operator versions of these. Want A + B, A - B
        Matrix* add(Matrix* that);
        Matrix* subtract(Matrix* that);
        Matrix* scale(double scalar);
        Matrix* multiply(Matrix* that);
        std::string toString();
};
