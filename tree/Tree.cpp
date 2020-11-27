#include "Tree.h"
#include "uniforms/varsfile.h"
#include "glm/gtx/transform.hpp"

Tree::Tree()
{

}

Tree::~Tree() {

}

/// arbitrarily chosen based on appearances
const glm::vec3 Tree::SCALE_FACTOR = glm::vec3(.5f, .8f, .5f);
const float Tree::ANGLE = degreesToRadians(65);

std::vector<glm::mat4> Tree::buildTree(const glm::mat4 &model) {

    // Example binary tree output from l system, iteration = 2
    // F[-F[-X][+X]][+F[-X][+X]]


    // temporarily hardcoded here to just check rendering, the goal is to take
    // input from L System, then build the mat4s based on that
    std::vector<glm::mat4> trans;
    trans.reserve(3);

    // trunk
    glm::mat4 original =  model;
    glm::mat4 initScale = glm::scale(original, glm::vec3(.4f, .7f, .4f));
    original = initScale * original;

    glm::mat4 child1 = original;
    glm::mat4 child2 = original;

    glm::mat4 scale = glm::scale(original, Tree::SCALE_FACTOR);
    glm::mat4 rotate1 = glm::rotate(-Tree::ANGLE, glm::vec3(0.f, 1.f, 1.f));
    glm::mat4 rotate2 = glm::rotate(Tree::ANGLE, glm::vec3(0.f, 1.f, 1.f));

    // Two child branches.
    child1 =  rotate1 * scale * child1;
    child1 = glm::translate(child1, glm::vec3(0.f, .7f, 0.f));

    child2 =  rotate2 * scale * child2;
    child2 = glm::translate(child2, glm::vec3(0.f, .7f, 0.f));

    original = initScale * original;
    trans.insert(trans.end(), {original, child1, child2});
    return trans;
}
