#ifndef BLACKCIRCLE_H
#define BLACKCIRCLE_H

#include <QDebug>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>

class BlackCircle : public QWidget
{
    Q_OBJECT
public:
    explicit BlackCircle(QWidget *parent = nullptr);    
    inline virtual ~BlackCircle() override {};

    inline int Diameter() { return _diameter; }

signals:

protected:
    virtual void paintEvent(QPaintEvent*) override;

private:
    int _diameter = 60;
    int _penSize = 4;
    int _shrinkBy = _penSize + 8;
};

#endif // BLACKCIRCLE_H
