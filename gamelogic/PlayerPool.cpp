#include "PlayerPool.h"
#include "Confi.h"
#include "PlayerAI.h"
PlayerPool::PlayerPool() {
}


void PlayerPool::SetupDefaultPlayerList() {

    bool clearMind = Confi::guration().ClearMind();
    PlayerList* pL = Confi::guration().GetPlayerList();

    int id = 0;
    bool added = false;
    for(int i = 0; i<2 ; i++){
        added = false;
        if (i == 0) {
            id = Confi::guration().PlayerOne();
        }
        if (i == 1) {
            id = Confi::guration().PlayerTwo();
        }
        if (pL != nullptr) {
            if (clearMind == false) {
                for(Player* pStoredItem: *pL) {
                    if ( id == pStoredItem->Id()) {
                        pStoredItem->ClearSessionPlayedWonEtc();
                        this->AddPlayer(pStoredItem);
                        added = true;
                    }
                }
            }
        }
        if (added == false) {
            switch (id) {
            case 1: {this->AddPlayer("Rudolf", Player::PTypes::machineRnd, 1); break;}
            case 2: {this->AddPlayer("Richard", Player::PTypes::machineRnd, 2);break;}
            case 3: {this->AddPlayer("Zebra", Player::PTypes::human, 3);break;}
            case 4: {this->AddPlayer("Gnu", Player::PTypes::human, 4);break;}
            case 5: {this->AddPlayer("Alice", Player::PTypes::machineAI, 5);break;}
            case 6: {this->AddPlayer("Anja", Player::PTypes::machineAI, 6);break;}
            default: {break;}
            }
        }

    }
}

/// <summary>
/// This method is static and a kind of config-list for setup.
/// </summary>
void PlayerPool::ExportPlayerList(){
    PlayerList pl{};
    Player* pP{};

    pP = Player::CreateNewPlayer("Rudolf", Player::PTypes::machineRnd, 1);
    pl.push_back(pP);
    pP = Player::CreateNewPlayer("Richard", Player::PTypes::machineRnd, 2);
    pl.push_back(pP);
    pP = Player::CreateNewPlayer("Zebra", Player::PTypes::human, 3);
    pl.push_back(pP);
    pP = Player::CreateNewPlayer("Gnu", Player::PTypes::human, 4);
    pl.push_back(pP);
    pP = Player::CreateNewPlayer("Alice", Player::PTypes::machineAI, 5);
    pl.push_back(pP);
    pP = Player::CreateNewPlayer("Anja", Player::PTypes::machineAI, 6);
    pl.push_back(pP);

    Confi::guration().SetCPlayers(pl);    
    Confi::guration().SetAIPlayers(pl);
};


void PlayerPool::AddPlayer(const string& name, const Player::PTypes& pType, const int& id) {
    Player* pP = Player::CreateNewPlayer(name, pType, id);
    //this->pPlayerList->push_back(pP);
    this->AddPlayer(pP);
}


void PlayerPool::AddPlayer(Player* pPlayer) {
    this->pPlayerList->push_back(pPlayer);
}


void PlayerPool::PrepareNewSession() {
	for (auto item : *(this->pPlayerList)) {
		item->PrepareNewSession();
	}
}


void PlayerPool::InitializePlayers(const Observer& observer) {
	if (this->pPlayerList != nullptr) {
		for (auto item : *this->pPlayerList) {
			if (item != nullptr) {
				item->Initialize(observer);
			}
		}
	}
}


void PlayerPool::CleanupSessionAfterMath() {
	for (auto item : *pPlayerList) {
		item->CleanupSessionAfterMath();
    }
}


Player* PlayerPool::GetPlayerByID(PlayerList* pPlayerList, const int& id) {
    Player* result = nullptr;
    if (pPlayerList == nullptr) { return result; }

    for (const auto item : *pPlayerList) {
        if (item != nullptr) {
            if (item->Id() == id) {
                result = item;
                break;
            }
        }
    }
    return result;
}


bool PlayerPool::EraseByID(PlayerList* pPlayerList, const int& id) {
    bool result = false;
    if (pPlayerList == nullptr) { return result; }

    for (PlayerList::iterator iter = pPlayerList->begin(); iter != pPlayerList->end(); iter++) {
        Player* pItem = static_cast<Player*>(*iter);
        if (pItem != nullptr) {
            if (pItem->Id() == id) {
                pPlayerList->erase(iter);
                delete pItem; pItem = nullptr;
                result = true;
                break;
            }
        }
    }

    return result;
}


PlayerPool::~PlayerPool() {
	SHOWD;
	if (this->pPlayerList != nullptr) {
        // Bring the AI away.
        PlayerList* pList = Confi::guration().GetPlayerList();
        if (pList == nullptr) { return; }

		while (this->pPlayerList->size() != 0) {
            Player* item = this->pPlayerList->back();
            if (typeid(*item) == typeid (PlayerAI)) {
                Player* candidate = GetPlayerByID(pList, item->Id());
                if (candidate != nullptr) {
                    if (item != candidate) {
                        // Remove the item.
                        EraseByID(pList, item->Id());
                        // Add the new one
                        pList->push_back(item);
                    }                     
                } else {
                    pList->push_back(item);
                }
            } else {
                delete item;
            }
			this->pPlayerList->pop_back();
		}
	}
	delete this->pPlayerList; this->pPlayerList = nullptr;
}
