#include "StackAllocator.h"
#include "ECS\Types\Types.h"

StackAllocator::StackAllocator(void * start, size_t memorySize) {
	this->start = start;
	this->size = memorySize;
	nextFree = start;
}

void * StackAllocator::Allocate(size_t size) {
	if ((this->size - usedMemory) > size) {
		void* previousHeader = static_cast<char *>(nextFree) - sizeof(u64);
		void* header = nextFree;
		//*static_cast<u64 *>(nextFree) = ;

		void* temp = static_cast<char *>(nextFree) + sizeof(u64);
		nextFree = static_cast<char *>(nextFree) + sizeof(u64) + size;
		allocationCount++;
		usedMemory += size;
		return temp;
	} else {
		return nullptr;
	}
}
