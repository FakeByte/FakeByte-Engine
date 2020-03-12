#include "StackAllocator.h"

StackAllocator::StackAllocator(void * start, size_t memorySize) {
	this->start = start;
	this->size = memorySize;
	nextFree = start;
}

void * StackAllocator::Allocate(size_t size) {
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
