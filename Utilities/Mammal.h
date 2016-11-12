//Mammal.h 
//Class used to demonstrate inheritance with dynamic memory management.

#include <iostream>

#ifndef MAMMAL_H
#define MAMMAL_H

using std::ostream;

class Mammal
{
	private:
		char* name;
		void setName(const char* name);

	public:
		Mammal();
		explicit Mammal(const char* name);
		Mammal(const Mammal& that);
		Mammal(Mammal&& that);

		//Have to make destructor virtual so that any child class will have its destructor called first 
		//in the cases where we have a pointer to mammal or reference to mammal and it is destroyed.
		//Without virtual, only the Mammal destructor would be called, not the derived class destructor.
		virtual ~Mammal();

		Mammal& operator=(const Mammal& that);
		Mammal& operator=(Mammal&& that);

		//Not virtual as we want exactly this behavior for getName(), no one can change it.
		const char* getName() const;

		//Virtual methods so child classes can override
		// = 0 means that this is pure virtual function, this makes Mammal an abstract class, so you can't create instances of it.
		//Also, with = 0, these methods are pure virtual methods, so you don't have to provide a definition for them, but the children do.
		//But you can provide a definition and children can use the default definition by invoking it. The children still have to write the method though, even if all it does is call Mammal::walk();
		//Force children to provide their own walk method
		virtual void walk() const = 0;
		
		//But we'll provide a default Mammalian yell method, so children can use it.
		virtual void yell() const = 0;

		//Create a method to handle output. Children can use this, but have to use a type cast. See Human.cpp
		friend ostream& operator<<(ostream& output, const Mammal& that);

};


#endif
