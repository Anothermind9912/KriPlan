#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "maintablemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTask_pushButton_clicked()
{
    model->insertRows(model->rowCount(),1);
}

