//
// Created by evane on 12/13/2023.
//

#include "BankAdd.h"
#include "ui_bankadd.h"

#include <string>

using namespace std;

BankAdd::BankAdd(QWidget* parent) : QDialog(parent), ui(new Ui::BankAdd){
    ui->setupUi(this);
    QObject::connect(ui->addButton, SIGNAL (clicked()), this, SLOT (on_add_clicked()));
    QObject::connect(ui->cancelButton, SIGNAL (clicked()), this, SLOT (on_cancel_clicked()));
}

BankAdd::~BankAdd(){
    delete ui;
}

void BankAdd::on_add_clicked(){
    string bankName = ui->bname_box->text().toStdString();
    string acctNum = ui->account_num_box->text().toStdString();
    string acctName = ui->account_name_box->text().toStdString();
    string balance = ui->balance_box->text().toStdString();
    if (bankName == "Bank name" || acctNum == "Account number" || acctName == "Account name" || balance == "Balance"){
        QMessageBox::warning(this, "Error", "Please fill out all fields");
    } else{
        emit addBank(bankName, acctNum, acctName, balance);
        this->close();
    }
}

void BankAdd::on_cancel_clicked(){
    this->close();
}
