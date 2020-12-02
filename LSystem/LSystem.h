#ifndef LSYSTEM_H
#define LSYSTEM_H
#include <string>
#include <map>
#include <vector>


class LSystem
{
public:
    LSystem();
    void generateSequence();
    std::string getSequence();
    void setRecursion(int recursion);

    void addRule(std::string key, std::string replacement);
    std::map<std::string, std::vector<std::string>> getRules();
    void clearRules();
    void setAxiom(std::string axiom);
private:
    void expand();
    int getReplacementIndex(int totalRules);
    int m_recursions;
    std::map<std::string, std::vector<std::string>> m_rules;
    std::string m_sequence;
};

#endif // LSYSTEM_H
