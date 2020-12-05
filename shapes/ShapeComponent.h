#ifndef SHAPECOMPONENT_H
#define SHAPECOMPONENT_H

#include <glm/glm.hpp>
#include "GL/glew.h"
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>

#include "lib/Utilities.h"
#include "triangle.h"

#include "gl/datatype/vao.h"
#include "gl/datatype/vbo.h"
#include "gl/datatype/vboattribmarker.h"
#include "gl/shaders/shaderattriblocations.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/string_cast.hpp>

using namespace CS123::GL;


namespace CS123 { namespace GL {
class VAO;
}}


class ShapeComponent
{
public:
    ShapeComponent(int param1, int param2);
    ShapeComponent(int param1, int param2, glm::mat4 transformation);
    virtual ~ShapeComponent();
    std::vector<GLfloat> getData();
    void draw();

protected:
    void buildVAO();
    float getCartesianSin(float rad, float angle, float radIndex, float angleIndex);
    float getCartesianCos(float rad, float angle, float radIndex, float angleIndex);
    virtual void setData() = 0;
    std::vector<GLfloat> m_vertexData;
    std::unique_ptr<CS123::GL::VAO> m_VAO;
    int m_param1;
    int m_param2;
    virtual glm::vec3 getNormal(glm::vec3 vert) = 0;
    glm::mat4 m_transformation;
    static const int COORDINATES_PER_TRIANGLE;
    void applyTransformation(std::vector<glm::vec3> &triangles);

    void setTriangleVertexData(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2,
                               glm::vec3 n0, glm::vec3 n1, glm::vec3 n2);

};

#endif // SHAPECOMPONENT_H
