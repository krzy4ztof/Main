#include "IResourceLoader.h"
#include "../debugging/Logger.h"

#include <sstream>      // std::stringstream
#include <string> // std::string
#include <regex>// std::regex, std::match

using std::stringstream;
using std::string;
using std::regex;
using std::regex_match;

namespace base_game {
IResourceLoader::IResourceLoader() {
	logger::trace("Create IResourceLoader");
}

IResourceLoader::~IResourceLoader() {
	logger::trace("Destroy IResourceLoader");
}

bool IResourceLoader::matchesPattern(const string fileName) {
	stringstream ss;

	ss << "Pattern " << vGetPattern() << " fileName: " << fileName;

	logger::info(ss);

	string regexExpr = "^\\S*\\." + vGetPattern() + "$";

	// string regexExpr = "^\\S*\\.txt$";
	regex expr { regexExpr };

	bool matchResult = regex_match(fileName, expr);

	if (matchResult) {
		ss << fileName << " MATCHES: " << vGetPattern();
		logger::info(ss);

		return true;
	} else {
		ss << fileName << " DOES NOT MATCH " << vGetPattern();
		logger::info(ss);

		return false;

	}

}

}
