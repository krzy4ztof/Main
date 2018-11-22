/*
 * MessageParams.h
 *
 *  Created on: 12 lis 2018
 *      Author: Krzysztof
 */

#ifndef RESOURCECACHE_MESSAGEPARAMS_H_
#define RESOURCECACHE_MESSAGEPARAMS_H_

#include <string> // string

namespace base_game {

class MessageParams {
public:
	MessageParams(std::string language, std::string encoding);
	virtual ~MessageParams();

	std::string getLanguage();
	std::string getEncoding();
	std::string getCode();


	void describeYourself();

private:
	std::string language;
	std::string encoding;

};

} /* namespace base_game */

#endif /* RESOURCECACHE_MESSAGEPARAMS_H_ */
