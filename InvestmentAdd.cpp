//
// Created by Ethan Edwards on 12/13/2023.
//

#include "InvestmentAdd.h"
#include "ui_investmentadd.h"

#include <string>

using namespace std;

InvestmentAdd::InvestmentAdd(QWidget* parent) : QDialog(parent), ui(new Ui::InvestmentAdd){
    ui->setupUi(this);
    QObject::connect(ui->addButton, SIGNAL (clicked()), this, SLOT (on_add_clicked()));
    QObject::connect(ui->cancelButton, SIGNAL (clicked()), this, SLOT (on_cancel_clicked()));
}

InvestmentAdd::~InvestmentAdd(){
    delete ui;
}

void InvestmentAdd::on_add_clicked(){
    string ticker = ui->ticker_box->text().toStdString();
    string shares = ui->shares_box->text().toStdString();
    try{
       stoi(shares);
    } catch (exception& e){
        QMessageBox::warning(this, "Error", "Please enter a valid number of shares");
    }
    if (ticker == "Stock ticker" || shares == "Num. Shares"){
        QMessageBox::warning(this, "Error", "Please fill out all fields");
    } else{
        emit addInvestment(ticker, shares);
        this->close();
    }
}

void InvestmentAdd::on_cancel_clicked(){
    this->close();
}