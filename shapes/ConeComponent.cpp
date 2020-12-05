#include "ConeComponent.h"

ConeComponent::ConeComponent(int param1, int param2, glm::mat4 transformation)
    :ShapeComponent(param1, param2, transformation)
{
    this->setData();
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

    bool useTransformation = m_transformation != glm::mat4(1.f);

    for (int i = 0; i < m_param2; i++) {
        this->setFan(triangles, i);
        for (int j = 1; j < m_param1; j++) {
            glm::vec3 v0 = glm::vec3(getCartesianCos(r, angle,j,i),
                                     TIP - (y * j),
                                     getCartesianSin(r, angle,j,i));
            glm::vec3 v1 = glm::vec3(getCartesianCos(r, angle,j+1,i),
                                     TIP - (y * (j + 1)),
                                     getCartesianSin(r, angle,j+1,i));
            glm::vec3 v2 = glm::vec3(getCartesianCos(r, angle,j,i+1),
                                     TIP  - (y * j),
                                     getCartesianSin(r, angle,j,i+1));
            glm::vec3 v3 = glm::vec3(getCartesianCos(r, angle,j+1,i+1),
                                     TIP - (y * (j + 1)),
                                     getCartesianSin(r, angle,j+1,i+1));

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

