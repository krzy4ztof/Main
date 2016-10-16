#include "Resource.h"

#include <string> //string
using std::string;

namespace base_game {
	Resource::Resource(const string &name) {
		this->name = name;
		//TODO: change name to lowercase
	}

	Resource::~Resource() {
		//dtor
	}

	const string Resource::getName() {
		return name;
	}
}
