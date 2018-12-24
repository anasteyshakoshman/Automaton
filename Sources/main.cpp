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