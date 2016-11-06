//ChattyTester.cpp - goes through various scenarios to demonstrate where what type of constructor or assignment operator is used.

#include <iostream>
#include <vector>
#include "Chatty.h"

using std::cout;

void constructors();
void arrayInitialization();
void functionReturn();
void collections();

Chatty makeChatty();

int main()
{
	constructors();
	arrayInitialization();
	functionReturn();
	collections();

	return 0;
}

void constructors()
{
	//Use string constructor for Chatty
	Chatty first("First Chatty");

	//Use string constructor for Chatty, but alternate syntax
	Chatty second = Chatty("Second Chatty");

	//Create temporary chatty object
	Chatty("Temporary Chatty");
}

void arrayInitialization()
{
	//Uses default constructor to make 3 Chatty objects.
	Chatty objects[3];

	//Uses explicit constructor to make two Chatty objects and then default constructor for one more.
	Chatty moreObjects[3] = { Chatty("First in Array"), Chatty("Second in Array")};

	//End of function, moreObjects[3] expires and the three objects are destroyed in opposite order created (think stack)
	//So default chatty is destroyed, then Second in Array, then First in Array
	//objects[3] expires and the three objects are destroyed, again in reverse order, but you can't tell from the messages printed out.
}

void functionReturn()
{
	//Although this might call Move Constructor (we have a new object and are assigning it a value), it probably won't as modern compilers optimize handling the case of 
	//returning objects from functions.
	Chatty newChatty = makeChatty(); 

	//Calls Move Assignment as newChatty already exists and makeChatty returns a temporary Chatty object.
	newChatty = makeChatty();
}

void collections()
{
	using std::vector;

	vector<Chatty> objects;
	//Note: Not sure why we don't see 3 calls to Chatty default constructor here.
	objects.reserve(3);	

	//Creates a Chatty object, then uses Move Constructor (as Chatty is a temporary object) to put it into vector
	objects.push_back(Chatty("First Item"));

	//Uses Move Assignment as objects already has a Chatty in the 0th spot
	objects[0] = Chatty("Replacement First Item");

	Chatty secondItem("Second Item");

	//Uses a copy constructor to put secondItem into vector as it is not a temporary object.
	objects.push_back(secondItem);


	//Uses Move Constructor to put new, temproary Chatty object into vector.
	objects.push_back(Chatty("Third Item"));
	
}

Chatty makeChatty()
{	
	return Chatty("Make Chatty From Function");
}
