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
#include <vector>

#include "System.h"

/* FORWARD DECLARATIONS */
class System;
enum SystemPriority;

/**
 * The System Manager manages all systems and calls their update functions
 */
class SystemManager {
public:
	/**
	 * Returns a singleton instance
	 *
	 * @returns Singleton Instance
	 */
	static SystemManager& GetInstance();
	
	/**
	 * Registers a System with the SystemManager
	 *
	 * @param &system The system we want to add
	 */
	static void RegisterSystem(System &system);
	/**
	 * Sorts the systems array from high priority to low priority
	 */
	static void SortSystemsArray();
	/**
	 * Starts the next simulation Step
	 */
	static void Step();
	/**
	 * Calls the FindCompatibleEntities methods in every system
	 */
	static void FindCompatibleEntities();

private:
	//Singleton--
	SystemManager() = default;
	~SystemManager() = default;
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	//Singleton--

	std::vector<System*> systems;						//Vector of all registered systems

	//Implementation methods
	void RegisterSystemImplementation(System &system);	
	void SortSystemsArrayImplementation();
	void StepImplementation();
	void FindCompatibleEntitiesImplementation();
};