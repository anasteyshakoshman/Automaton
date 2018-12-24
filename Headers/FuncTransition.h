//
// Created by Анастасия on 23/12/2018.
//

#ifndef AUTOMATON_FUNCTRANSITION_H
#define AUTOMATON_FUNCTRANSITION_H

#pragma once
#include "../Headers/Include.h"

class Transition;

//Функция перехода для детерминированного автомата
class FuncTransition
{
    set<state> Out;  //множество начальных состояний ФП
    char Letter;    //символ перехода
    set<state> In;   //множество конечных состояний ФП

public :

    FuncTransition(const manyStates, const char, const manyStates);

    FuncTransition(const Transition &);

    FuncTransition & operator =(const Transition &);

    manyStates getOut() const;

    char getLetter() const;

    manyStates getIn() const;

    ~FuncTransition();
};



#endif //AUTOMATON_FUNCTRANSITION_H
