//MammalTester.cpp
//Uses Human and Cat classes so demonstrate inheritance features.

#include <iostream>
#include "Mammal.h"
#include "Human.h"
#include "Cat.h"
#include <vector>

using namespace std;

void constructors();
void polymorphism();

int main()
{
	constructors();
	polymorphism();

	return 0;
}

void constructors()
{

	//Create Human and specify all arguments
	Human jane(3, "Jane");
	
	//Create Human and only specify name
	Human joe("Joe");

	//Move Assignment here - notice it uses both Mammal move and Human move assignment operators
	joe = Human(5, "Frank");

	//Copy Constructor here, uses Mammal and Human copy constructors
	Human jo = jane;

	//Assignment operator here, uses Mammal and Human assignment operators
	joe = jo;

	//operator<< here, uses both Human and Mammal operator<<
	cout << joe << "\n";

	//Create Cat and specify all arguments
	Cat mittens("Regular", "Mittens");

	//Provide Mammal's name only
	Cat persian("Persian");

	//Default constructor, uses another constructor
	Cat tabby;
	
	//Copy Constructor here, uses Mammal and Human copy constructors
	Cat charlie = tabby;

	//Assignment operator here, uses Mammal and Human assignment operators
	charlie = persian;	

	//operator<< here, uses both Human and Mammal operator<<
	cout << charlie << "\n";

	vector<Human> humans;

	//Use Move Constructor here, notice it uses Mammal move constructor too.
	humans.push_back(Human(7, "Neo"));
	
	vector<Cat> cats;
	
	//Use Move Constructor here, notice it uses Mammal move constructor too.
	cats.push_back(Cat("Fiona", "Fio"));
}

void polymorphism()
{
	Human joe(11, "Joe");
	Cat mittens("A Cat Named Mittens", "Mittens");

	const int NUMBER_OF_MAMMALS = 2;

	//We create an array of Mammal* so we can demonstrate the polymorphism given to use by inheritance.
	//Human joe and Cat mittens can both be in the Mammal* array as Human is-a Mammal and Cat is-a Mammal
	Mammal* mammals[NUMBER_OF_MAMMALS] = { &joe, &mittens };

	for(int i = 0; i < NUMBER_OF_MAMMALS; i++)
	{
		//walk and yell will call the Human walk/yell and Cat walk/yell as appropriate. 
		mammals[i]->walk();

		//Notice that a Cat Meows with no Mammal yell. A Human does a Mammal Yell and then a Human yell.
		mammals[i]->yell();
	}
}
