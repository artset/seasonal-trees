#include "Tree.h"
#include "glm/gtx/transform.hpp"

Tree::Tree()
{

}

Tree::~Tree() {

}

/// arbitrarily chosen based on appearances
const glm::vec3 Tree::SCALE_FACTOR = glm::vec3(.5f, .8f, .5f);
const float Tree::ANGLE = glm::radians(65.f);

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
    glm::mat4 rotate1 = glm::rotate(-Tree::ANGLE, glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 rotate2 = glm::rotate(Tree::ANGLE, glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 translate1 = glm::translate(glm::mat4(), glm::vec3(0.f, .2f, -.2f));
    glm::mat4 translate2 = glm::translate(glm::mat4(), glm::vec3(0.f, .2f, .2f));

    // Two child branches.
    child1 =  translate1 * rotate1 * scale * child1;
    child2 =  translate2 * rotate2  * scale * child2;

    original = initScale * original;
    trans.insert(trans.end(), {original, child1, child2});
    return trans;
}
