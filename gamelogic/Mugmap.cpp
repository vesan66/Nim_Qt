#include "Mugmap.h"
#include "Player.h"
#include "Confi.h"

bool Mugmap::SetupMugMap(const int& mugs, const int& maxpearls) {
	if (_pMugs != nullptr) {
        if (_pMugs->size() > 0) {
            if (Confi::guration().ClearMind() == true) {
                return false;
            } else {
                return true;
            }
        }
	}

	int number = 1;
	int pearls = 0;
	while (number <= mugs) {
		pearls = min((number-1), maxpearls);
		this->AddItem(number, pearls);
		number++;
	}
	return true;
}


/// <summary>
/// Deletes the set of mugs. This is for ending the whole player.
/// </summary>
/// <param name="createNew">If true, an empty list will be created.</param>
void Mugmap::ClearMugMap(const bool& createNew) {
	if (_pMugs != nullptr) {
		while (_pMugs->size() != 0) {
			auto item = _pMugs->begin();
			Mug* elem = item->second;
			delete elem;
			_pMugs->erase(item);
		}
		delete _pMugs; _pMugs = nullptr;
		if (createNew) { _pMugs = new Mugs(); }
	}
}


/// <summary>
/// Resets the mugs for another game with this set.
/// Will do learnings in desired.
/// </summary>
/// <param name="state">Won, Lost, Undefined.</param>
void Mugmap::CleanupSessionAfterMath(const Player::PStates& state) {

	bool isChainModified = false;
	this->LearnTheLession(state, isChainModified);

	this->CleanupChain();
}


/// <summary>
/// Add a mug to the muglist.
/// </summary>
/// <param name="number">This is the key and stands for the number of present items at the playground.</param>
/// <param name="countOfPearls">Number of pearls to add to the mug.</param>
void Mugmap::AddItem(const int& number, const int& countOfPearls) {
	Mug* pM = new Mug(number, countOfPearls);
	_pMugs->insert(MugPair(pM->Key(), pM));
}


/// <summary>
/// Resets the chain of the moves.
/// </summary>
void Mugmap::CleanupChain() {
	if (_pLastMug != nullptr) {
		Mug* pItem = _pLastMug;
		Mug* pPrev = nullptr;
		do {
			pPrev = pItem->Previous();
			pItem->Previous(nullptr);
			pItem = pPrev;
		} while (pItem != nullptr);
		_pLastMug = nullptr;
	}
}


void Mugmap::LearnTheLession(const Player::PStates& state, bool& isChainModified) {

	isChainModified = false;
	if (_pLastMug != nullptr) {

		// Go the chain up.
		Mug* pItem = _pLastMug;		
		do {			
			// Learning.
			if (_isTraining == true) {
				if (state == Player::PStates::lost) {
					if (isChainModified == false) {
						if (pItem->CountOfPearlsInTheMug() != 0) {							
							pItem->DiscardElected();
							isChainModified = true;
						}
					}
				}
			}

			// Same same. Learning or not.
			if (pItem->ElectedPearl() > 0) { pItem->PushPearlBackToMug(); }

			// Get the previous item.
			pItem = pItem->Previous();

		} while (pItem != nullptr);		
		
	}
	return;
}



void Mugmap::AddItemToChain(Mug* pNewItem) {
	if (pNewItem == nullptr) { return; }
	Mug* pTemp = _pLastMug;
	_pLastMug = nullptr;
	pNewItem->Previous(pTemp);
	_pLastMug = pNewItem;
}


Mug* Mugmap::GetItemByMugNumber(const int& number) {
	string key = Mug::MakeKey(number);
	Mug* pM = nullptr;

	auto item = this->_pMugs->find(key);
	if (item != this->_pMugs->end()) {
		pM = item->second;
	}
	return pM;
}


Mugmap::~Mugmap() {
	SHOWD;
	this->ClearMugMap();
}



