/*****************************************************
 * Order.cpp
 * Implementation file Client interface with Dictionary ADT
 * Lucas Ellenberger
 * lmellenb
 * pa8
 ****************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>

#include "Dictionary.h"

using namespace std;

int main (int argc, char** argv) {
    // check command line for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " invalid number of arguments " << endl;
        return(EXIT_FAILURE);
    }

    std::ifstream infile;
    infile.open(argv[1]);
    std::ofstream outfile;
    outfile.open(argv[2]);
    // check that we can open both files
    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Usage: " << argv[0] << " unable to open files " << endl;
        return(EXIT_FAILURE);
    }

    std::string line = "";
    int i = 1;
    Dictionary * dict = new Dictionary();
    // Load in the lines as keys and line num as values to the dict
    while (getline(infile, line)) {
        dict->setValue(line, i);
        i++;
    }
    outfile << (*dict) << endl;
    outfile << dict->pre_string();

    delete dict;
    return EXIT_SUCCESS;
}
