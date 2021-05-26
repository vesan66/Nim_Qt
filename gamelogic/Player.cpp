#include "Player.h"
#include "Observer.h"
#include "global_func.h"
#include "Controller.h"
#include "PlayerRandom.h"
#include "PlayerHuman.h"
#include "PlayerAI.h"

string Player::PlayerTypeToString(PTypes type) {

	string result{};
	switch (type) {
	case Player::PTypes::human: { result = "[HU] "; break; }
	case Player::PTypes::machineAI: { result = "[AI] "; break; }
	case Player::PTypes::machineRnd: { result = "[RN] "; break; }
	default: { result = "[UD] "; break; }
	}
	return result;
}

Player::PMoveResult Player::Play(Playground& playground, const Observer& observer) {

	PMoveResult result = PMoveResult::undefined;

    if (this->pMoves == nullptr) { throw EXCEPTSWICTH("this->pMoves == nullptr"); }

	Move* pM = new Move(this);

	// 'Inteligence'
	result = this->Intelligence(playground, observer, pM);

	// Handle the move.
	if (result == PMoveResult::OK) {

		// Last check before apply.
		if (observer.MoveIsValid(playground, *pM) == false) {
            throw EXCEPTSWICTH("Invalid move!");
		}

		// Publish the move.
		playground.DoMove(pM);
		this->pMoves->push_back(pM);

		// Display the result.
		Con::troller().SetPlayedPlayground(*pM, playground.GetAmountOfSticks());
		cnst::WaitSeconds(cnst::waitAfterMove);
	}

	pM = nullptr;
    return result;
}

void Player::ClearSessionPlayedWonEtc()
{
    sessionsPlayed = 0;
    sessionsWon = 0;
    sessionsLost = 0;
    sessionsUndefined = 0;
}


Player::PMoveResult Player::Intelligence(Playground&, const Observer&, Move*) {
    throw EXCEPTSWICTH("Don't call me exception!");
	return PMoveResult::error;
}

/// <summary>
/// Get type of the player.
/// </summary>
/// <returns>Element of Player::PTypes</returns>
Player::PTypes Player::GetType() const {
	return PTypes::undefined;
}


Player* Player::CreateNewPlayer(const string& name, const Player::PTypes& playerType, const int& id) {
	Player* result{ nullptr };
	switch (playerType) {
	case Player::PTypes::machineRnd: {
		result = new PlayerRandom(name);
        result->SetId(id);
		break;
	}
	case Player::PTypes::human: {
		result = new PlayerHuman(name);
        result->SetId(id);
		break;
	}
	case Player::PTypes::machineAI: {
		result = new PlayerAI(name);
        result->SetId(id);
		break;
	}
	default:
		break;
	}
	return result;
}


void Player::Initialize(const Observer&) {

}

void Player::PrepareNewSession() {
	this->UnloadOldMoves();
	this->pMoves = new Moves();
	this->state = PStates::undefined;
}


void Player::CleanupSessionAfterMath() {
	
	sessionsPlayed++;

	switch (this->state) {
	case Player::PStates::won:
		this->sessionsWon++;
		break;
	case Player::PStates::lost:
		this->sessionsLost++;
		break;
	case Player::PStates::undefined:
		this->sessionsUndefined++;
		break;
	default:
		break;
	}

	// TODO: Evaluate the data!
}


void Player::UnloadOldMoves() {
	if (this->pMoves != nullptr) {
		while (this->pMoves->size() != 0) {
			auto item = this->pMoves->back();
			delete item;
			this->pMoves->pop_back();
		}
	}
	delete this->pMoves; this->pMoves = nullptr;	
}


Player::~Player() {
	SHOWD;
	this->UnloadOldMoves();
}
