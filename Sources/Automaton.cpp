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
    map<state, bool> try_states;
    for(const auto it : Begin)
    {
        wayToBegin(it, try_states);
    }
    unordered_multimap<state, Transition> data;
    for(const auto it : Data)
    {
        data.insert({it.second.getIn(), it.second});
    }
    for(const auto it : Final)
    {
        wayToFinal(it, try_states, data);
    }
    Num = try_states.size();
    list<unordered_multimap<state, Transition>::iterator> eraseAdress;
    bool add = false;
    for(auto it = Data.begin(); it != Data.end(); ++it)
    {
        auto it2 = try_states.find(it->first);
        if(it2 == try_states.end())
        {
            eraseAdress.push_back(it);
            add = true;
        }
        else if(it2->second == false)
        {
            eraseAdress.push_back(it);
            add = true;
        }

        it2 = try_states.find(it->second.getIn());
        if(it2 == try_states.end())
        {
            if(!add) eraseAdress.push_back(it);
        }
        else if(it2->second == false)
        {
            if(!add) eraseAdress.push_back(it);
        }
        add = false;
    }
    for(auto it : eraseAdress) Data.erase(it);
    eraseFromBeginFinal(try_states);
};

void NonDeterAutomaton::eraseFromBeginFinal(const map<state, bool> & try_states)
{
    list<set<state>::iterator> eraseAdress;
    for(auto it = Begin.begin(); it != Begin.end(); ++it)
    {
        auto it2 = try_states.find(*it);
        if(it2 == try_states.end())
        {
            eraseAdress.push_back(it);
        }
        else if(it2->second == false)
        {
            eraseAdress.push_back(it);
        }
    }
    for(auto it : eraseAdress) Begin.erase(it);
    eraseAdress.clear();
    for(auto it = Final.begin(); it != Final.end(); ++it)
    {
        auto it2 = try_states.find(*it);
        if(it2 == try_states.end())
        {
            eraseAdress.push_back(it);
        }
        else if(it2->second == false)
        {
            eraseAdress.push_back(it);
        }
    }
    for(auto it : eraseAdress) Final.erase(it);
};

void NonDeterAutomaton::wayToBegin(const state & key, map<state, bool> & try_states) const
{
    try_states.insert({key, false});
    auto it = Data.equal_range(key);
    for(auto it2 = it.first; it2 != it.second; ++it2)
    {
        if(try_states.find(it2->second.getIn()) != try_states.end()) return;
        else wayToBegin(it2->second.getIn(), try_states);
    }
};

void NonDeterAutomaton::wayToFinal(const state & key, map<state, bool> & try_states, const unordered_multimap<state, Transition> & data) const
{
    auto it = try_states.find(key);
    if(it == try_states.end()) return;
    else if(it->second == true) return;
    else
    {
        it->second = true;
        auto it2 = data.equal_range(key);
        for(auto it3 = it2.first; it3 != it2.second; ++it3)
        {
            wayToFinal(it3->second.getOut(), try_states, data);
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
