#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void drawPeople(std::vector<Person> people);

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    DBManager database = DBManager::getInstance();
    Server server;
};

#endif // MAINWINDOW_H
