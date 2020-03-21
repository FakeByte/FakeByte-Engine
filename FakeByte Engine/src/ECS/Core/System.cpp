#include "System.h"
#include "SystemManager.h"
#include "ComponentManager.h"
#include <iostream>

System::System() {
	SystemManager::RegisterSystem(*this);
}

void System::RequireComponent(std::type_index componentType) {
	signature[ComponentManager::GetComponentIndex(componentType)] = true;
	FindCompatibleEntities();
}

void System::SetPriority(SystemPriority priority) {
	this->priority = priority;
	SystemManager::SortSystemsArray();
}

void System::FindCompatibleEntities() {
	compatibleEntities.clear();

	std::vector<entity> entities = ComponentManager::GetInstance().GetEntityVector();
	for (size_t i = 0; i < entities.size(); i++) {
		if ((ComponentManager::GetSignature(entities[i]) & signature) == signature) {
			compatibleEntities.push_back(entities[i]);
		}
	}
}

bool operator > (System &s1, System &s2) {
	return s1.GetPriority() > s2.GetPriority();
}

bool operator >= (System &s1, System &s2) {
	return s1.GetPriority() >= s2.GetPriority();
}

bool operator < (System &s1, System &s2) {
	return s1.GetPriority() < s2.GetPriority();
}

bool operator <= (System &s1, System &s2) {
	return s1.GetPriority() <= s2.GetPriority();
}
