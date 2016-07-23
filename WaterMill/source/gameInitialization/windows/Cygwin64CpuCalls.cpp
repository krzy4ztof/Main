#ifdef __CYGWIN__

#include "Cygwin64CpuCalls.h"

#include <iostream> // cout, endl
#include <string> // string
#include <vector> // vector
#include <sstream> // stringstream
#include <boost/algorithm/string.hpp> // boost::algorithm::to_lower(str)
#include <regex> //regex_search, smatch, pattern
#include <fstream> // ifstream

using namespace std;

namespace watermill {
	Cygwin64CpuCalls::Cygwin64CpuCalls() {
		//ctor
	}

	Cygwin64CpuCalls::~Cygwin64CpuCalls() {
		//dtor
	}

	namespace cygwin64_cpu_calls {

		// You could also take an existing vector as a parameter.
		void split ( vector<string>& internal, const string& str, char delimiter ) {
			stringstream ss ( str ); // Turn the string into a stream.
			string tok;

			while ( getline ( ss, tok, delimiter ) ) {
				internal.push_back ( tok );
			}
		}


		bool toDoubleStod ( double& speed, const string& str ) {
			try {
				speed = stod ( str );
				return true;
			}

			catch ( exception& e ) {
				return false;
			}
		}

		bool toDoubleStream ( double& speed, const string& str ) {
			stringstream ss;
			ss << str;
			ss >> speed;

			if ( !ss.fail() ) {
				return true;
			}

			else {
				return false;
			}
		}
		vector<double>* findSpeedPtr ( vector <string>& internal ) {
			vector<double>* doubleVector = new vector<double>();

			for ( int i = 0; i < internal.size(); i++ ) {
				boost::algorithm::trim ( internal[i] );
				double speed1;

				if ( toDoubleStod ( speed1, internal[i] ) ) {
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

			for ( int i = 0; i < internal.size(); i++ ) {
				boost::algorithm::trim ( internal[i] );
				double speed2;

				if ( toDoubleStream ( speed2, internal[i] ) ) {
					doubleVector->push_back ( speed2 );
				};
			}

			return *doubleVector;
		}

		vector<double> findSpeedMove ( vector <string>& internal ) {
			// Move constructor is used
			vector<double> doubleVector;

			for ( int i = 0; i < internal.size(); i++ ) {
				boost::algorithm::trim ( internal[i] );
				double speed2;

				if ( toDoubleStream ( speed2, internal[i] ) ) {
					doubleVector.push_back ( speed2 );
				};
			}

			return doubleVector;
		}
	}

	using cygwin64_cpu_calls::split ;
	using cygwin64_cpu_calls::toDoubleStod ;
	using cygwin64_cpu_calls::toDoubleStream ;
	using cygwin64_cpu_calls::findSpeedPtr ;
	using cygwin64_cpu_calls::findSpeedRefError;
	using cygwin64_cpu_calls::findSpeedMove;

	unsigned long Cygwin64CpuCalls::readCPUSpeed() {
		string line;
		ifstream myfile ( "/proc/cpuinfo" );
		vector <string> internal;
		smatch matches;
		regex pattern ( "cpu mhz" );

		if ( myfile.is_open() ) {
			while ( getline ( myfile, line ) ) {
				boost::algorithm::to_lower ( line );

				if ( regex_search ( line, matches, pattern ) ) {
					cout << "line: " << line << endl;

					for ( int i = 0; i < matches.size(); ++i )
						cout << "\tmatches[" << i << "]: "
							 << matches[i] << endl;

					split ( internal, line, ':' );
				}

				else {
					// No match
				}

				cout << line << '\n';
			}

			cout << "--------------" << endl;
			myfile.close();
		}

		else {
			cout << "Unable to open file";
		}

		cout << "internal size: " << internal.size() << endl;
		// DO NOT DO IT
		//        vector<double>& doubleVectorRef = findSpeedRefError(internal);
		vector<double>* doubleVectorPtr = findSpeedPtr ( internal );

		for ( double speed3 : *doubleVectorPtr ) {
			cout << "speed vector ptr: " << speed3 << endl;
		}

		vector<double> doubleVectorMove = findSpeedMove ( internal );

		for ( double speed3 : doubleVectorMove ) {
			cout << "speed vector move: " << speed3 << endl;
		}

		vector<double>::iterator doubleMinPtr = std::min_element ( doubleVectorPtr->begin(), doubleVectorPtr->end() );
		cout << "* 41 " << endl;
		double minDouble = 0;

		if ( doubleMinPtr != doubleVectorPtr->end() ) {
			cout << "!!!" << endl;
			cout << "doubleMinPtr1: " << *doubleMinPtr << endl;
			minDouble = *doubleMinPtr;
		}

		cout << "minDouble: " << minDouble << endl;
		cout << "* 5 " << endl;
		vector<double>::iterator doubleMinMove = std::min_element ( doubleVectorMove.begin(), doubleVectorMove.end() );

		if ( doubleMinMove != doubleVectorMove.end() ) {
			cout << "doubleMinMove: " << *doubleMinMove << "; size: " << doubleMinMove.base() << endl;
		}

		if ( doubleVectorPtr ) {
			cout << "delete doubleVectorPtr" << endl;
			delete doubleVectorPtr;
			doubleVectorPtr = nullptr;
		};

		cout << "del minDouble: " << minDouble << endl;

		unsigned long minUnsLong = static_cast <unsigned long> (minDouble);

		return minUnsLong;
	}

}
#endif /* __CYGWIN__ */
