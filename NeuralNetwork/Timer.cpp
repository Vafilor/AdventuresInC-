#include "Timer.hpp"

#include <vector>
#include <string>
#include <ctime>
#include <ostream>

using std::endl;
using std::ostream;
using std::string;

void Timer::setVerbose(bool verbose, ostream* os)
{
	this->verbose = verbose;
	this->output = os;
}

void Timer::mark() throw (runtime_error)
{
	if(this->timestamps.size() % 2 == 0)
	{
		throw runtime_error("timestamps are even, can't mark without identifier");
	}

	this->timestamps.push_back( time(0) );
	
	if(this->verbose && this->output != nullptr) {
		outputElapsedTime(*this->output, this->identifiers.back(), this->timestamps[ this->timestamps.size() - 2], this->timestamps.back());
	}	
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
	for(int i = 0; i < timer.timestamps.size(); i += 2)
	{
		Timer::outputElapsedTime(os, timer.identifiers[i / 2], timer.timestamps[i], timer.timestamps[i+1]);
	}
	
	Timer::outputElapsedTime(os, "Total Time", timer.timestamps.front(), timer.timestamps.back());
	
	return os;
}

double Timer::outputElapsedTime(ostream& os, const string& message, const clock_t& start, const clock_t& end)
{
	//TODO 2 decimal place formatting
	double timeElapsed = difftime(end, start);
	os << message << ": " << timeElapsed << " seconds" << endl;
	
	return timeElapsed;
}