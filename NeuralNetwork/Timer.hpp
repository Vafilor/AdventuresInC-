#include <chrono>
#include <vector>
#include <ostream>
#include <stdexcept>

#ifndef TIMER_H
#define TIMER_H

using std::ostream;
using std::runtime_error;
using std::string;
using std::vector;

using std::chrono::system_clock;


class Timer
{
	//TODO - add verbose setting that prints everything to console
	//TODO - add suffix indicating time units (e.g. seconds) and include 2 decimal places
	private:
		bool verbose;
		ostream* output;
		
		vector<system_clock::time_point> timestamps;	
		vector<string> identifiers;

		/**
		* Outputs the elapsed time between start and end in seconds with two decimal places. 
		* Returns the elapsed time in seconds.
		*/			
		static std::chrono::duration<double> outputElapsedTime(ostream& os, const string& message, const system_clock::time_point& start, const system_clock::time_point& end);	
		
	public:
		Timer() : verbose(false) {};
		
		void setVerbose(bool verbose, ostream* os = nullptr);
				
		void mark(const string& identifier) throw(runtime_error);
		void mark() throw (runtime_error);
		
		friend ostream& operator<<(ostream& os, const Timer& timer);
};

#endif

