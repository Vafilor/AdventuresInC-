#include <iostream>
#include <string>
#include "Matrix.h"


using namespace std;



int main()
{
	Matrix first(3,4);

	cout << "first" << endl << first << endl;	

	for(int i = 0; i < first.getRows(); i++)
	{
		for(int j = 0; j < first.getColumns(); j++)
		{
			first(i,j) = i + j;
		}
	}

	cout << first << endl;
	cout << "-first:" << endl << -first << endl;
	
	cout << "first transpose" << endl;
	cout << first.transpose() << endl;

	//Why not working? - cout << "first *= 5.0:" << (first *= 5.0) << endl;

	first *= 5.0;
	
	
	cout << "first after *= 5.0" << endl << first << endl;
	
	



	return 0;
}
