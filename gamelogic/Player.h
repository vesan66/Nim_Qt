#pragma once
#include <iostream>
#include "Playground.h"
#include "Move.h"
#include "global_exception.h"

using namespace std;

class Observer; // Foreward declaration.

class Player {
public:
	enum class PStates { won, lost, undefined };
	enum class PTypes { human, machineRnd, machineAI, undefined };
    enum class PMoveResult { OK, cancel, pass, error, undefined, terminateALL };

	Player() = delete;
	virtual void Initialize(const Observer&);
	virtual void PrepareNewSession();
	virtual PMoveResult Intelligence(Playground&, const Observer&, Move*);
	virtual void CleanupSessionAfterMath();
	virtual PTypes GetType() const;
	
    static Player* CreateNewPlayer(const string&, const Player::PTypes&, const int&);

	static string PlayerTypeToString(PTypes type);
	PMoveResult Play(Playground&, const Observer&);

	string GetName() const { return this->name; };
	PStates GetState() const { return this->state; };
	void SetState(const PStates& state) { this->state = state; };
    inline int Id() const { return _id; }
    inline void SetId(const int& value) { _id = value; }
	inline int GetSessionsPlayed() const { return this->sessionsPlayed; }
	inline int GetSessionsWon() const { return this->sessionsWon; }
	inline int GetSessionsLost() const { return this->sessionsLost; }
	inline int GetSessionsUndefined() const { return this->sessionsUndefined; }
    void ClearSessionPlayedWonEtc();
	virtual ~Player();

protected:
	Player(const string& name) : name{ name } {};
	Moves* pMoves{ new Moves() };	// I own.
	void UnloadOldMoves();

private:
	string name{};
	PStates state{ PStates::undefined };
    int _id = 0;
	int sessionsPlayed = 0;
	int sessionsWon = 0;
	int sessionsLost = 0;
	int sessionsUndefined = 0;
};
