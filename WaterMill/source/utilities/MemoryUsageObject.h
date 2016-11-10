#ifndef MEMORYUSAGEOBJECT_H
#define MEMORYUSAGEOBJECT_H
#include "MemoryPool.h"

//---------------------------------------------------------------------------------------------------------------------
// This macro is placed inside the body of the class that you want to use a memory pool with.  It declares the
// overloaded new and delete operators as well as the static MemoryPool object.
//
// IMPORTANT: InitMemoryPool() and DestroyMemoryPool() must be called manually unless you use the GCC_MEMORYPOOL_AUTOINIT()
// macro below.
//---------------------------------------------------------------------------------------------------------------------
namespace base_game {
	class MemoryUsageObject {
		public:
			MemoryUsageObject();
			virtual ~MemoryUsageObject();

			static MemoryPool* s_pMemoryPool;
			static void initMemoryPool(unsigned int numChunks = 0, const char* debugName = 0);
			static void destroyMemoryPool(void);
			static void* operator new(size_t size);
			static void operator delete(void* pPtr);
			static void* operator new[](size_t size);
			static void operator delete[](void* pPtr);

		protected:

		private:

	};

}
#endif // MEMORYUSAGEOBJECT_H
