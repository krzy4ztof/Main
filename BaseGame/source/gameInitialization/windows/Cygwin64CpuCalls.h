#ifndef CYGWIN64CPUCALLS_H
#define CYGWIN64CPUCALLS_H

#ifdef __CYGWIN__
#include <string> // string
#include <vector> // vector

namespace base_game {
	class Cygwin64CpuCalls {
	public:
		Cygwin64CpuCalls();
		virtual ~Cygwin64CpuCalls();
		unsigned long readCPUSpeed();
	protected:

	private:
	};

	namespace cygwin64_cpu_calls {
		std::vector<double>* findSpeedPtr ( std::vector <std::string>& internal );
		std::vector<double>& findSpeedRefError ( std::vector <std::string>& internal );
		std::vector<double> findSpeedMove ( std::vector <std::string>& internal );
	}
}
#endif /* __CYGWIN__ */
#endif // CYGWIN64CPUCALLS_H
