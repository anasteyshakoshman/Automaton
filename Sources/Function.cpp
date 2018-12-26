//
// Created by Анастасия on 23/12/2018.
//

#include "../Headers/Function.h"
#include "../Headers/Transition.h"
#include "../Headers/Automaton.h"
#include "../Headers/DeterAutomaton.h"
#include "../Headers/FuncTransition.h"

bool isNum(const string line)
{
    if(line.empty()) return false;
    else
    {
        for(const auto it : line)
        {
            if(!isdigit(it)) return false;
        }
        return true;
    }
};

bool correct0(string & user, set<state> & res)
{
    //Не может сущ. автомат без начальных(конечных) состояний
    if(user.empty()) return false;
    else
    {
        while(user.size())
        {
            string tmp;
            auto it = user.find(";");
            if(it == string::npos) return false;
            tmp = user.substr(0, it);
            if(!isNum(tmp)) return false;
            res.insert(stoi(tmp));
            user.erase(0, ++it);
        }
        return true;
    }
};

bool correct1(const string user)
{
    if(!isNum(user) || !stoi(user)) return false;
    else return true;
};

bool correct2(string & user, set<Transition> & res)
{
    //Может сущ. автомат с 1 состоянием (одновременно начальным и конечным),
    //и такой автомат будет корректным. Поэтому проверку user.empty() делать не надо
    string tmp, tmp2;
    while(user.size())
    {
        auto it = user.find(";");
        tmp = user.substr(0,  it + 1);
        if(tmp.empty()) return false;
        Transition tr;
        for(int i = 0; i < 3; ++i)
        {
            auto it2 = tmp.find(",");
            if(i == 2) it2 = tmp.find(";");
            tmp2 = tmp.substr(0, it2);
            if(tmp2.empty()) return false;
            if(i == 1)
            {
                if(!isalpha(tmp2[0])) return false;
                tr.setLetter(tmp2[0]);
            }
            else
            {
                if(!isNum(tmp2)) return false;
                if(!i) tr.setOut(stoi(tmp2));
                else tr.setIn(stoi(tmp2));
            }
            tmp.erase(0, it2 + 1);
            if(i == 2  && tmp.size()) return false;
        }
        res.insert(tr);
        user.erase(0, it + 1);
    }
    return true;
};

bool correct3(const string & user)
{
    for(const auto it : user)
    {
        if(!isalpha(it)) return false;
    }
    return true;
};

bool fromFile(ifstream & file, NonDeterAutomaton & automat)
{
    string user;
    state quan = 0;
    bool result = false;
    set<state> begin, final;
    set<Transition> trans;
    file >> user;
    if(correct1(user))
    {
        file >> user;
        if(correct0(user, begin))
        {
            file >> user;
            if(correct0(user, final))
            {
                file >> user;
                if(correct2(user, trans))
                {
                    file >> user;
                    if(correct3(user))
                    {
                        automat.setInputWord(user);
                        automat.setBegin(begin);
                        automat.setFinal(final);
                        automat.setData(trans);
                        result = true;
                    }
                }
            }
        }
    }
    file.close();
    if(!result) cout << "Uncorrect file!!!";
    else automat.eraseExtra();
    return result;
};

template <typename T>
ofstream & operator <<(ofstream & file, const set<T> & massiv)
{
    int num = 0;
    for(const auto it : massiv)
    {
        if(num) file << ",";
        num++;
        file << it;
    }
    return file;
};

void toFile(ofstream & file, const FuncTransition & trans)
{
    file << "{";
    file << trans.getOut();
    file << "},";
    file << trans.getLetter() << ",";
    file << "{";
    file << trans.getIn();
    file << "};";
}

void toFile(ofstream & file, const DeterAutomaton & automat)
{
    file << automat.getNum() << endl;
    file << "{" ;
    file << automat.getBegin();
    file << "};" << endl;
    for(const auto it :  automat.getFinal())
    {
        file << "{";
        file << it;
        file << "};";
    }
    file << endl;
    for(const auto it :  automat.getData()) toFile(file, it.second);
    if( automat.getAccept())  file << endl << "accept ";
    else file << endl << "not accept ";
    for(const auto it :  automat.getOutputList())
    {
        file << "{";
        file << it;
        file << "};";
    }
    file.close();
};



