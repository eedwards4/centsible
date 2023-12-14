//
// Created by Ethan Edwards on 12/13/2023.
//

#ifndef INVESTMENTDELETE_H
#define INVESTMENTDELETE_H

#include <QtWidgets>

namespace Ui{
    class InvestmentDelete;
}

class InvestmentDelete : public QDialog{
    Q_OBJECT

public:
    explicit InvestmentDelete(QWidget *parent = nullptr);
    ~InvestmentDelete();

private:
    Ui::InvestmentDelete *ui;

private slots:
    void on_delete_clicked();
    void on_cancel_clicked();

};



#endif //INVESTMENTDELETE_H
