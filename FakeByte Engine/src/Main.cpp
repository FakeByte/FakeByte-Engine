#include <stdlib.h>
#include "ECS\Core\ComponentManager.h"
#include "ECS\Types\EntityId.h"
#include "ECS\Core\SystemManager.h"
#include "ECS\Core\System.h"
#include "FakeByteEngine.h"
#include "Benchmark\Benchmark.h"

#include "Time\Timer.h"
#include "examples\console-animation\RenderSystem.h"
#include "examples\console-animation\PlayerMovementSystem.h"
#include "examples\console-animation\MoverSystem.h"

int main() {
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

	system("pause");
	return 0;
}