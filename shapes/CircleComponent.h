#ifndef CIRCLECOMPONENT_H
#define CIRCLECOMPONENT_H

#include "ShapeComponent.h"

class CircleComponent : public ShapeComponent
{
public: // TODO: generalize to any offset?
    CircleComponent(int param1, int param2, glm::mat4 transformation);
    ~CircleComponent();
    void setData() override;
private:
    virtual glm::vec3 getNormal(glm::vec3 vert) override;
    static const float RADIUS;
    static const float OFFSET;
    void setFanData(int angleIndex, float rad, float angle);
};

#endif // CIRCLECOMPONENT_H
