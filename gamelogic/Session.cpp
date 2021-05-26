#include "Session.h"
#include <thread>
#include <chrono>


Session::~Session() {
	delete this->pPlayground; pPlayground = nullptr;
	pObserver = nullptr;
	pPlayerPool = nullptr;
}


void Session::PlaySession(Observer* pObserver, PlayerPool* pPlayerPool) {
	
	this->ResetSessionCounters();
	bool terminateAll = false;

    sessionsToPlay = Confi::guration().NumberOfSessions();
	do {
		this->PrepareNewSession(pObserver, pPlayerPool);
		this->Play(terminateAll);
		this->EndSession();
	} while ((!terminateAll) && (this->sessionsPlayed < this->sessionsToPlay));

	if (!terminateAll) {
		if (this->sessionsToPlay > 1) { 
			Con::troller().SetEndSatistics(*(pPlayerPool->GetPlayerList()));
			Con::troller().WaitForKeyAfterSession(); 
		}
	}    
}


void Session::PrepareNewSession(Observer* pObserver, PlayerPool* pPlayerPool) {
	this->pObserver = pObserver;
	this->pObserver->PrepareNewSession();

	this->pPlayerPool = pPlayerPool;
	this->pPlayerPool->PrepareNewSession();

	this->pPlayground = this->pObserver->CreateNewPlayground();	
	this->pPlayground->PrepareNewSession();
}


void Session::EndSession() {

	this->pPlayerPool->CleanupSessionAfterMath();
	
	if (this->pPlayground != nullptr) {
		delete this->pPlayground; this->pPlayground = nullptr;
	}

	sessionsPlayed++;
	pObserver = nullptr;
	pPlayerPool = nullptr;
}


void Session::Play(bool& terminateAll) {
    if (this->pObserver == nullptr) { throw EXCEPTSWICTH("pObserver == nullptr"); }
    if (this->pPlayerPool == nullptr) { throw EXCEPTSWICTH("pPlayerPool == nullptr"); }
    if (this->pPlayground == nullptr) { throw EXCEPTSWICTH("pPlayground == nullptr"); }

	Player* pPlayer = nullptr;
	Player::PMoveResult playerResult = Player::PMoveResult::undefined;

	bool gameIsFinished = false;	
	Con::troller().PrepareNewSession();
	Con::troller().SetSessions(this->sessionsPlayed, this->sessionsToPlay);
	do {

		// Check for a Winner.
		if (!pObserver->GameOver(*pPlayground)) {

			// Elect next player
            pPlayer = pObserver->GetNextPlayer();

			// Draw playground
			pPlayground->DrawPlayground();

			// Play
			playerResult = pPlayer->Play(*pPlayground, *pObserver);
			if (playerResult != Player::PMoveResult::OK) {
				// Player wants to quit.				
                if ((playerResult == Player::PMoveResult::cancel) || (playerResult == Player::PMoveResult::terminateALL)) {
					Con::troller().SetGameWasCanceled(*pPlayer);
                }
                if (playerResult == Player::PMoveResult::terminateALL) {
                    terminateAll = true;
                }
				// Or other things.
				gameIsFinished = true;
			}
		}
		else {
			gameIsFinished = true;
		}

		Con::troller().LoopControl(gameIsFinished, terminateAll);

	} while (!gameIsFinished);

	Con::troller().EndSession();

	if (!terminateAll) {
		if (this->sessionsToPlay <= 1) { Con::troller().WaitForKeyAfterSession(); }
	}
}
