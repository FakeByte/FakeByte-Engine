#include <stdlib.h>
#include "ECS\Core\ComponentManager.h"
#include "ECS\Types\EntityId.h"
#include "ECS\Core\SystemManager.h"
#include "ECS\Core\System.h"
#include "FakeByteEngine.h"

#include "ECS\Types\Types.h"
#include "ECS\Memory\LinearAllocator.h"
#include "ECS\Memory\MemoryManager.h"
#include <cassert>

#include "Benchmark\Benchmark.h"

#include "Time\Timer.h"
#include "examples\console-animation\RenderSystem.h"
#include "examples\console-animation\PlayerMovementSystem.h"
#include "examples\console-animation\MoverSystem.h"


int main() {
#if 0
	{
		/*Timer st("Main.cpp");

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
		m2.RequireComponent(p.getType());*/

		//IntBenchMarkSystem bm1;

		Benchmark::BenchmarkTest();

		//Benchmark::BenchmarkString();

		/*FakeByteEngine::Initialize();
		FakeByteEngine::Start();
		*/
	}


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
#endif
	void* v = malloc(8);
	*static_cast<u64 *>(v) = 1;

#if _DEBUG
	std::cout << *static_cast<u64 *>(v) << std::endl;
#endif
	assert(true == false);

	system("pause");
	return 0;
}

