#include <stdlib.h>
#include <cassert>
#include "ComponentManager.h"
#include "TestComponent.h"
#include <iostream>
#include <chrono>
#include <vector>
#include "Types/EntityId.h"

class Timer {
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;
};

int main() {
	TestComponent t;
	t.test = 69;
	TestComponent2 t2;
	entity e = ComponentManager::GetInstance().CreateEntity(t, t2);
	ComponentManager::GetInstance().RemoveComponent(e, t);
	ComponentManager::GetInstance().AddComponent(e, t);
	std::cout << ComponentManager::GetInstance().GetComponent<TestComponent>(e).test << std::endl;
	ComponentManager::GetInstance().DestroyEntity(e);

	system("pause");
	return 0;
}