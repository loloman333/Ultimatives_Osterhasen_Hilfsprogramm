#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QBrush>
#include "person.h"
#include "dbmanager.h"
#include <vector>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);

    void resetPic();
    void drawPeople(std::vector<Person> people);
    QPoint personToPoint(Person person);
private:
    QPixmap pic;
    DBManager database = DBManager::getInstance();

    double leftLong{16.209652};
    double rightLong{16.281017};
    double topLat{47.846533};
    double bottomLat{47.786898};

    double mapWidth;
    double mapHeight;
};

#endif // DRAWWIDGET_H
