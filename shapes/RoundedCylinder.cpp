#include "RoundedCylinder.h"
#include "SphereComponent.h"

RoundedCylinder::RoundedCylinder(int param1, int param2) :
    Shape(param1, param2, glm::mat4(1.f))
{
    setUpShapeComponents();
}


RoundedCylinder::RoundedCylinder(int param1, int param2, glm::mat4 transformation) :
    Shape(param1, param2, transformation)
{
    setUpShapeComponents();
}

RoundedCylinder::~RoundedCylinder()
{
}

const int RoundedCylinder::COMPONENT_COUNT = 3;


std::vector<GLfloat> RoundedCylinder::getData() {
    const glm::mat4 rotate =  {
        1.f, 0.f, 0.0f, 0.0f,
        0.f, -1.f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    glm::mat4 sphereScale = glm::scale(glm::mat4(), glm::vec3(1.f, .2f, 1.f));

    glm::mat4 sphereTrans = glm::translate(glm::mat4(), glm::vec3(0.f, .5f, 0.f));

    m_components.clear();
    m_components.reserve(COMPONENT_COUNT);
    std::unique_ptr<ShapeComponent> s =
        std::make_unique<CircleComponent>(
            m_param1, m_param2, m_transformation * rotate
        );

    const int SPHERE_STACK = 10; // To have a "tight" rounded top.
    std::unique_ptr<ShapeComponent> s1 =
        std::make_unique<SphereComponent>(
            SPHERE_STACK, m_param2, sphereTrans * sphereScale * glm::mat4(1.f)
        );



    std::unique_ptr<ShapeComponent> s2 =
        std::make_unique<BarrelComponent>(
            m_param1, m_param2, m_transformation
        );

    std::vector<GLfloat> data;
    data = s->getData();


    std::vector<GLfloat> s1Data = s1->getData();
    auto middle = s1Data.begin() + s1Data.size() / 2;
    data.insert(std::end(data), std::begin(s1Data), middle);


    std::vector<GLfloat> s2Data = s2->getData();
    data.insert(std::end(data), std::begin(s2Data), std::end(s2Data));

    return data;

}

// NOT WORKING, BUT SHOULDN'T NEED
void RoundedCylinder::setUpShapeComponents() {

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
