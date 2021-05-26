#pragma once
#include "Player.h"

class PlayerHuman : public Player {
public:
	PlayerHuman(const string& name) : Player(name) {};
	virtual PMoveResult Intelligence(Playground&, const Observer&, Move*) override;
	virtual PTypes GetType() const override;
	virtual ~PlayerHuman() override;
};

