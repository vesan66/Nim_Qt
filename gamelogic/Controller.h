#pragma once
#include <string>
#include <set>
#include "globals_globals.h"
#include "Controller_structs.h"
#include "Observer.h"
#include "guiplaygroundbase.h"
#include "global_flags.h"
#include "Game.h"
#include "Confi.h"

class Player;


/// <summary>
/// Singleton class for holding display data.
/// This is somehow an Interface, which knows about the Classes and
/// maps it to stupid printable (array) strings.
/// </summary>

class Con final { 
public:

    enum class CLoopOptions: char { continueSession = cnst::continueChar,
                                    pausePerLoop = cnst::stepLoopChar,
                                    terminate = cnst::terminateChar,
                                    quit = cancelChar,
                                    empty = cnst::emptyChar };
    enum class CLoopStates { running, paused, undefined, stepRunning, otherInput, wantQuitFromTheRun, finished };

    Con& operator= (const Con&) = delete;
    Con(const Con&) = delete; 

    static Con& troller();

    void SetGUIInterface(GUIPlaygroundBase*);

    inline GUIPlaygroundBase* GUIInterface() { return this->_pGUI; }

    
    TChangeSet EverythingWasChanged() const;


    // Only outputs.
    void SetPlayerList(const PlayerCycle&, const Player*);
    void SetPlayGround(const Moves&, const int& sticks);
    void SetPlayedPlayground(const Move&, const int&);
    void SetWinner(const Player&);
    void SetLooser(const Player&);
    void SetGameWasCanceled(const Player&);
    void SetSessions(const int&, const int&);
    void SetEndSatistics(const PlayerList&);
    void SetBrainBeforeMove(Player*, const Observer&);
    void SetBrainAfterMove(Player*, const Observer&);

    // Output with input from user.
    char AskForMove(const Player&, const Observer&);
    void WaitForKeyAfterSession();


    // Use MagicCharChanel. For Qt.
    bool UseSingleMagicCharChannel();
    inline char MagicChar() { return this->_pGUI->MagicChar(); }
    inline void SetMagicChar(const char& magicChar ) { this->_pGUI->SetMagicChar(magicChar); }


    // 'Slots' for 'Signals' from the GUI.
    void StartGame();

    // Session
    void PrepareNewSession();
    void EndSession();
    void LoopControl(bool&, bool&);



    // Used for the GUI to receive the stored data.
    CPlayers GetPlayerList() const { return this->dplayers; };
    string GetWinner() const { return this->winner; };
    string GetLooser() const { return this->looser; };
    int GetPlayground() const { return sticks; };
    int GetPlayedPlayground() const { return sticksAfterMove; };
    CMoves GetMoves() const { return dmoves; };
    CMove GetMoveDone() const { return moveDone; };
    bool GetGameWasCanceled() const { return gameWasCanceled; };
    CLoopStates GetLoopState() const { return this->loopState; }
    CSessions GetSessions() const { return this->sessions; }
    bool IsMultiSession() const { return (this->sessions.sessionsToPlay > 1); }

    CMugs GetBraineBefore() const { return this->brainBefore; }
    CMugs GetBraineAfter() const { return this->brainAfter; }
    CMugs GetBrain(Player* player, const int&);

    //GUI* GetGUIObject() { return &g; };
    ~Con();

    // Configuration
    Con::CLoopStates  StartupLoopState() { return CLoopStates::running; }

private:
    Con();

    GUIPlaygroundBase* _pGUI{ nullptr };

    // Hier kommen Strukturen und Felder hin, die von den einzelnen Klassen befüllt werden.
    //string activePlayer{};
    CPlayers dplayers{};
    CPlayers dplayersEnd{};
    CMoves dmoves{};
    CSessions sessions{};
    CMugs brainBefore{};
    CMugs brainAfter{};

    int sticks = 0;
    int sticksAfterMove = 0;
    bool iOwnTheGui = false;

    CMove moveDone{};
    string winner{};
    string looser{};
    bool gameWasCanceled{};
    CLoopStates loopState = CLoopStates::undefined;

    // Methods
    void Refresh(const EWhatWasChanged& = EWhatWasChanged::all);
    void Refresh(const TChangeSet&);
    void SetLoopState(const CLoopStates&);
    
    template<class _cont>
    CPlayers MapPlayers(const _cont&, const Player*);
    

};

