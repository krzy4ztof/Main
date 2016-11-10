#ifdef __CYGWIN__

#include "Cygwin64CpuCalls.h"

#include <iostream> // cout, endl
#include <string> // string
#include <vector> // vector
#include <sstream> // stringstream
#include <boost/algorithm/string.hpp> // boost::algorithm::to_lower(str)
#include <regex> //regex_search, smatch, pattern
#include <fstream> // ifstream
#include "../../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include "../../utilities/StringUtils.h"

using std::string;
using std::stringstream;
using std::vector;
using std::exception;
using std::ifstream;
using std::regex;
using std::smatch;

namespace base_game {
	Cygwin64CpuCalls::Cygwin64CpuCalls() {
		logger::trace("Create Cygwin64CpuCalls");
	}

	Cygwin64CpuCalls::~Cygwin64CpuCalls() {
		logger::trace("Destroy Cygwin64CpuCalls");
	}

	namespace cygwin64_cpu_calls {

		vector<double>* findSpeedPtr ( vector <string>& internal ) {
			vector<double>* doubleVector = new vector<double>();

			for ( size_t i = 0; i < internal.size(); i++ ) {
				boost::algorithm::trim ( internal[i] );
				double speed1;

				if ( string_utils::stringToDoubleStod ( speed1, internal[i] ) ) {
					doubleVector->push_back ( speed1 );
				};
			}

			return doubleVector;
		}

		vector<double>& findSpeedRefError ( vector <string>& internal ) {
			// DO NOT DO IT
			// doubleVector is initialized on heap and returned as reference to outerMethod
			// The outerMethod has no way of deleting object on heap
			vector<double>* doubleVector = new vector<double>();

			for ( size_t i = 0; i < internal.size(); i++ ) {
				boost::algorithm::trim ( internal[i] );
				double speed2;

				if ( string_utils::stringToDoubleStream ( speed2, internal[i] ) ) {
					doubleVector->push_back ( speed2 );
				};
			}

			return *doubleVector;
		}

		vector<double> findSpeedMove ( vector <string>& internal ) {
			// Move constructor is used
			vector<double> doubleVector;

			for ( size_t i = 0; i < internal.size(); i++ ) {
				boost::algorithm::trim ( internal[i] );
				double speed2;

				if ( string_utils::stringToDoubleStream ( speed2, internal[i] ) ) {
					doubleVector.push_back ( speed2 );
				};
			}

			return doubleVector;
		}
	}

	using cygwin64_cpu_calls::findSpeedPtr ;
	using cygwin64_cpu_calls::findSpeedRefError;
	using cygwin64_cpu_calls::findSpeedMove;

	unsigned long Cygwin64CpuCalls::readCPUSpeed() {
		string line;
		ifstream myfile ( "/proc/cpuinfo" );
		vector <string> internal;
		smatch matches;
		regex pattern ( "cpu mhz" );

		stringstream ss;
		if ( myfile.is_open() ) {
			while ( getline ( myfile, line ) ) {
				boost::algorithm::to_lower ( line );

				if ( regex_search ( line, matches, pattern ) ) {
					ss << "line: " << line;
					logger::trace(ss);

					for ( size_t i = 0; i < matches.size(); ++i )
						ss << "\tmatches[" << i << "]: " << matches[i];
					logger::trace(ss);

					string_utils::splitString ( internal, line, ':' );
				}

				else {
					// No match
				}

				ss << line;
				logger::trace(ss);

			}

			logger::trace("--------------");

			myfile.close();
		}

		else {
			logger::warning("Unable to open file");

		}

		ss << "internal size: " << internal.size();
		logger::trace(ss);

		// DO NOT DO IT
		//        vector<double>& doubleVectorRef = findSpeedRefError(internal);
		vector<double>* doubleVectorPtr = findSpeedPtr ( internal );

		for ( double speed3 : *doubleVectorPtr ) {
			ss << "speed vector ptr: " << speed3;
			logger::trace(ss);

		}

		vector<double> doubleVectorMove = findSpeedMove ( internal );

		for ( double speed3 : doubleVectorMove ) {
			ss << "speed vector move: " << speed3;
			logger::trace(ss);

		}

		vector<double>::iterator doubleMinPtr = std::min_element ( doubleVectorPtr->begin(), doubleVectorPtr->end() );
		logger::trace("* 41 ");

		double minDouble = 0;

		if ( doubleMinPtr != doubleVectorPtr->end() ) {
			logger::trace("!!!");
			ss << "doubleMinPtr1: " << *doubleMinPtr;
			logger::trace(ss);
			minDouble = *doubleMinPtr;
		}

		ss << "minDouble: " << minDouble;
		logger::trace(ss);
		logger::trace("* 5 ");
		vector<double>::iterator doubleMinMove = std::min_element ( doubleVectorMove.begin(), doubleVectorMove.end() );

		if ( doubleMinMove != doubleVectorMove.end() ) {
			ss << "doubleMinMove: " << *doubleMinMove << "; size: " << doubleMinMove.base();
			logger::trace(ss);
		}

		if ( doubleVectorPtr ) {
			logger::trace("delete doubleVectorPtr");
			delete doubleVectorPtr;
			doubleVectorPtr = nullptr;
		};

		ss << "del minDouble: " << minDouble;
		logger::trace(ss);

		unsigned long minUnsLong = static_cast <unsigned long> (minDouble);

		return minUnsLong;
	}

}
#endif /* __CYGWIN__ */
