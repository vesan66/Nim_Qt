#include "Controller.h"

#ifndef CONTROLLER_CPP_INCLUDE
#define CONTROLLER_CPP_INCLUDE

#include "Player.h"
#include "PlayerAI.h"
#include "Mugmap.h"
#include "Mug.h"
#include "GUI.h"
#if _USEQT == true
#include "./gui_qt.h"
#endif
#include "PlayerPool.h"

#endif

Con::Con(): _pGUI {nullptr} {
    SHOWC;    
    //PlayerPool::ExportPlayerList();
    //Confi::guration().LoadFromFile();    

#if _USEQT == false
    this->_pGUI = new GUI();
    iOwnTheGui = true;    
    //Confi::guration().LoadFromFile();
#endif
}


Con::~Con() {
    SHOWD;
    if (this->_pGUI == nullptr) {return;}
    if (iOwnTheGui) { delete _pGUI; }
    _pGUI = nullptr;
}


Con& Con::troller() {
    static Con instance;
    return instance;
}

void Con::SetGUIInterface(GUIPlaygroundBase* g){
    this->_pGUI = g;
}


void Con::Refresh(const EWhatWasChanged& whatWasChanged) {
    if (whatWasChanged == EWhatWasChanged::all) {
        Refresh(EverythingWasChanged());
    }
    Refresh(TChangeSet{whatWasChanged});
}

void Con::Refresh(const TChangeSet& changeSet) {
    this->_pGUI->Draw(this, changeSet);
}

TChangeSet Con::EverythingWasChanged() const {
    return TChangeSet{ EWhatWasChanged::playground,
                       EWhatWasChanged::playedPlayground,
                       EWhatWasChanged::playerList,
                       EWhatWasChanged::sessionsPlayed,
                       EWhatWasChanged::brainBefore,
                       EWhatWasChanged::brainAfter,
                       EWhatWasChanged::winnerSet,
                       EWhatWasChanged::looserSet,
                       EWhatWasChanged::loopStateChange,
                       EWhatWasChanged::ALL_WAS_SET_Automatic
                      };
}


void Con::PrepareNewSession() {
    this->brainBefore.clear();
    this->brainAfter.clear();
    this->_pGUI->PrepareNewSession();
    this->SetLoopState(Con::troller().StartupLoopState());    
}


void Con::EndSession() {
    this->_pGUI->EndSession();
    this->_pGUI->Draw(this, EverythingWasChanged());
}


void Con::LoopControl(bool& gameIsFinished, bool& terminateAll) {
    if (gameIsFinished) { return; }
    
    // First pass per session
    if (this->loopState == Con::CLoopStates::undefined) {
        this->SetLoopState(Con::CLoopStates::running);
    }

    if (UseSingleMagicCharChannel()) {
        do {
            // Everything different.
            char input = MagicChar();
            if (this->loopState != Con::CLoopStates::paused) {
                if (input == cnst::emptyChar) { return; };
            }

            // consume char:
            SetMagicChar(cnst::emptyChar);

            // Check for things
            if (input == cnst::pauseChar) {
                this->SetLoopState(Con::CLoopStates::paused);
            }
            if (input == cnst::terminateChar) {
                this->SetLoopState(Con::CLoopStates::wantQuitFromTheRun);
                gameIsFinished = true;
                terminateAll = true;
                return;
            }
            if (input == cnst::continueChar) {
                this->SetLoopState(Con::CLoopStates::running);
                return;
            }
            if (input == cnst::stepLoopChar) {
                this->SetLoopState(Con::CLoopStates::stepRunning);
                return;
            }

            if (this->loopState == Con::CLoopStates::paused) {
                cnst::WaitSeconds(0.5);
            }


        } while (this->loopState == Con::CLoopStates::paused);
        // And OUT!
        return;
    }

    // Monitor the keyboard wo stopping.
    if (this->loopState == Con::CLoopStates::running) {

        // Check for userinput on the run...
        char input = this->_pGUI->GetCharOnTheRun();

        // Entering PauseMode if it is 'p'
        if (input == cnst::pauseChar) {
            this->SetLoopState(Con::CLoopStates::paused);
        }
        if (input == cnst::terminateChar) {
            this->SetLoopState(Con::CLoopStates::wantQuitFromTheRun);
            gameIsFinished = true;
            terminateAll = true;
            return;
        }
    }

    // Important: Imideatly catch the state.
    // Hold inside here, and ask for continue.
    if ((this->loopState == Con::CLoopStates::paused) ||
        (this->loopState == Con::CLoopStates::stepRunning)) {

        // Holding question:
        //string options{ (char)CLoopOptions::terminate, (char)CLoopOptions::continueSession, (char)CLoopOptions::pausePerLoop };
        //char result = this->_pGUI->AskForContinue(options, (char)CLoopOptions::quit);

        string options{ (char)CLoopOptions::terminate, (char)CLoopOptions::continueSession, (char)CLoopOptions::pausePerLoop, (char)CLoopOptions::quit };
        char result = this->_pGUI->AskForContinue(options, emptyChar);

        switch (result) {
        case (char)CLoopOptions::quit: {
            gameIsFinished = true;
            this->SetLoopState(Con::CLoopStates::running);
            break;
        }
        case (char)CLoopOptions::terminate: {
            gameIsFinished = true;
            terminateAll = true;
            this->SetLoopState(Con::CLoopStates::running);
            break;
        }
        case (char)CLoopOptions::continueSession: {
            this->SetLoopState(Con::CLoopStates::running);
            break;
        }
        case (char)CLoopOptions::pausePerLoop: {
            this->SetLoopState(Con::CLoopStates::stepRunning);
            break;
        }
        default:
            break;
        }
    }

}


void Con::SetPlayerList(const PlayerCycle& list, const Player* ap) {
    this->dplayers.clear();
    this->winner = "";
    this->looser = "";
    this->gameWasCanceled = false;
    this->brainBefore.clear();
    this->brainAfter.clear();
    this->dplayers = this->MapPlayers(list, ap);

    this->Refresh(EWhatWasChanged::playerList);
}


template <class _cont>
CPlayers Con::MapPlayers(const _cont& list, const Player* ap) {

    CPlayers pl{};

    for (auto item : list) {
        CPlayer dp{};
        dp.name = item->GetName();
        dp.type = item->GetType();

        if (ap != nullptr) {
            auto p1 = &(*item);
            auto p2 = ap;
            dp.isActive = (p1 == p2);
        }
        else {
            dp.isActive = false;
        }

        dp.sessionsPlayed = item->GetSessionsPlayed();
        dp.sessionsWon = item->GetSessionsWon();
        dp.sessionsLost = item->GetSessionsLost();
        dp.sessionsUndefined = item->GetSessionsUndefined();

        pl.push_back(dp);
    }
    return pl;
}


void Con::SetPlayGround(const Moves& list, const int& sticks) {
    this->dmoves.clear();
    this->sticksAfterMove = 0;
    this->moveDone = CMove();

    this->sticks = sticks;
    for (auto item : list) {
        CMove dm{};
        dm.name = item->GetName();
        dm.sticks = item->GetMove();
        this->dmoves.push_back(dm);
    }
    this->Refresh(EWhatWasChanged::playground);
}


void Con::SetPlayedPlayground(const Move& moveDone, const int& sticksRemain) {
    this->sticksAfterMove = sticksRemain;
    CMove dm{};
    dm.name = moveDone.GetName();
    dm.sticks = moveDone.GetMove();
    this->moveDone = dm;
    this->Refresh(EWhatWasChanged::playedPlayground);
}


void Con::SetWinner(const Player& p) {
    this->winner = p.GetName();
    this->Refresh(EWhatWasChanged::winnerSet);
}


void Con::SetLooser(const Player& p) {
    this->looser = p.GetName();
    this->Refresh(EWhatWasChanged::looserSet);
}


void Con::SetGameWasCanceled(const Player&) {
    this->gameWasCanceled = true;
    this->Refresh();
}


void Con::SetSessions(const int& played, const int& toPlay) {
    this->sessions.sessionsPlayed = played;
    this->sessions.sessionsToPlay = toPlay;
    this->Refresh(EWhatWasChanged::sessionsPlayed);
}


void Con::SetEndSatistics(const PlayerList& playerList) {
    this->dplayersEnd = this->MapPlayers(playerList, nullptr);
    this->_pGUI->DrawPlayerSummary(this->dplayersEnd);
}

void Con::SetBrainBeforeMove(Player* player, const Observer& o) {
    this->brainBefore.clear();
    int maxTake = o.GetMaxTake();
    this->brainBefore = GetBrain(player, maxTake);
    this->Refresh(EWhatWasChanged::brainBefore);
}


CMugs Con::GetBrain(Player* player, const int& maxTake) {
    CMugs result{};
    if (typeid(*player) == typeid(PlayerAI)) {
        PlayerAI* pPAI = dynamic_cast<PlayerAI*>(player);
        const Mugmap::Mugs* mm = pPAI->GetMugs();
        for (auto item = mm->crbegin(); item != mm->crend(); item++) {        
            Mugmap::MugPair mpair = *item;
            const Mug* m = mpair.second;
            CMug cm{};
            cm.number = m->NumberOfKey();
            cm.pearls.clear();
            const Mug::PearlSet* pPS = m->GetPearls();            
            for (int i = maxTake; i > 0; i--) {
                CPearl cp{};
                auto pearl = pPS->find(i);
                if (pearl != pPS->end()) {
                    cp.number = *pearl;
                } else {
                    cp.number = -1;
                }
                cm.pearls.push_back(cp);
            }
            cm.choosen = m->ElectedPearl();
            result.push_back(cm);
        }
    }
    return result;
}


void Con::SetBrainAfterMove(Player* player, const Observer& o) {
    this->brainAfter.clear();
    int maxTake = o.GetMaxTake();
    this->brainAfter = GetBrain(player, maxTake);
    this->Refresh(EWhatWasChanged::brainAfter);
}


void Con::SetLoopState(const CLoopStates& loopState){
    this->loopState = loopState;
    this->Refresh(EWhatWasChanged::loopStateChange);
}


char Con::AskForMove(const Player& p, const Observer& o) {

    string possibleInputs = "";
    for (int i = o.GetMinTake(); i <= o.GetMaxTake(); i++) {
        possibleInputs += to_string(i);
    }
    char result = this->_pGUI->AskForMove(p.GetName(), possibleInputs, cancelChar);

    return result;
}


void Con::WaitForKeyAfterSession() {
    this->_pGUI->WaitForKeyAfterSession();
}


bool Con::UseSingleMagicCharChannel() {
    return this->_pGUI->UseSingleMagicCharChannel();
}


void Con::StartGame(){    
   SHOWO;

   Game* pGame = new Game();

   pGame->Play();
   delete pGame; pGame = nullptr;
   SetLoopState(CLoopStates::finished);

}





