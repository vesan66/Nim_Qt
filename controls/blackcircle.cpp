#include "blackcircle.h"

BlackCircle::BlackCircle(QWidget *parent) : QWidget(parent) {
    this->setGeometry(QRect(0, 0, _diameter, _diameter));
}


void BlackCircle::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QRect rect {(_shrinkBy / 2), (_shrinkBy / 2), (_diameter - _shrinkBy), (_diameter - _shrinkBy)};
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen_darkGray(Qt::darkGray);
    pen_darkGray.setWidth(_penSize);
    painter.setPen(pen_darkGray);
    painter.drawEllipse(rect);
}
