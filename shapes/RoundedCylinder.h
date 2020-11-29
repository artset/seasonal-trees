#ifndef ROUNDEDCYLINDER_H
#define ROUNDEDCYLINDER_H


#include "Shape.h"
#include "CircleComponent.h"
#include "BarrelComponent.h"

class RoundedCylinder : public Shape
{
public:
    RoundedCylinder(int param1, int param2);
    RoundedCylinder(int param1, int param2, glm::mat4 transformation);
    ~RoundedCylinder();
    virtual std::vector<GLfloat> getData() override;

protected:
    virtual void setUpShapeComponents() override;
private:
    static const int COMPONENT_COUNT;
};
#endif // ROUNDEDCYLINDER_H
