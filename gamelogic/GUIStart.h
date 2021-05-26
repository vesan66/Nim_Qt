#pragma once
#include <iostream>
#include "globals_globals.h"
#include "Controller_structs.h"
#include "Player.h"

using namespace cnst;

class GUIStart {
public:
	void DrawPage(const CPlayer& playerOne, const CPlayer& playerTwo,
		const int& noOfSessions, const bool& resetBrain);

	int AskForSessionCount(const int&);
	char AskForBrain(const string& options, const bool& current);
	int AskForPlayerID(const int& playerNumber, const string& options);
	char AskForMainMenuInput(const string& options, const char& cancel);

	string DrawPlayerListGetIdList(const CPlayers& players, const int& currentP1, const int& currentP2);

	void ClearScreen();

	void DrawBrain(const CPlayer& player, const CMugs& cm);

	string MakeBrain(const CMugs& cm);

	void WaitForKey();

private:
	void DrawMenu();
	void DrawInfo();
	void DrawConfig(const CPlayer& playerOne, const CPlayer& playerTwo,
		const int& noOfSessions, const bool& resetBrain);

};

