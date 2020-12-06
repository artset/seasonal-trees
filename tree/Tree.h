#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "LSystem/LSystem.h"

struct LState {
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
    float length;

    glm::mat4 initialRotate;
    glm::mat4 initialScale;
};

class Tree
{
public:
    Tree();
    ~Tree();
    void buildTree(const glm::mat4 &model, const float leafScale);
    std::vector<glm::mat4> getBranchData();
    std::vector<glm::mat4> getLeafData();
    void addTreeOptionRule(int treeOption);
private:
    static const float BRANCH_LENGTH;
    static const glm::vec3 SCALE_FACTOR;
    static const glm::vec3 TRANSLATE;
    static const std::vector<glm::vec3> ROTATE_AXES;

    std::vector<glm::mat4> processBranch(const glm::mat4 &curr, const std::string &string);
    glm::vec3 getRotateAxis(int branchNum);
    glm::mat4 getBranchTransform(const glm::mat4 &model, const LState &state);
    glm::mat4 getLeafTransform(const glm::mat4 &model, const LState &state);

    LState getBranchInitialStateTransforms(const LState &state);
    LState createNewBranchState(const LState &state);
    bool matEq(const glm::mat4 &A, const glm::mat4 &B);
    float getRandomAngle(const int &branchNum, const float &angle);

    LSystem m_lsystem;
    std::vector <glm::mat4> m_leafData;
    std::vector<glm::mat4> m_branchData;
    float m_leafScale;
    bool m_is2D;


};

#endif // TREE_H
