#include "LSystem.h"
#include <iostream>
#include <random>

LSystem::LSystem():
    m_recursions(2),
    m_sequence("X")
{
    // Straight tree.
//    m_rules.insert(std::pair<std::string, std::vector<std::string>>("F",{"FF"}));
//    m_rules.insert(std::pair<std::string, std::vector<std::string>>("X",{"F[+X][-X]FX"}));

//    // Wavy tree
//    m_rules.insert(std::pair<std::string, std::vector<std::string>>("F",{"FF"}));
//    m_rules.insert(std::pair<std::string, std::vector<std::string>>("X",{"F-[[X]+X]+F[+FX]-X"}));

    // Other tree?
//    m_rules.insert(std::pair<std::string, std::vector<std::string>>("F",{"FF"}));
//    m_rules.insert(std::pair<std::string, std::vector<std::string>>("X",{"F[-X]F[-X]+X"}));


    // Sierpinski's Triangle
    m_rules.insert(std::pair<std::string, std::vector<std::string>>("F",{"+X-F-X+"}));
    m_rules.insert(std::pair<std::string, std::vector<std::string>>("X",{"-F+X+F-"}));

}

/**
 * Generates the string sequence based on the number of recursions.
 * @brief LSystem::generateSequence
 */
void LSystem::generateSequence(){
    m_sequence = "X";
    for (int i = 0; i < m_recursions; i++){
        expand();
    }
}

/**
 * Expands the string using the rules in the map.
 * @brief LSystem::expand
 */
void LSystem::expand(){
    std::string currCharacter = "";
    int sequenceLength = m_sequence.length();
    int currCharIndex = 0;
    while(currCharIndex < sequenceLength){
        currCharacter = m_sequence.at(currCharIndex);
        std::vector<std::string> replacements;
        if (m_rules.count(currCharacter)){
            replacements = m_rules.find(currCharacter)->second;
            int replacementIndex = getReplacementIndex(replacements.size() - 1);
            m_sequence.replace(currCharIndex, 1, replacements[replacementIndex]);
            sequenceLength += replacements[replacementIndex].length()-1;
            currCharIndex += replacements[replacementIndex].length();
        } else {
            currCharIndex += 1;
        }
    }
}

/**
 * Returns a uniformly distributed random number between 0 and the highest given index.
 * @brief LSystem::getRuleIndex
 * @param maxIndex last index in the vector for rule replacements
 * @return index
 */
int LSystem::getReplacementIndex(int maxIndex){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, maxIndex);
    return distrib(gen);
}

std::string LSystem::getSequence(){
    return m_sequence;
}

std::map<std::string, std::vector<std::string>> LSystem::getRules(){
    return m_rules;
}

/**
 * Adds rule to map of rules.
 * @brief LSystem::addRule
 * @param key key in the map
 * @param replacement value to add to vector in map
 */
void LSystem::addRule(std::string key, std::string replacement){
    if (key == "F"){
       std::map<std::string, std::vector<std::string>>::iterator it = m_rules.find("F");
       if (it != m_rules.end()){
           it->second.push_back(replacement);
       }
    } else if (key == "X"){
        std::map<std::string, std::vector<std::string>>::iterator it = m_rules.find("X");
        if (it != m_rules.end()){
            it->second.push_back(replacement);
        }
    }
}

/**
 * Sets the number of recursions.
 * @brief LSystem::setRecursion
 * @param recursions number of recursions
 */
void LSystem::setRecursion(int recursions){
    m_recursions = recursions;
}

/**
 * Clears the map of rules.
 * @brief LSystem::clearRules
 */
void LSystem::clearRules() {
    m_rules.clear();
}
