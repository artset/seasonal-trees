#include "Utilities.h"
#include <iostream>

#include "glm/ext.hpp"

namespace Utilities{



    void insertVec3(std::vector<float> &data, glm::vec3 v){
        data.push_back(v.x);
        data.push_back(v.y);
        data.push_back(v.z);
    }


    bool equals(float given, float val, float epsilon) {
        if (given <= val + epsilon &&
                given >= val - epsilon) {
            return true;
        } return false;
    }
}
