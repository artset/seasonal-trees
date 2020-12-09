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

    for (int i = 0; i < m_param1; i++) { // goes through a circle, theta
        for (int j = 0; j < m_param2; j++) { // from bottom to top, phi
            if (i == m_param1 - 1 || i == 0){
                this->setFan(i, j, phi, theta);
            } else {
                // bottom right
                glm::vec3 v1 = glm::vec3(RADIUS * sin(phi * (i+1)) * cos(theta * (j)),
                                         RADIUS * cos(phi * (i+1)),
                                         RADIUS * sin(phi * (i+1)) * sin(theta * (j)));
                // bottom left
                glm::vec3 v0 = glm::vec3(RADIUS * sin(phi * (i+1)) * cos(theta * (j+1)),
                                         RADIUS * cos(phi * (i+1)),
                                         RADIUS * sin(phi * (i+1)) * sin(theta * (j+1)));
                // top right
                glm::vec3 v3 = glm::vec3(RADIUS * sin(phi * (i)) * cos(theta * j),
                                         RADIUS * cos(phi * (i)),
                                         RADIUS * sin(phi * (i)) * sin(theta * j));
                // top left
                glm::vec3 v2 = glm::vec3(RADIUS * sin(phi * (i)) * cos(theta * (j+1)),
                                         RADIUS * cos(phi * (i)),
                                         RADIUS * sin(phi * (i)) * sin(theta * (j+1)));

                glm::vec3 n0 = glm::normalize(v0);
                glm::vec3 n1 = glm::normalize(v1);
                glm::vec3 n2 = glm::normalize(v2);
                glm::vec3 n3 = glm::normalize(v3);

                // "bottom left" triangle
                Utilities::setTriangleVertexData(m_vertexData, PrimitiveType::PRIMITIVE_SPHERE, m_transformation, { v0, n0 }, { v1, n1 }, { v2, n2 });
                // "upper right" triangle
                Utilities::setTriangleVertexData(m_vertexData, PrimitiveType::PRIMITIVE_SPHERE, m_transformation, { v1, n1 }, { v3, n3 }, { v2, n2 });
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
void SphereComponent::setFan(int i, int j, float phi, float theta) {
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
    glm::vec3 n3 = getNormal(v3);

    if (i > 0) { // bottom fan
        Utilities::setTriangleVertexData(m_vertexData, PrimitiveType::PRIMITIVE_SPHERE, m_transformation, { v2, n2 }, { v3, n3 }, { v1, n1 });
    } else { // top fan
        Utilities::setTriangleVertexData(m_vertexData, PrimitiveType::PRIMITIVE_SPHERE, m_transformation, { v3, n3 }, { v2, n2 }, { v1, n1 });
    }
}


glm::vec3 SphereComponent::getNormal(glm::vec3 v) {
    return glm::normalize(v);
}
