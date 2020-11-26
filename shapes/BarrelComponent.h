#ifndef BARRELCOMPONENT_H
#define BARRELCOMPONENT_H

#include "ShapeComponent.h"

class BarrelComponent : public ShapeComponent
{
public:
    BarrelComponent(int param1, int param2, glm::mat4 transformation);
    ~BarrelComponent();
protected:
    virtual glm::vec3 getNormal(glm::vec3 vert) override;
    glm::mat4 m_rotation;
    void setData() override;
private:
    static const float BASE;
    static const float RADIUS;
    static const float HEIGHT;
};

#endif // BARRELCOMPONENT_H
