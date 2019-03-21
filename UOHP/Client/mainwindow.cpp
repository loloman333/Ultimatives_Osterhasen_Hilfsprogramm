#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  

    if (! socket.doConnect()){
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Icon::Critical);
        msgBox.setText("Couldn't connect to Server!");

        msgBox.exec();
        failed = true;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QJsonObject person;
    person["name"] = ui->nameEdit->text();
    person["latitude"] = ui->latEdit->text().toDouble();
    person["longitude"] = ui->lonEdit->text().toDouble();

    ui->nameEdit->setText("");
    ui->latEdit->setText("");
    ui->lonEdit->setText("");

    socket.sendJson(std::ref(person));
}
