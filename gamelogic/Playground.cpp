#include "Playground.h"
#include "Player.h"
#include "Controller.h"

void Playground::DoMove(Move* const move) {
	if (move == nullptr) { return; }
	this->TakeSticks(move->GetMove());
	this->pMoves->push_back(move);
}

void Playground::TakeSticks(int number) {
	if (number < 0) {
        throw EXCEPTSWICTH("Number below zero. ");
	}
	if ((this->sticks - number) < this->minSticks) {
        throw EXCEPTSWICTH("Not enough sticks to take.");
	}
	this->sticks -= number;
}

void Playground::DrawPlayground() {
	Con::troller().SetPlayGround(*pMoves, sticks);
}


 void Playground::PrepareNewSession() {
	 this->sticks = this->maxSticks;
	 delete this->pMoves;
	 this->pMoves = new Moves();
 }
