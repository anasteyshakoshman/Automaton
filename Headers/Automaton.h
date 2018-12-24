//
// Created by Анастасия on 23/12/2018.
//

#ifndef AUTOMATON_AUTOMATON_H
#define AUTOMATON_AUTOMATON_H

#pragma once
#include "../Headers/Include.h"

class Transition;

//Недетерминированный конечный автомат
class NonDeterAutomaton
{
    unordered_multimap<state, Transition> Data; //список функций перехода
    set<state> Begin;    //множество начальных состояний
    set<state> Final;    //множество конечных состояний
    int Num;              //количество состояний
    string InputWord;     //входное слово

public:

    NonDeterAutomaton();

    void setData(set<Transition> &);

    void setBegin(const set<state> &);

    void setFinal(const set<state> &);

    void setNum(const int &);

    void setInputWord(const string &);

    string getInputWord() const;

    unordered_multimap<state, Transition> getData() const;

    set<state> getBegin() const;

    set<state> getFinal() const;

    void eraseExtra();

    void eraseFromBeginFinal(const state & key);

    void wayToBegin(const state &, map<state, bool> &) const;

    void wayToFinal(const state &, map<state, bool> &, const unordered_multimap<state, Transition> &) const;

    ~NonDeterAutomaton();
};



#endif //AUTOMATON_AUTOMATON_H
