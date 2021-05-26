#include "matrix.h"
#include "ui_matrix.h"

Matrix::Matrix(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix) {
    ui->setupUi(this);
    this->setupUi();
}


void Matrix::SetPlayerName_Player_One(const QString & name) {
    ui->label_name_p1->setText(name);
}


void Matrix::SetPlayerName_Player_Two(const QString & name) {
    ui->label_name_p2->setText(name);
}


void Matrix::SetMatrix_Player_One(const CMugs &cm){
    ui->widget_brain_p1->SetMugs(cm);
}


void Matrix::SetMatrix_Player_Two(const CMugs &cm){
    ui->widget_brain_p2->SetMugs(cm);
}


Matrix::~Matrix() {
    delete ui;
}


void Matrix::setupUi() {
    ui->label_name_p1->setText("");
    ui->label_name_p2->setText("");
}


void Matrix::on_pushButton_close_clicked()
{
    this->close();
}

