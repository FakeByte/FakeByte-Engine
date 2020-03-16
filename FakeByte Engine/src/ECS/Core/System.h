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
#include <vector>			//Dynamic Array Container
#include <bitset>			//Bitset is used for signatures
#include <typeindex>		//A wrapper around typeinfo

#include "ECS\Constants\Constants.h"//Defines various constants
#include "ECS\Types\EntityId.h"	//Defines the type entity

/* FORWARD DECLARATIONS */
class SystemManager;

/**
 * SystemPriority is used to determine the execution order of systems
 */
enum SystemPriority {
	LOWEST_SYSTEM_PRIORITY = 0,
	VERY_LOW_SYSTEM_PRIORITY = 99,
	LOW_SYSTEM_PRIORITY = 100,
	NORMAL_SYSTEM_PRIORITY = 200,
	MEDIUM_SYSTEM_PRIORITY = 300,
	HIGH_SYSTEM_PRIORITY = 400,
	VERY_HIGH_SYSTEM_PRIORITY = 401,
	HIGHEST_SYSTEM_PRIORITY = 1000
};

/**
 * Abstract System base class.
 */
class System {
public:
	friend bool operator > (System &s1, System &s2);
	friend bool operator <= (System &s1, System &s2);

	friend bool operator < (System &s1, System &s2);
	friend bool operator >= (System &s1, System &s2);

	/**
	 * The constructor will register the system with the SystemManager
	 */
	System();
	
	/*
	 * PreUpdate is called before Update
	 */
	virtual void PreUpdate() = 0;
	/**
	 * Update is called every frame
	 */
	virtual void Update() = 0;
	/**
	 * PostUpdate is called after update
	 */
	virtual void PostUpdate() = 0;

	/**
	 * RequireComponent will add a component type to the list of required components.
	 *
	 * @param componentType Type of the required component
	 */
	void RequireComponent(std::type_index componentType);
	/**
	 * Finds Compatible Entities and saved them in the compatibleEntities vector.
	 */
	void FindCompatibleEntities();

	/**
	 * Returns the systems priority
	 *
	 * @returns SystemPriority
	 */
	SystemPriority GetPriority() { return priority;}
	/**
	 * Sets the systems priority
	 *
	 * @param priority New system priority
	 */
	void SetPriority(SystemPriority priority);

	/**
	 * Shows if the system is enabled. If not enabled the system will not be called by the SystemManager
	 */
	bool enabled = true;

protected:
	SystemPriority priority = NORMAL_SYSTEM_PRIORITY;	//Systems priority
	std::vector<entity> compatibleEntities;				//Vector of compatible entities
	std::bitset<MAX_COMPONENTS> signature;				//Systems signature
};

bool operator < (System &s1, System&s2);
bool operator > (System &s1, System &s2);
bool operator <= (System &s1, System &s2);
bool operator >= (System &s1, System &s2);