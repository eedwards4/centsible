/// @brief Centsible
/// @details A program that allows users to track their spending/investing habits.
/// @brief Created by Ethan Edwards on 11/19/2023.

// QT
//#include <QApplication>
//#include <QPushButton>

// Python (for database)


#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void getDBInfo(){
    cout << "Attempting to get DB info...\n";
    string command = "cd mongo && mongo_get_bank.py && mongo_get_investments.py";
    int result = system(command.c_str());
    if (result != 0){
        cout << "FAILED TO GET DATABASE INFORMATION. EXITING...\n";
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    /*
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize( 200, 100 );
    button.show();
    return QApplication::exec();*/
    getDBInfo();
    ifstream bankFile("mongo/db_output/banks.txt");
    ifstream investmentFile("mongo/db_output/investments.txt");
    string bankLine, investLine;
    if (bankFile.is_open() && investmentFile.is_open()){
        while (getline(bankFile, bankLine)){
            cout << bankLine << endl;
        }
        while (getline(investmentFile, investLine)){
            cout << investLine << endl;
        }
        bankFile.close(); investmentFile.close();
    } else{
        cout << "FAILED ACCESSING DATABASE FILES. EXITING...\n";
    }
    return 0;
}
