#include "Sphere.h"

Sphere::Sphere(int param1, int param2):
    Shape(std::max(2, param1), param2, glm::mat4(1.f))
{
    setUpShapeComponents();
}

Sphere::Sphere(int param1, int param2, glm::mat4 transformation):
    Shape(std::max(2, param1), param2, transformation)
{
    setUpShapeComponents();
}

Sphere::~Sphere() {

}

std::vector<GLfloat> Sphere::getData() {
    std::unique_ptr<ShapeComponent> s1 =
        std::make_unique<SphereComponent>(
            m_param1, m_param2, m_transformation
        );
    return s1->getData();
}

const int Sphere::COMPONENT_COUNT = 1;
void Sphere::setParam1(int param1) {
    m_param1 = std::max(2, param1);
    this->setUpShapeComponents();
}

void Sphere::setUpShapeComponents() {
    m_components.clear();
    m_components.reserve(COMPONENT_COUNT);
    std::unique_ptr<ShapeComponent> s1 =
        std::make_unique<SphereComponent>(
            m_param1, m_param2, m_transformation
        );
    m_components.push_back(std::move(s1));

}
