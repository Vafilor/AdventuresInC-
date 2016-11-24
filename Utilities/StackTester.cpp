#include "Stack.h"
#include <iostream>

using namespace std;

int main()
{
	Stack<int> ints;

	ints.push(5);
	ints.push(3);
	ints.push(12);
	ints.push(18);

	cout << "Stack has " << ints.size() << " elements\n";

	while(!ints.isEmpty())
	{
		cout << ints << "\n";
		ints.pop();
	}
	
	cout << "Stack has " << ints.size() << " elements\n";
}
