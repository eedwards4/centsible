//
// Created by Ethan Edwards on 11/23/23.
//

#ifndef CENTSIBLE_MAINWINDOW_H
#define CENTSIBLE_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui{};

};

#endif //CENTSIBLE_MAINWINDOW_H
