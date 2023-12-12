//
// Created by Ethan Edwards on 11/23/23.
//

#ifndef CENTSIBLE_MAINWINDOW_H
#define CENTSIBLE_MAINWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QCloseEvent>
#include <QtCharts>
#include <QGraphicsView>

#include "mongoloid.h"

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
    void updateBankGraphs(vector<pair<string, vector<bankRecord>>> bankRecords);
    void updateInvestmentGraphs(vector<pair<string, vector<stockRecord>>> stockRecords);

};

#endif //CENTSIBLE_MAINWINDOW_H

// Related stock tracker (side by side type shit)