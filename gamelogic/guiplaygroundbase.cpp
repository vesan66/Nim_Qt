#ifndef GUIPLAYGROUNDBASE_CPP
#define GUIPLAYGROUNDBASE_CPP
#include "GUIPlaygroundBase.h"
#include "Controller.h"
#endif // GUIPLAYGROUNDBASE_CPP

GUIPlaygroundBase::GUIPlaygroundBase() {
    SHOWC;
}

char GUIPlaygroundBase::AskForMove(const string &, const string &, const char &) {
    return '\0';
}

char GUIPlaygroundBase::AskForContinue(const string &, const char &) {
    return '\0';
}

char GUIPlaygroundBase::GetCharOnTheRun() {
    return '\0';
}

void GUIPlaygroundBase::WaitForKeyAfterSession() {

}

void GUIPlaygroundBase::StartGame() {
    SHOWO;
    Con::troller().StartGame();
}

GUIPlaygroundBase::~GUIPlaygroundBase() {
    SHOWD;
}
