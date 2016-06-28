#include "Timer.hpp"

#include <vector>
#include <string>
#include <ctime>
#include <ostream>

using std::endl;
using std::ostream;
using std::string;

Timer::Timer()
{	
}

void Timer::mark() throw (runtime_error)
{
	if(this->timestamps.size() % 2 == 0)
	{
		throw runtime_error("timestamps are even, can't mark without identifier");
	}

	this->timestamps.push_back( time(0) );
}

void Timer::mark(const string& identifier) throw (runtime_error)
{
	if(this->timestamps.size() % 2 == 1)
	{
		throw runtime_error("Mismatch between identifiers and timerstamps");
	}

	this->timestamps.push_back( time(0) );
	this->identifiers.push_back(identifier);
}

ostream& operator<<(ostream& os, const Timer& timer)
{
	double timeElapsed = 0.0;

	for(int i = 0; i < timer.timestamps.size(); i += 2)
	{
		timeElapsed = difftime(timer.timestamps[i + 1], timer.timestamps[i]);
	
		os << timer.identifiers[i / 2] << ":" << timeElapsed << endl;
	}
	
	return os;
}