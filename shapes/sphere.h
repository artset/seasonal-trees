#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "SphereComponent.h"
class Sphere : public Shape
{
public:
    Sphere(int param1, int param2);
    Sphere(int param1, int param2, glm::mat4 transformation);
    ~Sphere();
    virtual void setParam1(int param1) override;
    virtual std::vector<GLfloat> getData() override;

protected:
    virtual void setUpShapeComponents() override;
private:
    static const int COMPONENT_COUNT;
};

#endif // SPHERE_H
