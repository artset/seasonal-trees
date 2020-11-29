#ifndef LSYSTEM_H
#define LSYSTEM_H
#include <string>
#include <map>
#include <vector>


class LSystem
{
private:
    void expand();
    int getReplacementIndex(int totalRules);
    int m_recursions;
    std::map<std::string, std::vector<std::string>> m_rules;
    std::string m_sequence;
public:
    LSystem();
    void generateSequence();
    std::string getSequence();
};

#endif // LSYSTEM_H
