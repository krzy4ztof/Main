#ifdef __CYGWIN__

#include "Cygwin64CpuCalls.h"

#include<iostream> // cout, endl
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
			cout << "3 speed: '" << speed << "'" << endl;
			return true;
		}

		catch ( exception& e ) {
			cout << "exception: " << e.what() << endl;
			return false;
		}
	}

	bool toDoubleStream ( double& speed, const string& str ) {
		stringstream ss;
		ss << str;
		ss >> speed;

		if ( !ss.fail() ) {
			cout << "4 speed2: '" << speed << "'" << endl;
			return true;
		}

		else {
			cout << "fail" << endl;
			return false;
		}
	}
	vector<double>* findSpeedPtr ( vector <string>& internal ) {
		vector<double>* doubleVector = new vector<double>();
		cout << "findSpeedPtr" << endl;

		for ( int i1 = 0; i1 < 0; i1++ ) {
			cout << "i1: " << i1 << endl;
		}

		for ( int i2 = 0; i2 <= 0; i2++ ) {
			cout << "i2: " << i2 << endl;
		}

		//cout << "internal size " << internal.size() << endl;

		for ( int i = 0; i < internal.size(); i++ ) {
			cout << "1 '" << internal[i] << "'" << endl;
			boost::algorithm::trim ( internal[i] );
			cout << "2 '" << internal[i] << "'" << endl;
			double speed1;

			if ( toDoubleStod ( speed1, internal[i] ) ) {
				cout << "toDouble1 speed: '" << speed1 << "'" << endl;
				doubleVector->push_back ( speed1 );
			};
		}

		cout << "findSpeedPtr End" << endl;
		return doubleVector;
	}

	vector<double>& findSpeedRefError ( vector <string>& internal ) {
		// DO NOT DO IT
		// doubleVector is initialized on heap and returned as reference to outerMethod
		// The outerMethod has no way of deleting object on heap
		vector<double>* doubleVector = new vector<double>();

		for ( int i = 0; i < internal.size(); i++ ) {
			cout << "1 '" << internal[i] << "'" << endl;
			boost::algorithm::trim ( internal[i] );
			cout << "2 '" << internal[i] << "'" << endl;
			double speed2;

			if ( toDoubleStream ( speed2, internal[i] ) ) {
				cout << "toDouble2 speed: '" << speed2 << "'" << endl;
				doubleVector->push_back ( speed2 );
			};
		}

		return *doubleVector;
	}

	vector<double> findSpeedMove ( vector <string>& internal ) {
		// Move constructor is used
		vector<double> doubleVector;

		for ( int i = 0; i < internal.size(); i++ ) {
			cout << "1 '" << internal[i] << "'" << endl;
			boost::algorithm::trim ( internal[i] );
			cout << "2 '" << internal[i] << "'" << endl;
			double speed2;

			if ( toDoubleStream ( speed2, internal[i] ) ) {
				cout << "toDouble2 speed: '" << speed2 << "'" << endl;
				doubleVector.push_back ( speed2 );
			};
		}

		return doubleVector;
	}



	double Cygwin64CpuCalls::readCPUSpeedCygwin() {
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
					//cout << "no match" << endl;
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

		cout << "* 3 " << endl;
		// *doubleMinPtr - operator*
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

		//    cout << "del doubleMinPtr: " << *doubleMinPtr << endl;
		cout << "del minDouble: " << minDouble << endl;

		//   cout << "del doubleMinMove: " << *doubleMinMove << endl;
		return minDouble;
	}

}
#endif /* __CYGWIN__ */
