#include "Tree.h"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "LSystem/LSystem.h"
#include "Settings.h"

Tree::Tree():
    m_lsystem()
{

    m_branchData.reserve(settings.recursions * 2); // TODO more optimal allocation
}

Tree::~Tree() {

}

/// arbitrarily chosen based on appearances
const float CYLINDER_RADIUS = .5f;
const glm::vec3 Tree::SCALE_FACTOR = glm::vec3(.5f, .8f, .5f);
const glm::vec3 Tree::TRANSLATE = glm::vec3(0, CYLINDER_RADIUS, 0);
const glm::vec3 Tree::ROTATE_AXIS = glm::vec3(1.f,0,0);

std::vector<glm::vec3> ROTATE_AXES = {
    glm::vec3(1.f,0,0),
    glm::vec3(0,1.f,0),
    glm::vec3(0,0,1.f),
    glm::vec3(.5f,0,.5f),
};
////

struct LState {
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
};

/**
 * @brief Parses an LSystem string and generates transformation matrices for primitives.
 * @param model: The initial model matrix.
 * @return A vector of transformation matrices to be applied to the same number of primitives.
 */
void Tree::buildTree(const glm::mat4 &model) {
    float ANGLE = glm::radians(settings.angle);
    m_lsystem.setRecursion(settings.recursions);
    m_lsystem.generateSequence();
    m_branchData.clear();
    std::string string = m_lsystem.getSequence();

    glm::vec4 origin = glm::vec4(0, 0, 0, 1.f);
    glm::mat4 identity = glm::mat4();
    glm::mat4 scale = glm::scale(identity, SCALE_FACTOR);
    glm::vec4 translate = glm::vec4(TRANSLATE, 1.f);

    LState currState = {
        glm::translate(identity, -1.f * translate.xyz()), // need to avoid overscaling
        identity,
        scale,
    };

    std::vector<LState> prevState = { };

    //Parse the string
    for (size_t i = 0 ; i < string.size() ; i++) {
        switch (string[i]) {
            case 'F':
            case 'X': {
                //For "Forward" symbols, translate a small distance in the current direction
                glm::mat4 transform = currState.translate * currState.rotate * currState.scale;
                //This is the translation out from the current branch
                glm::vec3 wscTranslate = (transform * translate - transform * origin).xyz();
                currState.translate = glm::translate(identity, wscTranslate) * currState.translate;
                //Ensure that transformation is in correct order (scale, rotate, translate)
                m_branchData.push_back(currState.translate * currState.rotate * currState.scale * model);
                break;
            }
            case '-': {
                //Rotate the current rotation matrix to the left
                glm::vec3 axis = ROTATE_AXES[2];
                currState.rotate = glm::rotate(-ANGLE, axis) * currState.rotate;
                break;
            }
            case '+': {
                //Rotate the current rotation matrix to the right
                glm::vec3 axis = ROTATE_AXES[2];
                currState.rotate = glm::rotate(ANGLE, axis) * currState.rotate;
                break;
            }
            case '[': {
                //Save the current state for later (splitting off into child branches)
                prevState.push_back(currState);
                //Scale down child branches
                currState.scale = scale * currState.scale;
                break;
            }
            case ']': {
                //Resume parsing with the last saved state (the current branch is closed)
                currState = prevState.back();
                prevState.pop_back();
                break;
            }
        default:
            std::cout << "BAD LSYSTEM SYMBOL:  " << string[i] << std::endl;
            break;
        }
    }
}

// Using setter and getters instead to avoid having to rebuild the tree
// when setting toggles don't change.
std::vector<glm::mat4> Tree::getBranchData() {
    return m_branchData;
}
