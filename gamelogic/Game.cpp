#include "Game.h"
#include <thread>
#include <chrono>


void Game::PrepareGame(const bool& bringMeDown) {

	static bool iAmPrepared = false;
    if (bringMeDown == true) { iAmPrepared = false; return;}

	if (iAmPrepared == false) {
		this->pPlayerPool->SetupDefaultPlayerList();
		this->pPlayerPool->InitializePlayers(*this->pObserver);
		this->pObserver->SetupPlayerList(*(this->pPlayerPool->GetPlayerList()));
		iAmPrepared = true;
	}
}


void Game::Play() {

	this->PrepareGame();

	Session* pSession = new Session();
	pSession->PlaySession(this->pObserver, this->pPlayerPool);
	delete pSession; pSession = nullptr;
}


Game::~Game() {
	SHOWD;
    PrepareGame(true);
	if (this->pObserver != nullptr) {
		delete this->pObserver; this->pObserver = nullptr;
	}
	if (this->pPlayerPool != nullptr) {
		delete this->pPlayerPool; this->pPlayerPool = nullptr;
	}
}


