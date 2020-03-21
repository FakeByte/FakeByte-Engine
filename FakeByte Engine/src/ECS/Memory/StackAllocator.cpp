#include "StackAllocator.h"
#include "ECS\Types\Types.h"

StackAllocator::StackAllocator(void * start, size_t memorySize, IAllocator * parent) {
	assert(memorySize != 0 && start != nullptr);
	this->start = start;
	this->size = memorySize;
	this->parent = parent;
	nextFree = start;
}

void * StackAllocator::Allocate(size_t size) {
	assert(size != 0);

#ifdef MEMORY_LEAK_DETECTION
	prev_position = nextFree;
#endif //MEMORY_LEAK_DETECTION

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

void StackAllocator::Free(void * p) {
#ifdef MEMORY_LEAK_DETECTION
	assert(p == prev_position);
#endif //MEMORY_LEAK_DETECTION

	usedMemory = static_cast<char*>(p) - static_cast<char*>(start);
	allocationCount--;
	nextFree = p;
}
