//
// Created by Ethan Edwards on 12/12/2023.
//

#ifndef BANKSTATS_H
#define BANKSTATS_H


#include <QWindow>
#include <QMainWindow>

#include "mongoloid.h"

using namespace std;
using namespace Qt;

QT_BEGIN_NAMESPACE
namespace Ui{
    class BankStats;
}
QT_END_NAMESPACE

class BankStats : public QMainWindow {
    Q_OBJECT

public:
    BankStats(QWidget *parent = nullptr);
    ~BankStats();

private:
    Ui::BankStats *ui;
    mongoloid *m;

};



#endif //BANKSTATS_H
