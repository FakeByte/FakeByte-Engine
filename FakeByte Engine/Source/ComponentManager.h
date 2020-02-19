#pragma once

#include <cassert>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <typeinfo>
#include <typeindex>

#include "Types/EntityId.h"
#include "ComponentArray.h"

//Remove
#include <iostream>


//Defines the size of the signature
#define MAX_COMPONENTS 1024

//Singleton Component Manager, manages Entities and Components as well as their relationships
class ComponentManager {
	public:
		//Get Singleton Instance
		static ComponentManager& GetInstance() {
			static ComponentManager instance;
			return instance;
		}

		template<typename... Components>
		entity CreateEntity(Components const&... components) {
			entity id;
			if (unusedEntityIdentifiers.empty()) {
				id = entityCount++;
			} else {
				id = unusedEntityIdentifiers.back();
				unusedEntityIdentifiers.pop_back();
			}

			std::bitset<MAX_COMPONENTS> signature;
			signatures[id] = signature;

			//Remove
			std::cout << "Entity: " << id << " created" << std::endl;

			if constexpr (sizeof...(components) > 0) {
				AddComponent(id, components...);
			}

			return id;
		}

		void DestroyEntity(entity id);

		template<typename Component, typename... Components>
		void AddComponent(entity id, Component const& first, Components const&... rest) {
			if (componentTypeToIndexMap.find(typeid(first)) == componentTypeToIndexMap.end()) {
				size_t index = componentArrays.size();
				ComponentArray<Component> *component = new ComponentArray<Component>;
				componentArrays.push_back(std::unique_ptr<IComponentArray>(component));
				static_cast<ComponentArray<Component>*>(componentArrays[index].get())->AddComponent(id, first);
				componentTypeToIndexMap[typeid(first)] = index;

				/*Remove 
				Component c = static_cast<ComponentArray<Component>*>(componentArrays[0].get())->GetData(0);
				TestComponent t = static_cast<TestComponent>(c);
				std::cout << t.test << std::endl;*/
			} else {
				static_cast<ComponentArray<Component>*>(componentArrays[componentTypeToIndexMap[typeid(first)]].get())->AddComponent(id, first);
			}

			signatures[id].set(componentTypeToIndexMap[typeid(first)]);

			//Remove
			std::cout << "Added Component: " << typeid(first).name() << " to Entity " << id << std::endl;

			if constexpr (sizeof...(rest) > 0) {
				AddComponent(id, rest...);
			}
		}

		template<typename Component, typename... Components>
		void RemoveComponent(entity id, Component const& first, Components const&... rest) {
			assert(componentTypeToIndexMap.find(typeid(first)) != componentTypeToIndexMap.end());

			static_cast<ComponentArray<Component>*>(componentArrays[componentTypeToIndexMap[typeid(first)]].get())->RemoveComponent(id);

			signatures[id].set(componentTypeToIndexMap[typeid(first)], false);

			//Remove
			std::cout << "Removed Component: " << typeid(first).name() << " from Entity " << id << std::endl;

			if constexpr (sizeof...(rest) > 0) {
				RemoveComponent(id, rest...);
			}
		}

		template<typename T>
		T& GetComponent(entity entityID) {
			return static_cast<ComponentArray<T>*>(componentArrays[componentTypeToIndexMap[typeid(T)]].get())->GetData(entityID);
		}

	private:
		//Singleton--
		ComponentManager() = default;
		~ComponentManager() = default;
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator=(const ComponentManager&) = delete;
		//Singleton--

		//Current existing entities
		unsigned int entityCount = 0;
		//Current different kind of Components in use on any entity
		size_t componentCount = 1;
		//List of existing Entities
		std::vector<entity> unusedEntityIdentifiers;
		//Entity Signatures
		std::unordered_map<entity, std::bitset<MAX_COMPONENTS>> signatures;
		//Map from Component Name to Index in componentArrays
		std::unordered_map<std::type_index, size_t> componentTypeToIndexMap;
		//List of Component Arrays
		std::vector<std::unique_ptr<IComponentArray>> componentArrays;
	};