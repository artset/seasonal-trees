#ifndef UTILITIES_H
#define UTILITIES_H



#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"


// ShapeUtils
enum class PrimitiveType {
    PRIMITIVE_CUBE,
    PRIMITIVE_CONE,
    PRIMITIVE_CYLINDER,
    PRIMITIVE_SPHERE
};

struct VertexData {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
};

namespace Utilities {
    void insertVec2(std::vector<float> &data, glm::vec2 v);
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    void insertVertexData(std::vector<float> &data, const VertexData &vdata);
    bool equals(float given, float val, float epsilon);
    float lerp(float x, float x0, float xf, float y0, float yf);

    // NormalMappingUtils
    glm::vec3 getTriangleTangentVec(const std::vector<glm::vec3> &triangleVerts);
    glm::vec3 calculateTriangleTangentVec(const glm::vec3 &edge0, const glm::vec3 &edge1,
                                                              const glm::vec2 &deltaUV0, const glm::vec2 &deltaUV1);

    // TextureMappingUtils
    glm::vec2 computeUV(PrimitiveType shape, const glm::vec3 &oscPoint, const glm::vec3 &oscNormal);
    glm::vec2 computeUVPlane(const glm::vec3 &oscPoint, const glm::vec3 &oscNormal);
    float computeUTrunk(const glm::vec3 &oscPoint);
    float computeVTrunk(float y);
};


#endif // UTILITIES_H
