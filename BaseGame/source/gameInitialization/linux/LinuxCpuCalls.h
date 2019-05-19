#ifndef LINUXCPUCALLS_H
#define LINUXCPUCALLS_H

#ifdef __linux__

#include <string> // string
#include <vector> // vector

namespace base_game {
	class LinuxCpuCalls {
	public:
		LinuxCpuCalls();
		virtual ~LinuxCpuCalls();
		unsigned long readCPUSpeed();
	protected:

	private:
	};

	namespace linux_cpu_calls {
		std::vector<double>* findSpeedPtr ( std::vector <std::string>& internal );
	}
}
#endif /* __linux__ */
#endif // LINUXCPUCALLS_H
