#include "Shape.h"

Shape::Shape(int param1, int param2):
    m_param1(std::max(1, param1)),
    m_param2(std::max(3, param2))
{

}

Shape::Shape(int param1, int param2, glm::mat4 transformation):
    m_param1(std::max(1, param1)),
    m_param2(std::max(3, param2)),
    m_transformation(transformation)
{

}


Shape::~Shape()
{
}

void Shape::setParam1(int param1) {
    m_param1 = std::max(1, param1);
    this->setUpShapeComponents();
}


void Shape::setParam2(int param2) {
    m_param2 = std::max(3, param2);
    this->setUpShapeComponents();
}

void Shape::draw() {
    for (int i = 0; i < (int) m_components.size(); i++) {
        m_components[i]->draw();
    }
}
