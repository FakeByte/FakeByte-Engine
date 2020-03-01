#include "BenchMark.h"

//DELET THIS
#include <iostream>


/**
		 * Integer Benchmark, creates and delete entities according to the inputted amount/index
		 *
		 * @param amount How many times you want to make a new entity and component.
		 */
void Benchmark::BenchmarkTest(long long amount) {
	IntBenchMarkSystem system1;

	std::cout << "\n\nBenchmarked input amount: " << amount << "\n" << std::endl;

	std::cout << "Benchmark #1: Creating Entities" << "\n" << std::endl;
	Timer t("BENCHMARKING");

	//1: Make x number of entities
	for (int i = 0; i < amount; i++) {
		ComponentManager::GetInstance().CreateEntity();
	}

	t.Stop();
	std::vector<entity> entities = ComponentManager::GetInstance().GetEntityVector();
	long long avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Creating Entities: " << avg << " ns\n" << std::endl;
	system("pause");

	//2: Adding components to an entity

	std::cout << "\nBenchmark #2: Adding Components" << "\n" << std::endl;


	t.reset();
	for (int i = 0; i < entities.size(); i++) {
		ComponentManager::GetInstance().AddComponent(entities[i], i);
	}

	system1.RequireComponent(typeid(int));
	SystemManager::GetInstance().Step();
	t.Stop();
	avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Adding Components: " << avg << " ns\n" << std::endl;
	system("pause");

	//3: Time to destroy x entities with components

	std::cout << "\nBenchmark #3: Destroying Entities" << "\n" << std::endl;

	t.reset();
	SystemManager::GetInstance().Step();
	for(int i=0;i < entities.size();i++){ 
	ComponentManager::GetInstance().DestroyEntity(entities[i]); 
	}

	t.Stop();
	avg = t.elapsedNanoseconds() / amount;
	std::cout << "Average Time for Destroying Entities: " << avg << " ns\n" << std::endl;
	system("pause");
}

/**
		 * String benchmark which checks for how many times a character appears and how long it took to iterate through the string
		 *
		 * @param inputtedString is for the string input to search from
		 * @param searchTerm is for which character would you like to search for within the String
		 */
void Benchmark::BenchmarkString(std::string inputtedString, char searchTerm) {
	StringBenchMarkSystem system2;

	entity e = ComponentManager::GetInstance().CreateEntity();
	ComponentManager::GetInstance().AddComponent(e, inputtedString);
	system2.RequireComponent(typeid(std::string));

	size_t counter = 0;
	char searchedTerm = searchTerm;

	std::cout << "Inputted String: " << inputtedString << std::endl;
	Timer st("STRING BENCHMARK");
	for(int i = 0;i < inputtedString.size();i++){
		if (inputtedString[i] == searchedTerm) counter++;
	}

	std::cout << "\n" << searchedTerm << " appeared: " << counter << " times" << std::endl;
}