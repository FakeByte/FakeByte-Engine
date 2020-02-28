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

#include <string>	//For std::string
#include <chrono>	//Time class
#include <iostream>	//To output to the console

/**
 * Timer class to measure time intervals. Needs Rework done.
 */
class Timer {
public:
	Timer(std::string name) : name(name), startTimepoint(std::chrono::high_resolution_clock::now()) {}
	~Timer() {
		Stop();
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(startTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(endTimepoint).time_since_epoch().count();

		auto nanoseconds = end - start;

		double microseconds = nanoseconds * 0.001;
		double milliseconds = nanoseconds * 0.000001;
		double seconds = nanoseconds * 0.000000001;

		std::cout << name << ": " << nanoseconds << " ns|" << microseconds << "¦Ìs|" << milliseconds << "ms|" << seconds << "s" << std::endl;
	}

	void reset() { startTimepoint = std::chrono::high_resolution_clock::now(); }

	double elapsedSeconds() const {
		return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1> >>
			(std::chrono::high_resolution_clock::now() - startTimepoint).count();
	}

	long long elapsedNanoseconds() const {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(startTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(endTimepoint).time_since_epoch().count();

		long long nanoseconds = end - start;

		return nanoseconds;
	}

private:
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
};