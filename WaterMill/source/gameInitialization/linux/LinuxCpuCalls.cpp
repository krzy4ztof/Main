#ifdef __linux__

#include "LinuxCpuCalls.h"

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
using std::min_element;

namespace base_game {
	LinuxCpuCalls::LinuxCpuCalls() {
		//ctor
	}

	LinuxCpuCalls::~LinuxCpuCalls() {
		//dtor
	}

	namespace linux_cpu_calls {

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

	}

	using linux_cpu_calls::findSpeedPtr ;

	unsigned long LinuxCpuCalls::readCPUSpeed() {
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

		vector<double>::iterator doubleMinPtr = min_element ( doubleVectorPtr->begin(), doubleVectorPtr->end() );
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




		vector<double>::iterator doubleIterPtr;
		double avgSpeed = 0;

		for (doubleIterPtr = doubleVectorPtr->begin(); doubleIterPtr != doubleVectorPtr->end(); doubleIterPtr++ ) {

			ss << "avgSpeed: " << avgSpeed << "; curSpeed: " << *doubleIterPtr;
			logger::info(ss);


			avgSpeed += *doubleIterPtr;

		}



		avgSpeed = avgSpeed / doubleVectorPtr->size();


		ss << "avgSpeed: " << avgSpeed << "; size: " << doubleVectorPtr->size();;
		logger::info(ss);



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

#endif /* __linux__ */
