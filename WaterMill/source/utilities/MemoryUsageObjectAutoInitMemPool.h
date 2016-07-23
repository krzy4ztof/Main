#ifndef MEMORYUSAGEOBJECTAUTOINITMEMPOOL_H
#define MEMORYUSAGEOBJECTAUTOINITMEMPOOL_H

//---------------------------------------------------------------------------------------------------------------------
// This macro defines a static class that automatically initializes a memory pool at global startup and destroys it at
// global destruction time.  Using this gets around the requirement of manually initializing and destroying the memory
// pool yourself.
//---------------------------------------------------------------------------------------------------------------------

namespace watermill {
	class MemoryUsageObjectAutoInitMemPool {
		public:
			MemoryUsageObjectAutoInitMemPool();
			virtual ~MemoryUsageObjectAutoInitMemPool();

		protected:

		private:
	};
}
#endif // MEMORYUSAGEOBJECTAUTOINITMEMPOOL_H
