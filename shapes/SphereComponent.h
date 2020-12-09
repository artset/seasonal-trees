#ifndef SPHERECOMPONENT_H
#define SPHERECOMPONENT_H

#include "ShapeComponent.h"

class SphereComponent : public ShapeComponent
{
public:
    SphereComponent(int param1, int param2);
    SphereComponent(int param1, int param2, glm::mat4 transformation);
    ~SphereComponent();
protected:
    virtual glm::vec3 getNormal(glm::vec3 vert) override;

    void setData() override;
    void setFan(int i, int j, float phi, float theta);
private:
    static const float RADIUS;
};

#endif // SPHERECOMPONENT_H
