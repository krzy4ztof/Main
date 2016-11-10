#ifndef RESOURCE_H
#define RESOURCE_H

#include <string> //string

namespace base_game {
	class Resource {
		public:
			Resource(const std::string &name);
			virtual ~Resource();
			const std::string getName();

		protected:

		private:
			std::string name;
	};
}

#endif // RESOURCE_H
