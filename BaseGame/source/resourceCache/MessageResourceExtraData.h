/*
 * MessageResourceExtraData.h
 *
 *  Created on: 12 lis 2018
 *      Author: Krzysztof
 */

#ifndef RESOURCECACHE_MESSAGERESOURCEEXTRADATA_H_
#define RESOURCECACHE_MESSAGERESOURCEEXTRADATA_H_

#include "IResourceExtraData.h"

#include <boost/cstdint.hpp> // boost::uintmax_t
#include <vector> // vector
#include <string> // string

namespace base_game {

class MessageResourceExtraData: public IResourceExtraData {
public:
	MessageResourceExtraData();
	virtual ~MessageResourceExtraData();

	virtual std::string vToString();

	void init(char* pRawBuffer, boost::uintmax_t rawSize);
	std::vector<char> getData();

private:
	std::vector<char> data;
};

} /* namespace base_game */

#endif /* RESOURCECACHE_MESSAGERESOURCEEXTRADATA_H_ */
