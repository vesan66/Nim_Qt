#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include "gamelogic/global_const.h"


namespace Ui {
class Info;
}

using namespace cnst;


class Info : public QDialog {
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);
    ~Info();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::Info *ui;

    void SetTexts();
};

#endif // INFO_H
