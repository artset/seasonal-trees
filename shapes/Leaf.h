#ifndef LEAF_H
#define LEAF_H

#include "Shape.h"

class Leaf : public Shape
{
public:
    Leaf(int param1, int param2);
    Leaf(int param1, int param2, glm::mat4 transformation);
    ~Leaf();
    virtual std::vector<GLfloat> getData() override;

protected:
    virtual void setUpShapeComponents() override;
private:
    void setLeafEnds(std::vector<glm::vec3> &t, bool top, int i);
    void setLeafBody(std::vector<glm::vec3> &triangles, bool top, int i);
    static const int COMPONENT_COUNT;
    float getCurve(float incr, float incrIndex, bool top);
    static const float START;
    float m_increment;
//    std::vector<GLfloat> m_leafData;

};

#endif // LEAF_H
