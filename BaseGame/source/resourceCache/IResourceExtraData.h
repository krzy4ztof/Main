/*
 * IResourceExtraData.h
 *
 *  Created on: 5 sie 2018
 *      Author: Krzysztof
 */

#ifndef RESOURCECACHE_IRESOURCEEXTRADATA_H_
#define RESOURCECACHE_IRESOURCEEXTRADATA_H_

#include <string>

namespace base_game {

class IResourceExtraData {
public:
	IResourceExtraData();
	virtual ~IResourceExtraData();

	virtual std::string vToString()=0;
};

} /* namespace base_game */

#endif /* RESOURCECACHE_IRESOURCEEXTRADATA_H_ */
