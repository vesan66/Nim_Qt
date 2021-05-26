#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QLabel>
#include <QSlider>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "controls/reddot.h"
#include "controls/blackcircle.h"
#include "controls/board.h"
#include "controls/dots.h"
#include "gui_qt.h"
#include "gamelogic/Controller.h"
#include "gamelogic/Controller_structs.h"
#include "gamelogic/Start.h"
#include "gamethread.h"
#include "gui_qt.h"
#include "gamelogic/guiplaygroundbase.h"
#include "controls/muggui.h"
#include "controls/muglist.h"
#include "controls/chooser.h"
#include "gamelogic/Confi.h"
#include "info.h"
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private slots:

    void Receive_PrepareNewSession();

    void Receive_EndSession();

    void Receive_DrawPlayground(const int& );

    void Receive_Playerlist(const CPlayers&, const bool&);

    void Receive_SessionsToPlay(const CSessions&);

    void Receive_BrainBefore(const CMugs&);

    void Receive_BrainAfter(const CMugs&);

    void Receive_AskForMove();

    void Receive_HU_Move(const int&);

    void Receive_Winner(const QString&);

    void Receive_LoopState(const Con::CLoopStates&);

    void on_pushButton_start_games_clicked();

    void on_pushButton_stop_games_clicked();

    void on_pushButton_pause_game_clicked();

    void on_pushButton_clicked();


    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_info_clicked();

    void on_pushButton_showBrain_clicked();

private:
    Ui::MainWindow *ui;
    GUI_Qt* _pInterface{};    
    GameThread* _pGameThread{};
    Board* _pBoard{};
    Dots* _pDots{};
    MugList* _pMugList{};
    Chooser* _pChooser{};
    QParallelAnimationGroup* _pHideC{};
    QParallelAnimationGroup* _pShowC{};

    void SetupGui();
    void closeEvent (QCloseEvent*);
    void SetActiveLabel(QLabel*, const bool&);
    void AnimationConfig();
};
#endif // MAINWINDOW_H
