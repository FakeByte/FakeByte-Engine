#include <stdlib.h>
#include "ComponentManager.h"
#include "Types/EntityId.h"
#include "SystemManager.h"
#include "System.h"
#include "FakeByteEngine.h"
#include "Types.h"

#include "Timer.h"
#include "RenderSystem.h"
#include "PlayerMovementSystem.h"
#include "MoverSystem.h"
#include "LinearAllocator.h"
#include "MemoryManager.h"
#include <cassert>

int main() {
#if 0
	{
		Timer st("Main.cpp");

		RenderComponent r1;
		PlayerComponent p;
		r1.model = "#####\n#   #\n#   #\n#   #\n#####\n";
		entity e1 = ComponentManager::GetInstance().CreateEntity(r1, p);

		PlayerComponent p2;
		p2.x = 1;
		p2.y = 1;
		entity e2 = ComponentManager::GetInstance().CreateEntity(p2, r1);

		RenderSystem r;
		r.SetPriority(LOWEST_SYSTEM_PRIORITY);
		r.RequireComponent(r1.getType());

		PlayerMovementSystem m;
		m.RequireComponent(p.getType());
		m.RequireComponent(r1.getType());

		MoverSystem m2;
		m2.RequireComponent(p.getType());

		FakeByteEngine::Initialize();
		FakeByteEngine::Start();
	}
#endif
	int test = 69;
	MemoryManager::Initialize();
	void* c;

	c = (void*)(*MemoryManager::GetAllocator()).Allocate(sizeof(void*));

	std::cout << "Start: " << MemoryManager::GetAllocator()->start << std::endl;
	std::cout << c << std::endl;
	//std::cout << *c << std::endl;
	std::cout << &c << std::endl;

	std::cout <<  std::endl;

	std::cout << *static_cast<int *>(MemoryManager::GetAllocator()->start) << std::endl;

	system("pause");
	return 0;
}

