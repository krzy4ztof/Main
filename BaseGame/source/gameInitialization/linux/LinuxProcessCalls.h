#ifndef LINUXPROCESSCALLS_H
#define LINUXPROCESSCALLS_H

#ifdef __linux__
#include <string> // string

namespace base_game {
	class LinuxProcessCalls {
	public:
		LinuxProcessCalls();
		virtual ~LinuxProcessCalls();
		bool isOnlyInstance ( const std::string& );

	protected:

	private:
	};
}
#endif /* __linux__ */
#endif // LINUXPROCESSCALLS_H

