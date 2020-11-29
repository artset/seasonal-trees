#include "ConeComponent.h"

ConeComponent::ConeComponent(int param1, int param2, glm::mat4 transformation)
    :ShapeComponent(param1, param2, transformation)
{
    this->setData();
    this->buildVAO();
}

ConeComponent::~ConeComponent() {

}

const float ConeComponent::TIP = .5f;
const float ConeComponent::HEIGHT = 1.f;
const float ConeComponent::RADIUS = .5f;


void ConeComponent::setData() {
    m_vertexData.clear();
    float angle = 2.f * M_PI / m_param2;
    int numTriangles = (1 * m_param1) - 1;
    std::vector<glm::vec3> triangles;
    triangles.reserve(numTriangles * COORDINATES_PER_TRIANGLE);

    float y = (1.0/ m_param1);
    float r = (RADIUS / m_param1);

    for (int i = 0; i < m_param2; i++) {
        this->setFan(triangles, i);
        for (int j = 1; j < m_param1; j++) {
            glm::vec3 v1 = glm::vec3(getCartesianCos(r, angle,j,i),
                                     TIP - (y * j),
                                     getCartesianSin(r, angle,j,i));
            glm::vec3 v2 = glm::vec3(getCartesianCos(r, angle,j+1,i),
                                     TIP - (y * (j + 1)),
                                     getCartesianSin(r, angle,j+1,i));
            glm::vec3 v3 = glm::vec3(getCartesianCos(r, angle,j,i+1),
                                     TIP  - (y * j),
                                     getCartesianSin(r, angle,j,i+1));
            glm::vec3 v4 = glm::vec3(getCartesianCos(r, angle,j+1,i+1),
                                     TIP - (y * (j + 1)),
                                     getCartesianSin(r, angle,j+1,i+1));

            glm::vec3 n1 = getNormal(v1);
            glm::vec3 n2 = getNormal(v2);
            glm::vec3 n3 = getNormal(v3);
            glm::vec3 n4 = getNormal(v4);

            triangles.insert(triangles.end(), {v3, n3, v2, n2, v1, n1});
            triangles.insert(triangles.end(), {v4, n4, v2, n2, v3, n3});
        }
    }

    if (m_transformation != glm::mat4(1.f)) {
        applyTransformation(triangles);
    }

    for (int i = 0; i < static_cast<int>(triangles.size()); i++) {
        Utilities::insertVec3(m_vertexData, triangles[i]);
    }
}

void ConeComponent::setFan(std::vector<glm::vec3> &triangles, int angleIndex) {
    float angle = 2.f * M_PI / m_param2;
    float y = TIP - (1.0/ m_param1);
    float r = (RADIUS / m_param1);
    if (m_param1 == 1) {
        y = -.5f;
        r = .5f;
    }

    glm::vec3 v1 = glm::vec3(0, HEIGHT / 2.0, 0);
    glm::vec3 v2 = glm::vec3(r * cos(angleIndex * angle), y, r * sin(angleIndex * angle));
    glm::vec3 v3 = glm::vec3(r * cos((angleIndex+1) * angle), y, r * sin((angleIndex+1) * angle));

    Triangle t1 = Triangle();
    t1.setTriangleData(v3, v2, v1);
    glm::vec3 n3 = getNormal(v3);
    glm::vec3 n2 = getNormal(v2);

    triangles.insert(triangles.end(), {v3, n3, v2, n2,v1, t1.getNormal()});
}

/**
 * @brief ConeComponent::getNormal
 * @param vertex the vertex coordinate
 * @return a normal to that vertex
 *
 * This is kinda hacky, but it is equivalent to the algorithm.
 * Basically, the y:horizontal component (if we take y as displaceent)
 * is 1:4 because sqrt(x^2 + z^2) = 1/2, hence x^2 + z^2  = 1/4
 * So the ydisplacement is 1/4 of the x and z components.
 */
glm::vec3 ConeComponent::getNormal(glm::vec3 vertex) {
    float yDisplacement = TIP - vertex.y;
    const int NORMALIZER = 4;
    return glm::normalize(
                glm::vec3(vertex.x * NORMALIZER, yDisplacement, vertex.z * NORMALIZER));
}

