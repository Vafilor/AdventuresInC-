ChattyTester : Chatty.o ChattyTester.cpp
	g++ -std=c++11 ChattyTester.cpp Chatty.o -o ChattyTester.out

Chatty.o : Chatty.h Chatty.cpp
	g++ -std=c++11 -c Chatty.cpp

clean:
	rm ChattyTester.out Chatty.o
