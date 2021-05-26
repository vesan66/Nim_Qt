#include "Start.h"


Start& Start::menu() {
    static Start instance;
    return instance;
}


Start::Start() : _pGuiStart{ new GUIStart() } {
    SHOWC;
    Con::troller();
}


int Start::DisplayMenu() {
    char askResult = '\0';
   
    this->Initialize();

    CPlayers playerList = Confi::guration().GetCPlayers();

    do {

        CPlayer p1 = GetCPlayerByID(playerList, Confi::guration().PlayerOne());
        CPlayer p2 = GetCPlayerByID(playerList, Confi::guration().PlayerTwo());

        this->_pGuiStart->DrawPage(
            p1, p2,
            Confi::guration().NumberOfSessions(),
            Confi::guration().ClearMind()
        );

        askResult = this->AskForMenuSelect();
        
        // Start game
        if (askResult == '1') {
            Con::troller().StartGame();
        }
        // Ask for players
        if (askResult == '2') {
            this->AskForPlayers();
        }
        // Count of seesions.
        if (askResult == '3') {            
            this->AskForSessionCount();
        }
        // Ask for brain.
        if (askResult == '4') {
            this->AskForBrain();
        }
        // Display Matrix
        if (askResult == '5') {
            this->DisplayMatrix();
        }
    } while (askResult != cnst::cancelChar);
    
    return 0;
}


char Start::AskForMenuSelect() {
    string options{ "12345" };
    char result = this->_pGuiStart->AskForMainMenuInput(options, cnst::cancelChar);
    return result;
}


void Start::AskForSessionCount() {

    int current = Confi::guration().NumberOfSessions();
    int max = Confi::guration().MaxNumberOfSessions();

    int askResult = this->_pGuiStart->AskForSessionCount(current);

    if ((askResult > 0) && (askResult < max)) {
        Confi::guration().SetNumberOfSessions(askResult);
    }
}


void Start::AskForBrain() {

    bool current = Confi::guration().ClearMind();    
    char askResult = this->_pGuiStart->AskForBrain("jn",current);
    bool newValue = askResult == 'j' ? true : false;
    Confi::guration().SetClearMind(newValue);
}


void Start::DisplayMatrix() {
    
    CPlayers cPlayers = Confi::guration().GetCPlayers();

    PlayerList* pPlayerList = Confi::guration().GetPlayerList();
    if (pPlayerList == nullptr) { return; }
    
    this->_pGuiStart->ClearScreen();

    for (const auto item : *pPlayerList) {
        if (item != nullptr) {
            if (item->GetType() == Player::PTypes::machineAI) {
                CMugs brain = Con::troller().GetBrain(item, Confi::guration().MaxTake());
                CPlayer cPlayer = GetCPlayerByID(cPlayers, item->Id());
                this->_pGuiStart->DrawBrain(cPlayer, brain);                                
            }
        }
    }
    this->_pGuiStart->WaitForKey();

}



void Start::AskForPlayers() {

    CPlayers playerList = Confi::guration().GetCPlayers();

    string idList = this->_pGuiStart->DrawPlayerListGetIdList(playerList, 
        Confi::guration().PlayerOne(),
        Confi::guration().PlayerTwo());
    int askResultPlayerOne = this->_pGuiStart->AskForPlayerID(1, idList);    
    cnst::ReplaceAll(idList, to_string(askResultPlayerOne), "");
    Confi::guration().SetPlayerOne(askResultPlayerOne);

    this->_pGuiStart->DrawPlayerListGetIdList(playerList,
        Confi::guration().PlayerOne(),
        Confi::guration().PlayerTwo());
    int askResultPlayerTwo = this->_pGuiStart->AskForPlayerID(2, idList);
    Confi::guration().SetPlayerTwo(askResultPlayerTwo);
}


void Start::Initialize() {
    if (!_isInitialized) {
        
        // Touch the Config.
        Confi::guration();
        // Get the playerlist.
        PlayerPool::ExportPlayerList();

        // Enrich the AI-Players
        this->EnrichPlayerList();

        // Load the configuration
        Confi::guration().LoadFromFile();

        // Touch the Controller.
        Con::troller();

        this->_isInitialized = true;
    }
}


void Start::EnrichPlayerList() {
    CPlayers cPlayers = Confi::guration().GetCPlayers();

    PlayerList* pPlayerList = Confi::guration().GetPlayerList();
    if (pPlayerList == nullptr) { return; }

    Observer o;

    this->_pGuiStart->ClearScreen();

    for (const auto item : *pPlayerList) {
        if (item != nullptr) {
            if (item->GetType() == Player::PTypes::machineAI) {
                item->Initialize(o);                
            }
        }
    }
}


Start::~Start() {
    SHOWD;    
}


