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
    if (ticker == "Stock ticker"){
        QMessageBox::warning(this, "Error", "Please fill out all fields");
    } else{
        return;
    }
}

void InvestmentAdd::on_cancel_clicked(){
    this->close();
}