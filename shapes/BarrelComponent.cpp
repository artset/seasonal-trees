#include "BarrelComponent.h"

BarrelComponent::BarrelComponent(int param1, int param2, glm::mat4 transformation) :
    ShapeComponent(param1, param2, transformation)
{
    this->setData();
}


BarrelComponent::~BarrelComponent() {

}

const float BarrelComponent::RADIUS = .5f;
const float BarrelComponent::BASE = -.5f;
const float BarrelComponent::HEIGHT = 1.f;

void BarrelComponent::setData() {
    m_vertexData.clear();

    float angle = 2.f * M_PI / m_param2;
    float interval = HEIGHT / m_param1;
    std::vector<glm::vec3> triangles;
    int numTriangles = m_param2 * m_param1 * 2;
    triangles.reserve(numTriangles * COORDINATES_PER_TRIANGLE);

    bool useTransformation = m_transformation != glm::mat4(1.f);

    for (int j = 0; j < m_param1; j++) {
        for (int i = 0; i < m_param2; i++) {
            // bottom right
            glm::vec3 v0 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i),
                                     BASE + (interval * j) ,
                                     getCartesianSin(RADIUS, angle,1.f,i));
            // bottom left
            glm::vec3 v1 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i+1),
                                     BASE + (interval * j),
                                     getCartesianSin(RADIUS, angle,1.f,i+1));
            // top right
            glm::vec3 v2 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i),
                                     BASE + (interval * (j + 1)),
                                     getCartesianSin(RADIUS, angle,1.f,i));
            // top left
            glm::vec3 v3 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i+1),
                                     BASE + (interval * (j + 1)),
                                     getCartesianSin(RADIUS, angle,1.f,i+1));

            glm::vec3 n0 = getNormal(v0);
            glm::vec3 n1 = getNormal(v1);
            glm::vec3 n2 = getNormal(v2);
            glm::vec3 n3 = getNormal(v3);

            // "bottom left" triangle
            setTriangleVertexData(v1, v0, v3);
            // "upper right" triangle
            setTriangleVertexData(v0, v2, v3);
       }
    }

}


glm::vec3 BarrelComponent::getNormal(glm::vec3 v) {
    return glm::normalize(glm::vec3(v.x, 0, v.z));
}
