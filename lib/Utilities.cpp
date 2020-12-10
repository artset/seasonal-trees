#include "Utilities.h"
#include <iostream>

#include "glm/ext.hpp"


namespace Utilities{

    const float UTIL_EPSILON = 1e-5;

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

    /**
     * @brief setTriangleVertexData - Sets the vertex data for an individual triangle given its vertices
     * and corresponding normals in counter-clockwise order.
     * @param v0
     * @param v1
     * @param v2
     * @param n0
     * @param n1
     * @param n2
     */
    void setTriangleVertexData(std::vector<GLfloat> &data, PrimitiveType shape, const glm::mat4 &transformation,
                                     const Vertex &vert0, const Vertex &vert1, const Vertex &vert2) {
        glm::vec3 v0 = vert0.pos;
        glm::vec3 v1 = vert1.pos;
        glm::vec3 v2 = vert2.pos;

        glm::vec3 n0 = vert0.normal;
        glm::vec3 n1 = vert1.normal;
        glm::vec3 n2 = vert2.normal;

        glm::vec2 uv0 = computeUV(shape, v0, n0);
        glm::vec2 uv1 = computeUV(shape, v1, n1);
        glm::vec2 uv2 = computeUV(shape, v2, n2);

        checkTriangleUV(&uv0, uv1, uv2);
        checkTriangleUV(&uv1, uv0, uv2);
        checkTriangleUV(&uv2, uv0, uv1);

        glm::vec3 edge0 = v1 - v0;
        glm::vec3 edge1 = v2 - v0;
        glm::vec3 edge2 = v2 - v1;

        glm::vec3 finalEdge0, finalEdge1;
        glm::vec2 finalDeltaUV0, finalDeltaUV1;

//        if (equals(glm::dot(edge0, edge1), 0, UTIL_EPSILON)) {

//        } else if (equals(glm::dot(edge0, edge1), 0, UTIL_EPSILON)) {

//        } else if (equals(glm::dot(edge0, edge1), 0, UTIL_EPSILON)) {

//        } else {

//        }

//        glm::vec2 deltaUV0 = uv1 - uv0;
//        glm::vec2 deltaUV1 = uv2 - uv0;

        glm::vec2 deltaUV0 = {0,-1};
        glm::vec2 deltaUV1 = {1,-1};

        glm::vec3 tangent = getTriangleTangentVec(edge0, edge1, deltaUV0, deltaUV1);

        if (transformation != glm::mat4(1.f)) {
            v0 = (transformation * glm::vec4(v0, 1)).xyz();
            v1 = (transformation * glm::vec4(v1, 1)).xyz();
            v2 = (transformation * glm::vec4(v2, 1)).xyz();

            n0 = (transformation * glm::vec4(n0, 1)).xyz();
            n1 = (transformation * glm::vec4(n1, 1)).xyz();
            n2 = (transformation * glm::vec4(n2, 1)).xyz();

    //        uv0 = (transformation * glm::vec4(uv0, 0, 1)).xy();
    //        uv1 = (transformation * glm::vec4(uv1, 0, 1)).xy();
    //        uv2 = (transformation * glm::vec4(uv2, 0, 1)).xy();

            tangent = (transformation * glm::vec4(tangent, 1)).xyz();
        }

        insertVertexData(data, {v0, n0, uv0, reorthogonalize(tangent, n0)});
        insertVertexData(data, {v1, n1, uv1, reorthogonalize(tangent, n1)});
        insertVertexData(data, {v2, n2, uv2, reorthogonalize(tangent, n2)});
    }

    // NormalMappingUtils

    glm::vec3 getTriangleTangentVec(const glm::vec3 &edge0, const glm::vec3 &edge1,
                                                              const glm::vec2 &deltaUV0, const glm::vec2 &deltaUV1) {
        float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);
        glm::vec3 tangent = f * (edge0 * deltaUV1.y - edge1 * deltaUV1.y);
        return tangent;
    }

    // Gram-Schmidt re-orthogonalization for tangent with respect to surface normal (gives slightly nicer results)
    glm::vec3 reorthogonalize(const glm::vec3 &v, const glm::vec3 &wrt) {
        return glm::normalize(v - glm::dot(v, wrt) * wrt);
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
                if (equals(fabs(oscNormal.y), 1.f, UTIL_EPSILON)) {
                    // case for cap
                    uv = computeUVPlane(oscPoint, oscNormal);
                }
                else {
                    // case for body
                    float r = 0.5f;
                    float v = lerp(oscPoint.y, -r, r, 1, 0);
                    uv = glm::vec2(computeUTrunk(oscPoint), v);
                }
                break;
            }
            case PrimitiveType::PRIMITIVE_SPHERE: {
                float u = computeUTrunk(oscPoint);
                float r = 0.5f;
                float inverseY = lerp(oscPoint.y, -r, r, r, -r);
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
        if (equals(oscNormal.x, 1.f, UTIL_EPSILON)) {
            u = z;
            v = inverseY;
        }
        else if (equals(oscNormal.x, -1.f, UTIL_EPSILON)) {
            u = inverseZ;
            v = inverseY;
        }
        else if (equals(oscNormal.y, 1.f, UTIL_EPSILON)) {
            u = x;
            v = z;
        }
        else if (equals(oscNormal.y, -1.f, UTIL_EPSILON)) {
            u = x;
            v = inverseZ;
        }
        else if (equals(oscNormal.z, 1.f, UTIL_EPSILON)) {
            u = x;
            v = inverseY;
        }
        else if (equals(oscNormal.z, -1.f, UTIL_EPSILON)) {
            u = inverseX;
            v = inverseY;
        }

        return glm::vec2(u, v);
    }

    float computeUTrunk(const glm::vec3 &oscPoint) {
        float x = oscPoint.x;
        float z = oscPoint.z;

        float u = 0;

        if (equals(x, 0, UTIL_EPSILON)) {
            if (equals(z, 0, UTIL_EPSILON)) {
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
            u = theta < UTIL_EPSILON ? partialU : 1.f + partialU;
        }

        return glm::clamp(u, 0.f, 1.f);
    }

    float computeVTrunk(float y) {
        float r = 0.5f;

        float phi = glm::asin(y / r);
        float v = (phi / M_PI) + 0.5f;

        return v;
    }

    void checkTriangleUV(glm::vec2* uv, const glm::vec2 &otherUV1, const glm::vec2 &otherUV2) {
        float uvMidpoint = 1.f / 2;
        if (equals(uv->x, 0, UTIL_EPSILON) &&
                (otherUV1.x > uvMidpoint || otherUV2.x > uvMidpoint)) {
            uv->x = 1.f;
        }
        if (equals(uv->y, 0, UTIL_EPSILON) &&
                (otherUV1.y > uvMidpoint || otherUV2.y > uvMidpoint)) {
            uv->y = 1.f;
        }
    }

}
