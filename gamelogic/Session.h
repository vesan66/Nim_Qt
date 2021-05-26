#pragma once
#include <iostream>
#include "Playground.h"
#include "Observer.h"
#include "PlayerPool.h"
#include "Controller.h"
#include "global_exception.h"
#include "Confi.h"

using namespace std;

class Session {
public:
	Session() {};

	void PlaySession(Observer* pObserver, PlayerPool* pPlayerPool);	

	virtual ~Session();
private:
	Playground* pPlayground{nullptr};	// I own
    Observer* pObserver{nullptr};
	PlayerPool* pPlayerPool{nullptr};

	int sessionsPlayed = 0;
	int sessionsToPlay = 1;

	void PrepareNewSession(Observer* pObserver, PlayerPool* pPlayerPool);
	void Play(bool&);
	void EndSession();
	
	inline void ResetSessionCounters() { sessionsPlayed = 0; sessionsToPlay = 1; }
};

