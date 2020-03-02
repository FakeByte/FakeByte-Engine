#include "SystemManager.h"
#include "System.h"

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
	GetInstance().updateCompatibleEntities = true;
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
