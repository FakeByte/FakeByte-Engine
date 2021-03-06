#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(void * start, size_t size, Allocator* parent) {
	this->start = start;
	this->size = size;
	this->parent = parent;
	nextFree = start;
}

void * LinearAllocator::Allocate(size_t size) {
	if ((this->size - usedMemory) > size) {
		void* temp = nextFree;
		nextFree = static_cast<char *>(nextFree) + size;
		allocationCount++;
		usedMemory += size;
		return temp;
	} else {
		return nullptr;
	}
}

void LinearAllocator::Free(void * p) {
	Clear();
}

void LinearAllocator::Clear() {
	nextFree = start;
}
