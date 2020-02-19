#include "ComponentManager.h"

void ComponentManager::DestroyEntity(entity id) {
	for (size_t i = 0; i < MAX_COMPONENTS; i++) {
		if (signatures[id][i] == true) {
			componentArrays[i].get()->RemoveComponent(id);
		}
	}

	//Remove
	std::cout << "Entity: " << id << " destroyed" << std::endl;
}
