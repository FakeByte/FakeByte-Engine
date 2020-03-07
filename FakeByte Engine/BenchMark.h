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

class Benchmark {
public:
	/**
	* Returns a singleton instance
	* @returns Singleton Instance
	*/
	static Benchmark& GetInstance() {
		static Benchmark instance;
		return instance;
	}

	/**
	* Recursively the benchmarking implementation by 100, 1000, 10000, 100000, 10000000
	* Stores the results in a .html file that can be found in the engine folder
	*/
	static void BenchmarkTest();

private:
	//Singleton
	Benchmark() = default;
	~Benchmark() = default;
	Benchmark(const Benchmark&) = delete;
	Benchmark& operator=(const Benchmark&) = delete;
	//Singleton

	/**
	*Implementation of 
	*/
	void BenchmarkTestImplementation(long long amount);

};