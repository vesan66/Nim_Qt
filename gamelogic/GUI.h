#pragma once
#include <iostream>
#include "global_func.h"
#include "Controller_structs.h"
#include "guiplaygroundbase.h"
#include "Game.h"

using namespace std;
using namespace cnst;

class Con;

class GUI final: public GUIPlaygroundBase {
public:
    GUI();
	~GUI();

	// Outputs
    void Draw(Con*, const TChangeSet&) override;
    void DrawPlayerSummary(const CPlayers&) override;

	// Inputs
    char AskForMove(const string&, const string&, const char&) override;
    char AskForContinue(const string&, const char&) override;
    char GetCharOnTheRun() override;
    void WaitForKeyAfterSession() override;

    //Signals to the Game
    //void StartGame() override;



	// Session
    void PrepareNewSession() override;
    void EndSession()override;

private:
    void DrawAll(Con*);
	void DrawPlayerList(const CPlayers&, const bool&);
	void DrawPlayground(const int&);
	void DrawRawPlayground(const int&);
	void DrawPlayedPlayground(const int&);
	void DrawWinner(const string&);
	void DrawLooser(const string&);
	void DrawMoves(const CMoves&);
	void DrawMove(const CMove&);
	void DrawLastMove(const CMove&);
	void DrawPlayerComment(const CMove&);
	void GameWasCanceled(const bool&);
	void DrawLoopState(const Con&);
	void DrawSessionsToPlay(const CSessions&);
	void DrawBrainBefore(const CMugs&);
	void DrawBrainAfter(const CMugs&);
	string MakeBrain(const CMugs&);

	Mousetrap* pMt = nullptr;	// I own!
	bool sessionIsOver = false;
};

