#include "StringUtils.h"

#include <cstring>// strcpy
#include <string> // string
#include <vector> // vector
#include <sstream> // stringstream

using std::string;
using std::strcpy;
using std::stringstream;
using std::vector;
using std::exception;

namespace base_game {
	namespace string_utils {

		void safe_delete_char_array(char* p) {
			if (p) {
				delete [] (p);
				(p)=nullptr;
			}
		}
		char* stringToChar(string inputString) {
			char* outputChar = new char[inputString.length() + 1];
			strcpy ( outputChar, inputString.c_str() );
			return outputChar;
		}

		string charToString(char* inputChar) {
			string str(inputChar);
			return str;
		}

		// You could also take an existing vector as a parameter.
		void splitString ( vector<string>& outputVector, const string& inputString, char delimiter ) {
			stringstream ss ( inputString ); // Turn the string into a stream.
			string tok;

			while ( getline ( ss, tok, delimiter ) ) {
				outputVector.push_back ( tok );
			}
		}


		bool stringToDoubleStod ( double& outputDouble, const string& inputString ) {
			try {
				outputDouble = stod ( inputString );
				return true;
			}

			catch ( exception& e ) {
				return false;
			}
		}

		bool stringToDoubleStream ( double& outputDouble, const string& inputString ) {
			stringstream ss;
			ss << inputString;
			ss >> outputDouble;

			if ( !ss.fail() ) {
				return true;
			}

			else {
				return false;
			}
		}

		int isCharNumeric ( const char* ccharptr_CharacterList ) {

			//		int isNumeric ( const char* ccharptr_CharacterList ) {
			for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++ )
				if ( *ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9' ) {
					return 0;    // false
				}

			return 1; // true
		}

		int compareChars ( const char *s1, const char *s2, bool intCaseSensitive ) {
			//		int strcmp_Wrapper ( const char *s1, const char *s2, bool intCaseSensitive ) {
			if ( intCaseSensitive ) {
				return !strcmp ( s1, s2 );
			}

			else {
				return !strcasecmp ( s1, s2 );
			}
		}
	}
}
