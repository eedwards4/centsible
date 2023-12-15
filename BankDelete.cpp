//
// Created by Ethan Edwards on 12/13/2023.
//

#include "BankDelete.h"
#include "ui_bankdelete.h"

using namespace std;

BankDelete::BankDelete(QWidget* parent) : QDialog(parent), ui(new Ui::BankDelete){
    ui->setupUi(this);
    QObject::connect(ui->deleteButton, SIGNAL (clicked()), this, SLOT (on_delete_clicked()));
    QObject::connect(ui->cancelButton, SIGNAL (clicked()), this, SLOT (on_cancel_clicked()));
}

BankDelete::~BankDelete(){
    delete ui;
}

void BankDelete::on_delete_clicked(){
    string toDel = ui->account_number_box->text().toStdString();
    if (toDel == "Account number"){
        QMessageBox::warning(this, "Error", "Please fill out all fields");
    } else{
        emit deleteBank(toDel);
        this->close();
    }
}

void BankDelete::on_cancel_clicked(){
    this->close();
}
