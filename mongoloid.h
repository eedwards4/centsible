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

class bankRecord{
public:
    bankRecord(string date, string name, string balance){
        this->date = date; this->name = name; this->balance = stoi(balance);
    }
    string getDate(){return date;}
    string getName(){return name;}
    [[nodiscard]] int getBalance() const {return balance;}

private:
    string date, name;
    int balance;

};

class stockRecord{
public:
    stockRecord(string date, string ticker, string value){
        this->date = date; this->ticker = ticker; this->value = stoi(value);
    }
    string getDate(){return date;}
    string getTicker(){return ticker;}
    [[nodiscard]] int getValue() const {return value;}

private:
    string date, ticker;
    int value;

};

class mongoloid {
public:
    mongoloid();
    // Getters
    int getFromDB();
    vector<vector<string>> getBankInfo() const {return bankInfo;}
    vector<vector<string>> getInvestmentInfo() const {return investmentInfo;}
    vector<pair<string, vector<bankRecord>>> getBankRecords() const {return bankRecords;}
    vector<pair<string, vector<stockRecord>>> getStockRecords() const {return stockRecords;}
    // Setters
    int sendToDB();
    void addBank(string name, string acctNum, string acctName, string balance);
    void addInvestment(string ticker);
    void addBankRecord(string date, string name, string balance);
    void addStockRecord(string date, string ticker, string value);

private:
    vector<vector<string>> bankInfo; // STRUCTURE: [[bank name, acct num, acct name, balance]]
    vector<vector<string>> investmentInfo; // STRUCTURE: [[ticker, last value, last total, 52 week high, 52 week low]]
    vector<pair<string, vector<bankRecord>>> bankRecords; // STRUCTURE: [[date, bankRecords]]
    vector<pair<string, vector<stockRecord>>> stockRecords; // STRUCTURE: [[date, stockRecords]]
    // Paths
    string BANK_IN_PATH = "mongo/db_output/banks.txt";
    string INVEST_IN_PATH = "mongo/db_output/investments.txt";
    string BANK_OUT_PATH = "mongo/db_input/banks.txt";
    string INVEST_OUT_PATH = "mongo/db_input/investments.txt";
    string BANK_RECORDS_PATH = "mongo/db_output/bank_records.txt";
    string STOCK_RECORDS_PATH = "mongo/db_output/stock_records.txt";
    string BANK_RECORDS_OUT_PATH = "mongo/db_input/bank_records.txt";
    string STOCK_RECORDS_OUT_PATH = "mongo/db_input/stock_records.txt";

};



#endif //MONGOLOID_H
