#ifndef GUI_QT_H
#define GUI_QT_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QMutex>
#include <QTime>
#include <QCoreApplication>
#include "gamethread.h"
#include "gamelogic/globals_globals.h"
#include "gamelogic/guiplaygroundbase.h"
#include "gamelogic/Controller_structs.h"
#include "gamelogic/Controller.h"

class GUI_Qt : public QObject, public GUIPlaygroundBase
{
    Q_OBJECT

public:
    explicit GUI_Qt(QObject *parent = nullptr);

    // Outputs
    void Draw(Con*, const TChangeSet&) override;
    void DrawPlayerSummary(const CPlayers&) override;

//	// Inputs
    char AskForMove(const string&, const string&, const char&) override;
//    char AskForContinue(const string&, const char&) override;
//    char GetCharOnTheRun() override;
//    void WaitForKeyAfterSession() override;

    // For the Qt-Runloops.
    inline bool UseSingleMagicCharChannel() override { return true; }

    //Signals to the Game    
    void StartGameThread();
    void StartGame() override;

    // From Con to Me
    void PrepareNewSession() override;
    void EndSession()override;

    // Properties
    inline GameThread* GetGameThread() {return _pGameThread; }

    ~GUI_Qt();
signals:
    void Send_PrepareNewSession();
    void Send_EndSession();
    void Send_SticksToShow(const int&);
    void Send_SticksToShowAfterMove(const int&);
    void Send_Players(const CPlayers&, const bool&);
    void Send_SessionsToPlay(const CSessions&);
    void Send_BrainBefore(const CMugs&);
    void Send_BrainAfter(const CMugs&);
    void Send_AskForMove();
    void Send_Winner(const QString&);
    void Send_LoopState(const Con::CLoopStates&);
private:
    GameThread* _pGameThread{};
    QMutex _mutex;

    //char _magicChar{cnst::emptyChar};

    int _delayNewSession = 1700;
    int _delayEndSession = 3000;
    int _delayMove = 800;
    void Delay(const int& millisecondsToWait);
    void DrawPlayground(const int&);
    void DrawPlaygroundAfterMove(const int&);
    void DrawPlayerList(const CPlayers& players, const bool& isMultiSession);
    void DrawSessionsToPlay(const CSessions&);
    void DrawBrainBefore(const CMugs&);
    void DrawBrainAfter(const CMugs&);
    void DrawWinner(const string&);
    void DrawLoopState(const Con::CLoopStates&);
};

#endif // GUI_QT_H
