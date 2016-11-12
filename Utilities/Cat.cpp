#include "Cat.h"
#include <utility> //For std::move
#include <iostream>

using std::cout;

//Here we call another class constructor. 
//This was introduced in C++11. 
//Alternatively, you can define the other constructor as Cat::Cat(const char* name ="Default Name Cat")
Cat::Cat() : Cat("Default Name Cat")
{
	cout << "Cat - " << this->getName() << " ~aka~ " << this->getPetName() << " : Cat() : Cat(\"Default Name Cat\")\n";	
}

Cat::Cat(const char* name) : Mammal(name)
{
	//Here we set the pet name variable just to do things differently from Human and Mammal.
	//This makes getPetName method much simpler, but takes more memory as we have to allocate the string petName to hold this data.
	this->setPetName("No Pet Name Cat");

	cout << "Cat - " << this->getName() << " ~aka~ " << this->getPetName() << " : Cat(const char* name) : Mammal(name)\n";	
}

Cat::Cat(const char* name, const char* petName) : Mammal(name)
{
	this->setPetName(petName);
	cout << "Cat - " << this->getName() << " ~aka~ " << this->getPetName() << " : Cat(const char* name, const char* petName) : Mammal(name)\n";
}

//See Human.cpp for why we use Mammal(std::move(that))
Cat::Cat(Cat&& that) : Mammal(std::move(that))
{
	this->petName = std::move(that.petName);

	cout << "Cat " << this->getName() << " ~aka~ " << this->getPetName() << " : Cat(Cat&& that) : Mammal(that)\n";
}

Cat::~Cat()
{
	cout << "Destroying Cat " << this->getName() << " ~aka~ " << this->getPetName() << "\n";
}

Cat& Cat::operator=(const Cat& that)
{
	Mammal::operator=(that);

	//string class uses its own assignment operator
	this->petName = that.petName;

	cout << "Cat " << this->getName() << " ~aka~ " << this->getPetName() << " : operator=(const Cat& that)\n";

	return *this;
}

Cat& Cat::operator=(Cat&& that)
{
	Mammal::operator=(std::move(that));

	this->petName = std::move(that.petName);

	cout << "Cat " << this->getName() << " ~aka~ " << this->getPetName() << " : operator=(Cat&& that)\n";	

	return *this;
}

void Cat::setPetName(const char* petName)
{
	//string class has logic to be initialized from const char*
	this->petName = petName;
}

const string& Cat::getPetName() const 
{
	return this->petName;
}

void Cat::walk() const
{
	cout << "Cat " << this->getName() << " ~aka~ " << this->getPetName() << " : walk()\n";	
}

void Cat::yell() const
{
	//You don't have to have Mammal::yell() here, or you can put it after cout <<... below. Up to you.
	//Mammal::yell();
	cout << "Cat " << this->getName() << " ~aka~ " << this->getPetName() << " : yell()\n";	
	cout << "MeeeeooooooWWWWWW\n";
}

ostream& operator<<(ostream& output, const Cat& that)
{
	//See Human.cpp for notes.
	output << (const Mammal&)that
	       << that.getPetName()
	       << "\n";

	return output;
}
