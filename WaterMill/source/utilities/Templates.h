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
				logger::info(ss);
				delete (p);
				(p)=nullptr;
			} else {
				logger::info("SAFE_DELETE pointer null");
			}

		}

		template <class className>
		void safe_delete1(className*& p) {
			if ((p)!=NULL) {
				logger::info("SAFE_DELETE delete");
				delete (p);
				(p)=NULL;
			} else {
				logger::info("SAFE_DELETE pointer null");

			}

		}
	}
}

#endif // TEMPLATES_H
