#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <typeinfo> // typeid

namespace base_game {
	namespace templates {


		template <class className>
		void safe_delete(className*& p) {
			std::stringstream ss;
			if ((p)!=nullptr) {
				ss << "SAFE_DELETE delete: " << typeid(p).name();
				logger::trace(ss);
				delete (p);
				(p)=nullptr;
			} else {
				logger::trace("SAFE_DELETE pointer null");
			}

		}

		template <class className>
		void safe_delete1(className*& p) {
			if ((p)!=NULL) {
				logger::trace("SAFE_DELETE delete");
				delete (p);
				(p)=NULL;
			} else {
				logger::trace("SAFE_DELETE pointer null");

			}

		}
	}
}

#endif // TEMPLATES_H
