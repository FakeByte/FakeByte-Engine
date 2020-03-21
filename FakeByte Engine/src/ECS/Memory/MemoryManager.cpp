#include <malloc.h>
#include <cstring> 
#include <cassert>
#include <stdlib.h>
#include <iostream>

#include "MemoryManager.h"
#include "ECS\Constants\Constants.h"

MemoryManager& MemoryManager::GetInstance() {
	static MemoryManager instance;
	return instance;
}

void MemoryManager::Initialize() {
	GetInstance().InitializeImplementation();
}

LinearAllocator* MemoryManager::GetAllocator() {
	return GetInstance().globalAllocator;
}

MemoryManager::~MemoryManager() {
	_aligned_free(memory);
}

void MemoryManager::InitializeImplementation() {
	void* mem = _aligned_malloc(MEMORY_CAPACITY, 64);
	if (mem == NULL) {
		assert(mem != NULL && "Memory allocation failed");
	}
	memset(mem, '0', MEMORY_CAPACITY);
	memory = mem;
	globalAllocator = new LinearAllocator(memory, MEMORY_CAPACITY);
}