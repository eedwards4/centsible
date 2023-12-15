//
// Created by Ethan Edwards on 11/23/23.
//

#ifndef CENTSIBLE_MAINWINDOW_H
#define CENTSIBLE_MAINWINDOW_H

// STD
#include <vector>
#include <ctime>
#include <string>

// QT
#include <QMainWindow>
#include <QCloseEvent>
#include <QtCharts>
#include <QValueAxis>
#include <QGraphicsView>
#include <QWindow>

// APIS
#include "mongoloid.h"

// Sub windows
#include "BankAdd.h"
#include "BankDelete.h"
#include "InvestmentAdd.h"
#include "InvestmentDelete.h"

using namespace std;
using namespace Qt;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Update controllers
    void updateBank();
    void updateInvestment();

    // Element linkages
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;
    mongoloid m;

    // Main table update handlers
    void updateBankTable(vector<vector<string>> bankInfo);
    void updateInvestmentTable(vector<vector<string>> investmentInfo);
    // Graph update handlers
    void updateBankGraphs(vector<pair<dateTime, vector<bankRecord>>> bankRecords);
    void updateInvestmentGraphs(vector<pair<dateTime, vector<stockRecord>>> stockRecords);

private slots:
    void on_update_clicked();
    void on_bank_stats_clicked();
    void on_investment_stats_clicked();
    void on_bank_add_clicked();
    void on_investment_add_clicked();
    void on_bank_edit_clicked();
    void on_investment_edit_clicked();
    void on_bank_remove_clicked();
    void on_investment_remove_clicked();
    void addBank(string bankName, string acctNum, string acctName, string balance);
    void deleteBank(string toDel);
    void addInvestment(string ticker, string shares);
    void deleteInvestment(string toDel);

};

#endif //CENTSIBLE_MAINWINDOW_H

// Related stock tracker (side by side type shit)