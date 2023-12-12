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

class dateTime{ // A class to handle date/time data
public:
    dateTime(int year, int month, int day, string time){
        this->year = year; this->month = month; this->day = day;
        this->time = time;
    }
    int getYear(){return year;}
    int getMonth(){return month;}
    int getDay(){return day;}
    string getTime(){return time;}
    string getAsDate(){
        return to_string(year) + "-" + to_string(month) + "-" + to_string(day) + "T" + time;
    }

    // Overload ==
    bool operator==(dateTime const &other) const {
        return this->year == other.year && this->month == other.month && this->day == other.day && this->time == other.time;
    }

private:
    int year = 0, month = 0, day = 0;
    string time; // Might need to change the way this is stored in the future

};

class bankRecord{ // A class to handle bank record data
public:
    bankRecord(dateTime date, string acctNum, string balance){
        this->date = date;
        this->balance = balance;
        this->acctNum = acctNum;
    }
    dateTime getDate(){return date;}
    string getBalance(){return balance;}
    string getAcctNum(){return acctNum;}

private:
    dateTime date = dateTime(0, 0, 0, "");
    string acctNum, balance;

};

class stockRecord{ // A class to handle stock record data
public:
    stockRecord(dateTime date, string ticker, string numShares, string value){
        this->ticker = ticker; this->numShares = stoi(numShares); this->value = stoi(value); this->date = date;
    }
    dateTime getDate(){return date;}
    string getTicker(){return ticker;}
    [[nodiscard]] int getValue() const {return value;}
    [[nodiscard]] int getNumShares() const {return numShares;}

private:
    string ticker;
    dateTime date = dateTime(0, 0, 0, "");
    int numShares = 0, value = 0;

};

class mongoloid {
public:
    mongoloid();
    // Getters
    int getFromDB();
    vector<vector<string>> getBankInfo() const {return bankInfo;}
    vector<vector<string>> getInvestmentInfo() const {return investmentInfo;}
    vector<pair<dateTime, vector<bankRecord>>> getBankRecords() const {return bankRecords;}
    vector<pair<dateTime, vector<stockRecord>>> getStockRecords() const {return stockRecords;}
    // Setters
    int sendToDB();
    void addBank(string name, string acctNum, string acctName, string balance);
    void addInvestment(string ticker);
    void addBankRecord(string date, string name, string balance);
    void addStockRecord(string date, string ticker, string value);
    void removeBank(string accountNum);
    void removeInvestment(string ticker);

private:
    vector<vector<string>> bankInfo; // STRUCTURE: [[bank name, acct num, acct name, balance]]
    vector<vector<string>> investmentInfo; // STRUCTURE: [[ticker, last value, last total, 52 week high, 52 week low]]
    vector<pair<dateTime, vector<bankRecord>>> bankRecords; // STRUCTURE: [[date, bankRecords]]
    vector<pair<dateTime, vector<stockRecord>>> stockRecords; // STRUCTURE: [[date, stockRecords]]
    // Paths
    string BANK_OUT_PATH = "mongo/db_input/banks.txt";
    string BANK_IN_PATH = "mongo/db_output/banks.txt";
    string DELETIONS_PATH = "mongo/db_input/deletions.txt";
    string INVEST_IN_PATH = "mongo/db_output/investments.txt";
    string INVEST_OUT_PATH = "mongo/db_input/investments.txt";
    string BANK_RECORDS_PATH = "mongo/db_output/bank_records.txt";
    string STOCK_RECORDS_PATH = "mongo/db_output/investment_records.txt";
    string BANK_RECORDS_OUT_PATH = "mongo/db_input/bank_records.txt";
    string STOCK_RECORDS_OUT_PATH = "mongo/db_input/investment_records.txt";

    dateTime convertToDateTime(string date);

};



#endif //MONGOLOID_H
