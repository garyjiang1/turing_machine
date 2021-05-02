
#include "TM.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

istream& operator>>(istream &is, Table_entry& entry)
{
    string s;
    is >> s;
    
    //input the format as in state, char, and direction
    sscanf(s.c_str(), "(%d,%c,%c)", &entry.new_state, &entry.new_char, &entry.direction);
    
    entry.entryInString = s; //store the entry in a format of a string
    
    return is;
}

// output the contents of a Table_entry
ostream& operator<<(ostream &os, const Table_entry& entry)
{
    return os << entry.entryInString;
}

TM::TM(ifstream &ifs)
{
    Table_entry entry;
    string alpha;
    
    ifs >> num_states;
    ifs >> sigma;
    ifs >> gamma;
    blank = gamma[gamma.size() - 1];
    
    state_table.resize(num_states);
    for(int i = 0; i < num_states; i++)
    {
        state_table[i].resize(gamma.size());
        for(unsigned int j = 0; j < gamma.length(); j++)
        {
            ifs >> entry;
            state_table[i][j] = entry;
        }
    }
    
}

void TM::describe()
{
    cout << "Input alphabet sigma: " << sigma << endl;
    cout << "Tape alphabet gamma: " << gamma << endl;
    cout << "Blank = " << blank << endl;
    cout << "Number of states: " << num_states << endl;
    
    cout << "State Transition Table:" << endl << setw(15);
    
    for(unsigned long int i = 0; i < gamma.length(); i++)
        cout << gamma[i] << "           ";
    
    cout << endl;
    
    for(unsigned int i = 0; i < state_table.size(); i++)
    {
        cout << "State#" << i + 1;
        for(unsigned int j = 0; j < state_table[i].size(); j++)
        {
            cout << "   " << state_table[i][j] << "  ";
        }
        cout << endl;
    }
}

bool TM::trace(string& in_string)
{
    bool accepted = false;  //initalized to false
    bool happened = false;
    
    cout << "Tracing the string: " << in_string << endl;
    
    vector<char> input(in_string.begin(), in_string.end());
    unsigned long int length = input.size();
    int currentState = 1;
    unsigned int headPosition = 0;
    
    Table_entry transition;
    
    while(currentState != 0 && currentState != -1)
    {
        print_config(currentState, headPosition, input);
        
        char currentChar = input[headPosition];
        
        for(unsigned long int i = 0; i < gamma.length(); i++)
        {
            if(currentChar == gamma[i])
                transition = state_table[currentState - 1][i];
        }
        
        currentState = transition.new_state;
        input[headPosition] = transition.new_char;
        
        if(transition.direction == 'L') //left
            headPosition -= 1;
        else if(transition.direction == 'R') //right
            headPosition += 1;
        
        /* if nothing happened push back the value of blank to handle
         both cases of blanks in m2 and m3  */
        if(headPosition == length && !happened)
        {
            happened = true;
            input.push_back(blank);
        }
    }
    
    if(currentState == 0)
        accepted = true;
    
    return accepted;
}

void TM::print_config(int state, unsigned int pos, vector<char> input)
{
    for(unsigned long int i = 0; i < input.size(); i++)
    {
        if(i == pos)
            cout << "q" << state << " ";
        cout << input[i] << " ";
    }
    cout << endl;
}
