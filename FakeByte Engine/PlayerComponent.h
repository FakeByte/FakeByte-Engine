#pragma once

#include "Component.h"
#include <string>

struct PlayerComponent : Component {
	int x = 0;
	int y = 0;
	int counter = 0;
	bool changed = true;
};