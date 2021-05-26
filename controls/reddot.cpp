#include "reddot.h"

RedDot::RedDot(QWidget *parent): QWidget(parent) {
    this->setGeometry(QRect(0, 0, _diameter, _diameter));
    _col = GetRandomColor();
}


void RedDot::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QRect rect {(_shrinkBy / 2), (_shrinkBy / 2), (_diameter - _shrinkBy), (_diameter - _shrinkBy)};
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRadialGradient radialGradient(50, 50, 50, 30, 30);
    radialGradient.setColorAt(0.0, Qt::lightGray);
    if (event->rect().y() > 50 ){ _col = GetRandomColor(); }
    radialGradient.setColorAt(0.2, _col);
    radialGradient.setColorAt(1.0, QColor(20,10,10));
    painter.setBrush(radialGradient);

    QPen pen_red(Qt::red);
    pen_red.setWidth(2);
    painter.drawEllipse(rect);
}

Qt::GlobalColor RedDot::GetRandomColor() {
    static bool wasOnceCalled = false;
    if (!wasOnceCalled) {
        srand((unsigned int)time(NULL));
        wasOnceCalled = true;
    }
    int idx = (rand() % _colors.size());
    return _colors.at(idx);
    }
