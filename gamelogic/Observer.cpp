#include "Observer.h"
#include "Controller.h"
#include "Confi.h"

Player* Observer::GetNextPlayer() {
	Player* p = this->pPlayerCycle->GetNextItem();
	Con::troller().SetPlayerList(*pPlayerCycle, p);
	return p;
}


void Observer::SetupPlayerList(const cnst::PlayerList& players, const PlayerOrder& playerOrder) {
    if (players.empty() == true) { throw EXCEPTSWICTH("Passed playerlist was empty."); };

	this->FillPlayerCycle(players);
	this->playerOrder = playerOrder;
	if ((playerOrder == PlayerOrder::mixOnce) || (playerOrder == PlayerOrder::mixEveryRound)) {
		pPlayerCycle->MixItB();
	}
}


bool Observer::GameOver(const Playground& plgr) {
	bool result = false;
	Player* winner = nullptr;
	Player* looser = nullptr;
	int number = plgr.GetAmountOfSticks();
	bool evaluate = false;

	// Check for still running game.
	if (number > this->winnerIfRemainingAmountAfterMove) {
		// The game still runs.
		return false;
	}

	Moves moves = plgr.GetMoves();
	int pos = (moves.size() - 1); // The last one.

	// First! If the number of Sticks is 0, then someone took the last 1,2 or 3 sticks:
	// This one is the stupid looser.
	if (number <= 0) {
		pos--; // The one before the last one is the winner.
		looser = moves.back()->GetPlayer();
		evaluate = true;
		cout << "Suicide player." << endl;
	}

	// Second. There is the posibility to take one last. But upcoming is the looser.
	if (number == 1) {
		// Means, the last one in list is the winner.
		evaluate = true;
		looser = this->pPlayerCycle->GetNextItem();
		cout << "Normal player." << endl;
	}

	if (evaluate == true) {
		if (pos < 0) {
            throw EXCEPTSWICTH("Error on determinig winner!");
		}
		Move* pM = moves.at(pos);
		if (pM != nullptr) {
			winner = pM->GetPlayer();
			if (winner == nullptr) {
                throw EXCEPTSWICTH("winner == nullptr");
			}
			result = true;
		}
	}

	if (result == true) {
		// aftermath.
		if ((winner != nullptr) && (looser != nullptr)) {
			for (auto item : *pPlayerCycle) {
				Player* p1 = &(*item);
				if (p1 == winner) {
					p1->SetState(Player::PStates::won);
				}
				else if (p1 == looser) {
					p1->SetState(Player::PStates::lost);
				}
			}
			Con::troller().SetWinner(*winner);
			Con::troller().SetLooser(*looser);
			cnst::WaitSeconds(cnst::waitAfterWin);
		}
	}

	return result;
}

/// <summary>
/// Checks, if the desired move is valid for this situtation.
/// </summary>
/// <param name="plgr">The playground at this state.</param>
/// <param name="move">The desired move.</param>
/// <returns>True, if allowed.</returns>
bool Observer::MoveIsValid(const Playground& plgr, const Move& move) const {
	int take = move.GetMove();
	int upperLimit = min<int>(this->maxTakeOfSticks, plgr.GetAmountOfSticks());

	// 1.a) Don't take more than maximum allowed.
	// 1.b) Don't take more than left on playground.
	if (take > upperLimit) { return false; }
	
	// 2.) Don't take less than allowed.
	if (take < this->minTakeOfSticks) { return false; }

	// 3.) Don't take just the rest, if it's more than one.
	//     Because that means, this player wants to be the looser.
	//	   Forbidden suicide.
	if ((plgr.GetAmountOfSticks() > this->minTakeOfSticks) && (take == plgr.GetAmountOfSticks())) { return false; }

	return true;
}


Observer::Observer() {
	maxTakeOfSticks = Confi::guration().MaxTake();
}

Playground* Observer::CreateNewPlayground() const {
	Playground* p = new Playground(this->initialSticksAtPlayground);	
	return p;
}


void Observer::PrepareNewSession() {
	// Playerorder
	switch (this->playerOrder) {
	case PlayerOrder::dontChange: {
		// Nothing to do.
		break;
	}
	case PlayerOrder::mixEveryRound: {
		this->pPlayerCycle->MixItB();
		break;
	}
	default:
		// Nothing
		break;
	}
	
	// Winner
	switch (this->winner) {
	case Winner::meansNothing: {
		this->pPlayerCycle->SetPosForNextItem(0);
		break;
	}
	case Winner::winnerStarts: {
		bool foundWinner = false;
		size_t i = 0;
		for (i = 0; i < this->pPlayerCycle->size(); i++) {
			Player* item = this->pPlayerCycle->at(i);
			if (item != nullptr) {
				if (item->GetState() == Player::PStates::won) {
					foundWinner = true;
					break;
				}
			}
		}
		i = (foundWinner == true) ? i : 0;
		this->pPlayerCycle->SetPosForNextItem(i);
		break;
	}
	default:
		break;
	}

}


void Observer::FillPlayerCycle(const cnst::PlayerList& playerList) {
	this->pPlayerCycle->Clear();

	for (auto item : playerList) {		
		this->pPlayerCycle->AddItem(item);
	}

}


Observer::~Observer() {
	SHOWD;
	delete this->pPlayerCycle; this->pPlayerCycle = nullptr;
}
