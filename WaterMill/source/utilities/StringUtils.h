#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string> // string
#include <vector> // vector

namespace base_game {
namespace string_utils {
char* stringToChar(std::string inputString);
std::string charToString(char* inputChar);

void splitString(std::vector<std::string>& outputVector,
		const std::string& inputString, char delimiter);
bool stringToDoubleStod(double& outputDouble, const std::string& inputString);
bool stringToDoubleStream(double& outputDouble, const std::string& inputString);

//void safe_delete_char_array(char* p);

int isCharNumeric(const char* ccharptr_CharacterList);
int compareChars(const char *s1, const char *s2, bool intCaseSensitive);

void toLower(std::string& inputString);

bool isStringNumeric(const std::string& inputString);
bool doesStringContainsIgnoreCase(const std::string& inputString,
		const std::string& endingString);

}
}

#endif // STRINGUTILS_H
