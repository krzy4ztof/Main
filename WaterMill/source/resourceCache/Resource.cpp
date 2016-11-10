#include "Resource.h"
#include "../debugging/Logger.h"

#include <string> //string
using std::string;

namespace base_game {
	Resource::Resource(const string &name) {
		logger::trace("Create Resource");
		this->name = name;
		//TODO: change name to lowercase
	}

	Resource::~Resource() {
		logger::trace("Destroy Resource");
	}

	const string Resource::getName() {
		return name;
	}
}
