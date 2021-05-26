#include "PlayerRandom.h"
#include "globals_globals.h"
#include "Observer.h"


/// <summary>
/// Just randum guesses.
/// </summary>
/// <param name="playground"></param>
/// <param name="observer"></param>
/// <param name="move">Current move</param>
/// <returns>PMoveResult</returns>
Player::PMoveResult PlayerRandom::Intelligence(Playground& playground, const Observer& observer, Move* move) {

	do {
		int guess = cnst::GetRandomIdForItemsCount(3) + 1;
		move->SetMove(guess);
		move->SetRemaining((playground.GetAmountOfSticks() - guess));
	} while (observer.MoveIsValid(playground, *move) == false);
	return PMoveResult::OK;
}

Player::PTypes PlayerRandom::GetType() const {
	return Player::PTypes::machineRnd;
}

PlayerRandom::~PlayerRandom() {
	SHOWD;
}
