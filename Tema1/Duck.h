#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace Duck
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateMesh(const std::string& name, glm::vec3 color, bool fill, float v[]);
}
