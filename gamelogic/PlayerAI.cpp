#include "PlayerAI.h"
#include "globals_globals.h"
#include "Observer.h"
#include "Controller.h"

/// <summary>
/// A kind of AI.
/// </summary>
/// <param name="playground"></param>
/// <param name="observer"></param>
/// <param name="move">Current move</param>
/// <returns>PMoveResult</returns>
Player::PMoveResult PlayerAI::Intelligence(Playground& playground, const Observer& observer, Move* move) {

	// Draw my brain before.
	Con::troller().SetBrainBeforeMove(this, observer);

	int tries = 20;
	bool moveIsValid = false;
	int guess = 0;
	int mugNo = playground.GetAmountOfSticks();
	Mug* mug = _pMM->GetItemByMugNumber(mugNo);

	if (mug != nullptr) {
		do {
			if (playground.GetAmountOfSticks() == 10) {
				cout << "";
			}
			// Get the desired move from AI.
			if (mug->ElectedPearl() != 0) {
				mug->PushPearlBackToMug();
			}
			if (mug->PullARandomPearl() == false) {
                throw EXCEPTSWICTH("No move possible.");
			}

			guess = mug->ElectedPearl();		

			// Fill the move-object.	
			move->SetMove(guess);
			move->SetRemaining((playground.GetAmountOfSticks() - guess));

			// Check, if valid.
			moveIsValid = observer.MoveIsValid(playground, *move);
			tries--;
		} while ((moveIsValid == false) && (tries != 0));
		if ((moveIsValid == false) && (tries == 0)) {
			if (mug->ElectedPearl() != 0) { mug->PushPearlBackToMug(); }
            throw EXCEPTSWICTH("After tries, there is no matching move.");
		}
	} else {
        throw EXCEPTSWICTH("No matching mug found!");
	}

	if (moveIsValid == true) {
		this->_pMM->AddItemToChain(mug);
	}

	// The Move is valid: Draw my brain.
	Con::troller().SetBrainAfterMove(this, observer);

	return PMoveResult::OK;
}


Player::PTypes PlayerAI::GetType() const {
	return Player::PTypes::machineAI;
}

PlayerAI::~PlayerAI() {
	SHOWD;
	if (_pMM != nullptr) {
		delete _pMM; _pMM = nullptr;
	}
}


void PlayerAI::CleanupSessionAfterMath() {
	Player::CleanupSessionAfterMath();
	_pMM->CleanupSessionAfterMath(this->GetState());
}


void PlayerAI::Initialize(const Observer& observer) {
	Player::Initialize(observer);
	_pMM->SetupMugMap(
		observer.GetInitialSticksAtPlayground(),
		observer.GetMaxTake());
	_pMM->IsTraining(_isTraining);	
}


void PlayerAI::PrepareNewSession() {
	Player::PrepareNewSession();
	_pMM->PrepareNewSession();
}

void PlayerAI::IsTraining(const bool& isTraining) {
	_isTraining = isTraining;
	if (_pMM != nullptr) {
		_pMM->IsTraining(_isTraining);
	}
}

const  Mugmap::Mugs* PlayerAI::GetMugs() const {
	if (_pMM != nullptr) {
		return _pMM->GetMugs();
	}
	return nullptr;
}

