#include "MemoryUsageObject.h"
#include "../gameInitialization/Macros.h"
#include <iostream> // cout, endl
//#include "../utilities/Templates.h"

using std::cout;
using std::endl;

namespace base_game {

	MemoryUsageObject::MemoryUsageObject() {
		cout << "Create MemoryUsageObject" << endl;
	}

	MemoryUsageObject::~MemoryUsageObject() {
		cout << "Destroy MemoryUsageObject" << endl;
	}

	//---------------------------------------------------------------------------------------------------------------------
	// This macro defines the definition for the overloaded new & delete operators on a class meant to be pooled with a
	// memory pool.  It is meant to work specifically with the MemoryPool class.  To use it, call this macro from the cpp
	// file where your class function definitions are.
	//	- _className_:		The name of this class.
	//---------------------------------------------------------------------------------------------------------------------
	MemoryPool* MemoryUsageObject::s_pMemoryPool = nullptr;

	void MemoryUsageObject::initMemoryPool(unsigned int numChunks, const char* debugName) {
		//cout << "MemoryUsageObject::initMemoryPool" << endl;

		if (s_pMemoryPool != nullptr) {
			GCC_ERROR("s_pMemoryPool is not NULL.  All data will be destroyed.  (Ignorable)");
			//templates::safe_delete<MemoryPool>(s_pMemoryPool);
			memory_pool::safe_delete(s_pMemoryPool);
		}

		s_pMemoryPool = GCC_NEW MemoryPool;

		if (debugName) {
			s_pMemoryPool->SetDebugName(debugName);
		} else {
			s_pMemoryPool->SetDebugName("MemoryUsageObject");
		}
		s_pMemoryPool->Init(sizeof(MemoryUsageObject), numChunks);
		//cout << "End MemoryUsageObject::initMemoryPool" << endl;
	}
	void MemoryUsageObject::destroyMemoryPool(void) {
		cout << "MemoryUsageObject::destroyMemoryPool" << endl;


		GCC_ASSERT(s_pMemoryPool);

		//GCC_ASSERT(!s_pMemoryPool);
		//GCC_ASSERT(s_pMemoryPool != nullptr);
		//templates::safe_delete<MemoryPool>(s_pMemoryPool);
		memory_pool::safe_delete(s_pMemoryPool);
		cout << "End MemoryUsageObject::destroyMemoryPool" << endl;
	}
	void* MemoryUsageObject::operator new(size_t size) {
		//cout << "MemoryUsageObject::new" << endl;
		GCC_ASSERT(s_pMemoryPool);
		void* pMem = s_pMemoryPool->Alloc();
		//cout << "End MemoryUsageObject::new" << endl;
		return pMem;
	}
	void MemoryUsageObject::operator delete(void* pPtr) {
		//cout << "MemoryUsageObject::delete" << endl;
		GCC_ASSERT(s_pMemoryPool);
		s_pMemoryPool->Free(pPtr);
		//cout << "End MemoryUsageObject::delete" << endl;
	}
	void* MemoryUsageObject::operator new[](size_t size) {
		//cout << "MemoryUsageObject::new[]" << endl;
		GCC_ASSERT(s_pMemoryPool);
		void* pMem = s_pMemoryPool->Alloc();
		//cout << "End MemoryUsageObject::new[]" << endl;
		return pMem;
	}
	void MemoryUsageObject::operator delete[](void* pPtr) {
		//cout << "MemoryUsageObject::delete[]" << endl;
		GCC_ASSERT(s_pMemoryPool);
		s_pMemoryPool->Free(pPtr);
		//cout << "End MemoryUsageObject::delete[]" << endl;
	}
}

