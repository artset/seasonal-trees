#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "LSystem/LSystem.h"

class Tree
{
public:
    Tree();
    ~Tree();
    std::vector<glm::mat4> buildTree(const glm::mat4 &model);
private:
    static const glm::vec3 SCALE_FACTOR;
    static const glm::vec3 TRANSLATE;
    static const glm::vec3 ROTATE_AXIS;
    std::vector<glm::mat4> processBranch(const glm::mat4 &curr, const std::string &string);
    LSystem lsystem;

};

#endif // TREE_H
