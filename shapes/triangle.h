#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <glm/glm.hpp>
#include "GL/glew.h"

#include <vector>
#include <iostream>


class Triangle
{
public:
    Triangle();
    ~Triangle();
    glm::vec3 getNormal();
    void getTriangleData(std::vector<glm::vec3> &data);
    void setTriangleData(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    void printData();

private:
    std::vector<glm::vec3> m_vertices;
    glm::vec3 m_normal;
};

#endif // TRIANGLE_H
