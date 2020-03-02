/*
 * Developed for the FakeByte Engine.
 * See the LICENSE file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * You should have received a copy of the MIT License
 * along with this program.  If not, see <https://opensource.org/licenses/MIT>.
 */

#pragma once

 /* INCLUDES */
#include <cassert>			//Used for Debug Build assert statements
#include <vector>			//Dynamic Array Container
#include <unordered_map>	//Unordered Hash Table	
#include <bitset>			//Bitset is used for signatures
#include <typeinfo>			//used for typeid()
#include <typeindex>		//A wrapper around typeinfo

#include "Types/EntityId.h"	//Defines the type entity
#include "Types/Constants.h"//Defines various constants

#include "ComponentArray.h"	//Array to hold Components
#include "SystemManager.h"	//Manages Systems
#include "Timer.h"

/**
 * Singleton Component Manager, manages Entities and Components as well as their relationships.
 */
class ComponentManager {
	public:
		/**
		 * Returns a singleton instance
		 *
		 * @returns Singleton Instance
		 */
		static ComponentManager& GetInstance() {
			static ComponentManager instance;
			return instance;
		}

		/**
		 * Created an entity with zero or more Components
		 *
		 * @tparam components The components that will be added
		 * @returns entity The newly created entity
		 */
		template<typename... Components>
		entity CreateEntity(Components const&... components) {
			entity id;
			if (unusedEntityIdentifiers.empty()) {	//If no unused ID is available assaign the entityCount as ID 
				id = entityCount++;
			} else {								//Else assaign an unused ID
				id = unusedEntityIdentifiers.back();
				unusedEntityIdentifiers.pop_back();
			}

			//Create signature for the newly created entity
			std::bitset<MAX_COMPONENTS> signature;
			signatures[id] = signature;

			//Add the Components to the newly created entity
			if constexpr (sizeof...(components) > 0) {
				AddComponent(id, components...);
			}

			//Add entity to the entity vector and return it
			entityIdentifiers.push_back(id);
			return id;
		}

		/**
		 * Destroys an entity and its components
		 *
		 * @param id Entity ID that will be destroyed
		 */
		void DestroyEntity(entity id) {
			//Destroys all Components
			for (size_t i = 0; i < MAX_COMPONENTS; i++) {
				if (signatures[id][i] == true) {
					componentArrays[i].get()->RemoveComponent(id);
				}
			}

			//Deletes the entity
			for (size_t i = 0; i < entityIdentifiers.size(); i++) {
				if (entityIdentifiers[i] == id) {
					entityIdentifiers.erase(entityIdentifiers.begin() + i);
				}
			}

			//Add the ID to the unused entity ID vector
			unusedEntityIdentifiers.push_back(id);
		}

		/**
		 * Adds a component to an entity. When multiple components are specified the functions calls itself recursively 
		 * until all components are added to the entity. 
		 *
		 * @param id The ID of the entity that we add components to
		 * @tparam first The component we add
		 * @tparam rest The components we will add recursively
		 */
		template<typename Component, typename... Components>
		void AddComponent(entity id, Component const& first, Components const&... rest) {
			//If the component array for this component type does not exist created and add it
			if (componentTypeToIndexMap.find(typeid(first)) == componentTypeToIndexMap.end()) { 
				size_t index = componentArrays.size();
				ComponentArray<Component> *component = new ComponentArray<Component>;
				componentArrays.push_back(std::unique_ptr<IComponentArray>(component));
				static_cast<ComponentArray<Component>*>(componentArrays[index].get())->AddComponent(id, first);
				componentTypeToIndexMap[typeid(first)] = index;
			} else { //else add the component to its component array
				static_cast<ComponentArray<Component>*>(componentArrays[componentTypeToIndexMap[typeid(first)]].get())->AddComponent(id, first);
			}

			//Update signature
			signatures[id].set(componentTypeToIndexMap[typeid(first)]);

			if constexpr (sizeof...(rest) > 0) { //If more component have to be added call AddComponent recursively
				AddComponent(id, rest...);
			} else { //else Tell the SystemManager to Update the systems compatible entity lists
				SystemManager::FindCompatibleEntities();
			}
		}

		/**
		 * Removes a component from an entity. When multiple components are specified the functions calls itself recursively
		 * until all components are removed from the entity.
		 *
		 * @param id The ID of the entity that we remove components from
		 * @tparam first The component we remove
		 * @tparam rest The components we will remove recursively
		 * @throws Throws if this component type does not have a component array.
		 * @note Only throws in Debug mode.
		 */
		template<typename Component, typename... Components>
		void RemoveComponent(entity id, Component const& first, Components const&... rest) {
			assert(componentTypeToIndexMap.find(typeid(first)) != componentTypeToIndexMap.end() && "Component has not ComponentArray");

			//Remove Component
			static_cast<ComponentArray<Component>*>(componentArrays[componentTypeToIndexMap[typeid(first)]].get())->RemoveComponent(id);

			//Update Signature
			signatures[id].set(componentTypeToIndexMap[typeid(first)], false);

			if constexpr (sizeof...(rest) > 0) {//If more component have to be removed call RemoveComponent recursively
				RemoveComponent(id, rest...);
			}
		}

		/**
		 * Returns a component of type T from the specified entity
		 *
		 * @param entityID The ID of the entity who we will return the component from.
		 * @tparam T The type of component we want to return
		 * @returns Component of type T from the specified entity
		 */
		template<typename T>
		T& GetComponent(entity entityID) {
			return static_cast<ComponentArray<T>*>(componentArrays[componentTypeToIndexMap[typeid(T)]].get())->GetData(entityID);
		}

		/**
		 * Returns the index of a component for the componentArrays vector
		 *
		 * @param componentType The type of the component whose index we want
		 * @returns size_t Index into componentArrays
		 */
		size_t GetComponentIndex(std::type_index componentType) {
			assert(componentTypeToIndexMap.find(componentType) != componentTypeToIndexMap.end() && "ComponentType Array is not yet created");
			return componentTypeToIndexMap[componentType];
		}

		/**
		 * Returns an entity's signature
		 *
		 * @param entityID ID of the entity whose signature we want
		 * @returns std::bitset<MAX_COMPONENTS> The entity's signature
		 */
		std::bitset<MAX_COMPONENTS> GetSignature(entity entityID) {
			return signatures[entityID];
		}

		/**
		 * Returns the Vector containing all entity ID's
		 *
		 * @returns std::vector<entity> The vector containing all entity ID's
		 */
		std::vector<entity> GetEntityVector() {
			return entityIdentifiers;
		}

	private:
		//Singleton--
		ComponentManager() = default;
		~ComponentManager() = default;
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator=(const ComponentManager&) = delete;
		//Singleton--

		unsigned int entityCount = 0;										//Current existing entities
		std::vector<entity> unusedEntityIdentifiers; 						//List of not existing Entities
		std::vector<entity> entityIdentifiers; 								//List of existing Entities
		std::unordered_map<entity, std::bitset<MAX_COMPONENTS>> signatures; //Entity Signatures
		std::unordered_map<std::type_index, size_t> componentTypeToIndexMap;//Map from Component Type to Index in componentArrays
		std::vector<std::unique_ptr<IComponentArray>> componentArrays; 		//List of Component Arrays
	};