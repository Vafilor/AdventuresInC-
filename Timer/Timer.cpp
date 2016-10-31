#include "Timer.h"

#include <vector>
#include <string>
#include <ostream>
#include <chrono>

using std::endl;
using std::ostream;
using std::string;
using std::chrono::system_clock;

//TODO add precision formatting
//TODO - add way to have cumulative times? e.g. accumulate entries for something specific and add them.
//-short functions called multiple times, see what times how much time

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

	this->timestamps.push_back( system_clock::now() );
	
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

	this->timestamps.push_back( system_clock::now() );
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

std::chrono::duration<double> Timer::outputElapsedTime(ostream& os, const string& message, const system_clock::time_point& start, const system_clock::time_point& end)
{
	std::chrono::duration<double> timeElapsed = end - start;
	os << message << ": " << timeElapsed.count() << " seconds" << endl;
	
	return timeElapsed;
}