#ifndef UTILITIES_H
#define UTILITIES_H



#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"

namespace Utilities {
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    bool equals(float given, float val, float epsilon);
};


#endif // UTILITIES_H
