/*
 * TextFileLoader.h
 *
 *  Created on: 13 sie 2018
 *      Author: Krzysztof
 */

#ifndef RESOURCECACHE_TEXTFILELOADER_H_
#define RESOURCECACHE_TEXTFILELOADER_H_

#include "DefaultResourceLoader.h"
#include "IResourceLoader.h"

#include <string> // string
#include <memory> // shared_ptr

namespace base_game {

class TextFileLoader: public DefaultResourceLoader {
public:
	TextFileLoader();
	virtual ~TextFileLoader();

	virtual std::string vGetPattern();
};

namespace text_file_loader {
std::shared_ptr<IResourceLoader> createTextFileLoader();
}

} /* namespace base_game */

#endif /* RESOURCECACHE_TEXTFILELOADER_H_ */
