//
// Created by Ethan Edwards on 12/13/2023.
//

#ifndef BANKDELETE_H
#define BANKDELETE_H

#include <QtWidgets>

namespace Ui {
    class BankDelete;
}

class BankDelete : public QDialog{
    Q_OBJECT

public:
    explicit BankDelete(QWidget *parent = nullptr);
    ~BankDelete();

private:
    Ui::BankDelete *ui;

private slots:
    void on_delete_clicked();
    void on_cancel_clicked();

};



#endif //BANKDELETE_H
