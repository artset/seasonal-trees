#include "Cylinder.h"

Cylinder::Cylinder(int param1, int param2) :
    Shape(param1, param2, glm::mat4(1.f))
{
}

Cylinder::Cylinder(int param1, int param2, glm::mat4 transformation) :
    Shape(param1, param2, transformation)
{
}

Cylinder::~Cylinder()
{
}

const int Cylinder::COMPONENT_COUNT = 3;

std::vector<GLfloat> Cylinder::getData() {
    const glm::mat4 rotate =  {
        1.f, 0.f, 0.0f, 0.0f,
        0.f, -1.f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    m_components.clear();
    m_components.reserve(COMPONENT_COUNT);
    std::unique_ptr<ShapeComponent> s =
        std::make_unique<CircleComponent>(
            m_param1, m_param2, m_transformation
        );
    std::unique_ptr<ShapeComponent> s1 =
        std::make_unique<CircleComponent>(
            m_param1, m_param2, m_transformation * rotate
        );

    std::unique_ptr<ShapeComponent> s2 =
        std::make_unique<BarrelComponent>(
            m_param1, m_param2, m_transformation
        );

    std::vector<GLfloat> data;
    data = s->getData();

    std::vector<GLfloat> s1Data = s1->getData();
    data.insert(std::end(data), std::begin(s1Data), std::end(s1Data));

    std::vector<GLfloat> s2Data = s2->getData();
    data.insert(std::end(data), std::begin(s2Data), std::end(s2Data));

    return data;

}

void Cylinder::setUpShapeComponents() {

    const glm::mat4 rotate =  {
        1.f, 0.f, 0.0f, 0.0f,
        0.f, -1.f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    m_components.clear();
    m_components.reserve(COMPONENT_COUNT);
    std::unique_ptr<ShapeComponent> s =
        std::make_unique<CircleComponent>(
            m_param1, m_param2, m_transformation
        );
    std::unique_ptr<ShapeComponent> s1 =
        std::make_unique<CircleComponent>(
            m_param1, m_param2, m_transformation * rotate
        );

    std::unique_ptr<ShapeComponent> s2 =
        std::make_unique<BarrelComponent>(
            m_param1, m_param2, m_transformation
        );
    m_components.push_back(std::move(s));
    m_components.push_back(std::move(s1));
    m_components.push_back(std::move(s2));
}
