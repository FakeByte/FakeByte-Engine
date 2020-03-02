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
	//File name the result will be stored in
	std::string fileName = "benchmark-result.html";
	//If the file exists
	bool fileExists = true;

	//Check if the file exists
	//Suppress Compiler warning 4996 | fopen is deprecated use fopen_s
#pragma warning(suppress : 4996)
	if (FILE *file = std::fopen(fileName.c_str(), "r")) {
		fclose(file);
	} else {
		fileExists = false;
	}

	//Open file in append mode
	std::ofstream outputFile;
	outputFile.open("benchmark-result.html", std::fstream::app);

	//If file doesnt exist, write a file header
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

	Timer t("BENCHMARKING", false);

	//1: Make x number of entities
	for (int i = 0; i < amount; i++) {
		ComponentManager::GetInstance().CreateEntity();
	}
	
	//Creating
	outputFile << "<td>" << t.elapsedSeconds() << "</td>";


	//2: Adding components to an entity

	std::vector<entity> entities = ComponentManager::GetInstance().GetEntityVector();
	t.reset();
	for (int i = 0; i < entities.size(); i++) {
		ComponentManager::GetInstance().AddComponent(entities[i], i);
	}

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

	outputFile << "<td>" << t.elapsedSeconds() << "</td>";
	//outputFile << "</table></br>";
	outputFile.close();
}