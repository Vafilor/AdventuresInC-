ChattyTester : Chatty.o ChattyTester.cpp
	g++ -std=c++11 ChattyTester.cpp Chatty.o -o ChattyTester.out

Chatty.o : Chatty.h Chatty.cpp
	g++ -std=c++11 -c Chatty.cpp

MammalTester : Human.o Cat.o Mammal.o MammalTester.cpp
	g++ -std=c++11 MammalTester.cpp Human.o Cat.o Mammal.o -o MammalTester.out

Mammal.o : Mammal.h Mammal.cpp
	g++ -std=c++11 -c Mammal.cpp

Human.o : Mammal.h Mammal.cpp Human.h Human.cpp
	g++ -std=c++11 -c Human.cpp

Cat.o : Mammal.h Mammal.cpp Cat.h Cat.cpp
	g++ -std=c++11 -c Cat.cpp

clean:
	rm ChattyTester.out Chatty.o MammalTester.out Mammal.o Human.o
