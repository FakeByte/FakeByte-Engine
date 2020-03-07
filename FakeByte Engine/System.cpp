#include "System.h"
#include "SystemManager.h"
#include "ComponentManager.h"
#include <iostream>

System::System() {
	SystemManager::RegisterSystem(*this);
}

void System::RequireComponent(std::type_index componentType) {
	signature[ComponentManager::GetInstance().GetComponentIndex(componentType)] = true;
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
		if ((ComponentManager::GetInstance().GetSignature(entities[i]) & signature) == signature) {
			compatibleEntities.push_back(entities[i]);
		}
	}
}
