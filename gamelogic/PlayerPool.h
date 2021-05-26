#pragma once
#include <iostream>
#include "globals_globals.h"
#include "Player.h"
#include "Confi.h"

using namespace std;
using namespace cnst;

class PlayerPool {
public:
	PlayerPool();
	void SetupDefaultPlayerList();

    static void ExportPlayerList();

    void AddPlayer(const string&, const Player::PTypes&, const int& id);
    void AddPlayer(Player* pPlayer);
	void PrepareNewSession();
	void InitializePlayers(const Observer&);
	void CleanupSessionAfterMath();    
    PlayerList* GetPlayerList() { return this->pPlayerList; };


	

	~PlayerPool();
private:
	PlayerList* pPlayerList{ new PlayerList() };	// I own.

	static Player* GetPlayerByID(PlayerList* pPlayerList, const int& id);
	static bool EraseByID(PlayerList* pPlayerList, const int& id);
};

