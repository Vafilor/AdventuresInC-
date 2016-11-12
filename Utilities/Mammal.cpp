#include <cstring>
#include <iostream>

#include "Mammal.h"

using std::cout;

Mammal::Mammal()
{
	this->setName(nullptr);

	cout << "Mammal : Mammal()\n";
}

Mammal::Mammal(const char* name)
{
	this->setName(name);
	
	cout << "Mammal - " << this->getName() << " : Mammal(const char* name)\n";
}

Mammal::Mammal(const Mammal& that)
{
	this->setName(that.name);
	
	cout << "Mammal - " << this->getName() << " : Mammal(const Mammal& that)\n";
}

Mammal::Mammal(Mammal&& that)
{
	this->name = that.name;
	that.name = nullptr;

	cout << "Mammal - " << this->getName() << " : Mammal(Mammal&& that)\n";
}

Mammal& Mammal::operator=(const Mammal& that)
{
	if( this == &that ) 
	{
		return *this;
	}

	delete[] this->name;

	this->setName(that.name);

	cout << "Mammal - " << this->getName() << " : operator=(const Mammal& that)\n";

	return *this;
}

Mammal& Mammal::operator=(Mammal&& that)
{
	delete[] this->name;

	this->name = that.name;
	that.name = nullptr;

	cout << "Mammal - " << this->getName() << " : Mammal(Mammal&& that)\n";
}

Mammal::~Mammal()
{
	cout << "Destroying Mammal with name - " << this->getName() << "\n";

	delete[] this->name;
}

//This method assumes this->name is unitialized.
void Mammal::setName(const char* name)
{
	if(name == nullptr)
	{
		return;
	}

	this->name = new char[ strlen(name) + 1 ];
	strcpy(this->name, name);
}

const char* Mammal::getName() const 
{
	if(this->name == nullptr)
	{
		return "No Name Mammal";
	}

	return this->name;
}

void Mammal::yell() const
{
	cout << "Mammal Yell: Oooooo-aaaaaa-lala-laaaaaaaaa\n";
}

ostream& operator<<(ostream& output, const Mammal& that)
{
	output << that.getName() << "\n";

	return output;
}
