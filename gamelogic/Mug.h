#pragma once
#include <iostream>
#include <set>
#include <string>
#include "globals_globals.h"

using namespace std;

/// <summary>
/// This class is a Mug with the possilble moves.
/// </summary>
class Mug final {
public:
	typedef int Pearl;
	typedef set<Pearl> PearlSet;

	Mug() = delete;

	/// <summary>
	/// Setup a mug with n Elements
	/// </summary>
	/// <param name="mugnumber"></param>
	/// <param name="countOfPearls"></param>
	Mug(const int&, const int&, Mug* = nullptr);

	/// <summary>
	/// Pull one pearl and put it aside.
	/// </summary>
	/// <returns>true if OK.</returns>
	bool PullARandomPearl();

	/// <summary>
	/// Lay the pearl back to the mug.
	/// </summary>
	/// <returns>true if OK.</returns>
	bool PushPearlBackToMug();

	/// <summary>
	/// Discard the pearl, which was layed aside.
	/// E.g. there are one pearl less.
	/// </summary>
	/// <returns>true if OK.</returns>
	bool DiscardElected();

	/// <summary>
	/// Count the pearls in the mug.
	/// </summary>
	/// <returns>Number</returns>
	inline int CountOfPearlsInTheMug() const { return _pMug->size(); }

	inline string Key() const { return Mug::MakeKey(_number); }
	inline int NumberOfKey() const { return _number; }

	inline static string MakeKey(const int& number) { 
		return "k_" + cnst::FillNumberLeft(number, cnst::mugKeyLength, '0');
	}

	//inline void Pearl(const int& move) { this->_move = move; };
	inline int ElectedPearl() const { return this->_pearl; };
	bool PullAPearl(const Pearl& pearl);
	int ElectAPearl(const unsigned int&);
	inline bool PearlIsInMug(const Pearl& pearl) const {
		return (this->_pMug->find(pearl) != this->_pMug->end());
	}
	
	inline const PearlSet* GetPearls() const { return _pMug; };

	// Navigation
	inline Mug* Previous() const { return _pPrevious; }
	inline void Previous(Mug* item) { _pPrevious = item; }

	//inline Mug* Next() const { return _pNext; }
	//inline void Next(Mug* item) { _pNext = item; }

	// Visualization
	string GetDispalyString();

	~Mug();

private:
	
	PearlSet* _pMug = { nullptr };		// I own;
	Pearl _pearl = 0;
	const int _number = 0;
	Mug* _pPrevious = { nullptr };
	//Mug* _pNext = { nullptr };
};

