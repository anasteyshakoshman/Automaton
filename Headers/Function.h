//
// Created by Анастасия on 23/12/2018.
//

#ifndef AUTOMATON_FUNCTION_H
#define AUTOMATON_FUNCTION_H

#pragma once
#include "../Headers/Include.h"

class NonDeterAutomaton;

class DeterAutomaton;

class FuncTransition;

class Transition;

bool isNum(const string);

bool correct0(string &, const int, set<state> &);

bool correct1(const string, int &);

bool correct2(string &, const int quan, set<Transition> &);

bool correct3(const string &);

bool fromFile(ifstream & file, NonDeterAutomaton &);

void toFile(ofstream & file, const DeterAutomaton &);

void toFile(ofstream & file, const FuncTransition &);

namespace std
{
    template<> class hash<set<int>>
    {
        public:

        size_t operator()(const set<int> & massiv) const
        {
            string tmp;
            for (const auto it : massiv) tmp += to_string(it);
            return hash<string>()(tmp);
        }
    };
};

#endif //AUTOMATON_FUNCTION_H
