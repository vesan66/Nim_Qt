#ifndef DOTS_H
#define DOTS_H

#include <QList>
#include <QWidget>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "reddot.h"

class Dots : public QWidget
{
    Q_OBJECT
public:
    explicit Dots(QWidget *parent = nullptr);
    inline virtual ~Dots() override {};

    inline bool Visible() const { return _isVisible; }
    int VisibleDots();

signals:
    void IsVisible();
    void IsHidden();

public slots:
    void ShowMe();
    void HideMe();
    void SetAmountOfDotsVisible(const int&);
    void SHOWOinished();
    void HideFinished();

protected:
    virtual void paintEvent(QPaintEvent*) override;

private:
    int _count = 10;
    int _spacing = 10;

    int _isVisible = false;
    int _hidePosition = -100;
    int _yOffset = 140;
    QRect _startupPosition {QRect(30, 0, 700, 221)};

    int _rndHideAmount = 400;
    int _rndShowAmount = 200;
    int _rndHideAmountSingle = 500;

    QParallelAnimationGroup* _pHide{};
    QParallelAnimationGroup* _pShow{};

    void SetVisibleFlag(const bool&);
    void FillList();
    int GetFadeTime(const int& upperValue);

};

#endif // DOTS_H
