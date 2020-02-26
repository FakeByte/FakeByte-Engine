#pragma once

#include "System.h"
#include "ComponentManager.h"
#include "PlayerComponent.h"

class MoverSystem : public System {
	void PreUpdate() {

	}
	void Update() {
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			if (ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).counter == 0) {
				if (ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).x < 2) {
					ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).x++;
				} else {
					ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).x = 0;
					if (ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).y < 2) {
						ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).y++;
					} else {
						ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).y = 0;
					}
				}


				ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).counter = 5;
				ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).changed = true;
			} else {
				ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).counter--;
			}
			
		}
	}
	void PostUpdate() {

	}
};