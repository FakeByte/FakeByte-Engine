#include "BenchMark.h"

//DELET THIS
#include <iostream>


void Benchmark::BenchmarkTest(long long amount) {
	std::cout << "\n\nBenchmarked input amount: " << amount << "\n" << std::endl;

	std::cout << "Benchmark #1: Creating Entities" << "\n" << std::endl;
	Timer t("BENCHMARKING");

	//1: Make x number of entities
	for (int i = 0; i < amount; i++) {
		ComponentManager::GetInstance().CreateEntity();
	}
	
	SystemManager::GetInstance().Step();
	t.Stop();
	long long avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Creating Entities: " << avg << " ns\n" << std::endl;
	system("pause");

	//2: Time to destroy x entities

	std::cout << "\nBenchmark #2: Destroying Entities" << "\n" << std::endl;

	t.reset();
	std::vector<entity> entities = ComponentManager::GetInstance().GetEntityVector();
	for(int i=0;i < entities.size();i++){ 
	ComponentManager::GetInstance().DestroyEntity(entities[i]); 
	}

	SystemManager::GetInstance().Step();
	t.Stop();
	avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Destroying Entities: " << avg << " ns\n" << std::endl;
	system("pause");

	//3: Adding components to an entity

	std::cout << "\nBenchmark #3: Adding Components" << "\n" << std::endl;
	entity e = ComponentManager::GetInstance().CreateEntity();
	entities = ComponentManager::GetInstance().GetEntityVector();

	t.reset();
	for (int i = 0; i < entities.size();i++) {
		ComponentManager::GetInstance().AddComponent(entities[i], i);
	}

	SystemManager::GetInstance().Step();
	t.Stop();
	avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Adding Components: " << avg << " ns\n" << std::endl;
	system("pause");

	//4: Deleting components from the entity
	std::cout << "\nBenchmark #4: Deleting Components" << "\n" << std::endl;
	
	entities = ComponentManager::GetInstance().GetEntityVector();

	t.reset();
	for (int i = 0; i < entities.size(); i++) {
		ComponentManager::GetInstance().RemoveComponent(entities[i], i);
	}

	t.Stop();
	avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Adding Components: " << avg << " ns\n" << std::endl;
	system("pause");

	//5: Deleting an entity with x number of components
	std::cout << "\nBenchmark #5: Deleting an Entity with Components" << " ns\n" << std::endl;
	for (int i = 0; i < entities.size(); i++) {
		ComponentManager::GetInstance().AddComponent(entities[i], i);
	}

	t.reset();
	ComponentManager::GetInstance().DestroyEntity(e);

	SystemManager::GetInstance().Step();
	t.Stop();
	std::cout << "Benchmarked Deleting an entity with " << amount << " components." << "\n" << std::endl;
	system("pause");

	//6: Steps benchmark
	std::cout << "\nBenchmark #5: Benchmarking steps" << "\n" << std::endl;
	
	t.reset();
	for (int i = 0; i < amount; i++) {
		SystemManager::GetInstance().Step();
	}
	
	t.Stop();
	avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Steps: " << avg << " ns\n" << std::endl;
	system("pause");
}

void Benchmark::BenchmarkStringAccessTime(std::string inputtedString, char searchTerm) {
	size_t counter = 0;
	char searchedTerm = searchTerm;
	
	std::cout << "Inputted String: " << inputtedString << std::endl;
	Timer st("BENCHMARKING ACCESS TIME");
	for(int i = 0;i < inputtedString.size();i++){
		if (inputtedString[i] == searchedTerm) counter++;
	}

	std::cout << "\n" << searchedTerm << " appeared: " << counter << " times" << std::endl;
}