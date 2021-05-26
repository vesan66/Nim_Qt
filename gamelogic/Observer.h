#pragma once
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>       
#include <vector>      
#include "global_typedef.h"
#include "Player.h"
#include "Playground.h"
#include "global_func.h"
#include "template_Cycle.h"
#include "global_exception.h"

using namespace std;

typedef Cycle<Player*> PlayerCycle;

class Observer {
public:
	enum class PlayerOrder : int { dontChange = 0, mixOnce = 1, mixEveryRound = 2 };
	enum class Winner : int { meansNothing = 0, winnerStarts = 1};

	Observer();

	Playground* CreateNewPlayground() const;
	void SetupPlayerList(const cnst::PlayerList&, const PlayerOrder& = PlayerOrder::mixEveryRound);
	void PrepareNewSession();

	Player* GetNextPlayer();
	bool GameOver(const Playground& plgr);
	bool MoveIsValid(const Playground& plgr, const Move& move) const;
	
	int GetMaxTake() const { return this->maxTakeOfSticks; };
	int GetMinTake() const { return this->minTakeOfSticks; };
	int GetInitialSticksAtPlayground() const { return this->initialSticksAtPlayground; };
	//const PlayerCycle* GetPlayerCycle() const { return pPlayerCycle; };

	virtual ~Observer();
private:	
	PlayerCycle* pPlayerCycle{ new PlayerCycle() };

	// Configuration
	PlayerOrder playerOrder{ PlayerOrder::mixEveryRound };
	Winner winner{ Winner::meansNothing };
	int maxTakeOfSticks{};
	const int minTakeOfSticks{ 1 };
	const int winnerIfRemainingAmountAfterMove{ 1 };
	const int initialSticksAtPlayground{ 10 };

	void FillPlayerCycle(const cnst::PlayerList& playerList);
};

