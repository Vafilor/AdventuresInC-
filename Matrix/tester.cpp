#define BOOST_TEST_MODULE NeuralNetworkTest
//This is so we can test private methods
#define private public

#include <boost/test/included/unit_test.hpp>
#include "Matrix.h"
namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

const double TOLERANCE = 0.0001;

void testAllEntriesZero(const Matrix& matrix);
void testAllEntries(const Matrix& matrix, double value);


BOOST_AUTO_TEST_CASE( constructor_test_default )
{
	Matrix matrix;
	
	BOOST_TEST(matrix.getRows() == 0);
	BOOST_TEST(matrix.getColumns() == 0);
}

BOOST_AUTO_TEST_CASE( constructor_test_dimensions )
{
	//TODO test exceptional cases - make sure exceptions are thrown
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
}

BOOST_AUTO_TEST_CASE( constructor_test_copy )
{
	//Test row
	
	Matrix row(1, 3);
	
	row(0,0) = 1.0;
	row(0,1) = 2.0;
	row(0,2) = 3.0;
	
	Matrix rowCopy(row);
	
	BOOST_TEST(rowCopy.getRows() == 1);
	BOOST_TEST(rowCopy.getColumns() == 3);
	BOOST_TEST(rowCopy(0,0) == 1.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(rowCopy(0,1) == 2.0, tt::tolerance(TOLERANCE));
	BOOST_TEST(rowCopy(0,2) == 3.0, tt::tolerance(TOLERANCE));
	
	
	//Test column
	//Test square
	//Text Rectangles
}

BOOST_AUTO_TEST_CASE( constructor_test_move )
{

}

BOOST_AUTO_TEST_CASE( operator_test_assignment )
{
}

BOOST_AUTO_TEST_CASE( operator_test_move_assignment )
{
}

BOOST_AUTO_TEST_CASE( operator_test_addition )
{
}

BOOST_AUTO_TEST_CASE( operator_test_addition_into )
{
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction )
{
}

BOOST_AUTO_TEST_CASE( operator_test_subtraction_into )
{
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication )
{
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar )
{
}

BOOST_AUTO_TEST_CASE( operator_test_multiplication_scalar_into )
{
}

BOOST_AUTO_TEST_CASE( operator_test_negation )
{
}

BOOST_AUTO_TEST_CASE( operator_test_getter )
{
}

BOOST_AUTO_TEST_CASE( operator_test_setter )
{
}

BOOST_AUTO_TEST_CASE( transpose )
{
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