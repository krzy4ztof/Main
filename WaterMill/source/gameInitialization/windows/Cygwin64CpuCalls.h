#ifndef CYGWIN64CPUCALLS_H
#define CYGWIN64CPUCALLS_H

#ifdef __CYGWIN__

namespace watermill {
	class Cygwin64CpuCalls {
		public:
			Cygwin64CpuCalls();
			virtual ~Cygwin64CpuCalls();
			double readCPUSpeedCygwin();
		protected:

		private:
	};
}
#endif /* __CYGWIN__ */
#endif // CYGWIN64CPUCALLS_H
