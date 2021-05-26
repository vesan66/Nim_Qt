#pragma once
#include "Player.h"
#include "Mugmap.h"
#include "global_exception.h"


class PlayerAI : public Player {
public:
	PlayerAI(const string& name) : Player(name), _pMM{ new Mugmap() } {};
	virtual PMoveResult Intelligence(Playground&, const Observer&, Move*) override;
	virtual PTypes GetType() const override;
	virtual ~PlayerAI() override;

	virtual void CleanupSessionAfterMath() override;
	virtual void Initialize(const Observer&) override;
	virtual void PrepareNewSession() override;

	virtual void IsTraining(const bool& isTraining);
	const Mugmap::Mugs* GetMugs() const;
	
private:
	bool _isTraining = true;
	//bool _isInitialized = false;
	Mugmap* _pMM = nullptr;		// I own.
};
