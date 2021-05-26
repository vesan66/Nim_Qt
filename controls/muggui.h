#ifndef MUGGUI_H
#define MUGGUI_H

#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class MugGUI : public QFrame
{
    Q_OBJECT
public:

    explicit MugGUI(QWidget* parent = nullptr);
    inline virtual ~MugGUI() override {};

    void ClearMarks();
    inline int MyId() { return _myId; }
    void SetMyId(const int& value);
    void SetMark(const int& value);
    void SetBtnVisible(const bool&, const int& value = 0);

private:
    QWidget *centralwidget;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_Close;
    QPushButton *pushButton_take_2;
    QPushButton *pushButton_take_1;
    QPushButton *pushButton_take_3;
    QWidget *widget_container;
    //QFrame *frame_mug;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_TopBottom;
    QLabel *label;
    QHBoxLayout *horizontalLayout_Buttons;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    int _myId = 0;

    void setupUi();
    void SetActiveLabel(QPushButton*, const bool&);
    void SetActiveLabelBG(QPushButton*, const bool&);
};

#endif // MUGGUI_H
