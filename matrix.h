#ifndef MATRIX_H
#define MATRIX_H

#include <QDialog>
#include "gamelogic/Controller_structs.h"


namespace Ui {
class Matrix;
}

//using namespace cnst;


class Matrix : public QDialog {
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = nullptr);
    void SetPlayerName_Player_One(const QString&);
    void SetPlayerName_Player_Two(const QString&);

    void SetMatrix_Player_One(const CMugs &cm);
    void SetMatrix_Player_Two(const CMugs &cm);
    ~Matrix();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::Matrix *ui;

    void setupUi();
};

#endif // MATRIX_H
