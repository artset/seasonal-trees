#ifndef UTILITIES_H
#define UTILITIES_H



#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"

namespace Utilities {
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    bool equals(float given, float val, float epsilon);

    glm::vec3 getTriangleTangentVec(const std::vector<glm::vec3> &triangleVerts);
    glm::vec3 calculateTriangleTangentVec(const glm::vec3 &edge0, const glm::vec3 &edge1,
                                                              const glm::vec2 &deltaUV0, const glm::vec2 &deltaUV1);
};


#endif // UTILITIES_H
