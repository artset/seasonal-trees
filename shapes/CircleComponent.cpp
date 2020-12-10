#include "CircleComponent.h"

CircleComponent::CircleComponent(int param1,
                                 int param2,
                                 glm::mat4 transformation)
    : ShapeComponent(param1, param2, transformation)
{
    this->setData();
}

CircleComponent::~CircleComponent(){
}


const float CircleComponent::OFFSET = .5f;
const float CircleComponent::RADIUS = .5f;

void CircleComponent::setData(){
    m_vertexData.clear();

    float angle = 2.f * M_PI / m_param2;
    float rad = RADIUS / m_param1;

    std::vector<glm::vec3> triangles;
    int numTriangles = m_param2 + (m_param2 * 2 * (m_param1 - 1));
    triangles.reserve(numTriangles * COORDINATES_PER_TRIANGLE);

    for (int i = 0; i < m_param2; i++) {
        this->setFanData(i, rad, angle);
        Triangle t0 = Triangle();
        Triangle t1 = Triangle();
        for (int j = 1; j < m_param1; j++) {
            glm::vec3 v0 = glm::vec3(getCartesianCos(rad, angle,j,i), OFFSET,
                                     getCartesianSin(rad, angle,j,i));
            glm::vec3 v1 = glm::vec3(getCartesianCos(rad, angle,j+1,i), OFFSET,
                                     getCartesianSin(rad, angle,j+1,i));
            glm::vec3 v2 = glm::vec3(getCartesianCos(rad, angle,j,i+1), OFFSET,
                                     getCartesianSin(rad, angle,j,i+1));
            glm::vec3 v3 = glm::vec3(getCartesianCos(rad, angle,j+1,i+1), OFFSET,
                                     getCartesianSin(rad, angle,j+1,i+1));

            t0.setTriangleData(v2, v1, v0);
            t1.setTriangleData(v3, v1, v2);

            glm::vec3 n0 = t0.getNormal();
            glm::vec3 n1 = t1.getNormal();

//            t1.getTriangleData(triangles);
//            t2.getTriangleData(triangles);

            // primitive type could also be cylinder
            Utilities::setTriangleVertexData(m_vertexData, PrimitiveType::PRIMITIVE_CONE, m_transformation, { v2, n0 }, { v1, n0 }, { v0, n0 });
            Utilities::setTriangleVertexData(m_vertexData, PrimitiveType::PRIMITIVE_CONE, m_transformation, { v3, n1 }, { v1, n1 }, { v2, n1 });
        }
    }

}

void CircleComponent::setFanData(int angleIndex, float rad, float angle) {
    int i = angleIndex;
    Triangle t = Triangle();
    glm::vec3 v0 = glm::vec3(0, OFFSET,0);
    glm::vec3 v1 = glm::vec3(rad * cos(angle * i), OFFSET, rad * sin(angle * i));
    glm::vec3 v2 = glm::vec3(rad * cos(angle * (i+ 1)), OFFSET, rad * sin(angle * (i+ 1)));

    t.setTriangleData(v0, v2, v1);
    glm::vec3 n = t.getNormal();

//    t1.getTriangleData(vertexData);
    Utilities::setTriangleVertexData(m_vertexData, PrimitiveType::PRIMITIVE_CONE, m_transformation, { v0, n }, { v2, n }, { v1, n });
}


glm::vec3 CircleComponent::getNormal(glm::vec3) {
    return glm::vec3(0,0,0);
}

