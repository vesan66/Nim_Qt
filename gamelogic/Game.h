#pragma once
#include "globals_globals.h"
#include "Observer.h"
#include "Session.h"
#include "PlayerPool.h"

using namespace std;
using namespace cnst;


class Game {
public:
	Game() {};
	
	void Play();

	virtual ~Game();

private:
	Observer* pObserver{ new Observer() };			// I own
	PlayerPool* pPlayerPool{ new PlayerPool() };	// I own	

    void PrepareGame(const bool& = false);
};
