#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"
#include "CircleComponent.h"
#include "BarrelComponent.h"

class Cylinder : public Shape
{
public:
    Cylinder(int param1, int param2);
    Cylinder(int param1, int param2, glm::mat4 transformation);
    ~Cylinder();
    virtual std::vector<GLfloat> getData() override;

protected:
    virtual void setUpShapeComponents() override;
private:
    static const int COMPONENT_COUNT;
};

#endif // CYLINDER_H
