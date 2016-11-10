#include "Resource.h"
#include "../debugging/Logger.h"

#include <string> //string
using std::string;

namespace base_game {
	Resource::Resource(const string &name) {
		logger::info("Create Resource");
		this->name = name;
		//TODO: change name to lowercase
	}

	Resource::~Resource() {
		logger::info("Destroy Resource");
	}

	const string Resource::getName() {
		return name;
	}
}
