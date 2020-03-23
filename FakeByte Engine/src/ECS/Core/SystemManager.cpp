#include "SystemManager.h"
#include "System.h"
#include "Sorting\MergeSort.h"
#include "Algorithm\BinaryFind.h"

#include <iostream>

SystemManager & SystemManager::GetInstance() {
	static SystemManager instance;
	return instance;
}

void SystemManager::RegisterSystem(System & system) {
	GetInstance().RegisterSystemImplementation(system);
}

void SystemManager::UnregisterSystem(System &system) {
	GetInstance().UnregisterSystemImplementation(system);
}

void SystemManager::SortSystemsArray() {
	GetInstance().SortSystemsArrayImplementation();
}

void SystemManager::Step() {
	GetInstance().StepImplementation();
}

void SystemManager::FindCompatibleEntities() {
	GetInstance().updateCompatibleEntities = true;
}


void SystemManager::RegisterSystemImplementation(System & system) {
	System* s = &system;
	systems.push_back(&system);
	SortSystemsArrayImplementation();
}


void SystemManager::UnregisterSystemImplementation(System &system) {
	auto it = Algorithm::BinaryFind<System>(0, systems.size()-1, system);
	if (it != systems.end()) {
		auto i = std::distance(systems.begin(), it);
		systems[i] = systems[systems.end];
		systems.pop_back();
	}
	else {
		std::cout << "System not found!" << std::endl;
		std::cout << std::endl;
	}
}

void SystemManager::SortSystemsArrayImplementation() {

	systems = Sorting::MergeSort(systems);
	
	for (int i = 0; i < systems.size(); i++) {
		std::cout << systems[i]->GetPriority() << std::endl;
	}
	std::cout << std::endl;
}

void SystemManager::StepImplementation() {
	if (updateCompatibleEntities) {
		FindCompatibleEntitiesImplementation();
	}

	for (size_t i = 0; i < systems.size(); i++) {
		if (systems[i]->enabled) {
			systems[i]->PreUpdate();
		}
	}
	for (size_t i = 0; i < systems.size(); i++) {
		if (systems[i]->enabled) {
			systems[i]->Update();
		}
	}
	for (size_t i = 0; i < systems.size(); i++) {
		if (systems[i]->enabled) {
			systems[i]->PostUpdate();
		}
	}
}

void SystemManager::FindCompatibleEntitiesImplementation() {
	for (size_t i = 0; i < systems.size(); i++) {
		systems[i]->FindCompatibleEntities();
	}
}
