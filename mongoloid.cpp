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
        return 1;
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
    } else{cout << "FAILED ACCESSING BANK DATABASE. EXITING!\n"; exit(-1);}
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
    } else{cout << "FAILED ACCESSING INVESTMENT DATABASE. EXITING!\n"; exit(-1);}
    return 0;
}

int mongoloid::sendToDB() {
    string command;
    // Change command depending on OS
    // TODO: Code to populate bank and investment files
    if constexpr(OS == "Windows"){command = "cd mongo && mongo_send_bank.py && mongo_send_investments.py";}
    else{command = "cd mongo && python3 mongo_send_bank.py && python3 mongo_send_investments.py";}
    int result = system(command.c_str());
    if (result != 0){
        return 1;
    }
    return 0;
}

void mongoloid::printBanks() const{
    cout << "Now printing bank info:\n";
    for (auto & i : bankInfo){
        for (auto & j : i){
            cout << j << endl;
        }
    }
}

void mongoloid::printInvestments() const{
    cout << "Now printing investment info:\n";
    for (auto & i : investmentInfo){
        for (auto & j : i){
            cout << j << endl;
        }
    }
}

