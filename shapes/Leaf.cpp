#include "Leaf.h"
#include "triangle.h"
#include "ShapeComponent.h"

Leaf::Leaf(int param1, int param2) :
    Shape(param1, param2, glm::mat4(1.f))
{
}


Leaf::Leaf(int param1, int param2, glm::mat4 transformation) :
    Shape(param1, param2, transformation)
{
}

Leaf::~Leaf()
{
}

const float Leaf::START = -1.f;


std::vector<GLfloat> Leaf::getData(){
    const int NUM_TRIANGLES = (m_param1 - 2) * 2;
    const int COORDINATES_PER_TRIANGLE  = 3;
    const int SIDES = 2;
    m_increment = 2.f / m_param1;


    std::vector<glm::vec3> triangles;
    triangles.reserve(NUM_TRIANGLES * COORDINATES_PER_TRIANGLE * SIDES);

    std::vector<GLfloat> leafData;
    leafData.reserve(NUM_TRIANGLES * COORDINATES_PER_TRIANGLE * 2 * SIDES);

    bool TOP = true;

    for (int i = 0; i < m_param1; i++) {
        setLeafEnds(triangles, TOP, i);
        setLeafEnds(triangles, !TOP, i);
        if (i > 0 && i < m_param1 - 1) {
             setLeafBody(triangles, TOP, i);
             setLeafBody(triangles, !TOP, i);
        }
    }

    for (int i = 0; i < static_cast<int>(triangles.size()); i++) {
        Utilities::insertVec3(leafData, triangles[i]);
    }

    return leafData;
}

/**
 * Sets the body of the leaves
 * @brief Leaf::setLeafBody
 * @param triangles
 * @param top
 * @param i
 */
void Leaf::setLeafBody(std::vector<glm::vec3> &triangles, bool top, int i) {
    Triangle t1 = Triangle();
    Triangle t2 = Triangle();

    glm::vec3 v1 = glm::vec3(i * m_increment + Leaf::START, 0, 0);
    glm::vec3 v2 = glm::vec3(i * m_increment + Leaf::START,
                             getCurve(m_increment, i, top), 0.f);
    glm::vec3 v3 = glm::vec3((i+1) * m_increment + Leaf::START,
                             getCurve(m_increment,i + 1, top), 0.f);
    glm::vec3 v4 = glm::vec3((i+1) * m_increment + Leaf::START,
                            0.f, 0.f);

    // Top leaf, front and back
    t1.setTriangleData(v1, v2, v3);
    t2.setTriangleData(v4, v1, v3);
    t1.getTriangleData(triangles);
    t2.getTriangleData(triangles);

    // Bottom leaf, front and back.
    t1.setTriangleData(v3, v2, v1);
    t2.setTriangleData(v1, v4, v3);
    t1.getTriangleData(triangles);
    t2.getTriangleData(triangles);

}

/**
 *  Set the end triangles of the leaves.
 * @brief Leaf::setLeafEnds
 * @param triangles
 * @param top
 * @param i
 */
void Leaf::setLeafEnds(std::vector<glm::vec3> &triangles, bool top, int i) {
    if (i == 0 || i == m_param1 - 1) {
        Triangle t1 = Triangle();
        glm::vec3 v1 = glm::vec3(i * m_increment + Leaf::START, 0, 0);
        glm::vec3 v2 = glm::vec3((i+1) * m_increment + Leaf::START, 0, 0);
        glm::vec3 v3 = glm::vec3(0.f);

        if (i == 0) {
            v3 = glm::vec3((i+1) * m_increment + Leaf::START,
                            getCurve(m_increment, i+1, top),
                            0);
        } else {
            v3 = glm::vec3((i) * m_increment + Leaf::START,
                          getCurve(m_increment, i, top),
                          0);
        }

       t1.setTriangleData(v3, v2, v1);
       t1.getTriangleData(triangles);

       // the other side
       t1.setTriangleData(v1, v2, v3);
       t1.getTriangleData(triangles);
    }
}


float Leaf::getCurve(float incr, float incrIndex, bool top) {
    float x = Leaf::START + (incr * incrIndex);
    float out = cos(x * M_PI_2);
    return top ? out : -out;
}


void Leaf::setUpShapeComponents() {
}
