//
// Created by Анастасия on 23/12/2018.
//

#include "../Headers/FuncTransition.h"
#include "../Headers/Transition.h"

FuncTransition::FuncTransition(const manyStates out, const char letter, const manyStates in)
{
    Out = out;
    In = in;
    Letter = letter;
};

FuncTransition::FuncTransition(const Transition & obj)
{
    Out = {obj.getOut()};
    Letter = obj.getLetter();
    In = {obj.getIn()};
};

FuncTransition & FuncTransition::operator =(const Transition & obj)
{
    Out = {obj.getOut()};
    Letter = obj.getLetter();
    In = {obj.getIn()};
    return *this;
};

char FuncTransition::getLetter() const
{
    return Letter;
};

manyStates FuncTransition::getOut() const
{
    return Out;
};

manyStates FuncTransition::getIn() const
{
    return In;
};

FuncTransition::~FuncTransition()
{
    Out.clear();
    In.clear();
};