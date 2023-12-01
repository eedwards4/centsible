//
// Created by Ethan Edwards on 12/1/2023.
//

#ifndef MONGOLOID_H
#define MONGOLOID_H

# if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   define OS "Windows"
# elif __APPLE__
#   define OS "MacOS"
# endif

#include <string>

using namespace std;

class mongoloid {
public:
    int getinfo();
    int sendinfo();

private:
    string BANK_IN_PATH = "mongo/db_input/banks.txt";
    string INVEST_IN_PATH = "mongo/db_input/investments.txt";
    string BANK_OUT_PATH = "mongo/db_output/banks.txt";
    string INVEST_OUT_PATH = "mongo/db_output/investments.txt";

};



#endif //MONGOLOID_H
