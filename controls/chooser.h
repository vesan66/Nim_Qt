#ifndef CHOOSER_H
#define CHOOSER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

class Chooser : public QFrame
{
    Q_OBJECT
public:
    explicit Chooser(QWidget* parent = nullptr);
    inline virtual ~Chooser() override {};


signals:
    void Send_HU_Move(const int&);

private slots:
    void Receive_Selection_w1();
    void Receive_Selection_w2();
    void Receive_Selection_w3();

private:
    QLabel *label_bitte_wahlen;
    QPushButton *pushButton_w1;
    QPushButton *pushButton_w2;
    QPushButton *pushButton_w3;
    QRect _startupPosition {QRect(30, 230, 700, 115)};

    void setupUi();
};

#endif // CHOOSER_H
