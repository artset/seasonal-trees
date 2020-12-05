#include "ShapeComponent.h"
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include "lib/Utilities.h"

using namespace CS123::GL;

ShapeComponent::ShapeComponent(int param1, int param2):
    m_VAO(nullptr),
    m_param1(param1),
    m_param2(param2),
    m_transformation(glm::mat4(1.f))
{
    m_vertexData.clear();
}


ShapeComponent::ShapeComponent(int param1, int param2, glm::mat4 transformation):
    m_VAO(nullptr),
    m_param1(param1),
    m_param2(param2),
    m_transformation(transformation)
{
    m_vertexData.clear();
}

ShapeComponent::~ShapeComponent() {

}

// 3(vert) + 3(norm) + 2(uv) + 3(tangent)
const int ShapeComponent::COORDINATES_PER_TRIANGLE = 11;

void ShapeComponent::draw() {
    if (m_VAO) {
        m_VAO->bind();
        m_VAO->draw();
        m_VAO->unbind();
    }
}

std::vector<GLfloat> ShapeComponent::getData() {
    return m_vertexData;
}

float ShapeComponent::getCartesianCos(float rad, float angle, float radIndex, float angleIndex) {
    return (radIndex * rad) * cos(angleIndex * angle);
}

float ShapeComponent::getCartesianSin(float rad, float angle, float radIndex, float angleIndex) {
    return (radIndex * rad) * sin(angleIndex * angle);
}


void ShapeComponent::buildVAO() {
    const int numFloatsPerVertex = 3;
    const int numVertices = m_vertexData.size() / numFloatsPerVertex;
    std::vector<VBOAttribMarker> markers;
    markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3 * sizeof(float)));
    VBO vbo = VBO(m_vertexData.data(), m_vertexData.size(), markers);
    m_VAO = std::make_unique<VAO>(vbo, numVertices);
}


void ShapeComponent::applyTransformation(std::vector<glm::vec3> &triangles) {
    for (int i = 0; i < static_cast<int>(triangles.size()); i++) {
        glm::vec3 point = triangles[i];
        glm::vec4 transformed = (m_transformation * glm::vec4(point, 1.f));
        triangles[i] = transformed.xyz();
    }
}

/**
 * @brief ShapeComponent::setTriangleVertexData - Sets the vertex data for an individual triangle given its vertices
 * and corresponding normals in counter-clockwise order.
 * @param v0
 * @param v1
 * @param v2
 * @param n0
 * @param n1
 * @param n2
 */
void ShapeComponent::setTriangleVertexData(const Vertex &vert0, const Vertex &vert1, const Vertex &vert2) {
    glm::vec3 v0 = vert0.pos;
    glm::vec3 v1 = vert1.pos;
    glm::vec3 v2 = vert2.pos;

    glm::vec3 n0 = vert0.normal;
    glm::vec3 n1 = vert1.normal;
    glm::vec3 n2 = vert2.normal;

    glm::vec3 tangent = Utilities::getTriangleTangentVec({v0, v1, v2});

    glm::vec2 uv0 = Utilities::computeUV(PrimitiveType::PRIMITIVE_CYLINDER, v0, n0);
    glm::vec2 uv1 = Utilities::computeUV(PrimitiveType::PRIMITIVE_CYLINDER, v1, n1);
    glm::vec2 uv2 = Utilities::computeUV(PrimitiveType::PRIMITIVE_CYLINDER, v2, n2);

    // there's definitely a nicer way to do this
    if (m_transformation != glm::mat4(1.f)) {
        v0 = (m_transformation * glm::vec4(v0, 0)).xyz();
        v1 = (m_transformation * glm::vec4(v1, 0)).xyz();
        v2 = (m_transformation * glm::vec4(v2, 0)).xyz();

        n0 = (m_transformation * glm::vec4(n0, 0)).xyz();
        n1 = (m_transformation * glm::vec4(n1, 0)).xyz();
        n2 = (m_transformation * glm::vec4(n2, 0)).xyz();

        uv0 = (m_transformation * glm::vec4(uv0, 0, 0)).xy();
        uv1 = (m_transformation * glm::vec4(uv1, 0, 0)).xy();
        uv2 = (m_transformation * glm::vec4(uv2, 0, 0)).xy();

        tangent = (m_transformation * glm::vec4(tangent, 0)).xyz();
    }

    Utilities::insertVertexData(m_vertexData, {v0, n0, uv0, tangent});
    Utilities::insertVertexData(m_vertexData, {v1, n1, uv1, tangent});
    Utilities::insertVertexData(m_vertexData, {v2, n2, uv2, tangent});
}
