#pragma once
#include <iostream>
#include "globals_globals.h"
#include "GUIStart.h"
#include "Controller.h"
#include "Confi.h"
#include "Controller_structs.h"
#include "Observer.h"

using namespace std;
using namespace cnst;

class Start {
public:
    Start& operator= (const Start&) = delete;
    Start(const Start&) = delete;

    static Start& menu();

    int DisplayMenu();

    inline void InitializeOnly() { this->Initialize(); }

    ~Start();

private:
    GUIStart* _pGuiStart{};
    bool _isInitialized = false;

    Start();
    char AskForMenuSelect();
    void AskForSessionCount();
    void AskForBrain();
    void DisplayMatrix();
    void AskForPlayers();  
    void Initialize();
    void EnrichPlayerList();
};


