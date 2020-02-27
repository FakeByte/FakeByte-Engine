#pragma once
#include "SystemManager.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"
#include "ComponentManager.h"
#include "Timer.h"

class BenchMark {
public:
	static BenchMark& GetInstance() {
		static BenchMark instance;
		return instance;
	}

	void BenchMarkTest(double x);
private:
	//Singleton
	BenchMark() = default;
	~BenchMark() = default;
	BenchMark(const BenchMark&) = delete;
	BenchMark& operator=(const BenchMark&) = delete;
};