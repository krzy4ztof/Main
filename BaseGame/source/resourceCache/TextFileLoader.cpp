/*
 * TextFileLoader.cpp
 *
 *  Created on: 13 sie 2018
 *      Author: Krzysztof
 */

#include "TextFileLoader.h"
#include "IResourceLoader.h"
#include "../debugging/Logger.h"

#include <string> // string
#include <memory> // shared_ptr

using std::string;
using std::shared_ptr;

namespace base_game {

TextFileLoader::TextFileLoader() {
	logger::trace("Create TextFileLoader");

}

TextFileLoader::~TextFileLoader() {
	logger::trace("Destroy TextFileLoader");
}

string TextFileLoader::vGetPattern() {
	return "*.txt";
}

namespace text_file_loader {
shared_ptr<IResourceLoader> createTextFileLoader() {
	TextFileLoader* loader = new TextFileLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
	return pointer;
}
}

} /* namespace base_game */
