#include <stdlib.h>
#include "ECS\Core\ComponentManager.h"
#include "ECS\Types\EntityId.h"
#include "ECS\Core\SystemManager.h"
#include "ECS\Core\System.h"
#include "FakeByteEngine.h"

#include "ECS\Types\Types.h"
#include "ECS\Memory\LinearAllocator.h"
#include "ECS\Memory\StackAllocator.h"
#include "ECS\Memory\MemoryManager.h"
#include <cassert>

#include "Benchmark\Benchmark.h"

#include "Time\Timer.h"
#include "examples\console-animation\RenderSystem.h"
#include "examples\console-animation\PlayerMovementSystem.h"
#include "examples\console-animation\MoverSystem.h"
#include <string.h>

#include "Debug/Instrumentor.h"

void Test2() {
	PROFILE_FUNCTION();
	for (int i = 0; i < 1000; i++) {
		i = i * 2;
	}
}

void Test() {
	PROFILE_FUNCTION();
	for (int i = 0; i < 100; i++) {
		Test2();
	}
}


int main() {
	PROFILE_START_SESSION(test, test.json);
//for(int i = 0; i < 23000; i++)
	Test2();
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
		RenderSystem r1;
		r1.SetPriority(NORMAL_SYSTEM_PRIORITY);
		RenderSystem r2;
		r2.SetPriority(LOW_SYSTEM_PRIORITY);
		RenderSystem r3;
		r3.SetPriority(HIGHEST_SYSTEM_PRIORITY);

		//SystemManager::SortSystemsArray();

		//Benchmark::BenchmarkTest();

		//Benchmark::BenchmarkString();

		/*FakeByteEngine::Initialize();
		FakeByteEngine::Start();
		*/
	}


	int test = 69;
	MemoryManager::Initialize();
	void* c;

	c = (void*)(*MemoryManager::GetAllocator()).Allocate(sizeof(void*));


	void* v = malloc(100);
	StackAllocator* sa = new StackAllocator((*MemoryManager::GetAllocator()).Allocate(1000), 1000, MemoryManager::GetAllocator());

	int* i = static_cast<int*>(sa->Allocate(sizeof(int)));
	*i = 69;

	std::cout << *i << std::endl;
	sa->Free(i);
	int* i2 = static_cast<int*>(sa->Allocate(sizeof(int)));
	*i2 = 42;
	std::cout << *i << std::endl;
	sa->Free(i2);
	delete sa;
#endif

	PROFILE_END_SESSION();
	Instrumentor::OpenTraceFile("test.json");
	system("pause");

	return 0;
}