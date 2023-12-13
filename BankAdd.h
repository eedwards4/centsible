//
// Created by evane on 12/13/2023.
//

#ifndef BANKADD_H
#define BANKADD_H

#include <QtWidgets>

namespace Ui {
    class BankAdd;
}

class BankAdd : public QDialog{
    Q_OBJECT

public:
    explicit BankAdd(QWidget *parent = nullptr);
    ~BankAdd();

private:
    Ui::BankAdd *ui;

private slots:
    void on_cancel_clicked();
    void on_add_clicked();

};



#endif //BANKADD_H
