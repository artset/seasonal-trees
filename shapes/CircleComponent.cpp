#include "CircleComponent.h"

CircleComponent::CircleComponent(int param1,
                                 int param2,
                                 glm::mat4 transformation)
    : ShapeComponent(param1, param2, transformation)
{
    this->setData();
//    this->buildVAO();
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
        this->setFanData(triangles, i, rad, angle);
        Triangle t1 = Triangle();
        Triangle t2 = Triangle();
        for (int j = 1; j < m_param1; j++) {
            glm::vec3 v1 = glm::vec3(getCartesianCos(rad, angle,j,i), OFFSET,
                                     getCartesianSin(rad, angle,j,i));
            glm::vec3 v2 = glm::vec3(getCartesianCos(rad, angle,j+1,i), OFFSET,
                                     getCartesianSin(rad, angle,j+1,i));
            glm::vec3 v3 = glm::vec3(getCartesianCos(rad, angle,j,i+1), OFFSET,
                                     getCartesianSin(rad, angle,j,i+1));
            glm::vec3 v4 = glm::vec3(getCartesianCos(rad, angle,j+1,i+1), OFFSET,
                                     getCartesianSin(rad, angle,j+1,i+1));

            t1.setTriangleData(v3, v2, v1);
            t2.setTriangleData(v4, v2, v3);
            t1.getTriangleData(triangles);
            t2.getTriangleData(triangles);
        }
    }

    if (m_transformation != glm::mat4(1.f)) {
        applyTransformation(triangles);
    }
    // Inserts information into the vertexData and applies rotational matrix.
    for (int i = 0; i < static_cast<int>(triangles.size()); i++) {
        Utilities::insertVec3(m_vertexData, triangles[i]);
    }
}

void CircleComponent::setFanData(std::vector<glm::vec3> &vertexData,
                                 int angleIndex, float rad, float angle) {
    int i = angleIndex;
    Triangle t1 = Triangle();
    glm::vec3 v1 = glm::vec3(0, OFFSET,0);
    glm::vec3 v2 = glm::vec3(rad * cos(angle * i), OFFSET, rad * sin(angle * i));
    glm::vec3 v3 = glm::vec3(rad * cos(angle * (i+ 1)), OFFSET, rad * sin(angle * (i+ 1)));
    t1.setTriangleData(v1, v3, v2);
    t1.getTriangleData(vertexData);
}


glm::vec3 CircleComponent::getNormal(glm::vec3) {
    return glm::vec3(0,0,0);
}

