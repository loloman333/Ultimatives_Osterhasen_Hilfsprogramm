#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server.startServer();
    connect(&server, &Server::refreshPeople, this, &MainWindow::drawPeople);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawPeople(std::vector<Person> people) {
    ui->centralWidget->drawPeople(people);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox box;
    box.setText("<center>Author: Lorenz Killer <br>Date: 21.03.2019</center>");
    box.exec();
}
