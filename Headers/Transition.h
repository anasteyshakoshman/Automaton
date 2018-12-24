//
// Created by Анастасия on 23/12/2018.
//

#ifndef AUTOMATON_TRANSITION_H
#define AUTOMATON_TRANSITION_H


#pragma once
#include "../Headers/Include.h"

//Функция перехода для недетерминированного автомата
class Transition
{
    state Out;   //начальное состояние ФП
    char Letter; //символ перехода
    state In;    //конечное состояние ФП

public :

    Transition();

    Transition(const state, const char, const state);

    Transition & operator =(const Transition &);

    Transition & setIn(const int);

    Transition & setOut(const int);

    Transition & setLetter(const char);

    state getOut() const;

    state getIn() const;

    char getLetter() const;

    void toFile(ofstream & file) const;

    bool operator ==(const Transition &) const;

    bool operator >(const Transition &) const;

    ~Transition();
};

bool operator <(const Transition &, const Transition &);


#endif //AUTOMATON_TRANSITION_H
