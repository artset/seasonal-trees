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
