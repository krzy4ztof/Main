#include "MemoryUsageObjectAutoInitMemPool.h"
#include "MemoryUsageObject.h"
#include <iostream> // cout, endl

using std::cout;
using std::endl;


namespace base_game {

	static MemoryUsageObjectAutoInitMemPool memoryUsageObjectAutoInitMemPool;

	MemoryUsageObjectAutoInitMemPool::MemoryUsageObjectAutoInitMemPool(void) {
		cout << "Create MemoryUsageObjectAutoInitMemPool" << endl;
		MemoryUsageObject::initMemoryPool(3, "MemoryUsageObject");
	}

	MemoryUsageObjectAutoInitMemPool::~MemoryUsageObjectAutoInitMemPool(void) {
		MemoryUsageObject::destroyMemoryPool();
		cout << "Destroy MemoryUsageObjectAutoInitMemPool" << endl;
	}
}
