#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>
#include <QDebug>
#include <QMutex>
//#include "gui_qt.h"
//#include "gamelogic/guiplaygroundbase.h"
//#include "gamelogic/Controller.h"

class GUI_Qt;
class GameThread : public QThread {
public:
    //explicit GameThread(QObject* parent = nullptr, GUI_Qt* = nullptr, int = 99);
    explicit GameThread(QObject* parent = nullptr);

    virtual ~GameThread();
protected:
    virtual void run() override;
private:
    GUI_Qt* _pGui{};
};

#endif // GAMETHREAD_H
