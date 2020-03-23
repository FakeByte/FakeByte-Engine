#pragma once
#include <algorithm>
#include <vector>
#include "ECS\Core\SystemManager.h"
#include "ECS\Core\System.h"

namespace Algorithm {
	template<typename T, class Compare = std::less<>>
	size_t BinaryFind(size_t firstIndex, size_t lastIndex, T, Compare comp = {}) {

		auto first = s.begin();
		auto last = s.begin() + last;
		firstIndex = std::lower_bound(first, last, systems, comp);
		return firstIndex != lastIndex && !comp(system, *firstIndex) ? firstIndex : lastIndex;
	}
}