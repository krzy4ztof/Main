#include "NumberUtils.h"

#include <boost/numeric/conversion/cast.hpp>
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::stringstream;

namespace base_game {
	namespace number_utils {
		unsigned long long toUnsignLongLong(long inValue) {
			unsigned long long outValue = 0;
			stringstream ss;
			ss << "number utils toLong inValue : " << inValue;
			logger::info(ss);
			try {
				outValue = boost::numeric_cast<unsigned long long>(inValue);
			} catch (boost::numeric::bad_numeric_cast &ex) {
				ss << "Exception: " << ex.what();
				logger::error(ss);
			}
			ss << "number utils toLong outValue : " << outValue;
			logger::info(ss);

			return outValue;
		}
	}
}
