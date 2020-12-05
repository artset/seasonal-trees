#include "Utilities.h"
#include <iostream>

#include "glm/ext.hpp"

namespace Utilities{



    void insertVec2(std::vector<float> &data, glm::vec2 v) {
        data.push_back(v.x);
        data.push_back(v.y);
    }

    void insertVec3(std::vector<float> &data, glm::vec3 v){
        data.push_back(v.x);
        data.push_back(v.y);
        data.push_back(v.z);
    }

    void insertVertexData(std::vector<float> &data, const VertexData &vdata) {
        insertVec3(data, vdata.pos);
        insertVec3(data, vdata.normal);
        insertVec2(data, vdata.uv);
        insertVec3(data, vdata.tangent);
    }

    bool equals(float given, float val, float epsilon) {
        if (given <= val + epsilon &&
                given >= val - epsilon) {
            return true;
        } return false;
    }

    float lerp(float x, float x0, float xf, float y0, float yf) {
        return (y0 * (xf - x) + yf * (x - x0)) / (xf - x0);
    }

    // NormalMappingUtils

    /**
     * @brief getTriangleTangentVec
     * @param triangle1Verts: bottom left triangle, 0=>topLeft, 1=>bottomLeft, 2=>bottomRight
     * @return
     */
    glm::vec3 getTriangleTangentVec(const std::vector<glm::vec3> &triangleVerts) {
        glm::vec2 uv0 = { 1, 0 };
        glm::vec2 uv1 = { 0, 0 };
        glm::vec2 uv2 = { 0, 1 };
        glm::vec2 uv3 = { 1, 1 };

        glm::vec3 v0 = triangleVerts[0];
        glm::vec3 v1 = triangleVerts[1];
        glm::vec3 v2 = triangleVerts[2];

        return calculateTriangleTangentVec(
                    v1 - v0,
                    v2 - v0,
                    uv1 - uv0,
                    uv2 - uv0);
    }

    glm::vec3 calculateTriangleTangentVec(const glm::vec3 &edge0, const glm::vec3 &edge1,
                                                              const glm::vec2 &deltaUV0, const glm::vec2 &deltaUV1) {
        float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);
        glm::vec3 tangent;

        tangent.x = f * (deltaUV1.y * edge0.x - deltaUV0.y * edge1.x);
        tangent.y = f * (deltaUV1.y * edge0.y - deltaUV0.y * edge1.y);
        tangent.z = f * (deltaUV1.y * edge0.z - deltaUV0.y * edge1.z);

        return tangent;
    }

    // TextureMappingUtils

    glm::vec2 computeUV(PrimitiveType shape, const glm::vec3 &oscPoint, const glm::vec3 &oscNormal) {
        glm::vec2 uv = glm::vec2(0);

        switch (shape) {
            case PrimitiveType::PRIMITIVE_CUBE: {
                uv = computeUVPlane(oscPoint, oscNormal);
                break;
            }
            case PrimitiveType::PRIMITIVE_CONE:
            case PrimitiveType::PRIMITIVE_CYLINDER: {
                if (fabs(oscNormal.y) == 1.f) {
                    // case for cap
                    uv = computeUVPlane(oscPoint, oscNormal);
                }
                else {
                    // case for body
                    float coneHeight = 1.f;
                    float inverseY = lerp(oscPoint.y, 0, 1, 1, 0);
                    uv = glm::vec2(computeUTrunk(oscPoint), inverseY + (coneHeight / 2));
                }
                break;
            }
            case PrimitiveType::PRIMITIVE_SPHERE: {
                float u = computeUTrunk(oscPoint);
                float inverseY = lerp(oscPoint.y, -1, 1, 1, -1);
                float v = computeVTrunk(inverseY);
                uv = glm::vec2(u, v);
                break;
            }
            default:
                break;
        }

        return uv;
    }

    glm::vec2 computeUVPlane(const glm::vec3 &oscPoint, const glm::vec3 &oscNormal) {
        float u = 0, v = 0;
        float r = 0.5;
        float x = oscPoint.x + r;
        float y = oscPoint.y + r;
        float z = oscPoint.z + r;

        // don't technically need to calc this here, but makes everything more readable
        float inverseX = lerp(x, 0, 1, 1, 0);
        float inverseY = lerp(y, 0, 1, 1, 0);
        float inverseZ = lerp(z, 0, 1, 1, 0);

        // TODO: generalize
        // this isn't really good, only works for planes of 6 orientations
        if (oscNormal.x == 1) {
            u = z;
            v = inverseY;
        }
        else if (oscNormal.x == -1) {
            u = inverseZ;
            v = inverseY;
        }
        else if (oscNormal.y == 1) {
            u = x;
            v = z;
        }
        else if (oscNormal.y == -1) {
            u = x;
            v = inverseZ;
        }
        else if (oscNormal.z == 1) {
            u = x;
            v = inverseY;
        }
        else if (oscNormal.z == -1) {
            u = inverseX;
            v = inverseY;
        }

        return glm::vec2(u, v);
    }

    float computeUTrunk(const glm::vec3 &oscPoint) {
        float x = oscPoint.x;
        float z = oscPoint.z;

        float u = 0;

        if (x == 0) {
            if (z == 0) {
                // special case for poles of spheres
                u = 0.5f;
            }
            else if (z < 0) {
                u = 0.25f;
            }
            else if (z > 0) {
                u = 0.75f;
            }
        }
        else {
            float theta = std::atan2(z, x);

            float partialU = -theta / (2 * M_PI);
            u = theta < 0 ? partialU : 1 + partialU;
        }

        return u;
    }

    float computeVTrunk(float y) {
        float r = 0.5f;

        float phi = glm::asin(y / r);
        float v = (phi / M_PI) + 0.5f;

        return v;
    }

}
