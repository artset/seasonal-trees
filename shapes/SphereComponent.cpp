#include "SphereComponent.h"

SphereComponent::SphereComponent(int param1, int param2)
    :ShapeComponent(param1, param2, glm::mat4(1.f))
{
    this->setData();
}

SphereComponent::SphereComponent(int param1, int param2, glm::mat4 transformation)
    :ShapeComponent(param1, param2, transformation)
{
    this->setData();
}

SphereComponent::~SphereComponent() {

}

const float SphereComponent::RADIUS = .5f;

void SphereComponent::setData(){
    m_vertexData.clear();
    float theta = 2.f * M_PI / m_param2;
    float phi = M_PI / m_param1;

    std::vector<glm::vec3> triangles;
    float triangleCount = 2 * m_param2 * (1 + m_param1);
    triangles.reserve(triangleCount * COORDINATES_PER_TRIANGLE);

    bool useTransformation = m_transformation != glm::mat4(1.f);

    for (int i = 0; i < m_param1; i++) { // goes through a circle, theta
        for (int j = 0; j < m_param2; j++) { // from bottom to top, phi
            if (i == m_param1 - 1 || i == 0){
                this->setFan(i, j, phi, theta, triangles);
            } else {

                glm::vec3 v0 = glm::vec3(RADIUS * sin(phi * (i)) * cos(theta * j),
                                         RADIUS * cos(phi * (i)),
                                         RADIUS * sin(phi * (i)) * sin(theta * j));
                glm::vec3 v1 = glm::vec3(RADIUS * sin(phi * (i)) * cos(theta * (j+1)),
                                         RADIUS * cos(phi * (i)),
                                         RADIUS * sin(phi * (i)) * sin(theta * (j+1)));
                glm::vec3 v2 = glm::vec3(RADIUS * sin(phi * (i+1)) * cos(theta * (j)),
                                         RADIUS * cos(phi * (i+1)),
                                         RADIUS * sin(phi * (i+1)) * sin(theta * (j)));
                glm::vec3 v3 = glm::vec3(RADIUS * sin(phi * (i+1)) * cos(theta * (j+1)),
                                         RADIUS * cos(phi * (i+1)),
                                         RADIUS * sin(phi * (i+1)) * sin(theta * (j+1)));
                glm::vec3 n0 = glm::normalize(v0);
                glm::vec3 n1 = glm::normalize(v1);
                glm::vec3 n2 = glm::normalize(v2);
                glm::vec3 n3 = glm::normalize(v3);

                glm::vec3 tangent1 = Utilities::getTriangleTangentVec({v0, v1, v2});
                glm::vec3 tangent2 = Utilities::getTriangleTangentVec({v2, v3, v0});

                glm::vec2 uv0 = Utilities::computeUV(PrimitiveType::PRIMITIVE_CYLINDER, v0, n0);
                glm::vec2 uv1 = Utilities::computeUV(PrimitiveType::PRIMITIVE_CYLINDER, v1, n1);
                glm::vec2 uv2 = Utilities::computeUV(PrimitiveType::PRIMITIVE_CYLINDER, v2, n2);
                glm::vec2 uv3 = Utilities::computeUV(PrimitiveType::PRIMITIVE_CYLINDER, v3, n3);

                // there's definitely a nicer way to do this
                if (useTransformation) {
                    v0 = (m_transformation * glm::vec4(v0, 0)).xyz();
                    v1 = (m_transformation * glm::vec4(v1, 0)).xyz();
                    v2 = (m_transformation * glm::vec4(v2, 0)).xyz();
                    v3 = (m_transformation * glm::vec4(v3, 0)).xyz();

                    n0 = (m_transformation * glm::vec4(n0, 0)).xyz();
                    n1 = (m_transformation * glm::vec4(n1, 0)).xyz();
                    n2 = (m_transformation * glm::vec4(n2, 0)).xyz();
                    n3 = (m_transformation * glm::vec4(n3, 0)).xyz();

                    uv0 = (m_transformation * glm::vec4(uv0, 0, 0)).xy();
                    uv1 = (m_transformation * glm::vec4(uv1, 0, 0)).xy();
                    uv2 = (m_transformation * glm::vec4(uv2, 0, 0)).xy();
                    uv3 = (m_transformation * glm::vec4(uv3, 0, 0)).xy();

                    tangent1 = (m_transformation * glm::vec4(tangent1, 0)).xyz();
                    tangent2 = (m_transformation * glm::vec4(tangent2, 0)).xyz();
                }

                Utilities::insertVertexData(m_vertexData, {v2, n2, uv2, tangent1});
                Utilities::insertVertexData(m_vertexData, {v1, n1, uv1, tangent1});
                Utilities::insertVertexData(m_vertexData, {v0, n0, uv0, tangent1});

                Utilities::insertVertexData(m_vertexData, {v3, n3, uv3, tangent1});
                Utilities::insertVertexData(m_vertexData, {v1, n1, uv1, tangent1});
                Utilities::insertVertexData(m_vertexData, {v2, n2, uv2, tangent1});
            }
        }
    }

}

/**
 * @brief SphereComponent::setFan
 * @param i - the index of the phi param
 * @param j - index of the theta param
 * @param phi
 * @param theta
 * @param triangles
 * Sets the top and bottom of the fan.
 */
void SphereComponent::setFan(int i, int j, float phi, float theta, std::vector<glm::vec3> &triangles) {
    float base = i > 0 ? -.5f : .5f;
    float pIndex = i > 0 ? i : i + 1;
    glm::vec3 v1 = glm::vec3(0.f, base, 0.f);
    glm::vec3 v2 = glm::vec3(RADIUS * sin(phi * (pIndex)) * cos(theta * j),
                             RADIUS * cos(phi * (pIndex)),
                             RADIUS * sin(phi * (pIndex)) * sin(theta * j));

    glm::vec3 v3 = glm::vec3(RADIUS * sin(phi * (pIndex)) * cos(theta * (j+1)),
                             RADIUS * cos(phi * (pIndex)),
                             RADIUS * sin(phi * (pIndex)) * sin(theta * (j+1)));
    glm::vec3 n1 = getNormal(v1);
    glm::vec3 n2 = getNormal(v2);
    glm::vec3 n3 =getNormal(v3);

    if (i > 0) { // bottom fan
        triangles.insert(triangles.end(), {v1, n1, v2, n2, v3,n3});
    } else { // top fan
        triangles.insert(triangles.end(), {v3, n3, v2, n2, v1,n1});
    }
}


glm::vec3 SphereComponent::getNormal(glm::vec3 v) {
    return glm::normalize(v);
}
