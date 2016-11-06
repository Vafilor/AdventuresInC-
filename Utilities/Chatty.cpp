//Chatty.h 
//A class that prints messages to the standard output for every constructor and assignment operator.

#include "Chatty.h"
#include <iostream>
#include <utility> //For std::move

using std::cout;
using std::move;

Chatty::Chatty()
{
	this->name = "Default Chatty";

	cout << this->name << " created : constructor()\n";
}

Chatty::Chatty(const string& name)
{
	this->name = name;
	
	cout << this->name << " created : constructor(string name)\n";
}

Chatty::Chatty(const Chatty& that)
{
	this->name = that.name;
	
	cout << this->name << " copied: constructor(const Chatty& that)\n";
}

Chatty::Chatty(Chatty&& that)
{
	//Move that.name instead of copying it. This is fine as that is a temporary object and will not be used elsewhere.
	//This will make that.name be an empty string.		
	this->name = move(that.name);

	cout << this->name << " moved : constructor(Chatty&& that)\n";
}

Chatty::~Chatty()
{
	cout << this->name << " destroyed\n";
}

Chatty& Chatty::operator=(const Chatty& that) 
{
	//Attempting to do self assignment, don't do anything.
	if(this == &that)
	{
		return *this;
	}

	this->name = that.name;

	cout << this->name << " assigned : operator=(const Chatty& that)\n";

	return *this;
}

Chatty& Chatty::operator=(Chatty&& that)
{
	//Attempting to assign temporary object to itself, don't do anything.
	if(this == &that)
	{
		return *this;	
	}

	//Move that.name instead of copying it. This is fine as that is a temporary object and will not be used elsewhere.
	//This will make that.name be an empty string.	
	this->name = move(that.name);

	cout << this->name << " assigned : operator=(Chatty&& that)\n";

	return *this;
}

const string& Chatty::getName() const
{
	return this->name;
}
