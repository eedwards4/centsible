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
    // change command depending on OS
    if constexpr(OS == "Windows"){command = "cd mongo && mongo_get_bank.py && mongo_get_investments.py";}
    else{command = "cd mongo && python3 mongo_get_bank.py && python3 mongo_get_investments.py";}
    if (int result = system(command.c_str()); result != 0){
        return 2;
    }
    ifstream bankFile(BANK_IN_PATH);
    ifstream investmentFile(INVEST_IN_PATH);
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
        bankRecordsOut << i.first << "\n";
        for (auto j : i.second){
            bankRecordsOut << j.getDate() << " ";
            bankRecordsOut << j.getName() << " ";
            bankRecordsOut << j.getBalance() << "\n";
        }
        bankRecordsOut << "END\n";
    }
    for (auto i : stockRecords){
        stockRecordsOut << i.first << "\n";
        for (auto j : i.second){
            stockRecordsOut << j.getDate() << " ";
            stockRecordsOut << j.getTicker() << " ";
            stockRecordsOut << j.getValue() << "\n";
        }
        stockRecordsOut << "END\n";
    }

    if constexpr(OS == "Windows"){command = "cd mongo && mongo_send_bank.py && mongo_send_investments.py";}
    else{command = "cd mongo && python3 mongo_send_bank.py && python3 mongo_send_investments.py";}
    int result = system(command.c_str());
    if (result != 0){
        return 2;
    }
    return 0;
}
