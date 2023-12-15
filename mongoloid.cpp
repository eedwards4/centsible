//
// Created by Ethan Edwards on 12/1/2023.
//

#include "mongoloid.h"

#include <fstream>
#include <iostream>

mongoloid::mongoloid(){
    getFromDB();
}


int mongoloid::getFromDB() {
    string command;
    bankInfo.clear();
    investmentInfo.clear();
    bankRecords.clear();
    stockRecords.clear();
    // change command depending on OS
    if constexpr(OS == "Windows"){command = "cd mongo && mongo_get_bank.py && mongo_get_investments.py";}
    else{command = "cd mongo && python3 mongo_get_bank.py && python3 mongo_get_investments.py";}
    if (int result = system(command.c_str()); result != 0){
        return 2;
    }
    ifstream bankFile(BANK_IN_PATH);
    ifstream investmentFile(INVEST_IN_PATH);
    ifstream bankRecordsFile(BANK_RECORDS_PATH);
    ifstream stockRecordsFile(STOCK_RECORDS_PATH);
    vector<string> tmp;
    if (bankFile.is_open()){
        string bankLine;
        while (getline(bankFile, bankLine)){
            if (bankLine == "END"){
                bankInfo.push_back(tmp);
                tmp.clear();
            } else{
                tmp.push_back(bankLine);
            }
        }
        bankFile.close();
    } else{cout << "FAILED ACCESSING BANK DATABASE. EXITING!\n"; return 1;}
    if (investmentFile.is_open()){
        string investLine;
        while (getline(investmentFile, investLine)){
            if (investLine == "END"){
                investmentInfo.push_back(tmp);
                tmp.clear();
            } else{
                tmp.push_back(investLine);
            }
        }
        investmentFile.close();
    } else{cout << "FAILED ACCESSING INVESTMENT DATABASE. EXITING!\n"; return 1;}
    if (bankRecordsFile.is_open()){
        string bankRecordsLine;
        while (getline(bankRecordsFile, bankRecordsLine)){
            string date, acctNum, balance;
            date = bankRecordsLine;
            getline(bankRecordsFile, bankRecordsLine);
            acctNum = bankRecordsLine;
            getline(bankRecordsFile, bankRecordsLine);
            balance = bankRecordsLine;
            getline(bankRecordsFile, bankRecordsLine);
            if (bankRecordsLine == "END"){
                dateTime tmpDate = convertToDateTime(date);
                bool found = false;
                for (auto & [fst, snd] : bankRecords){
                    if (fst == tmpDate){
                        snd.emplace_back(tmpDate, acctNum, balance);
                        found = true;
                    }
                }
                if (!found){
                    vector<bankRecord> tmp2;
                    tmp2.emplace_back(tmpDate, acctNum, balance);
                    bankRecords.emplace_back(tmpDate, tmp2);
                }
            }
        }
        bankRecordsFile.close();
    } else{cout << "FAILED ACCESSING BANK RECORDS DATABASE. EXITING!\n"; return 1;}
    if (stockRecordsFile.is_open()){
        string stockRecordsLine;
        while (getline(stockRecordsFile, stockRecordsLine)){
            string date, ticker, numShares, value;
            date = stockRecordsLine;
            getline(stockRecordsFile, stockRecordsLine);
            ticker = stockRecordsLine;
            getline(stockRecordsFile, stockRecordsLine);
            numShares = stockRecordsLine;
            getline(stockRecordsFile, stockRecordsLine);
            value = stockRecordsLine;
            getline(stockRecordsFile, stockRecordsLine);
            if (stockRecordsLine == "END"){
                dateTime tmpDate = convertToDateTime(date);
                bool found = false;
                for (auto & [fst, snd] : stockRecords){
                    if (fst == tmpDate){
                        snd.emplace_back(tmpDate, ticker, numShares, value);
                        found = true;
                    }
                }
                if (!found){
                    vector<stockRecord> tmp2;
                    tmp2.emplace_back(tmpDate, ticker, numShares, value);
                    stockRecords.emplace_back(tmpDate, tmp2);
                }
            }
        }
        stockRecordsFile.close();
    } else{cout << "FAILED ACCESSING STOCK RECORDS DATABASE. EXITING!\n"; return 1;}
    return 0;
}

int mongoloid::sendToDB() {
    string command;
    // Change command depending on OS
    ofstream bankOut(BANK_OUT_PATH);
    ofstream investmentOut(INVEST_OUT_PATH);
    ofstream bankRecordsOut(BANK_RECORDS_OUT_PATH);
    ofstream stockRecordsOut(STOCK_RECORDS_OUT_PATH);

    if (!bankOut.is_open() || !investmentOut.is_open() || !bankRecordsOut.is_open() || !stockRecordsOut.is_open()){
        return 1;
    }
    for (auto i : bankInfo){
        for (auto j : i){
            bankOut << j << "\n";
        }
        bankOut << "END\n";
    }
    for (auto i : investmentInfo){
        for (auto j : i){
            investmentOut << j << "\n";
        }
        investmentOut << "END\n";
    }
    for (auto i : bankRecords){
        for (auto j : i.second){
            bankRecordsOut << j.getDate().getAsDate() << "\n";
            bankRecordsOut << j.getAcctNum() << "\n";
            bankRecordsOut << j.getBalance() << "\n";
            bankRecordsOut << "END\n";
        }
    }
    for (auto i : stockRecords){
        for (auto j : i.second){
            stockRecordsOut << j.getDate().getAsDate() << "\n";
            stockRecordsOut << j.getTicker() << "\n";
            stockRecordsOut << j.getNumShares() << "\n";
            stockRecordsOut << j.getValue() << "\n";
            stockRecordsOut << "END\n";
        }
    }

    if constexpr(OS == "Windows"){command = "cd mongo && mongo_send_bank.py && mongo_send_investments.py && deletionHandler.py";}
    else{command = "cd mongo && python3 mongo_send_bank.py && python3 mongo_send_investments.py && python3 deletionHandler.py";}
    int result = system(command.c_str());
    if (result != 0){
        return 2;
    }
    return 0;
}

void mongoloid::addBank(string name, string acctNum, string acctName, string balance) {
    bankInfo.emplace_back(vector<string>{name, acctNum, acctName, balance});
}

void mongoloid::addInvestment(string ticker, string shares) {
    // TODO: USE SOME KIND OF API TO GET STOCK INFO
    investmentInfo.emplace_back(vector<string>{ticker, shares, "0", "0", "0"});
}

void mongoloid::addBankRecord(string date, string name, string balance) {
    bool found = false;
    dateTime tmpDate = convertToDateTime(date);
    for (auto & i : bankRecords){
        if (i.first == tmpDate){
            i.second.emplace_back(tmpDate, name, balance);
            found = true;
        }
    }
    if (!found){
        vector<bankRecord> tmp;
        tmp.emplace_back(tmpDate, name, balance);
        bankRecords.emplace_back(tmpDate, tmp);
    }
}

void mongoloid::addStockRecord(string date, string ticker, string value) {
    bool found = false;
    dateTime tmpDate = convertToDateTime(date);
    for (auto & i : stockRecords){
        if (i.first == tmpDate){
            i.second.emplace_back(tmpDate, ticker, "0", value);
            found = true;
        }
    }
    if (!found){
        vector<stockRecord> tmp;
        tmp.emplace_back(tmpDate, ticker, "0", value);
        stockRecords.emplace_back(tmpDate, tmp);
    }
}

void mongoloid::removeBank(string accountNum) {
    ofstream del(DELETIONS_PATH, ios::app);
    del << accountNum << "\n";
    del.close();
    for (int i = 0; i < bankInfo.size(); i++){
        if (bankInfo.at(i).at(1) == accountNum){
            bankInfo.erase(bankInfo.begin() + i);
            break;
        }
    }
}

void mongoloid::removeInvestment(string ticker) {
    ofstream del(DELETIONS_PATH, ios::app);
    del << ticker << "\n";
    del.close();
    for (int i = 0; i < investmentInfo.size(); i++){
        if (investmentInfo.at(i).at(0) == ticker){
            investmentInfo.erase(investmentInfo.begin() + i);
            break;
        }
    }
}

dateTime mongoloid::convertToDateTime(string date){
    string year = date.substr(0, date.find('-'));
    date.erase(0, date.find('-') + 1);
    string month = date.substr(0, date.find('-'));
    date.erase(0, date.find('-') + 1);
    string day = date.substr(0, date.find(' '));
    date.erase(0, date.find(' ') + 1);
    string time = date;
    return dateTime(stoi(year), stoi(month), stoi(day), time);
}
