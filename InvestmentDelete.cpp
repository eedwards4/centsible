//
// Created by Ethan Edwards on 12/13/2023.
//

#include "InvestmentDelete.h"
#include "ui_investmentdelete.h"

#include <string>

using namespace std;

InvestmentDelete::InvestmentDelete(QWidget* parent) : QDialog(parent), ui(new Ui::InvestmentDelete){
    ui->setupUi(this);
    QObject::connect(ui->deleteButton, SIGNAL (clicked()), this, SLOT (on_delete_clicked()));
    QObject::connect(ui->cancelButton, SIGNAL (clicked()), this, SLOT (on_cancel_clicked()));
}

InvestmentDelete::~InvestmentDelete(){
    delete ui;
}

void InvestmentDelete::on_delete_clicked(){
    string ticker = ui->ticker_box->text().toStdString();
    if (ticker == "Ticker"){
        QMessageBox::warning(this, "Error", "Please fill out all fields");
    } else{
        emit deleteInvestment(ticker);
        this->close();
    }
}

void InvestmentDelete::on_cancel_clicked(){
    this->close();
}
