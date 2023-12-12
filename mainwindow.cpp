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

MainWindow::~MainWindow(){
    delete ui;
}

// DB interaction handlers
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

void MainWindow::updateBankGraphs(vector<pair<string, vector<bankRecord>>> bankRecords){
    // Update year graph
    QLineSeries *series = new QLineSeries();
    for (auto i : bankRecords){
        int total = 0;
        for (auto j : i.second){
            total += stoi(j.getBalance());
        }
        string month = i.first.substr(i.first.find('-') + 1, i.first.find('-'));
        series->append(QPoint(stoi(month), total));
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Balance over 1 year");
    // Embed the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->banking_year_graph->setChart(chart);
    ui->banking_year_graph->setRenderHint(QPainter::Antialiasing);
    ui->banking_year_graph->show();
    // Update total graph
    QLineSeries *seriestoo = new QLineSeries();
    for (auto i : bankRecords){
        int total = 0;
        for (auto j : i.second){
            total += stoi(j.getBalance());
        }
        // TODO: MODIFY THE WAY DATE IS STORED SO WE CAN SORT BY MONTH/YEAR
    }
}

void MainWindow::updateBank(){
    vector<vector<string>> bankInfo = m.getBankInfo();
    int total = 0;
    for (auto i : bankInfo){ // Add all bank balances
        total += stoi(i.at(3));
    }
    ui->banking_total_label->setText(QString::fromStdString("$" + to_string(total)));
    updateBankTable(bankInfo);
    updateBankGraphs(m.getBankRecords());
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

void MainWindow::updateInvestmentGraphs(vector<pair<string, vector<stockRecord>>> stockRecords){
}

void MainWindow::updateInvestment(){
    vector<vector<string>> investmentInfo = m.getInvestmentInfo();
    int total = 0;
    for (auto i : investmentInfo){ // Add all investment totals
        total += stoi(i.at(3));
    }
    ui->invest_total_label->setText(QString::fromStdString("$" + to_string(total)));
    updateInvestmentTable(investmentInfo);
}

// Element linkages
void MainWindow::closeEvent(QCloseEvent *event){ // Handle database update on close
    // m.sendToDB();
}