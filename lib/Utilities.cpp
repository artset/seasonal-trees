#include "Utilities.h"
#include <iostream>

#include "glm/ext.hpp"

namespace Utilities{



    void insertVec3(std::vector<float> &data, glm::vec3 v){
        data.push_back(v.x);
        data.push_back(v.y);
        data.push_back(v.z);
    }


    bool equals(float given, float val, float epsilon) {
        if (given <= val + epsilon &&
                given >= val - epsilon) {
            return true;
        } return false;
    }

    /**
     * @brief getTangentBitangent
     * @param triangle1Verts: bottom left triangle, 0=>topLeft, 1=>bottomLeft, 2=>bottomRight
     * @return
     */
    std::pair<glm::vec3, glm::vec3> getTangentBitangent(const std::vector<glm::vec3> &triangle1Verts) {
        glm::vec2 uv0 = { 1, 0 };
        glm::vec2 uv1 = { 0, 0 };
        glm::vec2 uv2 = { 0, 1 };
        glm::vec2 uv3 = { 1, 1 };

        glm::vec3 v0 = triangle1Verts[0];
        glm::vec3 v1 = triangle1Verts[1];
        glm::vec3 v2 = triangle1Verts[2];

        return calculateTangentBitangent(
                    v1 - v0,
                    v2 - v0,
                    uv1 - uv0,
                    uv2 - uv0);
    }

    std::pair<glm::vec3, glm::vec3> calculateTangentBitangent(const glm::vec3 &edge0, const glm::vec3 &edge1,
                                                              const glm::vec2 &deltaUV0, const glm::vec2 &deltaUV1) {
        float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);
        glm::vec3 tangent, bitangent;

        tangent.x = f * (deltaUV1.y * edge0.x - deltaUV0.y * edge1.x);
        tangent.y = f * (deltaUV1.y * edge0.y - deltaUV0.y * edge1.y);
        tangent.z = f * (deltaUV1.y * edge0.z - deltaUV0.y * edge1.z);

        bitangent.x = f * (-deltaUV1.x * edge0.x + deltaUV0.x * edge1.x);
        bitangent.y = f * (-deltaUV1.x * edge0.y + deltaUV0.x * edge1.y);
        bitangent.z = f * (-deltaUV1.x * edge0.z + deltaUV0.x * edge1.z);

        return { tangent, bitangent };
    }
}
