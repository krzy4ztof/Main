/*
 * XmlResourceExtraData.cpp
 *
 *  Created on: 5 sie 2018
 *      Author: Krzysztof
 */

#include "XmlResourceExtraData.h"
#include "../debugging/Logger.h"
#include "../utilities/PropertyTreeUtils.h"
#include "../utilities/Templates.h"

#include <boost/property_tree/ptree.hpp> // ptree
#include <boost/property_tree/xml_parser.hpp> // read_xml
#include <boost/cstdint.hpp> // boost::uintmax_t

#include <istream> // std::istream, std::basic_istream<char>
#include <sstream> // std::stringbuf, std::stringstream


using boost::property_tree::ptree;
using boost::property_tree::read_xml;
using boost::uintmax_t;

using std::istream;
using std::stringbuf;
using std::stringstream;


namespace base_game {

XmlResourceExtraData::XmlResourceExtraData() {
	logger::trace("Create XmlResourceExtraData");
	m_pPtree = nullptr;

}

XmlResourceExtraData::~XmlResourceExtraData() {
	logger::trace("Destroy XmlResourceExtraData");
	templates::safe_delete<ptree> (m_pPtree);
}

void XmlResourceExtraData::parseXml(char* pRawBuffer, uintmax_t rawSize) {

	stringstream ss;
	m_pPtree = new ptree();

//	string filename = shrdPtrResourceCache->tempGetAssetsFolder()
//			+ resourceName;

	logger::info("--START STRINGBUF---");


	stringbuf myStreamBuf;
	//myStreamBuf.setg(pRawBuffer, pRawBuffer, pRawBuffer + rawSize);

	myStreamBuf.sputn(pRawBuffer, rawSize);

	istream inStream(&myStreamBuf);


//	ss << myStreamBuf.str(); //OK

//	logger::info(ss);

	logger::info("--STOP STRINGBUF---");




	read_xml(inStream, *m_pPtree);

	logger::info("--STOP READ_XML---");

	//read_xml(pRawBuffer, *m_pPtree);

	property_tree_utils::print_tree(*m_pPtree, 0);

	logger::info("--STOP PRINT_TREE---");

	// TODO zamiast
	// read_xml(filename, *pPtree);
	// użyc:
	// void read_xml(std::basic_istream<typename Ptree::key_type::value_type> &stream,Ptree &pt,

	// return pPtree;
}

} /* namespace base_game */
