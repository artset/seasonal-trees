#ifndef ISLAND_H
#define ISLAND_H

#include "ShapeComponent.h"


class Island : public ShapeComponent
{
public:
    Island(int param1, int param2, glm::mat4 transformation);
    ~Island();
protected:
    void setData() override;
    virtual glm::vec3 getNormal(glm::vec3 vert) override;
private:
    void setFan(std::vector<glm::vec3> &triangles, int angleIndex);
    float getRandom(int i, int j);
    float getHeight(int i, int j);

    static const float HEIGHT;
    static const float TIP;
    static const float RADIUS;
};



#endif // ISLAND_H
