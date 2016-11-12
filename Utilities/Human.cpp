#include "Human.h"
#include <iostream>
#include <utility>

using std::cout;

//Call base Mammal class constructor to initialize Mammal portion
Human::Human(const char* name) : Mammal(name)
{
	this->favoriteNumber = nullptr;
	cout << "Human - " << this->getName() << " " << this->getFavoriteNumber() << " : Human(const char* name) : Mammal(name)\n";
}

//Call base Mammal class constructor to initialize Mammal portion
Human::Human(int favoriteNumber, const char* name) : Mammal(name)
{
	this->setFavoriteNumber(favoriteNumber);

	cout << "Human - " << this->getName() << " " << this->getFavoriteNumber() << " : Human(int favoriteNumber, const char* name) : Mammal(name)\n";
}

//Destroy Human allocated data. The Mammal parent class destructor will be called automatically.
Human::~Human()
{
	cout << "Destroying Human with favoriteNumber - " << this->getFavoriteNumber() << "\n";

	delete this->favoriteNumber;
}

//Call base Mammal class copy constructor to initialize Mammal portion
Human::Human(const Human& that) : Mammal(that)
{
	this->setFavoriteNumber(that.getFavoriteNumber());
}

//Call base Mammal class Move Constructor to move Mammal portion
//We have to use std::move to indicate a Mammal&&, otherwise copy constructor is invoked.
Human::Human(Human&& that) : Mammal(std::move(that))
{
	this->favoriteNumber = that.favoriteNumber;
	that.favoriteNumber = nullptr;

	cout << "Human - " << this->getFavoriteNumber() << " : Human(Human&& that)\n";
}

Human& Human::operator=(const Human& that)
{
	if(this == &that)
	{
		return *this;
	}	


	//Use base Mammal class assignment to copy over its fields.
	Mammal::operator=(that);

	delete this->favoriteNumber;

	this->setFavoriteNumber(that.getFavoriteNumber());

	cout << "Human : operator=(const Human& that)\n";
}

Human& Human::operator=(Human&& that)
{
	if(this == &that)
	{
		return *this;
	}

	//Use base Mammal class move assignment to move its fields.
	Mammal::operator=(std::move(that));

	this->favoriteNumber = that.favoriteNumber;
	that.favoriteNumber = nullptr;

	cout << "Human - " << this->getName() << " , " << this->getFavoriteNumber() << " : operator=(Human&& that)\n";
}

void Human::setFavoriteNumber(int favoriteNumber)
{
	this->favoriteNumber = new int;
	*this->favoriteNumber = favoriteNumber;
}

//Implement the walk method, as required by Abstract Mammal base class.
void Human::walk() const
{
	cout << "Human - " << this->getName() << " : walk()\n";
}

//Here we use the abstract base class yell method, which is defined despite being a pure virtual function.
void Human::yell() const
{
	Mammal::yell();
	cout << "Human : yell()\n";
}

int Human::getFavoriteNumber() const 
{
	if(this->favoriteNumber == nullptr)
	{
		return 0;
	}

	return *this->favoriteNumber;
}

ostream& operator<<(ostream& output, const Human& that)
{
	//An operator of this form is not a member function, so we can not override it. 
	//However, we do know it exists in the parent, and so we can make use of the existing one.
	//Then add our own items to it.
	output << (const Mammal&)that
	       << that.getFavoriteNumber() 
	       << "\n";	

	return output;
}

