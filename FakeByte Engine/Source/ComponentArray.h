#pragma once

#include <vector>
#include <cassert>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include "Types/EntityId.h"

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void RemoveComponent(entity entityID) = 0;
};

template<typename ComponentType>
class ComponentArray : public IComponentArray{

public:
	void AddComponent(entity entityID, ComponentType component) {
		assert(entityToIndexMap.find(entityID) == entityToIndexMap.end() && "Component added to same entity more than once.");

		size_t newIndex = componentArrayData.size();
		entityToIndexMap[entityID] = newIndex;
		indexToEntityMap[newIndex] = entityID;
		componentArrayData.push_back(component);
	}

	void RemoveComponent(entity entityID) override{
		assert(entityToIndexMap.find(entityID) != entityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = entityToIndexMap[entityID];
		size_t indexOfLastElement = componentArrayData.size() - 1;
		componentArrayData[indexOfRemovedEntity] = componentArrayData[indexOfLastElement];

		// Update map to point to moved spot
		entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap.erase(entityID);
		indexToEntityMap.erase(indexOfLastElement);
	}

	ComponentType& GetData(entity entityID) {
		assert(entityToIndexMap.find(entityID) != entityToIndexMap.end() && "Retrieving non-existent component.");

		return componentArrayData[entityToIndexMap[entityID]];
	}

private:
	std::vector<ComponentType> componentArrayData{};
	std::unordered_map<entity, size_t> entityToIndexMap{};
	std::unordered_map<size_t, entity> indexToEntityMap{};
};