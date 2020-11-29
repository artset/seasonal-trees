#include "LSystem.h"
#include <iostream>
#include <random>

LSystem::LSystem():
    m_recursions(4),
    m_sequence("X")
{
    m_rules.insert(std::pair<std::string, std::vector<std::string>>("F", {"F", "F[+F]F[-F]F", "FF", "FF+[+F-F-F]-[-F+F+F]", "F[-F][+F]", "FX[FX[+XF]]", "FXF[-F[-FX]+FX]"}));
    m_rules.insert(std::pair<std::string, std::vector<std::string>>("X", {"F-[[X]+X]+F[+FX]-X", "F[+X]F[-X]+X", "X[-FFF][+FFF]FX", "-F[+F][--X]+F-F[+++X]-X", "F++F"}));

}

/**
 * Generates the string sequence based on the number of recursions.
 * @brief LSystem::generateSequence
 */
void LSystem::generateSequence(){
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