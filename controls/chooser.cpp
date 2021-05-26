#include "chooser.h"

Chooser::Chooser(QWidget *parent) : QFrame(parent) {
    this->setGeometry(_startupPosition);
    this->setObjectName("chooser");
    setupUi();

    connect(this->pushButton_w1, &QPushButton::clicked, this, &Chooser::Receive_Selection_w1);
    connect(this->pushButton_w2, &QPushButton::clicked, this, &Chooser::Receive_Selection_w2);
    connect(this->pushButton_w3, &QPushButton::clicked, this, &Chooser::Receive_Selection_w3);

}


void Chooser::Receive_Selection_w1(){
    emit Send_HU_Move(1);
}


void Chooser::Receive_Selection_w2() {
    emit Send_HU_Move(2);
}


void Chooser::Receive_Selection_w3() {
    emit Send_HU_Move(3);
}


void Chooser::setupUi() {

    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Plain);

    label_bitte_wahlen = new QLabel(this);
    label_bitte_wahlen->setObjectName(QString::fromUtf8("label_bitte_wahlen"));
    label_bitte_wahlen->setGeometry(QRect(20, 0, 251, 41));
    QFont font2;
    font2.setPointSize(12);
    label_bitte_wahlen->setFont(font2);
    pushButton_w1 = new QPushButton(this);
    pushButton_w1->setObjectName(QString::fromUtf8("pushButton_w1"));
    pushButton_w1->setGeometry(QRect(20, 40, 60, 60));
    QFont font3;
    font3.setPointSize(24);
    pushButton_w1->setFont(font3);
    pushButton_w2 = new QPushButton(this);
    pushButton_w2->setObjectName(QString::fromUtf8("pushButton_w2"));
    pushButton_w2->setGeometry(QRect(100, 40, 60, 60));
    pushButton_w2->setFont(font3);
    pushButton_w3 = new QPushButton(this);
    pushButton_w3->setObjectName(QString::fromUtf8("pushButton_w3"));
    pushButton_w3->setGeometry(QRect(180, 40, 60, 60));
    pushButton_w3->setFont(font3);

    label_bitte_wahlen->setText("Bitte w\303\244hle eine Anzahl:");
    pushButton_w1->setText("1");
    pushButton_w2->setText("2");
    pushButton_w3->setText("3");
}
