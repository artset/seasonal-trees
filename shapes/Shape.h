#ifndef SHAPE_H
#define SHAPE_H

/** imports the OpenGL math library https://glm.g-truc.net/0.9.2/api/a00001.html */
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <vector>
#include <iostream>
#include <memory>

#include "triangle.h"
#include "ShapeComponent.h"

#include "gl/datatype/vao.h"
#include "gl/datatype/vbo.h"
#include "gl/datatype/vboattribmarker.h"
#include "gl/shaders/shaderattriblocations.h"

using namespace CS123::GL;

/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
void insertVec3(std::vector<float> &data, glm::vec3 v);

namespace CS123 { namespace GL {
class VAO;
}}

class Shape
{
public:
    Shape(int param1, int param2);
    Shape(int param1, int param2, glm::mat4 transformation);

    virtual ~Shape();
    void draw();
    virtual void setParam1(int param1);
    void setParam2(int param2);
    virtual std::vector<GLfloat> getData() = 0;


protected:
    virtual void setUpShapeComponents() = 0;
    std::vector<std::unique_ptr<ShapeComponent>> m_components;
    int m_param1;
    int m_param2;
    glm::mat4 m_transformation;
};

#endif // SHAPE_H
