#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string> // string

namespace watermill {
	namespace string_utils {
	    char* stringToChar(std::string inputString);

	    void safe_delete_char_array(char* p);
	}
}

#endif // STRINGUTILS_H
