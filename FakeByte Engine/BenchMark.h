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
#include "SystemManager.h"
#include "System.h"
#include "ComponentManager.h"
#include "Timer.h"

//BenchmarkSystem for benchmarking using integers
class IntBenchmarkSystem : public System {
	void PreUpdate() {}

	void Update() {
		for (size_t i = 0; i < compatibleEntities.size(); i++) {
			ComponentManager::GetInstance().GetComponent<int>(compatibleEntities[i]);
		}
	}

	void PostUpdate() {}
};

class Benchmark {
public:
	/**
	* Returns a singleton instance
	* @returns Singleton Instance
	*/
	static Benchmark& GetInstance() {
		static Benchmark instance;
		return instance;
	}

	/**
	* Recursively the benchmarking implementation by 100, 1000, 10000, 100000, 10000000
	* Stores the results in a .html file that can be found in the engine folder
	*/
	static void BenchmarkTest();

private:
	//Singleton
	Benchmark() = default;
	~Benchmark() = default;
	Benchmark(const Benchmark&) = delete;
	Benchmark& operator=(const Benchmark&) = delete;
	//Singleton

	/**
	*Implementation of 
	*/
	void BenchmarkTestImplementation(long long amount);

};