#pragma once
#include <iostream>
#include <map>
#include <string>
#include "globals_globals.h"
#include "Mug.h"
#include "Player.h"

using namespace std;
using namespace cnst;


class Mugmap {
public:
	typedef pair<string, Mug*> MugPair;
	typedef map<MugPair::first_type, MugPair::second_type> Mugs;

	Mugmap() : _pMugs{ new Mugs() } {};

	// Map
	
	/// <summary>
	/// Setup the system.
	/// </summary>
	/// <param name="mugs">Equal to sticks.</param>
	/// <param name="maxpearls">Max to take</param>
	/// <returns>True, if this was the first call.</returns>
	bool SetupMugMap(const int&, const int&);	
	void AddItem(const int&, const int&);
	Mug* GetItemByMugNumber(const int& number);
	void ClearMugMap(const bool& = false);

	// Session
	inline void PrepareNewSession() {};
	void CleanupSessionAfterMath(const Player::PStates& state);
	void IsTraining(const bool& isTraining) { _isTraining = isTraining; }
	// Chain of moves
	void AddItemToChain(Mug*);
	inline Mug* LastMug() { return _pLastMug; }
	void CleanupChain();
	void LearnTheLession(const Player::PStates& state, bool& isChainModified);
	
	// The list
	inline const Mugs* GetMugs() const { return _pMugs; };

	~Mugmap();
private:	
	Mugs* _pMugs = nullptr;        // I own.
	Mug* _pLastMug = nullptr;
	bool _isTraining = false;
};

