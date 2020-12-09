#ifndef CONECOMPONENT_H
#define CONECOMPONENT_H

#include "ShapeComponent.h"

class ConeComponent : public ShapeComponent
{
public:
    ConeComponent(int param1, int param2, glm::mat4 transformation);
    ~ConeComponent();
protected:
    void setData() override;
    virtual glm::vec3 getNormal(glm::vec3 vert) override;
private:
    void setFan(int angleIndex);
    static const float HEIGHT;
    static const float TIP;
    static const float RADIUS;
};

#endif // CONECOMPONENT_H
