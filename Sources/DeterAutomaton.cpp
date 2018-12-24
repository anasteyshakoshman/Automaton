//
// Created by Анастасия on 23/12/2018.
//

#include "../Headers/DeterAutomaton.h"
#include "../Headers/Automaton.h"
#include "../Headers/Transition.h"
#include "../Headers/Transition.h"
#include "../Headers/FuncTransition.h"


DeterAutomaton::DeterAutomaton()
{
    Accept = false;
    Num = 0;
};

void DeterAutomaton::determinization(const NonDeterAutomaton & automat)
{
    InputWord = automat.getInputWord();
    Begin = automat.getBegin();
    set<manyStates> uniqueStates = {automat.getBegin()};
    uniqueWays(automat.getBegin(), automat.getData(), uniqueStates);
    reductionFinal(uniqueStates, automat.getFinal());
    emulation();
};


void DeterAutomaton::uniqueWays(const manyStates & key, const unordered_multimap<int, Transition> & data, set<manyStates> & uniq_stat)
{
    unordered_map<char, manyStates> tmp;
    for(const auto & it : key)
    {
        auto it2 =  data.equal_range(it);
        for(auto it3 = it2.first; it3 != it2.second; ++it3)
        {
            if(Begin.find(it3->second.getIn()) == Begin.end())
            {
                tmp[it3->second.getLetter()].insert(it3->second.getIn());
            }
            else
            {
                for(const auto it : Begin)
                    tmp[it3->second.getLetter()].insert(it);
            }
        }
    }
    for(auto & it : tmp)
    {
        Data.insert({key, FuncTransition(key, it.first, it.second)});
        if(uniq_stat.find(it.second) == uniq_stat.end())
        {
            uniq_stat.insert(it.second);
            uniqueWays(it.second, data, uniq_stat);
        }
    }
    ++Num;
};

void DeterAutomaton::reductionFinal(const set<manyStates> & uniq_stat, const manyStates & final)
{
    for(const auto & it : final)
    {
        for(const auto it2 : uniq_stat)
        {
            if(it2.find(it) != it2.end())
            {
                Final.insert(it2);
            }
        }
    }
};

void DeterAutomaton::emulation()
{
    if(InputWord.empty() && Final.find(Begin) != Final.end())
    {
        Accept = true;
        return;
    }
    bool find_letter = false;
    manyStates current = Begin;
    OutputList = {Begin};
    for(int i = 0; i < InputWord.size(); ++i)
    {
        auto it2 = Data.equal_range(current);
        for(auto it3 = it2.first; it3 != it2.second; ++it3)
        {
            if(it3->second.getLetter() == InputWord[i])
            {
                current = it3->second.getIn();
                find_letter = true;
                OutputList.push_back(current);
                if(i == InputWord.size() - 1 && Final.find(current) != Final.end())
                {
                    Accept = true;
                }
                break;
            }
        }
        if(!find_letter) return;
        else find_letter = false;
    }
};

void DeterAutomaton::emulation(const string & input_word)
{
    InputWord = input_word;
    Accept = false;
    emulation();
};

DeterAutomaton::~DeterAutomaton()
{
    Data.clear();
    for(auto it : Final) it.clear();
    Final.clear();
    InputWord.clear();
    for(auto & it : OutputList) it.clear();
    OutputList.clear();
    Num = 0;
};

unordered_multimap<manyStates, FuncTransition> DeterAutomaton::getData() const
{
    return Data;
};

manyStates DeterAutomaton::getBegin() const
{
    return Begin;
};

set<manyStates> DeterAutomaton::getFinal() const
{
    return Final;
};

int DeterAutomaton::getNum() const
{
    return Num;
};

bool DeterAutomaton::getAccept() const
{
    return Accept;
};

list<manyStates> DeterAutomaton::getOutputList() const
{
    return OutputList;
};
