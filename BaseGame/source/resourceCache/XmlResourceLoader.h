#ifndef XMLRESOURCELOADER_H
#define XMLRESOURCELOADER_H

#include "IResourceLoader.h"
#include <memory> // shared_ptr
#include <string> // string

namespace base_game {
	class XmlResourceLoader : public IResourceLoader {
		public:
			XmlResourceLoader();
			virtual ~XmlResourceLoader();

	virtual std::string vGetPattern();

		protected:

		private:
	};

	namespace xml_resource_loader {
		std::shared_ptr<IResourceLoader> createXmlResourceLoader();
	}
}
#endif // XMLRESOURCELOADER_H
