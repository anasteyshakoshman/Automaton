//
// Created by Анастасия on 23/12/2018.
//

#ifndef AUTOMATON_DETERAUTOMATON_H
#define AUTOMATON_DETERAUTOMATON_H

#include "../Headers/Include.h"
#include "../Headers/Function.h"

class NonDeterAutomaton;
class Transition;
class FuncTransition;

//Детерминированный конечный автомат
class DeterAutomaton
{
    unordered_multimap<manyStates, FuncTransition> Data; //список функций перехода
    manyStates Begin;              //начальное состояние
    set<manyStates> Final;       //множество конечных состояний
    int Num;                      //количество состояний

    string InputWord;             //входное слово для эмуляции ДКА
    list<manyStates> OutputList;  //результат эмуляции в виде списка  состояний ДКА
    bool Accept;                  //переменная, отвечающая за то, является ли входное
                                  //слово допустимым для ДКА

public:

    DeterAutomaton();

    void determinization(const NonDeterAutomaton &);

    void uniqueWays(const manyStates &, const unordered_multimap<int, Transition> &, set<manyStates> &);

    void reductionFinal(const set<manyStates> &, const manyStates &);

    void emulation();

    void emulation(const string & input_word);

    ~DeterAutomaton();

    unordered_multimap<manyStates, FuncTransition> getData() const;

    manyStates getBegin() const;

    set<manyStates> getFinal() const;

    int getNum() const;

    bool getAccept() const;

    list<manyStates> getOutputList() const;
};



#endif //AUTOMATON_DETERAUTOMATON_H
