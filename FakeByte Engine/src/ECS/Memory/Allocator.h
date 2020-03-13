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
#include <cassert>
#include <malloc.h>

#include "ECS\Types\Types.h"


template <class T>
class Allocator {
public:
	~Allocator() {
		assert(allocationCount == 0 && usedMemory == 0 && "Memory Leak Detected");
		if (parent == nullptr) {
			_aligned_free(start);
		}
	}

	void Allocate(size_t size) {
		// Dispatch call to exact type 
		static_cast<T*> (this)->Allocate();
	}

	void Free(void* p) {
		// Dispatch call to exact type 
		static_cast<T*> (this)->Free();
	}

	size_t GetUsedMemory() {
		return usedMemory;
	}

	//Make private
	void* start;
	size_t size;
	size_t usedMemory = 0;
	size_t allocationCount = 0;
	Allocator* parent = nullptr;
protected:
	

};