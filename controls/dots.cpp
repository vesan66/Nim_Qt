#include "dots.h"

Dots::Dots(QWidget *parent) : QWidget(parent) {
    this->setGeometry(_startupPosition);
    this->setObjectName("dotsinstance");
    this->_pHide = new QParallelAnimationGroup(this);
    this->_pShow = new QParallelAnimationGroup(this);

    this->FillList();

    this->connect(this->_pHide, &QAbstractAnimation::finished, this, &Dots::SHOWOinished);
    this->connect(this->_pShow, &QAbstractAnimation::finished, this, &Dots::HideFinished);

}


void Dots::ShowMe() {
    SetVisibleFlag(true);
    this->_pShow->start();
}


void Dots::HideMe() {
    if (VisibleDots() == _count ) {
        this->_pHide->start();
    } else {
        SetAmountOfDotsVisible(0);
        _isVisible = false;
    }
}


int Dots::VisibleDots() {
    int visibleCount = 0;
    for (int idx = (this->children().count() - 1); idx >= 0; --idx) {
        auto item = this->children().at(idx);
        if (typeid(*item) == typeid(RedDot)) {
            RedDot* const rd = dynamic_cast<RedDot* const>(item);
            if (!rd->IsHidden()) { visibleCount++;}
        }
    }
    return visibleCount;
}


void Dots::SetVisibleFlag(const bool& value) {
    for (int idx = (this->children().count() - 1); idx >= 0; --idx) {
        auto item = this->children().at(idx);
        if (typeid(*item) == typeid(RedDot)) {
            RedDot* const rd = dynamic_cast<RedDot* const>(item);
            rd->SetIsHidden(value);
        }
    }
}


void Dots::SetAmountOfDotsVisible(const int & desiredAmount)
{
    int visibleCount = VisibleDots();

    int toRemove = visibleCount - desiredAmount;
    if (toRemove > 0) {
        QParallelAnimationGroup* pElementsHide = new QParallelAnimationGroup(this);
        for (int idx = (this->children().count() - 1); idx >= 0; --idx) {
            auto item = this->children().at(idx);
            if (typeid(*item) == typeid(RedDot)) {
                RedDot* const rd = dynamic_cast<RedDot* const>(item);
                if (rd != nullptr) {
                     if (!rd->IsHidden()) {

                        QPropertyAnimation *animationHide = new QPropertyAnimation(rd, "pos");
                        int hideTime = 500 + GetFadeTime(_rndHideAmountSingle);
                        animationHide->setDuration(hideTime);
                        animationHide->setStartValue(rd->pos());
                        animationHide->setEndValue(QPoint(rd->pos().x(), _hidePosition));

                        animationHide->setEasingCurve(QEasingCurve::InCurve);
                        pElementsHide->addAnimation(animationHide);

                        rd->SetIsHidden(true);
                        toRemove--;
                    }
                    if (toRemove == 0) {
                        break;
                    }
                }
            }
        }
        pElementsHide->start();
        connect(pElementsHide, SIGNAL(finished()), pElementsHide, SLOT(deleteLater()));
    }
}


void Dots::SHOWOinished() {
    _isVisible = true;
    this->_pHide->stop();
    this->_pShow->stop();
    emit IsVisible();
}


void Dots::HideFinished() {
    _isVisible = false;
    this->_pHide->stop();
    this->_pShow->stop();
    SetVisibleFlag(false);      // !!!
    emit IsHidden();
}


void Dots::paintEvent(QPaintEvent * event) {
    QWidget::paintEvent(event);
}


void Dots::FillList() {

    int xEndPos = 0;
    for(int i = 0; i <_count; i++) {
        RedDot* pBC = new RedDot(this);
        xEndPos = i * (pBC->Diameter()+ _spacing);

        pBC->setGeometry(xEndPos, pBC->pos().y() + _yOffset , pBC->width(), pBC->height());

        QPropertyAnimation *animationHide = new QPropertyAnimation(pBC, "pos");
        int hideTime = 1500 + GetFadeTime(_rndHideAmount);
        animationHide->setDuration(hideTime);
        animationHide->setStartValue(pBC->pos());
        animationHide->setEndValue(QPoint(xEndPos, _hidePosition));

        animationHide->setEasingCurve(QEasingCurve::OutExpo);
        _pHide->addAnimation(animationHide);

        QPropertyAnimation *animationShow = new QPropertyAnimation(pBC, "pos");
        int showTime = 1250 + GetFadeTime(_rndShowAmount);
        animationShow->setDuration(showTime);
        animationShow->setStartValue(QPoint(xEndPos, _hidePosition));
        animationShow->setEndValue(pBC->pos());

        animationShow->setEasingCurve(QEasingCurve::OutBounce);
        _pShow->addAnimation(animationShow);

        pBC->setGeometry(xEndPos, _hidePosition, pBC->width(), pBC->height());
    }
    SetVisibleFlag(false);
    _isVisible = false;

}


int Dots::GetFadeTime(const int& upperValue) {
    static bool wasOnceCalled = false;
    if (!wasOnceCalled) {
        srand((unsigned int)time(NULL));
        wasOnceCalled = true;
    }
    return (rand() % upperValue);
}

























