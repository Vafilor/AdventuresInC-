#include "Mammal.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;

#ifndef CAT_H
#define CAT_H

class Cat : public Mammal
{
	private:
		//No memory allocation here. This makes the class a lot simpler.
		string petName; 

		//Private setter to help encapsulate setting pet name.
		//It's pretty simple logic now, but this allows us to have more control over what is allow, and helps keep changes centralized.
		void setPetName(const char* petName);
	public:
		//See the implementation. We will call another constructor for the default constructor.
		Cat();

		//We could do string here instead of const char*, but we use the same form as Mammal has for consistency.
		//Also, if we had string, it would convert the char* to string first, giving us extra overhead.
		explicit Cat(const char* name);
		Cat(const char* name, const char* petName);

		//Here we explicitly say to generate the default Copy Constructor. 
		//The default one calls the base Copy Constructor.
		//You can also use the keyword delete instead of default. 
		//That will make it so that that method is not automatically generated.
		Cat(const Cat& that) = default;
		Cat(Cat&& that);
		
		//Nothing to do here, but we define it for good measure in case we edit the class later.
		virtual ~Cat();

		Cat& operator=(const Cat& that);
		Cat& operator=(Cat&& that);
		
		const string& getPetName() const;

		virtual void yell() const;
		virtual void walk() const;

		friend ostream& operator<<(ostream& output, const Cat& that);
};

#endif
