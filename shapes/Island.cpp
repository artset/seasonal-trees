#include "Island.h"

Island::Island(int param1, int param2, glm::mat4 transformation)
    :ShapeComponent(param1, param2, transformation)
{
    this->setData();
}

Island::~Island() {

}

const float Island::TIP = .5f;
const float Island::HEIGHT = 1.f;
const float Island::RADIUS = .5f;


// goes from 0 to 1
float Island::getRandom(int i, int j) {
    return 2.f * glm::fract(sin(i * 127.1f + j * 311.7f) * 43758.5453123f);
}

float Island::getHeight(int i, int j) {
    return getRandom(i, j);

//    return heightA;
}

void Island::setData() {
    m_vertexData.clear();
    float angle = 2.f * M_PI / m_param2;
    int numTriangles = (1 * m_param1) - 1;
    std::vector<glm::vec3> triangles;
    triangles.reserve(numTriangles * COORDINATES_PER_TRIANGLE);

    float y = (1.0/ m_param1);
    float r = (RADIUS / m_param1);

    // goes through each the angles
    for (int i = 0; i < m_param2; i++) {
        this->setFan(triangles, i);

        // goes through each of the levels
        for (int j = 1; j < m_param1; j++) {
            int maxI = i + 1;
            if (maxI == m_param2) {
                maxI = 0;
            }

//            std::cout << i << " " << j << " " << y * getHeight(i, j) << std::endl;
//            std::cout << i+1 << " " << j << " " << y * getHeight(maxI, j) << std::endl;
//            std::cout << i+1 << " " << j+1 << " " << y * getHeight(maxI, j+1) << std::endl;

//            std::cout << "--" << std::endl;

            // interpolate between A and B

            glm::vec3 v1 = glm::vec3(getCartesianCos(r, angle,j,i),
                                      (y * getHeight(i, j)),
//                                     TIP - (y * j),
                                     getCartesianSin(r, angle,j,i));
            glm::vec3 v2 = glm::vec3(getCartesianCos(r, angle,j+1,i),
//                                     TIP - (y * (j + 1))  + getRandom(i, j),
                                     (y * getHeight(i, j+1)),
                                     getCartesianSin(r, angle,j+1,i));
            glm::vec3 v3 = glm::vec3(getCartesianCos(r, angle,j,i+1),
//                                     TIP  - (y * j)  + getRandom(i, j),
                                      (y * getHeight(maxI, j)),
                                     getCartesianSin(r, angle,j,i+1));
            glm::vec3 v4 = glm::vec3(getCartesianCos(r, angle,j+1,i+1),
//                                     TIP - (y * (j + 1))  + getRandom(i, j),
                                     (y * getHeight(maxI, j+1)),
                                     getCartesianSin(r, angle,j+1,i+1));



            Triangle t1 = Triangle();
            t1.setTriangleData(v3, v2, v1);
            glm::vec3 n1 = t1.getNormal();

            Triangle t2 = Triangle();
            t2.setTriangleData(v4, v2, v3);
            glm::vec3 n2 = t2.getNormal();


            triangles.insert(triangles.end(), {v3, n1, v2, n2, v1, n1});
            triangles.insert(triangles.end(), {v4, n2, v2, n2, v3, n2});
        }
    }

    if (m_transformation != glm::mat4(1.f)) {
        applyTransformation(triangles);
    }

    for (int i = 0; i < static_cast<int>(triangles.size()); i++) {
        Utilities::insertVec3(m_vertexData, triangles[i]);
    }
}

void Island::setFan(std::vector<glm::vec3> &triangles, int angleIndex) {
    float angle = 2.f * M_PI / m_param2;
    float y = TIP - (1.0/ m_param1);
    float r = (RADIUS / m_param1);
    if (m_param1 == 1) {
        y = -.5f;
        r = .5f;
    }

//    y = TIP - (y * getHeight(angleIndex, 0));
    float y1 = (y * getHeight(angleIndex, 1));

    float angleIndexPlusOne = angleIndex + 1;
    if (m_param2 == angleIndexPlusOne) {
        angleIndexPlusOne = 0;
    }
    float y2 = (y * getHeight(angleIndexPlusOne, 1));



    glm::vec3 v1 = glm::vec3(0, HEIGHT / 2.0, 0);
    glm::vec3 v2 = glm::vec3(r * cos(angleIndex * angle), y1, r * sin(angleIndex * angle));
    glm::vec3 v3 = glm::vec3(r * cos((angleIndex+1) * angle), y2, r * sin((angleIndex+1) * angle));

    Triangle t1 = Triangle();
    t1.setTriangleData(v3, v2, v1);
    glm::vec3 flatNormal = t1.getNormal();


    triangles.insert(triangles.end(), {v3, flatNormal, v2, flatNormal,v1, flatNormal});
}


glm::vec3 Island::getNormal(glm::vec3 vertex) {
    return glm::vec3(0.f);
}

