#define BOOST_TEST_MODULE NeuralNetworkTest
//This is so we can test private methods
#define private public

#include <boost/test/included/unit_test.hpp>
#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

const double TOLERANCE = 0.0001;

void testAllEntriesZero(const Matrix& matrix);

BOOST_AUTO_TEST_CASE( constructor_test )
{
	//TODO
}

BOOST_AUTO_TEST_CASE( getLargestRow )
{
	Matrix small(1,1);
	small(0,0) = -99.0;

	BOOST_TEST(NeuralNetwork::getLargestRow(small) == 0);

	Matrix matrix(3,1);
	matrix(2,0) = 1.0;

	BOOST_TEST(NeuralNetwork::getLargestRow(matrix) == 2);

	Matrix matrix2(4,1);
	matrix2(0,0) = 5.0;
	matrix2(1,0) = 6.0;
	matrix2(2,0) = 6.1;
	matrix2(3,0) = 1.0;

	BOOST_TEST(NeuralNetwork::getLargestRow(matrix2) == 2);

	Matrix sameContents(5,1);

	for(int i = 0; i < sameContents.getRows(); i++)
	{
		sameContents(i,0) = 1.0;
	}

	BOOST_TEST(NeuralNetwork::getLargestRow(sameContents) == 0);

	Matrix negatives(3,1);
	negatives(0,0) = -5.0;
	negatives(1,0) = 0.0;
	negatives(2,0) = -4.0;

	BOOST_TEST(NeuralNetwork::getLargestRow(negatives) == 1);

	Matrix allNegatives(4,1);
	allNegatives(0,0) = -10.0;
	allNegatives(1,0) = -15.0;
	allNegatives(2,0) = -20.0;
	allNegatives(3,0) = -1.0;

	BOOST_TEST(NeuralNetwork::getLargestRow(allNegatives) == 3);
}

BOOST_AUTO_TEST_CASE( getLastNonZeroRow )
{
	Matrix zeroes(3,1);
	zeroes(0,0) = 0.0;
	zeroes(1,0) = 0.0;
	zeroes(2,0) = 0.0;

	BOOST_TEST(NeuralNetwork::getLastNonZeroRow(zeroes) == -1);
	
	Matrix last(4,1);
	last(0,0) = 0.0;
	last(1,0) = 1.0;
	last(2,0) = 0.0;
	last(3,0) = 0.1;

	BOOST_TEST(NeuralNetwork::getLastNonZeroRow(last) == 3);

	Matrix middle(3,1);
	middle(0,0) = 0.0;
	middle(1,0) = 1.0;
	middle(2,0) = 0.0;

	BOOST_TEST(NeuralNetwork::getLastNonZeroRow(middle) == 1);

	Matrix first(2,1);
	first(0,0) = 12.0;
	first(1,0) = 0.0;

	BOOST_TEST(NeuralNetwork::getLastNonZeroRow(first) == 0);
}

BOOST_AUTO_TEST_CASE( createBlankCopy )
{
	//Test 0 matrices
	//Test 1
	//Test 3 
		//Make sure all entries 0
		//Trying doing it twice to the same existing vector - making sure it wipes data

	vector<Matrix> emptyVector;
	vector<Matrix> copy;

	NeuralNetwork::createBlankCopy(emptyVector, copy);

	BOOST_TEST(copy.size() == 0);

}

void testAllEntriesZero(const Matrix& matrix)
{
	for(int i = 0; i < matrix.getRows(); i++)
	{
		for(int j = 0; j < matrix.getColumns(); j++)
		{
			BOOST_TEST(matrix(i,j) == 0.0, tt::tolerance(TOLERANCE));
		}
	}	
}
