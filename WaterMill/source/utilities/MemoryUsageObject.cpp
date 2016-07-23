#include "MemoryUsageObject.h"
#include "../gameInitialization/Macros.hpp"
#include <iostream> // cout, endl

using namespace std;

namespace watermill {
	MemoryUsageObject::MemoryUsageObject() {
		//ctor
	}

	MemoryUsageObject::~MemoryUsageObject() {
		//dtor
	}

	//---------------------------------------------------------------------------------------------------------------------
	// This macro defines the definition for the overloaded new & delete operators on a class meant to be pooled with a
	// memory pool.  It is meant to work specifically with the MemoryPool class.  To use it, call this macro from the cpp
	// file where your class function definitions are.
	//	- _className_:		The name of this class.
	//---------------------------------------------------------------------------------------------------------------------
	MemoryPool* MemoryUsageObject::s_pMemoryPool = NULL;

	void MemoryUsageObject::initMemoryPool(unsigned int numChunks, const char* debugName) {

		if (s_pMemoryPool != NULL) {
			GCC_ERROR("s_pMemoryPool is not NULL.  All data will be destroyed.  (Ignorable)");
			SAFE_DELETE(s_pMemoryPool);
		}

		s_pMemoryPool = GCC_NEW MemoryPool;

		if (debugName) {
			s_pMemoryPool->SetDebugName(debugName);
		} else {
			s_pMemoryPool->SetDebugName("MemoryUsageObject");
		}
		s_pMemoryPool->Init(sizeof(MemoryUsageObject), numChunks);
	}
	void MemoryUsageObject::destroyMemoryPool(void) {
		GCC_ASSERT(s_pMemoryPool != NULL);
		SAFE_DELETE(s_pMemoryPool);
	}
	void* MemoryUsageObject::operator new(size_t size) {
		GCC_ASSERT(s_pMemoryPool);
		void* pMem = s_pMemoryPool->Alloc();
		return pMem;
	}
	void MemoryUsageObject::operator delete(void* pPtr) {
		GCC_ASSERT(s_pMemoryPool);
		s_pMemoryPool->Free(pPtr);
	}
	void* MemoryUsageObject::operator new[](size_t size) {
		GCC_ASSERT(s_pMemoryPool);
		void* pMem = s_pMemoryPool->Alloc();
		return pMem;
	}
	void MemoryUsageObject::operator delete[](void* pPtr) {
		GCC_ASSERT(s_pMemoryPool);
		s_pMemoryPool->Free(pPtr);
	}
}

