#include "Tree.h"
#include "glm/gtx/transform.hpp"

Tree::Tree()
{

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
    // Example binary tree output from l system, iteration = 2
    // F[-F[-X][+X]][+F[-X][+X]]
    std::string string;
//    string = "F[-X][+X]";
//    string = "F[-F[-X][+X]][+F[-X][+X]]";
//    string = "F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]";
    string = "F[-F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]]";

    glm::mat4 translate, rotate, scale;
    scale = glm::scale(glm::mat4(), SCALE_FACTOR);

    std::string term;
    std::vector<glm::mat4> mats = { };
    std::vector<glm::mat4> prevMats = { scale * model };

    // need to skip past first F in this strat, there might be a better way tho
    int start = string.find("[") + 1;
    int termStart = start;

    // parse the string
    for (size_t i = start ; i < string.size() ; i++) {
        if (string[i] == '[') {
            term = string.substr(termStart, i - termStart);

            if (term.compare("+F") == 0 || term.compare("F") == 0) {
                rotate = glm::rotate(Tree::ANGLE, ROTATE_AXIS);
                translate = glm::translate(glm::mat4(), TRANSLATE);
                prevMats.push_back(translate * rotate * scale * prevMats.back());
            } else if (term.compare("-F") == 0) {
                rotate = glm::rotate(-Tree::ANGLE, ROTATE_AXIS);
                translate = glm::translate(glm::mat4(), glm::vec3(TRANSLATE.xy(), TRANSLATE.z * -1.f));
                prevMats.push_back(translate * rotate * scale * prevMats.back());
            }

            termStart = i + 1;
        } else if (string[i] == ']') {
            term = string.substr(termStart, i - termStart);

            glm::mat4 mat;
            if (term.compare("+X") == 0 || term.compare("X") == 0) {
                rotate = glm::rotate(Tree::ANGLE, ROTATE_AXIS);
                translate = glm::translate(glm::mat4(), TRANSLATE);
                mat = translate * rotate * scale * prevMats.back();
            } else if (term.compare("-X") == 0) {
                rotate = glm::rotate(-Tree::ANGLE, ROTATE_AXIS);
                translate = glm::translate(glm::mat4(), glm::vec3(TRANSLATE.xy(), TRANSLATE.z * -1.f));
                mat = translate * rotate * scale * prevMats.back();
            } else {
                mat = prevMats.back();
                prevMats.pop_back();
            }

            mats.push_back(mat);
            termStart = i + 1;
        }
    }

    mats.push_back(prevMats.back());
    prevMats.pop_back();

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
