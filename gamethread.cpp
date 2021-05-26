#include "gamethread.h"
#include "gui_qt.h"


GameThread::GameThread(QObject* parent): QThread(parent) {
    qDebug() << __FUNCTION__;
    if (typeid (*parent) == typeid (GUI_Qt)) {
        _pGui = dynamic_cast<GUI_Qt*>(parent);
    }
}


GameThread::~GameThread() {
    qDebug() << __FUNCTION__;
    _pGui = nullptr;
}


void GameThread::run() {
    qDebug() << __FUNCTION__;

    if (_pGui != nullptr) {
        qDebug() << "Before start game.";
        _pGui->StartGame();
        qDebug() << "After start game.";
    }


};
