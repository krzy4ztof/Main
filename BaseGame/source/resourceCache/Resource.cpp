#include "Resource.h"
#include "../debugging/Logger.h"
#include "../utilities/StringUtils.h"

#include <sstream>      // std::stringstream
#include <string> //string
using std::string;
using std::stringstream;

namespace base_game {
	Resource::Resource(const string &name) {
		logger::info("Create Resource");

					stringstream ss;
			ss << "Orig name: " << name;
			logger::info(ss);

			this->name = name;
		string_utils::toLower(this->name);


			ss << "Tolower name: " << this->name;
			logger::info(ss);

		//TODO: change name to lowercase
	}

	Resource::~Resource() {
		logger::info("Destroy Resource");
	}

const string Resource::getName() const {
		return name;
	}

}
