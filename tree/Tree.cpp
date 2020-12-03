#include "Tree.h"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "LSystem/LSystem.h"
#include "Settings.h"
#include "time.h"
#include <random>

const float Tree::BRANCH_LENGTH = 1.f;
const glm::vec3 Tree::SCALE_FACTOR = glm::vec3(.6f, .8f, .6f);
//const glm::vec3 Tree::INIT_SCALE_FACTOR = glm::vec3(.05f, .2f, .05f);
// the .6f below is totally arbitrary, I'm not sure why it works
const glm::vec3 Tree::TRANSLATE = glm::vec3(0, Tree::BRANCH_LENGTH * .5f, 0);
const std::vector<glm::vec3> Tree::ROTATE_AXES = {
    glm::vec3(1.f,0,0),
    glm::vec3(-1.f,0, 0),
    glm::vec3(0,0,1.f),
    glm::vec3(0,0,-1.f),
    glm::vec3(.5f,0,.5f),
};


/// These are all for testing, totally ignorable
std::vector<std::string> strings = {
    "F[-X][+X]",
    "F[-F[-X][+X]][+F[-X][+X]]",
    "F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]",
    "F[-F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]]",
    "F[-F[-F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]][+F[-F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]][+F[-F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]][+F[-F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]][+F[-F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]][+F[-F[-F[-X][+X]][+F[-X][+X]]][+F[-F[-X][+X]][+F[-X][+X]]]]]]]]]]",

    "F++F++F",
    "F-F++F-F++F-F++F-F++F-F++F-F",
    "F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F",
    "F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F",

    "FFFFFFFFFFFFFFFF[-FFFFFFFF[-FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFFFFFF[-FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFFFFFFFFFFFFFF[-FFFFFFFF[-FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFFFFFF[-FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FFFFFFFF[-FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFFFFFF[-FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]FFFF[-FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X]+FF[-F[-X]F[-X]+X]FF[-F[-X]F[-X]+X]+F[-X]F[-X]+X",
    "FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-[-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]+[+FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]-FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]+FF-[-F+F+F]+[+F-F-F]]+[+FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]-FF-[-F+F+F]+[+F-F-F]]]]",
//"FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]]",
//        "FFFF-FFFFF++F",
//        "F[-X]F",
//        "F",
//        "F[-X]",
//        "FF-[-F+F+F]+[+F-F-F]FF-[-F+F+F]+[+F-F-F]-[-FF-[-F+F+F]+[+F-F-F]]",
    "+-+-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-++-+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+-++-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-+--+-+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+--+-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-+--+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+-+--+-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-++-+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+-++-+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+--+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-+--+-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-++-+-A+B+A--+B-A-B+--A+B+A-++-+B-A-B++-A+B+A-++B-A-B+-++-A+B+A--+B-A-B+--A+B+A-+-++-+B-A-B++-A+B+A-++B-A-B+--+-A+B+A--+B-A-B+--A+B+A-+--+B-A-B++-A+B+A-++B-A-B+-+-+-+",
    "F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F-F-F++F-F-F-F++F-F++F-F++F-F-F-F++F-F",
}
;

Tree::Tree():
    m_lsystem()
{
    m_branchData.reserve(settings.recursions * 2);
}

Tree::~Tree() {

}

/**
 * @brief Parses an LSystem string and generates transformation matrices for primitives.
 * @param model: The initial model matrix.
 * @return
 */
void Tree::buildTree(const glm::mat4 &model) {
    addTreeOptionRule(settings.treeOption);
    float ANGLE = glm::radians(settings.angle);
    m_lsystem.setRecursion(settings.recursions);
    m_lsystem.generateSequence();
    m_branchData.clear();
    srand(time(NULL));

    std::string string = m_lsystem.getSequence();

    std::vector<char> forwardSymbols;
    forwardSymbols.reserve(m_lsystem.getRules().size());
    for (auto const& key_val : m_lsystem.getRules()) {
        forwardSymbols.push_back(key_val.first[0]);
    }

    const glm::vec3 INIT_SCALE_FACTOR = glm::vec3(0.05f, 0.2f, 0.05f);
    glm::vec4 origin = glm::vec4(0, 0, 0, 1.f);
    glm::mat4 identity = glm::mat4();
    glm::mat4 initScale = glm::scale(identity, INIT_SCALE_FACTOR);
    glm::mat4 scale = glm::scale(identity, SCALE_FACTOR);
    glm::vec4 translate = glm::vec4(TRANSLATE, 1.f);

    LState currState = {
        glm::translate(identity, -1.f * translate.xyz()), //Needed to avoid overtranslating
        identity,
        initScale,
        0,
        identity,
        initScale,
    };
    std::vector<LState> prevStates;

    //Calculates the overall transformation matrix of a branch given its current state
    auto getBranchTransform = [] (const glm::mat4 &model, const LState &state) {
        if (state.length == 0) {
            return glm::mat4(0);
        }
        glm::mat4 selfScale = glm::scale(glm::mat4(), { 1.f, BRANCH_LENGTH * state.length, 1.f });
        return state.translate * state.rotate * state.scale * (selfScale) * model;
    };

    //Produces an LState with all of the initial values of the given state
    //except for the length
    auto getBranchInitialStateTransforms = [] (const LState &state) {
        LState initState = state;
        initState.rotate = initState.initialRotate;
        initState.scale = initState.initialScale;
        return initState;
    };

    //Initializes the state of a child branching off from the given state
    auto createNewBranchState = [] (const LState &state) {
        LState newState = state;
        newState.initialRotate = newState.rotate;
        newState.initialScale = newState.scale;
        newState.length = 0;
        return newState;
    };

    //Determines if two matrices are equal within epsilon
    auto matEq = [] (const glm::mat4 &A, const glm::mat4 &B, float epsilon=1e-4) {
        int height = 4;
        for (int i = 0 ; i < height ; i++) {
            if (!glm::all(glm::epsilonEqual(A[i], B[i], epsilon))) {
                return false;
            }
        }
        return true;
    };


    // Returns some variance to the original angle by some random degree.
    // Potentially let the RANGE be decided by the UI?
    auto getRandomAngle = [] (const int &branchNum, const float &angle) {
        int RANGE = 5;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, RANGE);
        int newAngle = distribution(generator);
        if (branchNum % 2) {
            return angle - newAngle;
        }
        return angle + newAngle;
    };

    //Parse the string
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, ROTATE_AXES.size());
    int branchNum = distribution(generator);

    for (size_t i = 0 ; i < string.size() ; i++) {
        switch (string[i]) {
            case '-': {
                //Rotate the current rotation matrix to the left
                glm::vec3 axis = getRotateAxis(branchNum);
                currState.rotate = glm::rotate(-ANGLE, axis) * currState.rotate;
                if (currState.length == 0) {
                    //Need to update initial state for branch that hasn't been drawn yet
                    currState.initialRotate = currState.rotate;
                }
                break;
            }
            case '+': {
                //Rotate the current rotation matrix to the right
                glm::vec3 axis = getRotateAxis(branchNum);
                currState.rotate = glm::rotate(ANGLE, axis) * currState.rotate;
                if (currState.length == 0) {
                    //Need to update initial state for branch that hasn't been drawn yet
                    currState.initialRotate = currState.rotate;
                }
                break;
            }
            case '[': {
                //Save the current state for later (splitting off into child branches)
                prevStates.push_back(currState);
                currState.scale = scale * currState.scale; //Scale down child branches
                currState = createNewBranchState(currState); //Initialize child branch state
                break;
            }
            case ']': {
                //Resume parsing with the last saved state (the current branch is closed)
                m_branchData.push_back(getBranchTransform(model, currState));
                currState = prevStates.back();
                prevStates.pop_back();
                break;
            }
        default:
            if (std::find(forwardSymbols.begin(), forwardSymbols.end(), string[i]) != forwardSymbols.end()) {
                branchNum++;

                //For "Forward" symbols, translate a small distance in the current direction
                //Start a new line if the scale or rotation matrices are different from the initial branch transformation
                //Otherwise, continue the current line
                bool isNewBranch =
                        currState.length != 0 &&
                        !(matEq(currState.scale, currState.initialScale) && matEq(currState.rotate, currState.initialRotate));

                if (isNewBranch) {
                    LState branchInitState = getBranchInitialStateTransforms(currState);
                    m_branchData.push_back(getBranchTransform(model, branchInitState));
                    currState = createNewBranchState(currState);
                }

                glm::mat4 transform = currState.translate * currState.rotate * currState.scale;
                //This is the translation out from the current branch
                glm::vec3 wscTranslate = (transform * translate - transform * origin).xyz();
                currState.translate = glm::translate(identity, wscTranslate) * currState.translate;
                currState.length += BRANCH_LENGTH;
                break;
            } else {
                std::cout << "BAD LSYSTEM SYMBOL: " << string[i] << std::endl;
            }
            break;
        }

    }

    if (currState.length != 0) {
        m_branchData.push_back(getBranchTransform(model, currState));
    }
    if (prevStates.size() != 0) {
        std::cout << "Missed " << prevStates.size() << " cached states" << std::endl;
    }
}

/**
 * Adds the L-system rules and sets the axiom depending on the tree chosen in the dropdown of the ui.
 * @brief Tree::addTreeOptionRule
 * @param treeOption index of selected tree option in the ui combo box
 */
void Tree::addTreeOptionRule(int treeOption){
    m_lsystem.clearRules();
    switch (treeOption){
        //Binary tree
        case 0:
            m_lsystem.setAxiom("X");
            m_lsystem.addRule("F", "F");
            m_lsystem.addRule("X", "F[-X][+X]");
            m_is2D = true;
            break;
        //Arrow Weed
        case 1:
            m_lsystem.setAxiom("X");
            // Temporary visual patch as the FF creates this long string
            m_lsystem.addRule("F", "F");
            m_lsystem.addRule("F", "F[+X]");
            m_lsystem.addRule("F", "F[-X]");
            m_lsystem.addRule("X", "F[+X][-X]F");
            // Original Rules
//            m_lsystem.addRule("F", "FF");
//            m_lsystem.addRule("X", "F[+X][-X]FX");
            m_is2D = false;
            break;
        //Fuzzy Weed
        case 2:
            m_lsystem.setAxiom("X");
//            m_lsystem.addRule("F", "FF"); // Original rule
            m_lsystem.addRule("F", "F"); // Temp rule
            m_lsystem.addRule("X", "F-[[X]+X]+F[+FX]-X");
            m_is2D = false;
            break;
        //Wavy Seaweed
        case 3:
            m_lsystem.setAxiom("F");
            m_lsystem.addRule("F", "FF-[-F+F+F]+[+F-F-F]");
            m_is2D = false;
            break;
        //Twiggy weed
        case 4:
            m_lsystem.setAxiom("X");
//            m_lsystem.addRule("F", "FF"); // Original Rule
            // Temporary visual patch as the FF creates this long string
            m_lsystem.addRule("F", "F");
            m_lsystem.addRule("F", "F[X]");
            // End visual patch

            m_lsystem.addRule("X", "F[-X]F[-X]+X");
            m_is2D = false;
            break;
        //Stochastic Fuzzy Weed
        case 5:
            m_lsystem.setAxiom("X");
            m_lsystem.addRule("F", "FF"); // Original Rule

            // Temp Visual Patch
            m_lsystem.addRule("F", "F");
            m_lsystem.addRule("F", "F[+X]");
            m_lsystem.addRule("F", "F[-X]");
            // End Visual Patch

            m_lsystem.addRule("X", "F-[[X]+X]+F[+FX]-X");
            m_lsystem.addRule("X", "F+[[X]-X]-F[-FX]+X");
            m_is2D = false;

    }
}

// Using setter and getters instead to avoid having to rebuild the tree
// when setting toggles don't change.
std::vector<glm::mat4> Tree::getBranchData() {
    return m_branchData;
}

glm::vec3 Tree::getRotateAxis(int branchNum) {
    if (m_is2D) {
       return Tree::ROTATE_AXES[2];
    }
    return Tree::ROTATE_AXES[branchNum % (ROTATE_AXES.size() - 1)];
}


