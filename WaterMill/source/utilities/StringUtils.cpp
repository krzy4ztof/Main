#include "StringUtils.h"

#include <cstring>// strcpy
#include <string> // string

using std::string;
using std::strcpy;

namespace watermill {
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
	}
}
