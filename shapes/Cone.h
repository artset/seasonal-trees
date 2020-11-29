#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include "CircleComponent.h"
#include "ConeComponent.h"

class Cone : public Shape
{
public:
    Cone(int param1, int param2);
    Cone(int param1, int param2, glm::mat4 transformation);
    ~Cone();
    virtual std::vector<GLfloat> getData() override;

protected:
    virtual void setUpShapeComponents() override;
private:
    static const int COMPONENT_COUNT;
};

#endif // CONE_H
