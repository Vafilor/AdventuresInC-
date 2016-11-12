#include "Mammal.h"
#include <iostream>

#ifndef HUMAN_H
#define HUMAN_H

using std::ostream;

//Human publicly inherits from Mammal. Human is-a Mammal. Human can be treated like a Mammal as it has the interface of Mammal (and more).
//All of Mammal's public methods are public in human, protected methods are protected in human, and 
//Human can't access/use Mammal's private methods.
class Human : public Mammal
{
	private:
		//Contrived member, we use int* so we have to worry about memory allocation and see how it interacts with base class.
		int* favoriteNumber;

		void setFavoriteNumber(int favoriteNumber);
	public:
		explicit Human(const char* name);
		Human(int favoriteNumber, const char* name);
		Human(const Human& that);
		Human(Human&& that);

		//The destroyer of man, well, human(s).
		//You don't have to mark methods as virtual that are already virtual in the parent class(s), but it doesn't hurt and helps
		//to remind you that they are virtual.
		virtual ~Human();

		Human& operator=(const Human& that);
		Human& operator=(Human&& that);

		int getFavoriteNumber() const;
		virtual void yell() const;
		virtual void walk() const;
		
		friend ostream& operator<<(ostream& output, const Human& that);
};

#endif
