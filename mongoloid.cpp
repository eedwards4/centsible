//
// Created by Ethan Edwards on 12/1/2023.
//

#include "mongoloid.h"

int mongoloid::getinfo() {
    string command;
    // change command depending on OS
    if constexpr(OS == "Windows"){command = "cd mongo && mongo_get_bank.py && mongo_get_investments.py";}
    else{command = "cd mongo && python3 mongo_get_bank.py && python3 mongo_get_investments.py";}
    int result = system(command.c_str());
    if (result != 0){
        return 1;
    }
    return 0;
}

int mongoloid::sendinfo() {
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