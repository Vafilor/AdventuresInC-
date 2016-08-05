#define BOOST_TEST_MODULE NeuralNetworkTest
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "Matrix.h"
#include <vector>

namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

using std::vector;
const double TOLERANCE = 0.0001;

void testAllEntriesZero(const Matrix& matrix);
void testAllEntries(const Matrix& matrix, double value);

//TODO separate these out, this file is huge!
BOOST_AUTO_TEST_CASE( constructor_test_default )
{
	Matrix matrix;
	
	BOOST_TEST(matrix.getRows() == 0);
	BOOST_TEST(matrix.getColumns() == 0);
}

BOOST_AUTO_TEST_CASE( constructor_test_dimensions )
{
	Matrix zero; 

	Matrix single(1,1);
	
	BOOST_TEST(single.getRows() == 1);
	BOOST_TEST(single.getColumns() == 1);
	testAllEntriesZero(single);
	
	Matrix row(1, 3);
	
	BOOST_TEST(row.getRows() == 1);
	BOOST_TEST(row.getColumns() == 3);
	testAllEntriesZero(row);
	
	Matrix column(5, 1);
	
	BOOST_TEST(column.getRows() == 5);
	BOOST_TEST(column.getColumns() == 1);
	testAllEntriesZero(column);
	
	Matrix square(3,3);
	
	BOOST_TEST(square.getRows() == 3);
	BOOST_TEST(square.getColumns() == 3);
	testAllEntriesZero(square);
	
	Matrix rectangle(2,3);
	
	BOOST_TEST(rectangle.getRows() == 2);
	BOOST_TEST(rectangle.getColumns() == 3);
	testAllEntriesZero(rectangle);
	
	Matrix rectangle2(3,2);
	
	BOOST_TEST(rectangle2.getRows() == 3);
	BOOST_TEST(rectangle2.getColumns() == 2);
	testAllEntriesZero(rectangle2);	
}

BOOST_AUTO_TEST_CASE( constructor_test_functor )
{
	Matrix zero(0, 0, [](unsigned int row, unsigned int column) {
		return 0.0;
	});
	
	Matrix single(1, 1, [](unsigned int row, unsigned int column) {
		return 5.0;
	});
	
	BOOST_TEST(single.getRows() == 1);
	BOOST_TEST(single.getColumns() == 1);
	BOOST_TEST(single(0,0) == 5.0, tt::tolerance(TOLERANCE));

	Matrix row(1, 3, [](unsigned int row, unsigned int column) {
		return (double)column;
	});
	
	BOOST_TEST(row.getRows() == 1);
	BOOST_TEST(row.getColumns() == 3);
	
	BOOST_TEST(row(0,0) == 0.0, tt::tolerance(TOLERANCE));	
	BOOST_TEST(row(0,1) == 1.0, tt::tolerance(TOLERANCE));		
	BOOST_TEST(row(0,2) == 2.0, tt::tolerance(TOLERANCE));	
		
	Matrix column(3, 1, [](unsigned int row, unsigned int column) {
		return (double)row;
	});
	
	BOOST_TEST(column.getRows() == 3);
	BOOST_TEST(column.getColumns() == 1);
	
	BOOST_TEST(column(0,0) == 0.0, tt::tolerance(TOLERANCE));	
	BOOST_TEST(column(1,0) == 1.0, tt::tolerance(TOLERANCE));		
	BOOST_TEST(column(2,0) == 2.0, tt::tolerance(TOLERANCE));	
			
			
	Matrix square(3, 3, [](unsigned int row, unsigned int column) {
		return row + column;
	});

	BOOST_TEST(square.getRows() == 3);
	BOOST_TEST(square.getColumns() == 3);
	
	for(int i = 0; i < square.getRows(); i++)
	{
		for(int j = 0; j < square.getColumns(); j++)
		{
			BOOST_TEST(square(i,j) == (double)(i + j), tt::tolerance(TOLERANCE));	
		}
	}
	

	Matrix rectangle(2, 3, [](unsigned int row, unsigned int column) {
		return (int)row - (int)column;
	});

	BOOST_TEST(rectangle.getRows() == 2);
	BOOST_TEST(rectangle.getColumns() == 3);
	
	for(int i = 0; i < rectangle.getRows(); i++)
	{
		for(int j = 0; j < rectangle.getColumns(); j++)
		{
			BOOST_TEST(rectangle(i,j) == (double)(i - j), tt::tolerance(TOLERANCE));	
		}
	}


	Matrix rectangle2(3, 2, [](unsigned int row, unsigned int column) {
		return (int)row - (int)column;
	});

	BOOST_TEST(rectangle2.getRows() == 3);
	BOOST_TEST(rectangle2.getColumns() == 2);
	
	for(int i = 0; i < rectangle2.getRows(); i++)
	{
		for(int j = 0; j < rectangle2.getColumns(); j++)
		{
			BOOST_TEST(rectangle2(i,j) == (double)(i - j), tt::tolerance(TOLERANCE));	
		}
	}
}

BOOST_AUTO_TEST_CASE( equality_zero ) 
{
	Matrix zero;
	Matrix zero2(0,0);
	
	BOOST_TEST(zero == zero2);
	
}

BOOST_AUTO_TEST_CASE( equality_single )
{ 
	Matrix single(1,1);
	single(0,0) = 5.0;
	
	Matrix single2(1,1);
	single2(0,0) = 5.0;
	
	BOOST_TEST(single == single2);
	
	single2(0,0) = -1.0;
	
	BOOST_TEST(!(single == single2));
}

BOOST_AUTO_TEST_CASE( equality_row )
{ 
	Matrix row(1,3);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;

	Matrix row2(1,3);
	row2(0,0) = 1.0;
	row2(0,1) = 2.0;
	row2(0,2) = 3.0;
	
	BOOST_TEST(row == row2);
	
	row2(0,0) = -1.0;
	BOOST_TEST(!(row == row2));
}

BOOST_AUTO_TEST_CASE( equality_column)
{ 
	Matrix column(3,1);
	column(0,0) = 1.0;
	column(1,0) = 2.0;
	column(2,0) = 3.0;

	Matrix column2(3,1);
	column2(0,0) = 1.0;
	column2(1,0) = 2.0;
	column2(2,0) = 3.0;
	
	BOOST_TEST(column == column2);
	
	column2(0,0) = -1.0;
	BOOST_TEST(!(column == column2));
}

BOOST_AUTO_TEST_CASE( equality_square)
{ 
	Matrix square(2,2);
	square(0,0) = 1.0;
	square(0,1) = 2.0;
	square(1,0) = 3.0;	
	square(1,1) = 4.0;

	Matrix square2(2,2);
	square2(0,0) = 1.0;
	square2(0,1) = 2.0;
	square2(1,0) = 3.0;	
	square2(1,1) = 4.0;
	
	BOOST_TEST(square == square2);
	
	square2(0,0) = -1.0;
	BOOST_TEST(!(square == square2));
}

BOOST_AUTO_TEST_CASE( equality_rectangle)
{ 
	Matrix rectangle(2,3);
	rectangle(0,0) = 1.0;
	rectangle(0,1) = 2.0;
	rectangle(0,2) = 3.0;	
	rectangle(1,0) = 4.0;	
	rectangle(1,1) = 5.0;
	rectangle(1,2) = 6.0;

	Matrix rectangle2(2,3);
	rectangle2(0,0) = 1.0;
	rectangle2(0,1) = 2.0;
	rectangle2(0,2) = 3.0;	
	rectangle2(1,0) = 4.0;	
	rectangle2(1,1) = 5.0;
	rectangle2(1,2) = 6.0;
	
	BOOST_TEST(rectangle == rectangle2);
	
	rectangle2(0,0) = -1.0;
	BOOST_TEST(!(rectangle == rectangle2));
}

BOOST_AUTO_TEST_CASE( equality_rectangle_2)
{ 
	Matrix rectangle(3,2);
	rectangle(0,0) = 1.0;
	rectangle(0,1) = 2.0;
	rectangle(1,0) = 3.0;	
	rectangle(1,1) = 4.0;	
	rectangle(2,0) = 5.0;
	rectangle(2,1) = 6.0;

	Matrix rectangle2(3,2);
	rectangle2(0,0) = 1.0;
	rectangle2(0,1) = 2.0;
	rectangle2(1,0) = 3.0;	
	rectangle2(1,1) = 4.0;	
	rectangle2(2,0) = 5.0;
	rectangle2(2,1) = 6.0;
	
	BOOST_TEST(rectangle == rectangle2);
	
	rectangle2(0,0) = -1.0;
	BOOST_TEST(!(rectangle == rectangle2));
}

BOOST_AUTO_TEST_CASE( constructor_test_copy )
{	
	//Here we're making sure we don't get any exceptions for zero matrix
	Matrix zero;
	Matrix zeroCopy(zero);
	
	Matrix single(1,1);
	single(0,0) = 5.0;
	
	Matrix singleCopy(single);
	BOOST_TEST(single == singleCopy);
	
	Matrix row(1, 3);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;
	
	Matrix rowCopy(row);
	
	BOOST_TEST(row == rowCopy);
	
	Matrix column(3,1);
	column(0,0) = 1.0;
	column(1,0) = 2.0;
	column(2,0) = 3.0;

	Matrix columnCopy(column);

	BOOST_TEST(column == columnCopy);
	
	Matrix square(2,2);
	square(0,0) = 1.0;
	square(0,1) = 2.0;
	square(1,0) = 3.0;	
	square(1,1) = 4.0;
	
	Matrix squareCopy(square);
	
	BOOST_TEST(square == squareCopy);

	Matrix rectangle(2,3);
	rectangle(0,0) = 1.0;
	rectangle(0,1) = 2.0;
	rectangle(0,2) = 3.0;	
	rectangle(1,0) = 4.0;	
	rectangle(1,1) = 5.0;
	rectangle(1,2) = 6.0;

	Matrix rectangleCopy(rectangle);
	
	BOOST_TEST(rectangle == rectangleCopy);
	
	Matrix rectangle2(3,2);
	rectangle2(0,0) = 1.0;
	rectangle2(0,1) = 2.0;
	rectangle2(1,0) = 3.0;	
	rectangle2(1,1) = 4.0;	
	rectangle2(2,0) = 5.0;
	rectangle2(2,1) = 6.0;

	Matrix rectangle2Copy(rectangle2);

	BOOST_TEST(rectangle2 == rectangle2Copy);
}


BOOST_AUTO_TEST_CASE( constructor_test_move_zero )
{
	Matrix zero;
	
	Matrix single(1,1, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix row(1,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix column(3,1, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});	
	
	Matrix square(2,2, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix rectangle(3,4, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix rectangle2(4,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});

	vector<Matrix> matrices;
	matrices.reserve(7);
	
	matrices.push_back(Matrix());
	
	//Single
	matrices.push_back(	Matrix(1,1, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	}));
	
	//Row
	matrices.push_back(	Matrix(1,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	}));
	
	//Column
	matrices.push_back(	Matrix(3,1, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	}));
	
	//Square
	matrices.push_back(	Matrix(2,2, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	}));

	//Rectangle
	matrices.push_back(	Matrix(3,4, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	}));

	//Rectangle2	
	matrices.push_back(	Matrix(4,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	}));

	BOOST_TEST(matrices[0] == zero);
	BOOST_TEST(matrices[1] == single);
	BOOST_TEST(matrices[2] == row);
	BOOST_TEST(matrices[3] == column);
	BOOST_TEST(matrices[4] == square);
	BOOST_TEST(matrices[5] == rectangle);
	BOOST_TEST(matrices[6] == rectangle2);
}

BOOST_AUTO_TEST_CASE( operator_test_assignment_zero )
{
	Matrix zero;
	
	Matrix zeroTest(3,3);
	zeroTest = zero;
	
	BOOST_TEST(zero == zeroTest);
	
	Matrix square(2,2, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	zero = square;
	
	BOOST_TEST(zero == square);
}

BOOST_AUTO_TEST_CASE( operator_test_assignment_single )
{
	Matrix single(1,1);
	
	Matrix singleTest(3,3);
	singleTest = single;
	
	BOOST_TEST(single == singleTest);
	
	Matrix square(3,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	single = square;
	
	BOOST_TEST(single == square);
}

BOOST_AUTO_TEST_CASE( operator_test_assignment_row )
{
	Matrix row(1,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix rowCopy(3,1);
	
	rowCopy = row;
	
	BOOST_TEST(row == rowCopy);
	
	Matrix column(3,1,[](unsigned int row, unsigned int column){
		return (double)(row+column);
	});
	
	row = column;
	
	BOOST_TEST(row == column);
}

BOOST_AUTO_TEST_CASE( operator_test_assignment_column )
{
	Matrix column(3,1, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix columnCopy(1,3);
	
	columnCopy = column;
	
	BOOST_TEST(column == columnCopy);
	
	Matrix row(1,3,[](unsigned int row, unsigned int column){
		return (double)(row+column);
	});
	
	column = row;
	
	BOOST_TEST(row == column);
}

BOOST_AUTO_TEST_CASE( operator_test_assignment_square )
{
	Matrix square(2,2, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix squareCopy;
	
	squareCopy = square;
	
	BOOST_TEST(square == squareCopy);
	
	Matrix rectangle(3,4, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	square = rectangle;
	
	BOOST_TEST(square == rectangle);
}

BOOST_AUTO_TEST_CASE( operator_test_assignment_rectangle )
{
	Matrix rectangle(3,4, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix rectangleCopy;
	
	rectangleCopy = rectangle;
	
	BOOST_TEST(rectangle == rectangleCopy);
	
	Matrix rectangle2(4,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	rectangle = rectangle2;
	
	BOOST_TEST(rectangle == rectangle2);
}

BOOST_AUTO_TEST_CASE( operator_test_assignment_rectangle2 )
{
	Matrix rectangle(4,3, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	Matrix rectangleCopy;
	
	rectangleCopy = rectangle;
	
	BOOST_TEST(rectangle == rectangleCopy);
	
	Matrix rectangle2(3,4, [](unsigned int row, unsigned int column){
		return (double)(row + column);
	});
	
	rectangle = rectangle2;
	
	BOOST_TEST(rectangle == rectangle2);
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment_zero )
{
	Matrix zero;
	Matrix zeroMove;
		
	zeroMove = Matrix();
	
	BOOST_TEST(zero == zeroMove);
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment_single )
{
	Matrix single(1,1);
	single(0,0) = 5.0;
	
	Matrix singleMove(1,1);
		
	singleMove = Matrix(1,1, [](unsigned int row, unsigned int column) {
		return 5.0;
	});
	
	BOOST_TEST(single == singleMove);
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment_row )
{
	Matrix row(1,3);
	row(0,0) = 0.0;
	row(0,1) = 1.0;
	row(0,2) = 2.0;
	
	Matrix rowMove(1,3);
		
	rowMove = Matrix(1,3, [](unsigned int row, unsigned int column) {
		return (double)column;
	});
	
	BOOST_TEST(row == rowMove);
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment_column )
{
	Matrix column(3,1);
	column(0,0) = 0.0;
	column(1,0) = 1.0;
	column(2,0) = 2.0;
	
	Matrix columnMove(3,1);
		
	columnMove = Matrix(3,1, [](unsigned int row, unsigned int column) {
		return (double)row;
	});
	
	BOOST_TEST(column == columnMove);
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment_square )
{
	Matrix square(3,3, [](unsigned int row, unsigned int column) {
		return (double)(row + column);
	});
	
	Matrix squareMove(3,3);
		
	squareMove = Matrix(3,3, [](unsigned int row, unsigned int column) {
		return (double)(row + column);
	});
	
	BOOST_TEST(square == squareMove);
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment_rectangle )
{
	Matrix rectangle(3,4, [](unsigned int row, unsigned int column) {
		return (double)(row + column);
	});
	
	Matrix rectangleMove(3,4);
		
	rectangleMove = Matrix(3,4, [](unsigned int row, unsigned int column) {
		return (double)(row + column);
	});
	
	BOOST_TEST(rectangle == rectangleMove);
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment_rectangle_2 )
{
	Matrix rectangle(4,3, [](unsigned int row, unsigned int column) {
		return (double)(row + column);
	});
	
	Matrix rectangleMove(4,3);
		
	rectangleMove = Matrix(4,3, [](unsigned int row, unsigned int column) {
		return (double)(row + column);
	});
	
	BOOST_TEST(rectangle == rectangleMove);
}

BOOST_AUTO_TEST_CASE( operator_test_addition_exceptions )
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(3,3);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);

	//Check valid cases
	
	//Note: We do not test 0x0 matrix addition as it is invalid to access a row.
	//As long as it doesn't throw exception to add them, that's alright.
	zero + zero;
	single + single;
	row + row;
	column + column;
	square + square;
	rectangle + rectangle;
	rectangle2 + rectangle2;

	//Check invalid cases
	
	//Check Zero
	BOOST_CHECK_THROW(
		zero + single,
		std::invalid_argument
	);

	
	//Check different columns
	BOOST_CHECK_THROW(
		single + row,
		std::invalid_argument
	);
	
	BOOST_CHECK_THROW(
		row + single,
		std::invalid_argument
	);
	
	//Check different rows
	BOOST_CHECK_THROW(
		single + column,
		std::invalid_argument
	);
		
	BOOST_CHECK_THROW(
		column + single,
		std::invalid_argument
	);	
	
	//Check different rows and columns
	BOOST_CHECK_THROW(
		single + square,
		std::invalid_argument
	);	
	
	BOOST_CHECK_THROW(
		square + single,
		std::invalid_argument
	);	
}

BOOST_AUTO_TEST_CASE( operator_test_addition_single )
{
	Matrix left(1,1);
	left(0,0) = 1.0;
	
	Matrix right(1,1);
	right(0,0) = 2.0;
	
	Matrix sum = left + right;
	
	BOOST_TEST(sum(0,0) == 3.0, tt::tolerance(TOLERANCE));
	
	Matrix sumSecond = right + left;
	
	BOOST_TEST(sumSecond(0,0) == 3.0, tt::tolerance(TOLERANCE));

}

BOOST_AUTO_TEST_CASE( operator_test_addition_square )
{
	Matrix left(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	Matrix sum = left + right;
	
	for(int i = 0; i < sum.getRows(); i++)
	{
		for(int j = 0; j < sum.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
	
	Matrix sumSecond = right + left;
	
	for(int i = 0; i < sumSecond.getRows(); i++)
	{
		for(int j = 0; j < sumSecond.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_addition_rectangle )
{
	Matrix left(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	
	Matrix sum = left + right;
	
	for(int i = 0; i < sum.getRows(); i++)
	{
		for(int j = 0; j < sum.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
	
	Matrix sumSecond = right + left;
	
	for(int i = 0; i < sumSecond.getRows(); i++)
	{
		for(int j = 0; j < sumSecond.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_addition_rectangle_2 )
{
	Matrix left(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	Matrix sum = left + right;
	
	for(int i = 0; i < sum.getRows(); i++)
	{
		for(int j = 0; j < sum.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
	
	Matrix sumSecond = right + left;
	
	for(int i = 0; i < sumSecond.getRows(); i++)
	{
		for(int j = 0; j < sumSecond.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_addition_into_exceptions )
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(3,3);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);

	//Check valid cases
	
	//We do not test 0x0 matrix addition into as it is invalid to access a row.
	//As long as it doesn't throw exception, that's alright.
	zero += zero;
	single += single;
	row += row;
	column += column;
	square += square;
	rectangle += rectangle;
	rectangle2 += rectangle2;

	//Check invalid cases

	//Check zero
	BOOST_CHECK_THROW(
		zero += single,
		std::invalid_argument
	);
	
	//Check different columns
	BOOST_CHECK_THROW(
		single += row,
		std::invalid_argument
	);
	
	BOOST_CHECK_THROW(
		row += single,
		std::invalid_argument
	);
	
	//Check different rows
	BOOST_CHECK_THROW(
		single += column,
		std::invalid_argument
	);
		
	BOOST_CHECK_THROW(
		column += single,
		std::invalid_argument
	);	
	
	//Check different rows and columns
	BOOST_CHECK_THROW(
		single += square,
		std::invalid_argument
	);	
	
	BOOST_CHECK_THROW(
		square += single,
		std::invalid_argument
	);	
}

BOOST_AUTO_TEST_CASE( operator_test_addition_into_single )
{
	Matrix left(1,1);
	left(0,0) = 1.0;
	
	Matrix right(1,1);
	right(0,0) = 2.0;
	
	left += right;
	
	BOOST_TEST(left(0,0) == 3.0, tt::tolerance(TOLERANCE));
	
	right += left;
	
	BOOST_TEST(right(0,0) == 5.0, tt::tolerance(TOLERANCE));

}

BOOST_AUTO_TEST_CASE( operator_test_addition_into_square )
{
	Matrix left(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	left += right;
	
	for(int i = 0; i < left.getRows(); i++)
	{
		for(int j = 0; j < left.getColumns(); j++)
		{
			BOOST_TEST(left(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
	
	right += left;
	
	for(int i = 0; i < right.getRows(); i++)
	{
		for(int j = 0; j < right.getColumns(); j++)
		{
			BOOST_TEST(right(i, j) == 3.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_addition_into_rectangle )
{
	Matrix left(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	
	left += right;
	
	for(int i = 0; i < left.getRows(); i++)
	{
		for(int j = 0; j < left.getColumns(); j++)
		{
			BOOST_TEST(left(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
	
	right += left;
	
	for(int i = 0; i < right.getRows(); i++)
	{
		for(int j = 0; j < right.getColumns(); j++)
		{
			BOOST_TEST(right(i, j) == 3.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_addition_into_rectangle_2 )
{
	Matrix left(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	left += right;
	
	for(int i = 0; i < left.getRows(); i++)
	{
		for(int j = 0; j < left.getColumns(); j++)
		{
			BOOST_TEST(left(i, j) == 2.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
	
	right += left;
	
	for(int i = 0; i < right.getRows(); i++)
	{
		for(int j = 0; j < right.getColumns(); j++)
		{
			BOOST_TEST(right(i, j) == 3.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_exceptions )
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(3,3);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);

	//Check valid cases
	zero - zero;
	single - single;
	row - row;
	column - column;
	square - square;
	rectangle - rectangle;
	rectangle2 - rectangle2;

	//Check invalid cases

	//Check zero
	BOOST_CHECK_THROW(
		zero - single,
		std::invalid_argument
	);
	
	//Check different columns
	BOOST_CHECK_THROW(
		single - row,
		std::invalid_argument
	);
	
	BOOST_CHECK_THROW(
		row - single,
		std::invalid_argument
	);
	
	//Check different rows
	BOOST_CHECK_THROW(
		single - column,
		std::invalid_argument
	);
		
	BOOST_CHECK_THROW(
		column - single,
		std::invalid_argument
	);	
	
	//Check different rows and columns
	BOOST_CHECK_THROW(
		single - square,
		std::invalid_argument
	);	
	
	BOOST_CHECK_THROW(
		square - single,
		std::invalid_argument
	);	
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_single )
{
	Matrix left(1,1);
	left(0,0) = 1.0;
	
	Matrix right(1,1);
	right(0,0) = 2.0;
	
	Matrix sum = left - right;
	
	BOOST_TEST(sum(0,0) == -1.0, tt::tolerance(TOLERANCE));
	
	Matrix sumSecond = right - left;
	
	BOOST_TEST(sumSecond(0,0) == 1.0, tt::tolerance(TOLERANCE));

}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_square )
{
	Matrix left(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	Matrix sum = left - right;
	
	for(int i = 0; i < sum.getRows(); i++)
	{
		for(int j = 0; j < sum.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
	
	Matrix sumSecond = right - left;
	
	for(int i = 0; i < sumSecond.getRows(); i++)
	{
		for(int j = 0; j < sumSecond.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_rectangle )
{
	Matrix left(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	
	Matrix sum = left - right;
	
	for(int i = 0; i < sum.getRows(); i++)
	{
		for(int j = 0; j < sum.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
	
	Matrix sumSecond = right - left;
	
	for(int i = 0; i < sumSecond.getRows(); i++)
	{
		for(int j = 0; j < sumSecond.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 0.0*(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_rectangle_2 )
{
	Matrix left(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	Matrix sum = left - right;
	
	for(int i = 0; i < sum.getRows(); i++)
	{
		for(int j = 0; j < sum.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
	
	Matrix sumSecond = right - left;
	
	for(int i = 0; i < sumSecond.getRows(); i++)
	{
		for(int j = 0; j < sumSecond.getColumns(); j++)
		{
			BOOST_TEST(sum(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_into_exceptions )
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3,1);
	Matrix square(3,3);
	Matrix rectangle(3,4);
	Matrix rectangle2(4,3);

	//Check valid cases
	zero -= zero;
	single -= single;
	row -= row;
	column -= column;
	square -= square;
	rectangle -= rectangle;
	rectangle2 -= rectangle2;

	//Check invalid cases

	//Check zero
	BOOST_CHECK_THROW(
		zero -= single,
		std::invalid_argument
	);
	
	//Check different columns
	BOOST_CHECK_THROW(
		single -= row,
		std::invalid_argument
	);
	
	BOOST_CHECK_THROW(
		row -= single,
		std::invalid_argument
	);
	
	//Check different rows
	BOOST_CHECK_THROW(
		single -= column,
		std::invalid_argument
	);
		
	BOOST_CHECK_THROW(
		column -= single,
		std::invalid_argument
	);	
	
	//Check different rows and columns
	BOOST_CHECK_THROW(
		single -= square,
		std::invalid_argument
	);	
	
	BOOST_CHECK_THROW(
		square -= single,
		std::invalid_argument
	);	
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_into_single )
{
	Matrix left(1,1);
	left(0,0) = 1.0;
	
	Matrix right(1,1);
	right(0,0) = 2.0;
	
	left -= right;
	
	BOOST_TEST(left(0,0) == -1.0, tt::tolerance(TOLERANCE));
	
	right -= left;
	
	BOOST_TEST(right(0,0) == 3.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_into_square )
{
	Matrix left(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	left -= right;
	
	for(int i = 0; i < left.getRows(); i++)
	{
		for(int j = 0; j < left.getColumns(); j++)
		{
			BOOST_TEST(left(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
	
	right -= left;
	
	for(int i = 0; i < right.getRows(); i++)
	{
		for(int j = 0; j < right.getColumns(); j++)
		{
			BOOST_TEST(right(i, j) == (double)(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_into_rectangle )
{
	Matrix left(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(3,4, [](unsigned int row, unsigned int column){ return row + column; });
	
	left -= right;
	
	for(int i = 0; i < left.getRows(); i++)
	{
		for(int j = 0; j < left.getColumns(); j++)
		{
			BOOST_TEST(left(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
	
	right -= left;
	
	for(int i = 0; i < right.getRows(); i++)
	{
		for(int j = 0; j < right.getColumns(); j++)
		{
			BOOST_TEST(right(i, j) == (double)(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_into_rectangle_2 )
{
	Matrix left(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	Matrix right(4,3, [](unsigned int row, unsigned int column){ return row + column; });
	
	left -= right;
	
	for(int i = 0; i < left.getRows(); i++)
	{
		for(int j = 0; j < left.getColumns(); j++)
		{
			BOOST_TEST(left(i, j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}
	
	right -= left;
	
	for(int i = 0; i < right.getRows(); i++)
	{
		for(int j = 0; j < right.getColumns(); j++)
		{
			BOOST_TEST(right(i, j) == (double)(i+j), tt::tolerance(TOLERANCE));
		}
	}
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_exceptions )
{
	Matrix single(1,1);
	Matrix column(3, 1);
	Matrix square(2,2);
	
	//Column Mismatch
	BOOST_CHECK_THROW(
		single * column,
		std::invalid_argument
	);
	
	BOOST_CHECK_THROW(
		column * square,
		std::invalid_argument
	);	
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_sizes )
{
	Matrix zero;
	Matrix single(1,1);
	Matrix row(1,3);
	Matrix column(3, 1);
	
	Matrix zeroResult = zero * zero;
	BOOST_TEST(zeroResult.getRows() == 0);
	BOOST_TEST(zeroResult.getColumns() == 0);	
	
	Matrix singleResult = single * single;
	BOOST_TEST(singleResult.getRows() == 1);
	BOOST_TEST(singleResult.getColumns() == 1);	

	Matrix rowColumnResult = row * column;
	BOOST_TEST(rowColumnResult.getRows() == 1);
	BOOST_TEST(rowColumnResult.getColumns() == 1);	
	
	Matrix columnRowResult = column * row;
	BOOST_TEST(columnRowResult.getRows() == 3);
	BOOST_TEST(columnRowResult.getColumns() == 3);	
	
	Matrix singleRowResult = single * row;
	BOOST_TEST(singleRowResult.getRows() == 1);
	BOOST_TEST(singleRowResult.getColumns() == 3);		
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_single )
{
	Matrix first(1,1);
	first(0,0) = 5.0;
	
	Matrix second(1,1);
	second(0,0) = 3.0;
	
	Matrix result = first * second;
	
	BOOST_TEST(result(0,0) == 15.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_row )
{
	Matrix row(1,3);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;
	
	Matrix column(3,1);
	column(0,0) = 1.0;
	column(1,0) = 2.0;
	column(2,0) = 3.0;

	Matrix result = row * column;
	
	BOOST_TEST(result(0,0) == 14.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_column )
{
	Matrix column(2,1);
	column(0,0) = 1.0;
	column(1,0) = 2.0;
	
	Matrix row(1,2);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	
	Matrix result = column * row;
	
	BOOST_TEST(result(0,0) == 1.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(0,1) == 2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(1,0) == 2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(1,1) == 4.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_square )
{
	Matrix square1(2,2);
	square1(0,0) = 1.0;
	square1(0,1) = 2.0;
	square1(1,0) = 3.0;
	square1(1,1) = 4.0;
	
	Matrix square2(2,2);
	square2(0,0) =  1.0;
	square2(0,1) = -1.0;
	square2(1,0) =  1.0;
	square2(1,1) =  2.0;
	
	Matrix result = square1 * square2;
	
	BOOST_TEST(result(0,0) == 3.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(0,1) == 3.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(1,0) == 7.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(1,1) == 5.0, tt::tolerance(TOLERANCE));
	
	Matrix result2 = square2 * square1;
	
	BOOST_TEST(result2(0,0) == -2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result2(0,1) == -2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result2(1,0) ==  7.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result2(1,1) == 10.0, tt::tolerance(TOLERANCE));	
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_rectangle_1 )
{
	Matrix rectangle(2,3);
	rectangle(0,0) = 0.0;
	rectangle(0,1) = 1.0;
	rectangle(0,2) = 2.0;
	rectangle(1,0) = 1.0;
	rectangle(1,1) = 2.0;
	rectangle(1,2) = 0.0;
	
	Matrix rectangle2(3,3);
	rectangle2(0,0) = -8.0;
	rectangle2(0,1) = -7.0;
	rectangle2(0,2) = -6.0;
	rectangle2(1,0) = -5.0;
	rectangle2(1,1) = -4.0;
	rectangle2(1,2) = -3.0;	
	rectangle2(2,0) = -2.0;	
	rectangle2(2,1) = -1.0;	
	rectangle2(2,2) =  0.0;	
	
	Matrix result = rectangle * rectangle2;
	BOOST_TEST(result(0,0) ==  -9.0, tt::tolerance(TOLERANCE));	
	BOOST_TEST(result(0,1) ==  -6.0, tt::tolerance(TOLERANCE));	
	BOOST_TEST(result(0,2) == -3.0, tt::tolerance(TOLERANCE));	
	BOOST_TEST(result(1,0) == -18.0, tt::tolerance(TOLERANCE));	
	BOOST_TEST(result(1,1) == -15.0, tt::tolerance(TOLERANCE));	
	BOOST_TEST(result(1,2) == -12.0, tt::tolerance(TOLERANCE));		
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_rectangle_2 )
{
	Matrix rectangle(3,2);
	rectangle(0,0) = 1.0;
	rectangle(0,1) = 1.0;
	rectangle(1,0) = 1.0;
	rectangle(1,1) = 1.0;
	rectangle(2,0) = 1.0;
	rectangle(2,1) = 1.0;
	
	Matrix rectangle2(2,2);
	rectangle2(0,0) = 1.0;
	rectangle2(0,1) = 1.0;
	rectangle2(1,0) = 1.0;
	rectangle2(1,1) = 1.0;
	
	Matrix result = rectangle * rectangle2;

	testAllEntries(result, 2.0);
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_zero )
{
	Matrix zero;
	
	//You can't access zero matrix entries. 
	//Just need to make sure it doesn't throw exception.
	
	zero * 2.0;	
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_single )
{	
	Matrix single(1,1);
	single(0,0) = 5.0;
	
	Matrix result = single * 5.0;
	
	BOOST_TEST(result(0,0) == 25.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_row )
{
	Matrix row(1,3);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;
	
	Matrix result = row * -2.0;
	
	BOOST_TEST(result(0,0) == -2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(0,1) == -4.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(0,2) == -6.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_column )
{
	Matrix column(3,1);
	column(0,0) =  0.0;
	column(1,0) = -1.0;
	column(2,0) = -2.0;
	
	Matrix result = column * -5.0;
	
	BOOST_TEST(result(0,0) == 0.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(1,0) == 5.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(result(2,0) == 10.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_square )
{
	Matrix square(2,2, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	Matrix result = square * 3.0;
	
	testAllEntries( result, 6.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_rectangle_1 )
{
	Matrix rectangle(2,3, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	Matrix result = rectangle * 3.0;
	
	testAllEntries( result, 6.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_rectangle_2 )
{
	Matrix rectangle(3,2, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	Matrix result = rectangle * 3.0;
	
	testAllEntries( result, 6.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into_zero )
{
	Matrix zero;
	
	//Here we're making sure no exception is thrown.
	zero *= 0;
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into_single )
{	
	Matrix single(1,1);
	single(0,0) = 5.0;
	
	single *= 5.0;
	
	BOOST_TEST(single(0,0) == 25.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into_row )
{
	Matrix row(1,3);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;
	
	row *= -2.0;
	
	BOOST_TEST(row(0,0) == -2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(row(0,1) == -4.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(row(0,2) == -6.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into_column )
{
	Matrix column(3,1);
	column(0,0) =  0.0;
	column(1,0) = -1.0;
	column(2,0) = -2.0;
	
	column *= -5.0;
	
	BOOST_TEST(column(0,0) == 0.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(column(1,0) == 5.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(column(2,0) == 10.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into_square )
{
	Matrix square(2,2, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	square *= 3.0;
	
	testAllEntries( square, 6.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into_rectangle_1 )
{
	Matrix rectangle(2,3, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	rectangle *= 3.0;
	
	testAllEntries( rectangle, 6.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into_rectangle_2 )
{
	Matrix rectangle(3,2, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	rectangle *= 3.0;
	
	testAllEntries( rectangle, 6.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_negation_zero)
{
	Matrix zero;
	
	//Here we're making sure no exception is thrown.
	-zero;
}

BOOST_AUTO_TEST_CASE( operator_test_negation_single )
{
	Matrix single(1,1);
	single(0,0) = 5.0;
	
	BOOST_TEST(-single(0,0) == -5.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_negation_row )
{
	Matrix row(1,3);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;
	
	BOOST_TEST(-row(0,0) == -1.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(-row(0,1) == -2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(-row(0,2) == -3.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_negation_column )
{
	Matrix column(3,1);
	column(0,0) =  0.0;
	column(1,0) = -1.0;
	column(2,0) = -2.0;
	
	BOOST_TEST(-column(0,0) == 0.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(-column(1,0) == 1.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(-column(2,0) == 2.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( operator_test_negation_square )
{
	Matrix square(2,2, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	testAllEntries( -square, -2.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_negation_rectangle )
{
	Matrix rectangle(2,3, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	testAllEntries( -rectangle, -2.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_negation_rectangle2 )
{
	Matrix rectangle(3,2, [](unsigned int row, unsigned int column){
		return -2.0;
	});
	
	testAllEntries( -rectangle, 2.0 );
}

BOOST_AUTO_TEST_CASE( operator_test_getter )
{	
	//Invalid to access zero matrix entries.
	Matrix zero;
	
	BOOST_CHECK_THROW(
		zero(0,0),
		std::invalid_argument
	);
	
	Matrix matrix(2,3, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	
	//Test legal access
	BOOST_TEST(matrix(1,2) == 2.0, tt::tolerance(TOLERANCE));
	
	//Invalid Row
	BOOST_CHECK_THROW(
		double result = matrix(2,0),
		std::invalid_argument
	);

	//Invalid Row
	BOOST_CHECK_THROW(
		double result = matrix(3,0),
		std::invalid_argument
	);
	
	//Invalid column
	BOOST_CHECK_THROW(
		double result = matrix(0,3),
		std::invalid_argument
	);

	//Invalid column
	BOOST_CHECK_THROW(
		double result = matrix(0,4),
		std::invalid_argument
	);
	
	//Invalid Row/Column
	BOOST_CHECK_THROW(
		double result = matrix(4,5),
		std::invalid_argument
	);
}

BOOST_AUTO_TEST_CASE( operator_test_setter )
{
	//Invalid to set zero matrix entries.
	Matrix zero;

	BOOST_CHECK_THROW(
		zero(0,0) = 1.0,
		std::invalid_argument
	);
	
	Matrix matrix(2,3, [](unsigned int row, unsigned int column){
		return 2.0;
	});
	
	matrix(1,2) = 5.0;
	
	//Check if setter worked
	BOOST_TEST(matrix(1,2) == 5.0, tt::tolerance(TOLERANCE));
	
	//Invalid Row
	BOOST_CHECK_THROW(
		matrix(2,0) = 1.0,
		std::invalid_argument
	);

	//Invalid Row
	BOOST_CHECK_THROW(
		matrix(3,0) = 5.0,
		std::invalid_argument
	);
	
	//Invalid column
	BOOST_CHECK_THROW(
		matrix(0,3) = 6.0,
		std::invalid_argument
	);

	//Invalid column
	BOOST_CHECK_THROW(
		matrix(0,4) = 2.0,
		std::invalid_argument
	);
	
	//Invalid Row/Column
	BOOST_CHECK_THROW(
		matrix(4,5) = -5.0,
		std::invalid_argument
	);
}

BOOST_AUTO_TEST_CASE( transpose_zero )
{
	Matrix zero;
	
	//Here we're making sure no exception is thrown.
	Matrix transpose = zero.transpose();
}

BOOST_AUTO_TEST_CASE( transpose_single )
{
	Matrix single(1,1);
	single(0,0) = 5.0;

	Matrix transpose = single.transpose();

	BOOST_TEST(transpose(0, 0) == 5.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( transpose_row )
{
	Matrix row(1,3);
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;

	Matrix transpose = row.transpose();

	BOOST_TEST(transpose(0, 0) == 1.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(transpose(1, 0) == 2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(transpose(2, 0) == 3.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( transpose_column )
{
	Matrix column(3,1);
	column(0,0) = 1.0;
	column(1,0) = 2.0;
	column(2,0) = 3.0;

	Matrix transpose = column.transpose();

	BOOST_TEST(transpose(0, 0) == 1.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(transpose(0, 1) == 2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(transpose(0, 2) == 3.0, tt::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE( transpose_square )
{
	Matrix square(2,2, [](unsigned int row, unsigned int column){
		return (double)(row + 2.0*column);
	});

	Matrix transpose = square.transpose();

	for(int row = 0; row < transpose.getRows(); row++)
	{
		for(int column = 0; column < transpose.getColumns(); column++)
		{
			BOOST_TEST(transpose(row, column) == (double)(2.0 * row + column), tt::tolerance(TOLERANCE));			
		}
	}
}

BOOST_AUTO_TEST_CASE( transpose_rectangle )
{
	Matrix rectangle(3,2, [](unsigned int row, unsigned int column){
		return (double)(row + 2.0*column);
	});

	Matrix transpose = rectangle.transpose();

	for(int row = 0; row < transpose.getRows(); row++)
	{
		for(int column = 0; column < transpose.getColumns(); column++)
		{
			BOOST_TEST(transpose(row, column) == (double)(2.0 * row + column), tt::tolerance(TOLERANCE));			
		}
	}
}

BOOST_AUTO_TEST_CASE( transpose_rectangle_2 )
{
	Matrix rectangle(2,3, [](unsigned int row, unsigned int column){
		return (double)(2.0 * row + column);
	});

	Matrix transpose = rectangle.transpose();

	for(int row = 0; row < transpose.getRows(); row++)
	{
		for(int column = 0; column < transpose.getColumns(); column++)
		{
			BOOST_TEST(transpose(row, column) == (double)(row + 2.0 * column), tt::tolerance(TOLERANCE));			
		}
	}
}

void testAllEntriesZero(const Matrix& matrix)
{
	testAllEntries(matrix, 0.0);
}

void testAllEntries(const Matrix& matrix, double value)
{
	for(int i = 0; i < matrix.getRows(); i++)
	{
		for(int j = 0; j < matrix.getColumns(); j++)
		{
			BOOST_TEST(matrix(i,j) == value, tt::tolerance(TOLERANCE));
		}
	}	
}