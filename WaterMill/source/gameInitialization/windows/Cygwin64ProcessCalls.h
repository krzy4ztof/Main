#ifndef CYGWIN64PROCESSCALLS_H
#define CYGWIN64PROCESSCALLS_H

#ifdef __CYGWIN__
#include <string> // string

namespace watermill {
	class Cygwin64ProcessCalls {
		public:
			Cygwin64ProcessCalls();
			virtual ~Cygwin64ProcessCalls();
			bool isOnlyInstance ( const std::string& );


		protected:

		private:
	};
}
#endif /* __CYGWIN__ */
#endif // CYGWIN64PROCESSCALLS_H

