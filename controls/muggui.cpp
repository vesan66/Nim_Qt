#include "muggui.h"


MugGUI::MugGUI(QWidget *parent): QFrame(parent)
{
    setupUi();
}

void MugGUI::ClearMarks() {
    SetActiveLabel(pushButton_1 ,false);
    SetActiveLabel(pushButton_2 ,false);
    SetActiveLabel(pushButton_3 ,false);
}


void MugGUI::SetMyId(const int &value) {
     _myId = value;
     this->label->setText(QString().number(value));
}


void MugGUI::SetMark(const int &value) {
    switch (value) {

    case 1: {
        SetActiveLabel(pushButton_1, true);
        break;
    }
    case 2: {
        SetActiveLabel(pushButton_2, true);
        break;
    }
    case 3: {
        SetActiveLabel(pushButton_3, true);
        break;
    }
    default: break;
    }
}


void MugGUI::SetBtnVisible(const bool& visible, const int& value) {
    switch (value) {

    case 1: {
        pushButton_1->setVisible(visible);
        break;
    }
    case 2: {
        pushButton_2->setVisible(visible);
        break;
    }
    case 3: {
        pushButton_3->setVisible(visible);
        break;
    }
    default: {
        pushButton_1->setVisible(visible);
        pushButton_2->setVisible(visible);
        pushButton_3->setVisible(visible);
    }
    }
}


void MugGUI::setupUi() {
    this->setObjectName(QString::fromUtf8("frame_mug"));
    this->setGeometry(QRect(30, 30, 60, 60));
    this->setMinimumSize(QSize(60, 60));
    this->setMaximumSize(QSize(60, 60));
    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Plain);
    gridLayout_2 = new QGridLayout(this);
    gridLayout_2->setSpacing(2);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    gridLayout_2->setContentsMargins(2, 2, 2, 2);
    verticalLayout_TopBottom = new QVBoxLayout();
    verticalLayout_TopBottom->setObjectName(QString::fromUtf8("verticalLayout_TopBottom"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setPointSize(15);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    verticalLayout_TopBottom->addWidget(label);

    horizontalLayout_Buttons = new QHBoxLayout();
    horizontalLayout_Buttons->setSpacing(2);
    horizontalLayout_Buttons->setObjectName(QString::fromUtf8("horizontalLayout_Buttons"));
    pushButton_1 = new QPushButton(this);
    pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
    pushButton_1->setEnabled(true);
    pushButton_1->setMinimumSize(QSize(16, 26));
    pushButton_1->setMaximumSize(QSize(16, 26));
    QFont font1;
    font1.setPointSize(10);
    pushButton_1->setFont(font1);

    horizontalLayout_Buttons->addWidget(pushButton_1);

    pushButton_2 = new QPushButton(this);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setEnabled(true);
    pushButton_2->setMinimumSize(QSize(16, 26));
    pushButton_2->setMaximumSize(QSize(16, 26));
    pushButton_2->setFont(font1);

    horizontalLayout_Buttons->addWidget(pushButton_2);

    pushButton_3 = new QPushButton(this);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setEnabled(true);
    pushButton_3->setMinimumSize(QSize(16, 26));
    pushButton_3->setMaximumSize(QSize(16, 26));
    pushButton_3->setFont(font1);

    horizontalLayout_Buttons->addWidget(pushButton_3);


    verticalLayout_TopBottom->addLayout(horizontalLayout_Buttons);


    gridLayout_2->addLayout(verticalLayout_TopBottom, 0, 0, 1, 1);


    label->setText("2");
    pushButton_1->setText("1");
    pushButton_2->setText("2");
    pushButton_3->setText("3");

    //SetActiveLabel(pushButton_3, true);
    //pushButton_2->setVisible(false);
}


void MugGUI::SetActiveLabel(QPushButton* label, const bool& isActive) {
    QPalette palette{};

    if (label == nullptr) {return;}

    palette = label->palette();
    if (isActive) {
        palette.setColor(label->foregroundRole(), Qt::red);
    } else {
        palette.setColor(label->foregroundRole(), Qt::black);
    }
   label->setPalette(palette);
}


void MugGUI::SetActiveLabelBG(QPushButton* label, const bool& isActive) {
    QPalette palette{};

    if (label == nullptr) {return;}

    palette = label->palette();
    if (isActive) {
        palette.setColor(label->backgroundRole(), Qt::red);
    } else {
        palette.setColor(label->backgroundRole(), Qt::black);
    }
   label->setPalette(palette);
}


