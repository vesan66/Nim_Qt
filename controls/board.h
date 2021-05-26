#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QWidget>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "blackcircle.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    inline virtual ~Board() override {};

    inline bool Expanded() const { return _isExpanded; }

signals:
    void IsExpanded();
    void IsCollapsed();

public slots:
    void ExpandMe();
    void CollapseMe();
    void ExpandFinished();
    void CollapesFinished();

protected:
    virtual void paintEvent(QPaintEvent*) override;

private:
    int _count = 10;
    int _spacing = 10;
    int _isExpanded = false;
    int _yOffset = 140;
    QRect _startupPosition {QRect(30, 0, 700, 221)};
    QParallelAnimationGroup* _pExpand{};
    QParallelAnimationGroup* _pCollapse{};

    void FillList();
};

#endif // BOARD_H
