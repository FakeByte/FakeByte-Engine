#pragma once
#include "SystemManager.h"
#include "System.h"
#include "ComponentManager.h"
#include "Timer.h"

class IntBenchMarkSystem : public System {
	void Update() {
		system("cls");
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			std::cout << ComponentManager::GetInstance().GetComponent<int>(compatibleEntities[i]);
		}
	}
};

class StringBenchMarkSystem : public System {
	void Update() {
		system("cls");
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			std::cout << ComponentManager::GetInstance().GetComponent<std::string>(compatibleEntities[i]);
		}
	}
};

class Benchmark {
public:
	static Benchmark& GetInstance() {
		static Benchmark instance;
		return instance;
	}

	void BenchmarkTest(long long dong);

	void BenchmarkStringAccessTime(std::string x, char searchTerm);

private:
	//Singleton
	Benchmark() = default;
	~Benchmark() = default;
	Benchmark(const Benchmark&) = delete;
	Benchmark& operator=(const Benchmark&) = delete;
};