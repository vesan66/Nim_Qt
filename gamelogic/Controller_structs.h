#pragma once
#include "Player.h"
#include <vector>
#include <set>
#ifndef CONTROLLER_STRUCTS_H
#define CONTROLLER_STRUCTS_H

// Remember: TChangeSet Con::EverythingWasChanged() const {
enum class EWhatWasChanged: int { all = 99,
                                  nothing = 0,
                                  playground = 1,
                                  playedPlayground = 2,
                                  playerList = 3,
                                  sessionsPlayed = 4,
                                  brainBefore = 5,
                                  brainAfter = 6,
                                  winnerSet = 7,
                                  looserSet = 8,
                                  loopStateChange = 9,
                                  ALL_WAS_SET_Automatic = 200
                                };

using TChangeSet = set<EWhatWasChanged>;


//enum class EWhatEvent: int { nothing = 0,
//                             endSession = 1,
//                             beginNewSession = 2
//                            };




struct CPlayer {
    int id = 0;
    string name = "";
    Player::PTypes type = Player::PTypes::undefined;
    bool isActive = false;
    int sessionsPlayed = 0;
    int sessionsWon = 0;
    int sessionsLost = 0;
    int sessionsUndefined = 0;
};
using CPlayers = vector<CPlayer>;

inline CPlayer GetCPlayerByID(CPlayers playerList, const int& id) {
    CPlayer result{};
    for (auto const item : playerList) {
        if (item.id == id) {
            result = item;
            break;
        }
    }
    return result;
}




struct CMove {
    string name = "";    
    int sticks = 0;
};
using CMoves = vector<CMove>;


struct CSessions {
    int sessionsPlayed = 0;
    int sessionsToPlay = 0;
};


struct CPearl {
    int number;
};
using CPearls = vector<CPearl>;


struct CMug {
    int number;
    int choosen;
    CPearls pearls;
};
using CMugs = vector<CMug>;

#endif // CONTROLLER_STRUCTS_H
