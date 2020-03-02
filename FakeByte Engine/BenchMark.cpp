#include "Benchmark.h"

#include <fstream>
#include <iostream>

#include <string>


void Benchmark::BenchmarkTest() {
	for (int i = 100; i <= 1000000; ) {
		GetInstance().BenchmarkTestImplementation(i);
		i *= 10;
	}
}

/**
		 * Integer Benchmark, creates and delete entities according to the inputted amount/index
		 *
		 * @param amount How many times you want to make a new entity and component.
		 */
void Benchmark::BenchmarkTestImplementation(long long amount) {
	std::string fileName = "benchmark-result.html";
	bool fileExists = true;
#pragma warning(suppress : 4996)
	if (FILE *file = std::fopen(fileName.c_str(), "r")) {
		fclose(file);
	} else {
		fileExists = false;
	}

	std::ofstream outputFile;
	outputFile.open("benchmark-result.html", std::fstream::app);

	if (!fileExists) {
		//HTML Header
		outputFile << "<!DOCTYPE html><html><head><style>table{font - family: arial, sans - serif; border - collapse: collapse; width: 100 % ;} td, th{ border: 1px solid #dddddd; text - align: left; padding: 8px;} tr:nth - child(even) { background - color: #dddddd;}</style></head><body>";
		//Headline
		outputFile << "<h2>Integer Benchmark</h2>";
		//Table Head
		outputFile << "<table><tr><th>Amount</th><th>Creation</th><th>Adding</th><th>Step</th><th>Destroying</th></tr>";
	}

	//Amount
	outputFile << "<tr><td>" << amount << "</td>";

	Timer t("BENCHMARKING");

	//1: Make x number of entities
	for (int i = 0; i < amount; i++) {
		ComponentManager::GetInstance().CreateEntity();
	}

	t.Stop();
	
	//Creating
	outputFile << "<td>" << t.elapsedSeconds() << "</td>";


	//2: Adding components to an entity

	std::vector<entity> entities = ComponentManager::GetInstance().GetEntityVector();
	t.reset();
	for (int i = 0; i < entities.size(); i++) {
		ComponentManager::GetInstance().AddComponent(entities[i], i);
	}

	t.Stop();

	//Adding
	outputFile << "<td>" << t.elapsedSeconds() << "</td>";


	//Systems Test
	IntBenchMarkSystem system1;
	system1.RequireComponent(typeid(int));
	t.reset();
	SystemManager::GetInstance().Step();
	outputFile << "<td>" << t.elapsedSeconds() << "</td>";



	//3: Time to destroy x entities with component
	t.reset();
	SystemManager::GetInstance().Step();
	for(int i=0;i < entities.size();i++){ 
	ComponentManager::GetInstance().DestroyEntity(entities[i]); 
	}

	t.Stop();
	outputFile << "<td>" << t.elapsedSeconds() << "</td>";
	//outputFile << "</table></br>";
	outputFile.close();
}

/**
		 * String benchmark which checks for how many times a character appears and how long it took to iterate through the string
		 *
		 * @param inputtedString is for the string input to search from
		 * @param searchTerm is for which character would you like to search for within the String
		 */
void Benchmark::BenchmarkStringImplementation(std::string inputtedString, char searchTerm) {
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