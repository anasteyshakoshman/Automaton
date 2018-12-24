//
// Created by Анастасия on 23/12/2018.
//

#include "../Headers/Automaton.h"
#include "../Headers/Transition.h"


NonDeterAutomaton::NonDeterAutomaton()
{
    Num = 0;
};

void NonDeterAutomaton::setData(set<Transition> & trans)
{
    for(const auto it : trans)
    {
        Data.insert({it.getOut(), it});
    }
};

void NonDeterAutomaton::setBegin(const set<state> & begin)
{
    Begin = begin;
};

void NonDeterAutomaton::setFinal(const set<state> & final)
{
    Final = final;
};

void NonDeterAutomaton::setNum(const int & num)
{
    Num = num;
};

void NonDeterAutomaton::setInputWord(const string & word)
{
    InputWord = word;
};

string NonDeterAutomaton::getInputWord() const
{
    return InputWord;
};

unordered_multimap<state, Transition> NonDeterAutomaton::getData() const
{
    return Data;
};

set<state> NonDeterAutomaton::getBegin() const
{
    return Begin;
};

set<state> NonDeterAutomaton::getFinal() const
{
    return Final;
};


void NonDeterAutomaton::eraseExtra()
{
    map<state, bool> waysStates;
    for(const auto it : Begin)
    {
        wayToBegin(it, waysStates);
    }
    unordered_multimap<state, Transition> data;
    for(const auto it : Data)
    {
        data.insert({it.second.getIn(), it.second});
    }
    for(const auto it : Final)
    {
        wayToFinal(it, waysStates, data);
    }

    list<unordered_multimap<state, Transition>::iterator> eraseAdress;
    bool add = false;
    for(auto it = Data.begin(); it != Data.end(); ++it)
    {
        auto it2 = waysStates.find(it->first);
        if(it2 == waysStates.end())
        {
            eraseAdress.push_back(it);
            add = true;
            eraseFromBeginFinal(it->first);
        }
        else if(it2->second == false)
        {
            eraseAdress.push_back(it);
            add = true;
            eraseFromBeginFinal(it->first);
        }

        it2 = waysStates.find(it->second.getIn());
        if(it2 == waysStates.end())
        {
            if(!add) eraseAdress.push_back(it);
            eraseFromBeginFinal(it->second.getIn());
        }
        else if(it2->second == false)
        {
            if(!add) eraseAdress.push_back(it);
            eraseFromBeginFinal(it->second.getIn());
        }
        add = false;
    }
    for(auto it : eraseAdress) Data.erase(it);
};

void NonDeterAutomaton::eraseFromBeginFinal(const state & key)
{
    auto it2 = Begin.find(key);
    if(it2 != Begin.end()) Begin.erase(it2);

    it2 = Final.find(key);
    if(it2 != Final.end()) Final.erase(it2);
};

void NonDeterAutomaton::wayToBegin(const state & key, map<state, bool> & waysStates) const
{
    waysStates.insert({key, false});
    auto it = Data.equal_range(key);
    for(auto it2 = it.first; it2 != it.second; ++it2)
    {
        if(waysStates.find(it2->second.getIn()) != waysStates.end()) return;
        else wayToBegin(it2->second.getIn(), waysStates);
    }
};

void NonDeterAutomaton::wayToFinal(const state & key, map<state, bool> & waysStates, const unordered_multimap<state, Transition> & data) const
{
    auto it = waysStates.find(key);
    if(it == waysStates.end()) return;
    else if(it->second == true) return;
    else
    {
        it->second = true;
        auto it2 = data.equal_range(key);
        for(auto it3 = it2.first; it3 != it2.second; ++it3)
        {
            wayToFinal(it3->second.getOut(), waysStates, data);
        }
    }
};

NonDeterAutomaton::~NonDeterAutomaton()
{
    Data.clear();
    Final.clear();
    Begin.clear();
    InputWord.clear();
};
