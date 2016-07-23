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


	namespace cygwin64_process_calls {
		int isNumeric ( const char* ccharptr_CharacterList ) ;
		int strcmp_Wrapper ( const char *s1, const char *s2, bool intCaseSensitive );
	}

}
#endif /* __CYGWIN__ */
#endif // CYGWIN64PROCESSCALLS_H

