#include "board.h"

Board::Board(QWidget *parent) : QWidget(parent) {
    this->setGeometry(_startupPosition);
    this->setObjectName("boardinstance");

    this->_pExpand = new QParallelAnimationGroup(this);
    this->_pCollapse = new QParallelAnimationGroup(this);
    this->FillList();

    this->connect(this->_pExpand, &QAbstractAnimation::finished, this, &Board::ExpandFinished);
    this->connect(this->_pCollapse, &QAbstractAnimation::finished, this, &Board::CollapesFinished);
}


void Board::ExpandMe() {
   this->_pExpand->start();
}


void Board::CollapseMe() {
   this->_pCollapse->start();
}


void Board::ExpandFinished() {
    _isExpanded = true;
    this->_pExpand->stop();
    this->_pCollapse->stop();
    emit IsExpanded();
}


void Board::CollapesFinished() {
    _isExpanded = false;
    this->_pCollapse->stop();
    this->_pExpand->stop();
    emit IsCollapsed();
}


void Board::paintEvent(QPaintEvent * event) {
    QWidget::paintEvent(event);
}


void Board::FillList() {

    int xEndPos = 0;
    for(int i = 0; i <_count; i++) {
        BlackCircle* pBC = new BlackCircle(this);
        xEndPos = i * (pBC->Diameter()+ _spacing);

        pBC->setGeometry(0, pBC->pos().y() + _yOffset , pBC->width(), pBC->height());

        QPropertyAnimation *animationExp = new QPropertyAnimation(pBC, "pos");
        animationExp->setDuration(1500);
        animationExp->setStartValue(pBC->pos());
        animationExp->setEndValue(QPoint(xEndPos, pBC->pos().y()));

        animationExp->setEasingCurve(QEasingCurve::OutExpo);
        _pExpand->addAnimation(animationExp);

        QPropertyAnimation *animationCola = new QPropertyAnimation(pBC, "pos");
        animationCola->setDuration(500);
        animationCola->setStartValue(QPoint(xEndPos, pBC->pos().y()));
        animationCola->setEndValue(QPoint(0, pBC->pos().y()));

        animationCola->setEasingCurve(QEasingCurve::OutExpo);
        _pCollapse->addAnimation(animationCola);
    }

}



























