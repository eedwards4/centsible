// mongoDB? More like bongoDB
// Created by Ethan Edwards on 12/1/2023.
// Essentially just a wrapper for mongoDB

#ifndef MONGOLOID_H
#define MONGOLOID_H

# if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   define OS "Windows"
# elif __APPLE__
#   define OS "MacOS"
# endif

#include <string>
#include <vector>

using namespace std;

class mongoloid {
public:
    mongoloid();
    int getFromDB();
    int sendToDB();
    void printBanks() const;
    void printInvestments() const;

private:
    vector<vector<string>> bankInfo; // STRUCTURE: [[bank name, acct num, acct name, balance]]
    vector<vector<string>> investmentInfo; // STRUCTURE: [[ticker, last value, last total, 52 week high, 52 week low]]
    string BANK_IN_PATH = "mongo/db_output/banks.txt";
    string INVEST_IN_PATH = "mongo/db_output/investments.txt";
    string BANK_OUT_PATH = "mongo/db_input/banks.txt";
    string INVEST_OUT_PATH = "mongo/db_input/investments.txt";

};



#endif //MONGOLOID_H
