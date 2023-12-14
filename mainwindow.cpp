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

    QObject::connect(ui->update_banking, SIGNAL (clicked()), this, SLOT (on_update_clicked()));
    QObject::connect(ui->update_investment, SIGNAL (clicked()), this, SLOT (on_update_clicked()));
    QObject::connect(ui->addBank, SIGNAL (clicked()), this, SLOT (on_bank_add_clicked()));
    QObject::connect(ui->editBank, SIGNAL (clicked()), this, SLOT (on_bank_edit_clicked()));
    QObject::connect(ui->removeBank, SIGNAL (clicked()), this, SLOT (on_bank_remove_clicked()));
    QObject::connect(ui->addInvest, SIGNAL (clicked()), this, SLOT (on_investment_add_clicked()));
    QObject::connect(ui->editInvest, SIGNAL (clicked()), this, SLOT (on_investment_edit_clicked()));
    QObject::connect(ui->removeInvest, SIGNAL (clicked()), this, SLOT (on_investment_remove_clicked()));
    QObject::connect(ui->bankStats, SIGNAL (clicked()), this, SLOT (on_bank_stats_clicked()));
    QObject::connect(ui->investStats, SIGNAL (clicked()), this, SLOT (on_investment_stats_clicked()));
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

void MainWindow::updateBankGraphs(vector<pair<dateTime, vector<bankRecord>>> bankRecords){
    // TODO: REFACTOR TO USE A DATE/NUMBER GRAPH
    time_t t = time(nullptr);
    tm *const pTInfo = localtime(&t);
    int year = 1900 + pTInfo->tm_year;
    // int month = 1 + pTInfo->tm_mon;
    // Update year graph
    QLineSeries *series = new QLineSeries();
    for (auto i : bankRecords){
        if (i.first.getYear() == year){ // Only add records from this year
            int total = 0;
            for (auto j : i.second){
                total += stoi(j.getBalance());
            }
            QDateTime date;
            date.setDate(QDate(i.first.getYear(), i.first.getMonth(), i.first.getDay()));
            series->append(QPoint(i.first.getMonth(), total));
        }
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    auto axisx = new QDateTimeAxis;
    axisx->setTickCount(12);
    axisx->setFormat("MMM");
    chart->addAxis(axisx, Qt::AlignBottom);
    series->attachAxis(axisx);
    auto axisy = new QValueAxis;
    axisy->setLabelFormat("%i");
    chart->addAxis(axisy, Qt::AlignLeft);
    series->attachAxis(axisy);
    chart->setTitle("Balance over 1 year");
    // Embed the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->banking_year_graph->setChart(chart);
    ui->banking_year_graph->setRenderHint(QPainter::Antialiasing);
    ui->banking_year_graph->show();
    // Update total graph
    QLineSeries *seriestoo = new QLineSeries();
    int tmpYear = 0;
    for (auto i : bankRecords){
        // TODO: FIX THIS
        // Currently gets total for WHOLE YEAR
        // Need to get total for each month, but make sure that months of different years aren't grouped together
        if (i.first.getYear() != tmpYear){
            tmpYear = i.first.getYear();
        } else{
            int total = 0;
            for (auto j : i.second){
                total += stoi(j.getBalance());
            }
            seriestoo->append(QPoint(tmpYear, total));
        }
    }
    QChart *charttoo = new QChart();
    charttoo->legend()->hide();
    charttoo->addSeries(seriestoo);
    charttoo->createDefaultAxes();
    charttoo->setTitle("Balance over all time");
    // Embed the chart
    QChartView *chartViewtoo = new QChartView(charttoo);
    chartViewtoo->setRenderHint(QPainter::Antialiasing);
    ui->banking_total_graph->setChart(charttoo);
    ui->banking_total_graph->setRenderHint(QPainter::Antialiasing);
    ui->banking_total_graph->show();
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

void MainWindow::updateInvestmentGraphs(vector<pair<dateTime, vector<stockRecord>>> stockRecords){
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

void MainWindow::on_update_clicked(){
    m.getFromDB();
    updateBank();
    updateInvestment();
}

void MainWindow::on_bank_stats_clicked(){
    return;
}

void MainWindow::on_investment_stats_clicked(){
    return;
}

void MainWindow::on_bank_add_clicked(){
    BankAdd *b = new BankAdd();
    b->show();
}

void MainWindow::on_investment_add_clicked(){
    InvestmentAdd *i = new InvestmentAdd();
    i->show();
}

void MainWindow::on_bank_edit_clicked(){
    return;
}

void MainWindow::on_investment_edit_clicked(){
    return;
}

void MainWindow::on_bank_remove_clicked(){
    BankDelete *b = new BankDelete();
    b->show();
}

void MainWindow::on_investment_remove_clicked(){
    InvestmentDelete *i = new InvestmentDelete();
    i->show();
}

