#ifndef REDDOT_H
#define REDDOT_H

#include <QDebug>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QVector>

class RedDot : public QWidget
{
    Q_OBJECT
public:
    explicit RedDot(QWidget *parent = nullptr);
    inline virtual ~RedDot() override {};

    inline int Diameter() { return _diameter; }
    inline bool IsHidden() {return _isHidden;}
    inline void SetIsHidden(const bool& value) { _isHidden = value;}

signals:

protected:
    virtual void paintEvent(QPaintEvent*) override;

private:
    int _isHidden = false;
    int _diameter = 60;
    int _penSize = 4;
    int _shrinkBy = _penSize + 8 ;
    Qt::GlobalColor _col{Qt::GlobalColor::red};

    QVector<Qt::GlobalColor> _colors {
        Qt::GlobalColor::red,
        Qt::GlobalColor::green,
        Qt::GlobalColor::blue,
        Qt::GlobalColor::cyan,
        Qt::GlobalColor::magenta,
        Qt::GlobalColor::yellow,
        Qt::GlobalColor::darkRed,
        Qt::GlobalColor::darkGreen,
        Qt::GlobalColor::darkBlue,
        Qt::GlobalColor::darkCyan,
        Qt::GlobalColor::darkMagenta,
        Qt::GlobalColor::darkYellow };

    Qt::GlobalColor GetRandomColor();

};
#endif // REDDOT_H
