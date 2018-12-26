#include "../Headers/Automaton.h"
#include "../Headers/Include.h"
#include "../Headers/Transition.h"
#include "../Headers/Function.h"
#include "../Headers/FuncTransition.h"
#include "../Headers/DeterAutomaton.h"

int main(int argc, char *argv[])
{
    ifstream outputFile(argv[1]);
    if(!outputFile.is_open()) return 0;

    NonDeterAutomaton NKA;
    if(!fromFile(outputFile, NKA)) return 1;

    DeterAutomaton DKA;
    DKA.determinization(NKA);

    ofstream inputFile(argv[2]);
    if(!inputFile.is_open()) return 2;

    toFile(inputFile, DKA);
    return 3;
}

// 8
// {0};
// {0,3};{2,3};{3};
// {1,2},a,{1};{1,2},c,{2};{1,2},b,{0,3};{3},b,{2};
//  {3},c,{0,2};{0},b,{3};{0},a,{1,2};{1},c,{2};
//  {1},b,{0,3};{2},b,{3};{2},a,{1};{0,3},c,{0,2};
//  {0,3},b,{2,3};{0,3},a,{1,2};{0,2},b,{3};{0,2},a,{1,2};
//  {2,3},c,{0,2};{2,3},b,{2,3};{2,3},a,{1};
// not accept {0};{1,2};{1};{2};{3};{0,2};