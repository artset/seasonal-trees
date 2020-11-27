#ifndef TREE_H
#define TREE_H

#include <vector>
#include "glm/glm.hpp"

class Tree
{
public:
    Tree();
    ~Tree();
    std::vector<glm::mat4> buildTree(const glm::mat4 &model);
private:
    static const glm::vec3 SCALE_FACTOR;
    static const float ANGLE;

};

#endif // TREE_H
