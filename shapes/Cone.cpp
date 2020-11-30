#include "Cone.h"

Cone::Cone(int param1, int param2):
    Shape(param1, param2, glm::mat4(1.f))
{
}

Cone::Cone(int param1, int param2, glm::mat4 transformation):
    Shape(param1, param2, transformation)
{
}

Cone::~Cone() {

}

const int Cone::COMPONENT_COUNT = 2;

std::vector<GLfloat> Cone::getData() {
    const glm::mat4 rotate =  {
        1.f, 0.f, 0.0f, 0.0f,
        0.f, -1.f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    std::unique_ptr<ShapeComponent> s1 =
        std::make_unique<CircleComponent>(
            m_param1, m_param2, m_transformation * rotate
        );

    std::unique_ptr<ShapeComponent> s2 =
        std::make_unique<ConeComponent>(
            m_param1, m_param2, m_transformation
        );

    std::vector<GLfloat> data = s1->getData();
    std::vector<GLfloat> s2Data = s2->getData();

    data.insert(std::end(data), std::begin(s2Data), std::end(s2Data));

    return data;


}
void Cone::setUpShapeComponents() {
    m_components.clear();
    m_components.reserve(COMPONENT_COUNT);

    const glm::mat4 rotate =  {
        1.f, 0.f, 0.0f, 0.0f,
        0.f, -1.f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    std::unique_ptr<ShapeComponent> s1 =
        std::make_unique<CircleComponent>(
            m_param1, m_param2, m_transformation * rotate
        );

    std::unique_ptr<ShapeComponent> s2 =
        std::make_unique<ConeComponent>(
            m_param1, m_param2, m_transformation
        );
    m_components.push_back(std::move(s1));
    m_components.push_back(std::move(s2));
}
