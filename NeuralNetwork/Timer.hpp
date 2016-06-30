#include <ctime>
#include <vector>
#include <ostream>
#include <stdexcept>


#ifndef TIMER_H
#define TIMER_H

using std::ostream;
using std::runtime_error;
using std::string;
using std::vector;

class Timer
{
	//TODO - add verbose setting that prints everything to console
	//TODO - add suffix indicating time units (e.g. seconds) and include 2 decimal places
	private:
		vector<clock_t> timestamps;	
		vector<string> identifiers;
		
	public:
		Timer();
				
		void mark(const string& identifier) throw(runtime_error);
		void mark() throw (runtime_error);
		
		friend ostream& operator<<(ostream& os, const Timer& timer);
};

#endif

