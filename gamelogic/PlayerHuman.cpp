#include "PlayerHuman.h"
#include "globals_globals.h"
#include "Observer.h"
#include "Controller.h"

/// <summary>
/// I'm the player. Human.
/// </summary>
/// <param name="playground"></param>
/// <param name="observer"></param>
/// <param name="move">Current move</param>
/// <returns>PMoveResult</returns>
Player::PMoveResult PlayerHuman::Intelligence(Playground& playground, const Observer& observer, Move* move) {

	bool wantCancel = false;
    bool wantTerminate = false;
	bool moveIsValid = false;
	int guess = 0;
	auto result = Player::PMoveResult::undefined;

	do {		
		char selection = Con::troller().AskForMove(*this, observer);
        if ((selection == cnst::cancelChar)||(selection == cnst::terminateChar)) {
            if (selection == cnst::cancelChar) { wantCancel = true;}
            if (selection == cnst::terminateChar) { wantTerminate = true;}
		}
		else {
			guess = (selection - '0');
			move->SetMove(guess);
			move->SetRemaining((playground.GetAmountOfSticks() - guess));
			moveIsValid = observer.MoveIsValid(playground, *move);
		}		
    } while ( (moveIsValid == false) && (wantCancel == false) && (wantTerminate == false) );

	if (wantCancel) {       
		result = Player::PMoveResult::cancel;
    } else if (wantTerminate) {
        result = Player::PMoveResult::terminateALL;
    }
	else if (moveIsValid) {
		result = Player::PMoveResult::OK;
	}

	return result;
}

Player::PTypes PlayerHuman::GetType() const {
	return Player::PTypes::human;
}

PlayerHuman::~PlayerHuman() {
	SHOWD;
}
