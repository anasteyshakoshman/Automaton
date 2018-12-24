//
// Created by Анастасия on 23/12/2018.
//

#include "../Headers/Transition.h"

Transition::Transition()
{
    Out = NONE;
    In = NONE;
};

Transition::Transition(const state out, const char letter, const state in)
{
    Out = out;
    In = in;
    Letter = letter;
};

Transition & Transition::operator =(const Transition & obj)
{
    Out = obj.Out;
    Letter = obj.Letter;
    In = obj.In;
    return *this;
};

Transition & Transition::setIn(const int in)
{
    In = in;
    return *this;
};

Transition & Transition::setOut(const int out)
{
    Out = out;
    return *this;
};

Transition & Transition::setLetter(const char letter)
{
    Letter = letter;
    return *this;
};

state Transition::getOut() const
{
    return Out;
};

state Transition::getIn() const
{
    return In;
};

char Transition::getLetter() const
{
    return Letter;
};

bool Transition::operator ==(const Transition & obj) const
{
    return obj.In == In && obj.Out == Out && obj.Letter == Letter;
};

bool Transition::operator >(const Transition & obj) const
{
    if(Out == obj.Out) return In > obj.In;
    else return Out > obj.Out;
};

Transition::~Transition()
{
    Out = NONE;
    In = NONE;
};

bool operator <(const Transition & lhs, const Transition & rhs)
{

    if(lhs == rhs) return false;
    else return !(lhs > rhs);
};