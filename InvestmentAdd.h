//
// Created by Ethan Edwards on 12/13/2023.
//

#ifndef INVESTMENTADD_H
#define INVESTMENTADD_H

#include <QtWidgets>

namespace  Ui {
    class InvestmentAdd;
}

class InvestmentAdd : public QDialog{
    Q_OBJECT

public:
    explicit InvestmentAdd(QWidget *parent = nullptr);
    ~InvestmentAdd();

private:
    Ui::InvestmentAdd *ui;

private slots:
    void on_add_clicked();
    void on_cancel_clicked();

};



#endif //INVESTMENTADD_H
