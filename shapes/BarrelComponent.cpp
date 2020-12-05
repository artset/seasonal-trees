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

    for (int j = 0; j < m_param1; j++) {
        for (int i = 0; i < m_param2; i++) {
            glm::vec3 v0 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i),
                                     BASE + (interval * j) ,
                                     getCartesianSin(RADIUS, angle,1.f,i));
            glm::vec3 v1 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i+1),
                                     BASE + (interval * j),
                                     getCartesianSin(RADIUS, angle,1.f,i+1));
            glm::vec3 v2 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i),
                                     BASE + (interval * (j + 1)),
                                     getCartesianSin(RADIUS, angle,1.f,i));
            glm::vec3 v3 = glm::vec3(getCartesianCos(RADIUS, angle,1.f,i+1),
                                     BASE + (interval * (j + 1)),
                                     getCartesianSin(RADIUS, angle,1.f,i+1));

            glm::vec3 n0 = getNormal(v0);
            glm::vec3 n1 = getNormal(v1);
            glm::vec3 n2 = getNormal(v2);
            glm::vec3 n3 = getNormal(v3);

            glm::vec3 tangent1 = Utilities::getTriangleTangentVec({v0, v1, v2});
            glm::vec3 tangent2 = Utilities::getTriangleTangentVec({v2, v3, v0});

            glm::vec3 uv0, uv1, uv2; // ??? glm::vec2
            glm::vec3 uv3, uv4, uv5; // ??? glm::vec2

            triangles.insert(triangles.end(), {v2, n2, uv0, tangent1, v1, n1, uv1, tangent1, v0, n0, uv2, tangent1});
            triangles.insert(triangles.end(), {v3, n3, uv3, tangent2, v1, n1, uv4, tangent2, v2, n2, uv5, tangent2});
       }
    }

    if (m_transformation != glm::mat4(1.f)) {
        applyTransformation(triangles);
    }


    for (int i = 0; i < static_cast<int>(triangles.size()); i++) {
        Utilities::insertVec3(m_vertexData, triangles[i]);
    }
}


glm::vec3 BarrelComponent::getNormal(glm::vec3 v) {
    return glm::normalize(glm::vec3(v.x, 0, v.z));
}
