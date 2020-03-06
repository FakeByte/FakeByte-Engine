#pragma once
#include "SystemManager.h"
#include "System.h"
#include "ComponentManager.h"
#include "Timer.h"

//BenchmarkSystem for benchmarking using integers
class IntBenchmarkSystem : public System {
	void PreUpdate() {}

	void Update() {
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			ComponentManager::GetInstance().GetComponent<int>(compatibleEntities[i]);
		}
	}

	void PostUpdate() {}
};

class StringBenchmarkSystem : public System {
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

	/**
	*Creates 1 million entities and components recursively and deletes them
	*Displays running time in nanoseconds for each process
	*/

	static void BenchmarkTest();

private:
	//Singleton
	Benchmark() = default;
	~Benchmark() = default;
	Benchmark(const Benchmark&) = delete;
	Benchmark& operator=(const Benchmark&) = delete;
	//Singleton

	void BenchmarkTestImplementation(long long amount);

};