#pragma once
#include <iostream>
#include "globals_globals.h"
#include "global_exception.h"

using namespace std;
using namespace cnst;


class Player;	// Forward Declaration


class Playground {
public:
	Playground() {};
	Playground(const int& maxSticks) : maxSticks{ maxSticks } {};
	void DoMove(Move* const move);
	
	virtual int GetAmountOfSticks() const { return this->sticks; };
	virtual void DrawPlayground();
	virtual void PrepareNewSession();
	virtual ~Playground() { SHOWD; };
	virtual const Moves& GetMoves() const { return *pMoves; };
private:
	int sticks{ 0 };
	int maxSticks{ 0 };
	int minSticks{ 0 };
	Moves* pMoves{ new Moves() };	// I don't own.

	void TakeSticks(int);
};

