//
// Created by Ethan Edwards on 11/23/23.
//

#ifndef CENTSIBLE_MAINWINDOW_H
#define CENTSIBLE_MAINWINDOW_H

#include <vector>

#include <QMainWindow>

using namespace std;

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

    void updateBankTable(vector<vector<string>> bankInfo);
    void updateInvestmentTable(vector<vector<string>> investmentInfo);
    void updateBank(vector<vector<string>> bankInfo);
    void updateInvestment(vector<vector<string>> investmentInfo);

private:
    Ui::MainWindow *ui;
};

#endif //CENTSIBLE_MAINWINDOW_H

// Related stock tracker (side by side type shit)