/*
 * XmlResourceExtraData.h
 *
 *  Created on: 5 sie 2018
 *      Author: Krzysztof
 */

#ifndef RESOURCECACHE_XMLRESOURCEEXTRADATA_H_
#define RESOURCECACHE_XMLRESOURCEEXTRADATA_H_

#include "IResourceExtraData.h"

#include <boost/property_tree/ptree.hpp> // ptree
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <string>

namespace base_game {

class XmlResourceExtraData: public IResourceExtraData {
public:
	XmlResourceExtraData();
	virtual ~XmlResourceExtraData();

	virtual std::string vToString() {
		return "XmlResourceExtraData";
	}

	void parseXml(char* pRawBuffer, boost::uintmax_t rawSize);

	boost::property_tree::ptree* getRoot() {
		return m_pPtree;
	}
;

	/*
	 void ParseXml(char* pRawBuffer);
	 TiXmlElement* GetRoot(void) { return m_xmlDocument.RootElement(); }
	 */

protected:

private:
	boost::property_tree::ptree* m_pPtree;
};

} /* namespace base_game */

#endif /* RESOURCECACHE_XMLRESOURCEEXTRADATA_H_ */
