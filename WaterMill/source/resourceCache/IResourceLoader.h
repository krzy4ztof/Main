#ifndef IRESOURCELOADER_H
#define IRESOURCELOADER_H

#include <string> // string

namespace base_game {
	class IResourceLoader {
		public:
			IResourceLoader();
			virtual ~IResourceLoader();

	virtual std::string vGetPattern()=0;

	/*
	 * 		virtual std::string VGetPattern()=0;
	 virtual bool VUseRawFile()=0;
	 virtual bool VDiscardRawBufferAfterLoad()=0;
	 virtual bool VAddNullZero() { return false; }
	 virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize)=0;
	 virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, shared_ptr<ResHandle> handle)=0;
	 *
	 */
	bool matchesPattern(const std::string fileName);

		protected:

		private:
	};
}
#endif // IRESOURCELOADER_H
