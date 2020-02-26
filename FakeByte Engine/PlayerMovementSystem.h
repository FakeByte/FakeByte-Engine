#pragma once

#include "System.h"
#include "ComponentManager.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"

class PlayerMovementSystem : public System {
	void PreUpdate() {

	}
	void Update() {
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			if (ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).changed) {
				ComponentManager::GetInstance().GetComponent<RenderComponent>(compatibleEntities[i]).model = "#####\n#   #\n#   #\n#   #\n#####\n";

				int playerPosX = ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).x;
				int playerPosY = ComponentManager::GetInstance().GetComponent<PlayerComponent>(compatibleEntities[i]).y;
				int padding = 0;
				if (playerPosY == 0) {
					padding = 7;
				} else if (playerPosY == 1) {
					padding = 13;
				} else if (playerPosY == 2) {
					padding = 19;
				}
				ComponentManager::GetInstance().GetComponent<RenderComponent>(compatibleEntities[i]).model[playerPosX + padding] = 'O';
			}
		}		
	}
	void PostUpdate() {

	}
};