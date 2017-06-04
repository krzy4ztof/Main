#include "StringUtils.h"
#include "../utilities/Templates.h"

#include <cstring>// strcpy
#include <string> // string, std::stod
#include <vector> // vector
#include <sstream> // stringstream

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with
#include <boost/algorithm/string.hpp>  // to_lower, to_lower_copy, contains

using std::string;
using std::strcpy;
using std::stringstream;
using std::vector;
using std::exception;
using std::transform;
using std::stod;

//using boost::ends_with;
using boost::algorithm::to_lower;
//using boost::algorithm::to_lower_copy;
using boost::algorithm::contains;


namespace base_game {
namespace string_utils {

/*
 void safe_delete_char_array(char* p) {
 if (p) {
 delete [] (p);
 (p)=nullptr;
 }
 }
 */
char* stringToChar(string inputString) {
	char* outputChar = new char[inputString.length() + 1];
	strcpy(outputChar, inputString.c_str());
	return outputChar;
}

string charToString(char* inputChar) {
	string str(inputChar);
	return str;
}

// You could also take an existing vector as a parameter.
void splitString(vector<string>& outputVector, const string& inputString,
		char delimiter) {
	stringstream ss(inputString); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		outputVector.push_back(tok);
	}
}

bool stringToDoubleStod(double& outputDouble, const string& inputString) {
	try {
		outputDouble = stod(inputString);
		return true;
	}

	catch (exception& e) {
		return false;
	}
}

bool stringToDoubleStream(double& outputDouble, const string& inputString) {
	stringstream ss;
	ss << inputString;
	ss >> outputDouble;

	if (!ss.fail()) {
		return true;
	}

	else {
		return false;
	}
}

int isCharNumeric(const char* ccharptr_CharacterList) {

	//		int isNumeric ( const char* ccharptr_CharacterList ) {
	for (; *ccharptr_CharacterList; ccharptr_CharacterList++)
		if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9') {
			return 0;    // false
		}

	return 1; // true
}

bool isStringNumeric(const string& inputString) {

	bool has_only_digits = true;
	for (size_t n = 0; n < inputString.length(); n++) {
		if (!isdigit(inputString[n])) {
			has_only_digits = false;
			break;
		}
	}

	return has_only_digits;
}

int compareChars(const char *s1, const char *s2, bool intCaseSensitive) {
	//		int strcmp_Wrapper ( const char *s1, const char *s2, bool intCaseSensitive ) {
	if (intCaseSensitive) {
		return !strcmp(s1, s2);
	}

	else {
		return !strcasecmp(s1, s2);
	}
}

void toLower(string& inputString) {
	transform(inputString.begin(), inputString.end(), inputString.begin(),
			::tolower);
}

bool doesStringContainsIgnoreCase(const string& inputString,
		const string& endingString) {

	stringstream ss;

	string lowerInputString = inputString;
	to_lower(lowerInputString);
	string lowerEndingString = endingString;
	to_lower(lowerEndingString);

	//string lowerInputString = to_lower_copy(lowerInputString);
	//string lowerEndingString = to_lower_copy(endingString);


	ss
			<< "doesString #" + lowerInputString + "# ends with #"
					+ lowerEndingString + "#";
	logger::trace(ss);


	bool result = contains(lowerInputString,
			lowerEndingString);

	return result;


}
}
}
