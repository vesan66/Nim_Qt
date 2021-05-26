#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info) {
    ui->setupUi(this);
    this->SetTexts();
}


Info::~Info() {
    delete ui;
}


void Info::SetTexts() {
    QString title{};

    title = cnst::info_text_title;
    ui->label_title->setText(title);

    QString text{};
    text += cnst::info_text_line_1 + QString('\n');
    text += cnst::info_text_line_2 + QString('\n');
    text += cnst::info_text_line_3 + QString('\n');
    text += cnst::info_text_line_4 + QString('\n');

    ui->textEdit->setPlainText(text);
}

void Info::on_pushButton_close_clicked()
{
    this->close();
}

