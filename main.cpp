/// @brief Centsible
/// @details A program that allows users to track their spending/investing habits.
/// @brief Created by Ethan Edwards on 11/19/2023.

// QT
//#include <QApplication>
//#include <QPushButton>

#include <string>
#include <iostream>
#include <fstream>

#include "mongoloid.h"

using namespace std;

// Globals
# define BANK_IN_PATH "mongo/db_output/banks.txt"
# define INVEST_IN_PATH "mongo/db_output/investments.txt"
# define BANK_OUT_PATH "mongo/db_input/banks.txt"
# define INVEST_OUT_PATH "mongo/db_input/investments.txt"

int main(int argc, char *argv[]) {
    // Get info from database
    mongoloid m;
    m.printBanks();
    m.printInvestments();
    return 0;
}
