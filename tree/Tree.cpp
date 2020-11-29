#include "Tree.h"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "LSystem/LSystem.h"

Tree::Tree():
    lsystem()
{
    lsystem.generateSequence();
}

Tree::~Tree() {

}

/// arbitrarily chosen based on appearances
const glm::vec3 Tree::SCALE_FACTOR = glm::vec3(.5f, .8f, .5f);
const glm::vec3 Tree::TRANSLATE = glm::vec3(0.f, .35f, .35f);
const glm::vec3 Tree::ROTATE_AXIS = glm::vec3(1.f,0,0);
const float Tree::ANGLE = glm::radians(65.f);

/**
 * @brief Right now, we iterate through the string linearly, keeping track of open brackets and pushing matrices to the response vec when
 * a close bracket is reached. If an X term is reached, we don't pop from the prevMats vec, since there may be a future X term that needs the
 * last prevMat.
 * @param model
 * @return
 */
std::vector<glm::mat4> Tree::buildTree(const glm::mat4 &model) {
    std::cout << "in build tree" << std::endl;
    // Example binary tree output from l system, iteration = 2
    // F[-F[-X][+X]][+F[-X][+X]]
    std::string string;
//    string = "F[-X][+X]";
//    string = "F[-F[-X][+X]][+F[-X][+X]]";
//    string = "F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]";
//    string = "F[-F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]]";
    string = lsystem.getSequence();
    std::cout << lsystem.getSequence() << std::endl;

    glm::mat4 scale = glm::scale(glm::mat4(), SCALE_FACTOR);

    std::string term;
    glm::mat4 currMat = scale * model;
    std::vector<glm::mat4> mats = { currMat };
    std::vector<glm::mat4> prevMats = { };

    // parse the string
    float translateCoeff = 1.f;
    for (size_t i = 0 ; i < string.size() ; i++) {
        switch (string[i]) {
            case 'F':
            case 'X': {
                if (prevMats.size() != 0) {
                    currMat = glm::translate(glm::mat4(), glm::vec3(TRANSLATE.xy(), translateCoeff * TRANSLATE.z)) * currMat;
                }
                break;
            }
            case '-': {
                currMat = glm::rotate(Tree::ANGLE, ROTATE_AXIS) * currMat;
                translateCoeff = 1.f;
                break;
            }
            case '+': {
                currMat = glm::rotate(-Tree::ANGLE, ROTATE_AXIS) * currMat;
                translateCoeff = -1.f;
                break;
            }
            case '[': {
                prevMats.push_back(currMat);
                currMat = scale * currMat;
                break;
            }
            case ']': {
                mats.push_back(currMat);

                currMat = prevMats.back();

                prevMats.pop_back();
                break;
            }
        default:
            std::cout << "BAD LSYSTEM SYMBOL:  " << string[i] << std::endl;
            break;
        }
    }

    return mats;
}

/**
 * @brief Not used, just for reference.
 * @param model
 * @return
 */
std::vector<glm::mat4> buildTreeHardcode(const glm::mat4 &model) {

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

    glm::mat4 scale = glm::scale(original, glm::vec3(.5f, .8f, .5f));
    glm::mat4 rotate1 = glm::rotate(-glm::radians(65.f), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 rotate2 = glm::rotate(glm::radians(65.f), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 translate1 = glm::translate(glm::mat4(), glm::vec3(0.f, .2f, -.2f));
    glm::mat4 translate2 = glm::translate(glm::mat4(), glm::vec3(0.f, .2f, .2f));

    // Two child branches.
    child1 =  translate1 * rotate1 * scale * child1;
    child2 =  translate2 * rotate2  * scale * child2;

    original = initScale * original;
    trans.insert(trans.end(), {original, child1, child2});
    return trans;
}
