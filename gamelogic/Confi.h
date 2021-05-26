#pragma once
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "./globals_globals.h"
#include "./Observer.h"
#include "./Controller_structs.h"
#include "./PlayerPool.h"
#include "LXMLObjectMapper/LXMLObject.h"

using namespace std;
using namespace cnst;
using namespace LXMLObjects;

class Confi final : public LXMLObject {
public:
    Confi& operator= (const Confi&) = delete;
    Confi(const Confi&) = delete;

    static Confi& guration();

    inline int NumberOfSessions() {return _numberOfSessions;}
    inline void SetNumberOfSessions(const int& value) { _numberOfSessions = value;}

    inline int PlayerOne() { return _player1;}
    inline void SetPlayerOne(const int& value) { _player1 = value;}
    inline int PlayerTwo() { return _player2;}
    inline void SetPlayerTwo(const int& value) { _player2 = value;}

    inline bool ClearMind() {return _pClearMind;}
    inline void SetClearMind(const bool& value) {_pClearMind = value;}

    inline PlayerList* GetPlayerList() {return _pPlayerList;}
    
    void LoadFromFile();
    void SaveToFile();

    void SetCPlayers(PlayerList&);
    void SetAIPlayers(PlayerList&);
    inline CPlayers GetCPlayers() {return _cPlayers; }

    inline int MaxNumberOfSessions() { return _maxNumberOfSessions; }
    inline int MaxTake() { return _maxTake; }


    virtual string ClassNameXML() const override;
    static string ClassName();

    ~Confi();

protected:    
    inline virtual bool FillObjectFromSource(LXMLElement* pLXML) override {
        bool wasDefault = false;
        this->_pClearMind = this->GetBoolFromSource_Or_Default(pLXML, _kClearMind, _dClearMind, wasDefault);
        this->_numberOfSessions = this->GetIntFromSource_Or_Default(pLXML, _kNumberOfSessions, _dNumberOfSessions, wasDefault);
        this->_player1 = this->GetIntFromSource_Or_Default(pLXML, _kPlayer1, _dPlayer1, wasDefault);
        this->_player2 = this->GetIntFromSource_Or_Default(pLXML, _kPlayer2, _dPlayer2, wasDefault);
        return true;
    }


    inline virtual bool FillSourceFromObject(LXMLElement* pLXML) override {
        this->AddBoolNode(pLXML, _kClearMind, _pClearMind);
        this->AddIntegerNode(pLXML, _kNumberOfSessions, _numberOfSessions);
        this->AddIntegerNode(pLXML, _kPlayer1, _player1);
        this->AddIntegerNode(pLXML, _kPlayer2, _player2);
        return true;
    }
private:


    const string _dPath = "take.cfg";

    // The Keys for the Properties.
    const string _kStartWithAmount{ "StartWithAmount" };
    const string _kMinTake{ "MinTake" };
    const string _kMaxTake{ "MaxTake" };
    const string _kPlayerOrder{ "PlayerOrder" };
    const string _kWinner{ "Winner" };

    // On Persistence-Lane
    const string _kClearMind{ "clearmind" };
    const string _kNumberOfSessions{ "NumberOfSessions" };
    const string _kPlayer1{ "playerone" };
    const string _kPlayer2{ "playertwo" };
   

    // Default values.
    const int _dStartWithAmount = 10;
    const int _dMinTake = 1;
    const int _dMaxTake = 3;
    const Observer::PlayerOrder _dPlayerOrder = Observer::PlayerOrder::mixEveryRound;
    const Observer::Winner _dWinner = Observer::Winner::meansNothing;

    // On Persistence-Lane    
    const bool _dClearMind = false;
    const int _dNumberOfSessions = 73;    
    const int _dPlayer1 = 1;
    const int _dPlayer2 = 5;


    // Limits:
    const int _maxNumberOfSessions = cnst::maxSessions;
    const int _maxTake = _dMaxTake;

    // On Persistence-Lane
    bool _pClearMind = _dClearMind;
    int _numberOfSessions = _dNumberOfSessions;
    int _player1 = _dPlayer1;
    int _player2 = _dPlayer2;
    
    CPlayers _cPlayers{};

    PlayerList* _pPlayerList{ new PlayerList() };	// I own.

    Confi();

};
