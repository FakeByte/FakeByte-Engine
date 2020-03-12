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
#include <vector>		//Dynamic Array Container
#include <cassert>		//Used for Debug Build assert statements
#include <unordered_map>//Unordered Hash Table	
#include <typeinfo>		//used for typeid()
#include <typeindex>	//A wrapper around typeinfo

#include "ECS\Types\EntityId.h"	//Defines the type entity

/**
 * Component Array Interface.
 */
class IComponentArray {
public:
	/**
	 * Virtual function to Remove Components
	 *
	 * @param entityID The ID of the entity whose component will be removed.
	 * @see ComponentArray RemoveComponent
	 */
	virtual void RemoveComponent(entity entityID) = 0;
	virtual ~IComponentArray() = default;
};

/**
 * This ComponentArray Template can create an array of components of any type.
 * Inherits from the IComponentArray interface.
 * 
 * @tparam ComponentType Type of the component that will be saved in the ComponentArray.
 */
template<typename ComponentType>
class ComponentArray : public IComponentArray{

public:
	/**
	 * Adds a Component to an entity
	 *
	 * @param entityID ID of the entity we will add a component to
	 * @param component Component we will add to the entity
	 *
	 * @throws Throws if the entity already has this component. 
	 * @note Only throws in Debug builds only, undefined behavior in Release builds.
	 */
	void AddComponent(entity entityID, ComponentType component) {
		assert(entityToIndexMap.find(entityID) == entityToIndexMap.end() && "Component added to same entity more than once.");

		size_t newIndex = componentArrayData.size();	//New index is the end of the array
		entityToIndexMap[entityID] = newIndex;			//Created a mapping from entityID to the newIndex
		indexToEntityMap[newIndex] = entityID;			//and from newIndex to entityID
		componentArrayData.push_back(component);		//Adds the component to the vector
	}

	/**
	 * Removes a Component from an entity
	 *
	 * @param entityID ID of the entity we will remove a component from
	 *
	 * @throws Throws if the entity does not have this component.
	 * @note Only throws in Debug builds only, undefined behavior in Release builds.
	 */
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

		//Erase the entity
		entityToIndexMap.erase(entityID);
		indexToEntityMap.erase(indexOfLastElement);

		//Remove the last Component
		componentArrayData.pop_back();
	}

	/**
	 * Returns a Component.
	 * 
	 * @param entityID The ID of the entity whose component we want.
	 * @returns ComponentType& Returns a component linked to the specified entity.
	 */
	ComponentType& GetData(entity entityID) {
		assert(entityToIndexMap.find(entityID) != entityToIndexMap.end() && "Retrieving non-existent component.");

		return componentArrayData[entityToIndexMap[entityID]];
	}

private:
	///Holds the component data
	std::vector<ComponentType> componentArrayData{};		
	///Hash map from entity to index
	std::unordered_map<entity, size_t> entityToIndexMap{};
	///Hash map from index to entity
	std::unordered_map<size_t, entity> indexToEntityMap{};
};