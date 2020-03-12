#pragma once

#include "ECS\Core\Component.h"
#include <string>

struct RenderComponent : Component {
	std::string model = "Model Not found";
};