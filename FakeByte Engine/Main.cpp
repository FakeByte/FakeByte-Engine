#include <stdlib.h>
#include "ComponentManager.h"
#include "Types/EntityId.h"
#include "SystemManager.h"
#include "System.h"
#include "FakeByteEngine.h"
#include "BenchMark.h"

#include "Timer.h"
#include "RenderSystem.h"
#include "PlayerMovementSystem.h"
#include "MoverSystem.h"

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

		BenchMark::GetInstance().BenchMarkTest(1000);
		BenchMark::GetInstance().BenchMarkTest(2000);

		/*FakeByteEngine::Initialize();
		FakeByteEngine::Start();
		*/
	}
	system("pause");
	return 0;
}