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

