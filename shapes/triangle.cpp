#include "triangle.h"

/**
 * @brief Triangle::Triangle
 * This class computs normals for a triangle given three
 * vertices and is used in the CircleComponent and SquareComponenet.
 */
Triangle::Triangle():
    m_vertices(),
    m_normal(0.f, 0.f, 0.f)
{
    m_vertices.reserve(3);
}

Triangle::~Triangle() {

}

glm::vec3 Triangle::getNormal(){
    return m_normal;
}
/**
 * @brief Triangle::getTriangleData
 * @param data
 * Modifies the data for the triangle. Make sure
 * to reserve space beforehand. This is the order needed
 * to render in the VAO.
 */
void Triangle::getTriangleData(std::vector<glm::vec3> &data) {
    for (int i = 0; i < (int) m_vertices.size(); i++) {
        data.push_back(m_vertices[i]);
        data.push_back(m_normal);
    }
}

// will set the data in the array and compute the normal
// the normal will be computed from v1->v2 v2->v3
void Triangle::setTriangleData(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {

    m_vertices.push_back(v1);
    m_vertices.push_back(v2);
    m_vertices.push_back(v3);

    glm::vec3 v1v2 = glm::vec3(
                v2.x - v1.x,
                v2.y - v1.y,
                v2.z - v1.z);

    glm::vec3 v2v3 = glm::vec3(
                v3.x - v2.x,
                v3.y - v2.y,
                v3.z - v2.z);

    m_normal = glm::normalize(glm::cross(v1v2, v2v3));
}


/**
 * @brief Triangle::printData
 * Prints the data for debugging.
 */
void Triangle::printData() {
    std::cout << "Coordinates: ";
    for (int i = 0; i < (int) m_vertices.size(); i++) {
        std::cout << m_vertices[i].x << " " << m_vertices[i].y << " " << m_vertices[i].z << std::endl;
    }
    std::cout << "Normal: " <<
        m_normal.x << " " << m_normal.y << " " << m_normal.z << std::endl;
}


