//
// Created by Ethan Edwards on 11/23/23.
//
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBankTable(vector<vector<string>> bankInfo){
    ui->accountTable->clear();
    ui->accountTable->setRowCount(bankInfo.size());
    ui->accountTable->setColumnCount(4);
    ui->accountTable->setHorizontalHeaderLabels(QStringList() << "Bank" << "Account Number" << "Account Name" << "Balance");
    for (int i = 0; i < bankInfo.size(); i++){
        for (int j = 0; j < bankInfo.at(i).size(); j++){
            ui->accountTable->setItem(i, j, new QTableWidgetItem(QString::fromStdString(bankInfo.at(i).at(j))));
        }
    }
    QHeaderView* header = ui->accountTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateBank(vector<vector<string>> bankInfo){
    int total = 0;
    for (auto i : bankInfo){ // Add all bank balances
        total += stoi(i.at(3));
    }
    ui->banking_total_label->setText(QString::fromStdString("$" + to_string(total)));
    updateBankTable(bankInfo);
}

void MainWindow::updateInvestmentTable(vector<vector<string>> investmentInfo){
    ui->investmentTable->clear();
    ui->investmentTable->setRowCount(investmentInfo.size());
    ui->investmentTable->setColumnCount(5);
    ui->investmentTable->setHorizontalHeaderLabels(QStringList() << "Ticker" << "Last Value" << "Last Total" << "52 Week High" << "52 Week Low");
    for (int i = 0; i < investmentInfo.size(); i++){
        for (int j = 0; j < investmentInfo.at(i).size(); j++){
            ui->investmentTable->setItem(i, j, new QTableWidgetItem(QString::fromStdString(investmentInfo.at(i).at(j))));
        }
    }
    QHeaderView* header = ui->investmentTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateInvestment(vector<vector<string>> investmentInfo){
    int total = 0;
    for (auto i : investmentInfo){ // Add all investment totals
        total += stoi(i.at(3));
    }
    ui->invest_total_label->setText(QString::fromStdString("$" + to_string(total)));
    updateInvestmentTable(investmentInfo);
}