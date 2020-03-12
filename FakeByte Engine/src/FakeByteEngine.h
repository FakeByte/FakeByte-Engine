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
#include <cassert>	//Used for Debug Build assert statements
#include <float.h>	//Used for floating point flags

/**
 * The FakeByteEngine singleton class contains the GameLoop and controls the flow of the running engine.
 */
class FakeByteEngine {
public:
	/**
	 * Returns a singleton instance
	 *
	 * @returns Singleton Instance
	 */
	static FakeByteEngine& GetInstance() {
		static FakeByteEngine instance;
		return instance;
	}

	/**
	 * Initializes the engine
	 *
	 * @see InitializeImplementation()
	 */
	static void Initialize();
	
	/**
	 * Starts the gameloop
	 *
	 * @see StartImplementation()
	 */
	static void Start();

	/**
	 * Stops the gameloop
	 *
	 * @see QuitImplementation()
	 */
	static void Quit();

private:
	//Singleton--
	FakeByteEngine() = default;
	~FakeByteEngine() = default;
	FakeByteEngine(const FakeByteEngine&) = delete;
	FakeByteEngine& operator=(const FakeByteEngine&) = delete;
	//Singleton--

	bool initialized = false;	//Required to start gameloop
	bool quit = false;			//Stops the gameloop

	//Implementations of static methods
	void InitializeImplementation(); 
	void StartImplementation();
	void QuitImplementation();

	void GameLoop();
	void SetFloatingPointControl(); //Sets floating point flags
};