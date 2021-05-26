#include "Confi.h"

Confi &Confi::guration() {
    static Confi instance;
    return instance;
}


string Confi::ClassNameXML() const {
    return Confi::ClassName();
}


string Confi::ClassName() {
    return "configuration";
}


void Confi::LoadFromFile() {
    this->LoadObjectFromSourceFile(this->_dPath, true);
}


void Confi::SaveToFile() {
    this->StoreObjectToSource(this->_dPath);
}


void Confi::SetCPlayers(PlayerList& list) {

    CPlayers pl{};

    for (auto item : list) {
        CPlayer dp{};
        dp.name = item->GetName();
        dp.type = item->GetType();
        dp.id = item->Id();
        pl.push_back(dp);
    }
    this->_cPlayers = pl;    
}


void Confi::SetAIPlayers(PlayerList& list) {

    this->_pPlayerList = new PlayerList();
    
    // Only hold the AI-Players.
    // The others will be deleted.
    for (auto item : list) {
        if (item->GetType() == Player::PTypes::machineAI) {
            this->_pPlayerList->push_back(item);
        }
        else {
            delete item;
        }
    }    
    list.clear();
}


Confi::~Confi() {
    SHOWD;    
    this->SaveToFile();
    if (this->_pPlayerList != nullptr) {
        while (this->_pPlayerList->size() != 0) {
            auto item = this->_pPlayerList->back();
            delete item;
            this->_pPlayerList->pop_back();
        }
    }
    delete this->_pPlayerList; this->_pPlayerList = nullptr;
}


Confi::Confi() {
    SHOWC;    
    this->SetNamespaceXML("https://dirk-scheidt.de");
    this->SetVersion("0.9");
}
