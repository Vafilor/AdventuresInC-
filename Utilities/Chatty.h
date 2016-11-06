//Chatty.h 
//A class that prints messages to the standard output for every constructor and assignment operator.

#include <string>

#ifndef CHATTY_H
#define CHATTY_H

using std::string;

class Chatty
{
	private:
		string name;

	public:
		//Default Constructor
		Chatty();
		
		//Constructor
		Chatty(const string& name);

		//Copy Constructor
		//Used when copying one object from another Chatty a; Chatty b(a);
		//Or when a function argument is of type Chatty and you pass it. E.g. 
		// void func(Chatty that); When you pass a Chatty to func, it will use Copy Constructor to create that.
		Chatty(const Chatty& that);
		
		//Move Constructor
		//Used when creating a Chatty object from a temporary object. This may happen when creating a Chatty object
		//from a function that returns a Chatty object, but modern compilers might not, as they work around it.
		//Collections can use this too, e.g. vector's push_back, so that you can do this
		//vector myVector; myVector.push_back(Chatty("test"))
		//This is can be more efficient than using a copy constructor, especially if you have data on the heap.
		//As the temporary object won't be used anywhere else.
		Chatty(Chatty&& that);

		//Destructor
		~Chatty();
		
		const string& getName() const;

		//Copy Assignment
		//Used when assigning a non-temporary Chatty object to an existing Chatty object, as in
		//Chatty a; Chatty b; a = b;
		Chatty& operator=(const Chatty& that);
		
		//Move Assignment
		//Used when assigning a temporary Chatty object to an existing Chatty object, as in
		//Chatty a; a = Chatty("temp"); 
		Chatty& operator=(Chatty&& that);
};

#endif
