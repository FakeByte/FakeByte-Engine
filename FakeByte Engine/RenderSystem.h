#pragma once

#include "System.h"
#include "ComponentManager.h"
#include "RenderComponent.h"

class RenderSystem : public System {
	void PreUpdate() {

	}
	void Update() {
		system("cls");
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			std::cout << ComponentManager::GetInstance().GetComponent<RenderComponent>(compatibleEntities[i]).model;
		}
	}
	void PostUpdate() {

	}
};