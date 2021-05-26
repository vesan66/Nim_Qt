#include "gui_qt.h"
#include "./gamelogic/Controller.h"


GUI_Qt::GUI_Qt(QObject *parent) : QObject(parent) {    
    SHOWC;
    Con::troller();
}


void GUI_Qt::Draw(Con * con, const TChangeSet & changeSet) {
    SHOWO;
    if (changeSet.find(EWhatWasChanged::ALL_WAS_SET_Automatic) != changeSet.end() ) {
        qDebug() << "ALL_WAS_SET_Automatic";
        return;
    }
    if (changeSet.find(EWhatWasChanged::playerList) != changeSet.end() ) {
        qDebug() << "Update for Playerlist";
        CPlayers players = con->GetPlayerList();
        DrawPlayerList(con->GetPlayerList(), con->IsMultiSession());
    }
    if (changeSet.find(EWhatWasChanged::playground) != changeSet.end() ) {
        qDebug() << "EWhatWasChanged::playground: SKIPPING";
        //DrawPlayground(con->GetPlayground());
    }

    if (changeSet.find(EWhatWasChanged::playedPlayground) != changeSet.end() ) {
        qDebug() << "EWhatWasChanged::playedPlayground";
        DrawPlaygroundAfterMove(con->GetPlayedPlayground());
    }

    if (changeSet.find(EWhatWasChanged::sessionsPlayed) != changeSet.end() ) {
        qDebug() << "EWhatWasChanged::sessionsPlayed";
        DrawSessionsToPlay(con->GetSessions());
    }

    if (changeSet.find(EWhatWasChanged::brainBefore) != changeSet.end() ) {
        qDebug() << "EWhatWasChanged::brainBefore";
        DrawBrainBefore(con->GetBraineBefore());
    }

    if (changeSet.find(EWhatWasChanged::brainAfter) != changeSet.end() ) {
        qDebug() << "EWhatWasChanged::brainAfter";
        DrawBrainAfter(con->GetBraineAfter());
    }
    if (changeSet.find(EWhatWasChanged::winnerSet) != changeSet.end() ) {
        qDebug() << "EWhatWasChanged::winnerSet";
        DrawWinner(con->GetWinner());
    }
    if (changeSet.find(EWhatWasChanged::loopStateChange) != changeSet.end() ) {
        qDebug() << "EWhatWasChanged::loopStateChange";
        DrawLoopState(con->GetLoopState());
    }
}


void GUI_Qt::DrawPlayerSummary(const CPlayers &) {
    SHOWO;
}


char GUI_Qt::AskForMove(const string &, const string &, const char &) {
    SHOWO;
    this->_mutex.lock();
    char c{cnst::emptyChar};
    this->SetMagicChar(cnst::emptyChar);
    emit Send_AskForMove();
    do {
        Delay(200);
        c = this->MagicChar();
        //qDebug() << "Waiting: " << c;
    } while (c == cnst::emptyChar);
    this->SetMagicChar(cnst::emptyChar);
    this->_mutex.unlock();
    return c;
}


void GUI_Qt::StartGameThread()
{
    if (_pGameThread != nullptr) {
        if (_pGameThread->isRunning()) { return; }
        if (!_pGameThread->isFinished()) {return;}
        delete _pGameThread; _pGameThread = nullptr;
    }
    if (_pGameThread == nullptr) {
        _pGameThread = new GameThread(this);
    }
    _pGameThread->start();
}


void GUI_Qt::StartGame(){
    SHOWO;
    // Do Preparations
    this->SetMagicChar(cnst::emptyChar);
    GUIPlaygroundBase::StartGame();
}


void GUI_Qt::PrepareNewSession() {
    SHOWO;
    this->_mutex.lock();
    emit Send_PrepareNewSession();
    this->Delay(_delayNewSession);
    this->_mutex.unlock();
}


void GUI_Qt::EndSession() {
    SHOWO;
    this->_mutex.lock();
    emit Send_EndSession();
    this->Delay(_delayEndSession);
    this->_mutex.unlock();
}


GUI_Qt::~GUI_Qt() {    
    SHOWD;
}


void GUI_Qt::Delay(const int& millisecondsToWait) {
    //https://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        if (this->MagicChar() != cnst::emptyChar) {
            qDebug() << "Loop Break.";
            break;
        }
    }
}


void GUI_Qt::DrawPlayground(const int& sticks) {
    SHOWO;
    qDebug() << "Sticks on Playground: " << sticks;
    this->_mutex.lock();
    emit Send_SticksToShow(sticks);
    this->Delay(_delayMove);
    this->_mutex.unlock();
}


void GUI_Qt::DrawPlaygroundAfterMove(const int& sticks) {
    SHOWO;
    qDebug() << "Sticks on Playground after Move: " << sticks;
    this->_mutex.lock();
    emit Send_SticksToShowAfterMove(sticks);
    this->Delay(_delayMove);
    this->_mutex.unlock();
}


void GUI_Qt::DrawPlayerList(const CPlayers& players, const bool& isMultiSession) {
    SHOWO;
    //this->_mutex.lock();
    emit Send_Players(players, isMultiSession);
    //this->_mutex.unlock();
}


void GUI_Qt::DrawSessionsToPlay(const CSessions& s) {
    SHOWO;
    emit Send_SessionsToPlay(s);
}


void GUI_Qt::DrawBrainBefore(const CMugs & cm) {
    this->_mutex.lock();
    emit Send_BrainBefore(cm);
    this->_mutex.unlock();
}


void GUI_Qt::DrawBrainAfter(const CMugs & cm) {
    this->_mutex.lock();
    qDebug() << "Braincount: " << cm.size();
    emit Send_BrainAfter(cm);
    this->Delay(_delayMove);
    this->_mutex.unlock();
}


void GUI_Qt::DrawWinner(const string& value) {
    SHOWO;
    emit Send_Winner(QString::fromStdString(value));
}


void GUI_Qt::DrawLoopState(const Con::CLoopStates& state) {
    SHOWO;
    emit Send_LoopState(state);
}











