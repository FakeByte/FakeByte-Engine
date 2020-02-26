#include "SystemManager.h"
#include "System.h"

//TODO: Remove
#include <iostream>

SystemManager & SystemManager::GetInstance() {
	static SystemManager instance;
	return instance;
}

void SystemManager::RegisterSystem(System & system) {
	GetInstance().RegisterSystemImplementation(system);
}

void SystemManager::SortSystemsArray() {
	GetInstance().SortSystemsArrayImplementation();
}

void SystemManager::Step() {
	GetInstance().StepImplementation();
}

void SystemManager::FindCompatibleEntities() {
	GetInstance().FindCompatibleEntitiesImplementation();
}

void SystemManager::RegisterSystemImplementation(System & system) {
	System* s = &system;
	systems.push_back(&system);
	SortSystemsArrayImplementation();
}

void SystemManager::SortSystemsArrayImplementation() {
	//Bubblesort #Slow #FutureMeChangeThis
	for (int i = 0; i < systems.size() - 1; i++){
		// Last i elements are already in place  
		for (int j = 0; j < (systems.size() - i - 1); j++) {
			if (systems[j]->GetPriority() < systems[j + 1]->GetPriority()) {
				System* temp = systems[j];
				systems[j] = systems[j + 1];
				systems[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < systems.size(); i++) {
		std::cout << systems[i]->GetPriority() << std::endl;
	}
}

void SystemManager::StepImplementation() {
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
