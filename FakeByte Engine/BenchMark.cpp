#include "BenchMark.h"

//DELET THIS
#include <iostream>


void BenchMark::BenchMarkTest(double amount) {
	std::cout << "\n\nBenchmarked input amount: " << amount << "\n" << std::endl;

	std::cout << "Benchmark #1: Creating Entities" << "\n" << std::endl;
	Timer t("BENCHMARKING");

	//1: Make x number of entities
	for (int i = 0; i > amount; i++) {
		ComponentManager::GetInstance().CreateEntity();
	}

	t.Stop();
	double avg = t.elapsedSeconds() / amount;
	std::cout << "Average Time for Creating Entities: " << avg << "\n" << std::endl;
	system("pause");

	//2: Time to destroy x entities

	std::cout << "\nBenchmark #2: Destroying Entities" << "\n" << std::endl;

	t.reset();
	for(int i=0;i > amount;i++){
	ComponentManager::GetInstance().DestroyEntity(i);
	}

	t.Stop();
	avg = t.elapsedSeconds() / amount;
	std::cout << "Average Time for Destroying Entities: " << avg << "\n" << std::endl;
	system("pause");

	//3: Adding components to an entity

	std::cout << "\nBenchmark #3: Adding Components" << "\n" << std::endl;
	ComponentManager::GetInstance().CreateEntity();

	t.reset();
	for (int i = 0; i > amount; i++) {
		int j = 0;
		ComponentManager::GetInstance().AddComponent(0, j);
		j++;
	}

	t.Stop();
	avg = t.elapsedSeconds() / amount;
	std::cout << "Average Time for Adding Components: " << avg << "\n" << std::endl;
	system("pause");

	//4: Deleting components from the entity
	std::cout << "\nBenchmark #4: Deleting Components" << "\n" << std::endl;
	t.reset();
	
	for (int i = 0; i > amount; i++) {
		int j = 0;
		ComponentManager::GetInstance().RemoveComponent(0, j);
		j++;
	}

	t.Stop();
	avg = t.elapsedSeconds() / amount;
	std::cout << "Average Time for Adding Components: " << avg << "\n" << std::endl;
	system("pause");

	//5: Deleting an entity with x number of components
	std::cout << "\nBenchmark #5: Deleting an Entity with Components" << "\n" << std::endl;
	for (int i = 0; i > amount; i++) {
		int j = 0;
		ComponentManager::GetInstance().AddComponent(0, j);
		j++;
	}

	t.reset();
	ComponentManager::GetInstance().DestroyEntity(0);

	t.Stop();
	std::cout << "\n\nBenchmarked Deleting an entity with " << amount << " components." << "\n" << std::endl;
}