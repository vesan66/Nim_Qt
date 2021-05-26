#pragma once
#include "Player.h"

class PlayerRandom : public Player {
public:
	PlayerRandom(const string& name) : Player(name) {};
	virtual PMoveResult Intelligence(Playground&, const Observer&, Move*) override;
	virtual PTypes GetType() const override;
	virtual ~PlayerRandom() override;
private:
	bool isTraining = false;
};

