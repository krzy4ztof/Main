/*
 * BmpResourceExtraData.h
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_BMPRESOURCEEXTRADATA_H_
#define GRAPHICS3D_BMPRESOURCEEXTRADATA_H_

#include "../resourceCache/IResourceExtraData.h"

#include <boost/cstdint.hpp> // boost::uintmax_t
#include <vector> // vector
#include <string> // string

namespace base_game {

class BmpResourceExtraData: public IResourceExtraData {
public:
	BmpResourceExtraData();
	virtual ~BmpResourceExtraData();

	virtual std::string vToString();

	void init(char* pRawBuffer, boost::uintmax_t rawSize);
	std::vector<char> getData();

private:
	std::vector<char> data;
};

} /* namespace base_game */

#endif /* GRAPHICS3D_BMPRESOURCEEXTRADATA_H_ */
