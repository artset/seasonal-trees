#include "Tree.h"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "LSystem/LSystem.h"
#include "Settings.h"
#include "time.h"
#include <random>

const float Tree::BRANCH_LENGTH = 1.f;
const glm::vec3 Tree::SCALE_FACTOR = glm::vec3(.6f, .8f, .6f);
// the .5f below is totally arbitrary, I'm not sure why it works
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
    m_branchData.body.reserve(settings.recursions * 2);
    m_branchData.tip.reserve(settings.recursions);
    m_leafData.reserve(settings.recursions * 2);
}

Tree::~Tree() {

}

/**
 * @brief Parses an LSystem string and generates transformation matrices for primitives.
 * @param model: The initial model matrix.
 * @return
 */
void Tree::buildTree(const glm::mat4 &model, const float leafScale) {
    m_leafScale = leafScale;
    addTreeOptionRule(settings.treeOption);
    float ANGLE = glm::radians(settings.angle);
    m_lsystem.setRecursion(settings.recursions);
    m_lsystem.generateSequence();
    m_branchData.body.clear();
    m_branchData.tip.clear();
    m_leafData.clear();
//    srand(time(NULL));

    std::string string = m_lsystem.getSequence();

//    string = "F[X][-F[-X]F[-X]+X]F[X][-F[-X]F[-X]+X]+F[-X]F[-X]+X";
//    string = "F[X][-F[-X]F[-X]+X]+F[-X]F[-X]+X";
//    string = "F[-F[-X]F[-X]+X]F[-F[-X]F[-X]+X]+F[-X]F[-X]+X";

//    std::cout << " ----- " << std::endl;
//    std::cout << string << std::endl;

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
    std::vector<LState> bodyStates; // These are the LStates for the branches that will be cylinders
                                    // Later, we add a cone cap to them.

    // Creates a random distribution on how the angles of the branches are generated.
    // Not necessary though for the randomnization, but leaving here for reference.
//    std::default_random_engine generator;
//    std::uniform_int_distribution<int> distribution(0, ROTATE_AXES.size());
//    int branchNum = distribution(generator);

    int branchNum = 0;

    // Parse the string
    for (size_t i = 0 ; i < string.size() ; i++) {
        switch (string[i]) {
            case '-': {
                //Rotate the current rotation matrix to the left
                glm::vec3 axis = getRotateAxis(branchNum);
                float newAngle = getRandomAngle(branchNum, ANGLE);
                currState.rotate = glm::rotate(-newAngle, axis) * currState.rotate;
                if (currState.length == 0) {
                    //Need to update initial state for branch that hasn't been drawn yet
                    currState.initialRotate = currState.rotate;
                }
                break;
            }
            case '+': {
                //Rotate the current rotation matrix to the right
                glm::vec3 axis = getRotateAxis(branchNum);
                float newAngle = getRandomAngle(branchNum, ANGLE);
                currState.rotate = glm::rotate(newAngle, axis) * currState.rotate;
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
                m_branchData.tip.push_back(getBranchTransform(model, currState)); // Pushes as a tip because it's the last of the branch.
                buildLeaves(model, currState, branchNum);
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

                    // When we are in the middle of a branch, we want to push it as a cylinder. Potentially questionable
                    // But it looks ok
                    std::string bracket = "]";
                    if (i < string.size() - 1 && string[i+1] != bracket[0]) {
                        bodyStates.push_back(branchInitState);
                    } else { // otherwise, we push as a tip.
                        m_branchData.tip.push_back(getBranchTransform(model, branchInitState));
                    }
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

    // Going through all the ones that are cylinders, and places a cone at the top
    for (size_t i = 0; i < bodyStates.size(); i++) {
        LState savedState = bodyStates[i];
        // Pushes cylinder to be rendered.
        m_branchData.body.push_back(getBranchTransform(model, savedState));

        // Trial and error for numbers
        glm::mat4 newScale = glm::scale(glm::mat4(), glm::vec3(1.f, .2f, 1.f));
        glm::mat4 newTrans = glm::translate(glm::mat4(), glm::vec3(0.f, Tree::BRANCH_LENGTH * .43f, 0.f));

        savedState.length += BRANCH_LENGTH;
        //This is the translation out from the current branch
        glm::mat4 t = getBranchTransform(model, savedState)  * newTrans * newScale;
        m_branchData.tip.push_back(t);
    }

    if (currState.length != 0) {
        m_branchData.tip.push_back(getBranchTransform(model, currState));
    }
    if (prevStates.size() != 0) {
        std::cout << "Missed " << prevStates.size() << " cached states" << std::endl;
    }
}


/**
 * Adds the leaf data to the member variable. If it's not a 2D array, will add
 * 3 leaves per branch.
 * @brief Tree::buildLeaves
 * @param model
 * @param state
 * @param branchLevel
 */
void Tree::buildLeaves(const glm::mat4 &model, const LState &state, const int branchLevel) {
    m_leafData.push_back(getLeafTransform(model, state, branchLevel, TOP));

    // In the 2D case (binary tree) we do not render all the leaves for the sake of space.
    if (!m_is2D) {
        m_leafData.push_back(getLeafTransform(model, state, branchLevel, LEFT));
        m_leafData.push_back(getLeafTransform(model, state, branchLevel, RIGHT));
    }
}

/**
 * Gets the transformation of the leaf, given the branch state.
 * @brief Tree::getLeafTransform
 * @param model
 * @param state
 * @param branchNum
 * @return
 */
glm::mat4 Tree::getLeafTransform(const glm::mat4 &model, const LState &state, const int branchLevel, LeafDir dir) {
    if (state.length == 0) {
        return glm::mat4(0);
    }

    // Positioning a leaf to be at the end of the branch.
    glm::mat4 INIT_ROTATE = glm::rotate(glm::radians(90.f), Tree::ROTATE_AXES[2]);
    glm::mat4 INIT_TRANSLATE = glm::translate(glm::mat4(), glm::vec3(0.f, 7.5f + 1.f * Tree::BRANCH_LENGTH, 0.f));
    glm::mat4 INIT_SCALE = glm::scale(glm::mat4(), glm::vec3(m_leafScale, .8, 1.f)); // Scales to size of branches.

    if (dir == LEFT) { // A leaf for the left side
        INIT_ROTATE = glm::rotate(glm::radians(50.f), getRotateAxis(branchLevel - 1));
        INIT_TRANSLATE = glm::translate(glm::mat4(), glm::vec3(1.f,  Tree::BRANCH_LENGTH, 0.f));
        INIT_SCALE = glm::scale(glm::mat4(), glm::vec3(m_leafScale, .8, 1.f)); // Scales to size of branches.
    } else if (dir == RIGHT) { // A leaf for right side
        INIT_ROTATE = glm::rotate(glm::radians(-50.f), getRotateAxis(branchLevel - 1));
        INIT_TRANSLATE = glm::translate(glm::mat4(), glm::vec3(-1.f,  Tree::BRANCH_LENGTH, 0.f));
        INIT_SCALE = glm::scale(glm::mat4(), glm::vec3(m_leafScale, .8, 1.f)); // Scales to size of branches.
    }
    glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(.01f, .01f, .01f));
    glm::mat4 rotate = state.rotate;
    glm::mat4 translate = state.translate;
    return translate * rotate * scale * INIT_TRANSLATE * INIT_ROTATE * INIT_SCALE * model;
}


//Calculates the overall transformation matrix of a branch given its current state
glm::mat4 Tree::getBranchTransform (const glm::mat4 &model, const LState &state) {
    if (state.length == 0) {
        return glm::mat4(0);
    }
    glm::mat4 selfScale = glm::scale(glm::mat4(), { 1.f, BRANCH_LENGTH * state.length, 1.f });
    return state.translate * state.rotate * state.scale * (selfScale) * model;
};

//Produces an LState with all of the initial values of the given state
//except for the length
LState Tree::getBranchInitialStateTransforms(const LState &state) {
    LState initState = state;
    initState.rotate = initState.initialRotate;
    initState.scale = initState.initialScale;
    return initState;
};


//Initializes the state of a child branching off from the given state
LState Tree::createNewBranchState(const LState &state) {
    LState newState = state;
    newState.initialRotate = newState.rotate;
    newState.initialScale = newState.scale;
    newState.length = 0;
    return newState;
};

// Returns a struct of all the branch data.
Branch Tree::getBranchData() {
    return m_branchData;
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

            // Temporary visual patch as the FF creates this long string
            m_lsystem.addRule("F", "F");
            m_lsystem.addRule("F", "F[X]");
            // End visual patch

            m_lsystem.addRule("X", "F[-X]F[-X]");
            m_lsystem.addRule("X", "F[-X]F[-X]+X");
            m_lsystem.addRule("X", "F[-X]F[-X]-X");

            m_is2D = false;
            m_is2D = false;
            break;

    }
}

// Returns a list of transformations for the leaves.
std::vector<glm::mat4> Tree::getLeafData() {
    return m_leafData;
}

// Returns the access to rotate the branch upon. In the 2 dimensional space
// it is always along the same axis.
glm::vec3 Tree::getRotateAxis(const int branchNum) {
    if (m_is2D) {
       return Tree::ROTATE_AXES[2];
    }
    return Tree::ROTATE_AXES[branchNum % (ROTATE_AXES.size() - 1)];
}

//Determines if two matrices are equal within epsilon
bool Tree::matEq(const glm::mat4 &A, const glm::mat4 &B) {
    float epsilon=1e-4;
    int height = 4;
    for (int i = 0 ; i < height ; i++) {
        if (!glm::all(glm::epsilonEqual(A[i], B[i], epsilon))) {
            return false;
        }
    }
    return true;
};

// Returns some variance to the original angle by some random degree.
// Potentially let the RANGE be decided by the UI. Not using rn.
float Tree::getRandomAngle(const int &branchNum, const float &angle) {
    int MAX_LEVEL = 10; // Value was determined by trial and error
    if (branchNum < MAX_LEVEL) { // Only creates a wider angle if we are deeper in tree.
        return angle;
    }
    int RANGE = 5;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, RANGE);
    int newAngle = glm::radians(distribution(generator) * 1.f);
    return angle + newAngle;
};

