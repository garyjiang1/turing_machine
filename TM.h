#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;

// entry for a TM state table
struct Table_entry
{
    int new_state;  // 0 for accept, -1 for reject
    char new_char;
    char direction; // 'L' or 'R'
    string entryInString; 
};

// I/O for Table_entry
std::istream& operator>>(std::istream &is, Table_entry& entry);
std::ostream& operator<<(std::ostream &os, const Table_entry& entry);

// deterministic Turing machine
class TM {
public:
    // trace the TM on input in_string, returning true if it accepts
    // and false if it rejects
    TM(std::ifstream &ifs);
    TM() = delete;                      // disallow 0-param ctor
    void describe();
    bool trace(std::string& in_string);
private:
    string sigma;             // input alphabet
    string gamma;             // tape alphabet
    int num_states;                // number of states
    char blank;               // how we represent a blank
    std::vector<std::vector<Table_entry> > state_table; // transition table
    
    // helper function that nicely prints a single configuration
    static void print_config(int state, unsigned int pos,
                             vector<char> input);
};
