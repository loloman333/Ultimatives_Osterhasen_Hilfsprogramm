#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    resetPic();
}

void DrawWidget::paintEvent(QPaintEvent *) {
    QPainter painter{this};
    painter.drawPixmap(0, 0, pic);
}

void DrawWidget::resetPic() {
    QPixmap map(":/res/res/Stadtplan.jpg");
    map = map.scaled(490, 600);

    QPixmap l_pic{490, 600};
    QPainter painter(&l_pic);

    painter.drawPixmap(0, 0, map);

    mapWidth = map.width();
    mapHeight = map.height();
    this->pic = l_pic;

    drawPeople(database.getPeople());
}

QPoint DrawWidget::personToPoint(Person person) {
    return QPoint(static_cast<int>((person.getLongitude() - leftLong) /
                                   (rightLong - leftLong) * mapWidth),
                      static_cast<int>((person.getLatitude() - topLat) /
                                       (bottomLat - topLat) * mapHeight));
}

void DrawWidget::drawPeople(std::vector<Person> people) {

    QPainter painter{&pic};
    painter.setPen(QPen{QColor{0, 0, 255}, 12});

    // Corners
    /*
    painter.drawPoint(0, 0);
    painter.drawPoint(490, 600);
    painter.drawPoint(0, 600);
    painter.drawPoint(490, 0);
    */

    for (unsigned int i{0}; i < people.size(); i++) {
        painter.drawPoint(personToPoint(people.at(i)));
    }

    update();
}
