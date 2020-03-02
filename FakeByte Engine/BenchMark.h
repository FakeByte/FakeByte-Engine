#pragma once
#include "SystemManager.h"
#include "System.h"
#include "ComponentManager.h"
#include "Timer.h"

class IntBenchMarkSystem : public System {
	void PreUpdate() {}

	void Update() {
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			ComponentManager::GetInstance().GetComponent<int>(compatibleEntities[i]);
		}
	}

	void PostUpdate() {}
};

class StringBenchMarkSystem : public System {
	void PreUpdate() {}

	void Update() {
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			ComponentManager::GetInstance().GetComponent<std::string>(compatibleEntities[i]);
		}
	}

	void PostUpdate() {}
};

class Benchmark {
public:
	static Benchmark& GetInstance() {
		static Benchmark instance;
		return instance;
	}

	static void BenchmarkTest();

	static void BenchmarkString();

private:
	//Singleton
	Benchmark() = default;
	~Benchmark() = default;
	Benchmark(const Benchmark&) = delete;
	Benchmark& operator=(const Benchmark&) = delete;
	//Singleton

	void BenchmarkTestImplementation(long long amount);

	void BenchmarkStringImplementation(std::string x, char searchTerm);
};