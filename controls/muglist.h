#ifndef MUGLIST_H
#define MUGLIST_H

#include <QWidget>
#include "muggui.h"
#include "gamelogic/Controller_structs.h"

class MugList : public QWidget
{
    Q_OBJECT
public:
    explicit MugList(QWidget *parent = nullptr);
    MugGUI* GetMugById(const int& id);
    void ClearAllMarksAndHideElements();
    void SetMugs(const CMugs&);

signals:

private:
    int _count = 10;
    int _spacing = 10;
    QRect _startupPosition {QRect(30, 200, 700, 140)};

    void setupUi();
};

#endif // MUGLIST_H
