#include "MemoryUsageObjectAutoInitMemPool.h"
#include "MemoryUsageObject.h"

namespace watermill {

	static MemoryUsageObjectAutoInitMemPool memoryUsageObjectAutoInitMemPool;

	MemoryUsageObjectAutoInitMemPool::MemoryUsageObjectAutoInitMemPool(void) {
		MemoryUsageObject::initMemoryPool(3, "MemoryUsageObject");
	}

	MemoryUsageObjectAutoInitMemPool::~MemoryUsageObjectAutoInitMemPool(void) {
		MemoryUsageObject::destroyMemoryPool();
	}
}
