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


glm::vec3 BarrelComponent::getNormal(glm::vec3 v) {
    return glm::normalize(glm::vec3(v.x, 0, v.z));
}
