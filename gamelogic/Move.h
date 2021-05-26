#pragma once
#include <iostream>
#include "globals_globals.h"

using namespace std;

class Player;

class Move {
public:
	Move() = delete;
	Move(Player* player, const int& sticks = 0, const int& remaining = 0) : 
		pMe { player },
		sticksToTake{ sticks },
		remainingSticks{ remaining } {};

	int GetMove() const { return this->sticksToTake; };
	int GetRemaining() const { return this->remainingSticks; };
	Player* GetPlayer() const { return this->pMe; };
	string GetName() const;
	void SetMove(const int& sticks) { this->sticksToTake = sticks; };
	void SetRemaining(const int& sticks) { this->remainingSticks = sticks; };
	
	virtual ~Move() { SHOWD; this->pMe = nullptr; };
private:
    Player* pMe{ nullptr };
	int sticksToTake{ 0 };
	int remainingSticks{ 0 };	
};

