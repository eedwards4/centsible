//
// Created by evane on 12/12/2023.
//

#include "bankstats.h"
#include "bankstats.h"

#include <ui_mainwindow.h>
#include "./ui_bankstats.h"

BankStats::BankStats(QWidget *parent) : QMainWindow(parent), ui(new Ui::BankStats) {
    ui->setupUi(this);
}

BankStats::~BankStats() {
    delete ui;
}