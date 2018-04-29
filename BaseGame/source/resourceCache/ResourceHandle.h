#ifndef RESOURCEHANDLE_H
#define RESOURCEHANDLE_H

#include "Resource.h"

namespace base_game {
	class ResourceHandle {
		public:
			ResourceHandle(Resource& resource);
			virtual ~ResourceHandle();
			Resource getResource();

		protected:
			Resource m_resource;

		private:
	};
}

#endif // RESOURCEHANDLE_H
