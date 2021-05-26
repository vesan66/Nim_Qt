#ifndef GUIPLAYGROUNDBASE_H
#define GUIPLAYGROUNDBASE_H
#include "globals_globals.h"
#include "Controller_structs.h"

class Con;

class GUIPlaygroundBase {
public:
    GUIPlaygroundBase();

    // Outputs
    virtual void Draw(Con*, const TChangeSet&) = 0;
    virtual void DrawPlayerSummary(const CPlayers&) = 0;

    // Inputs
    virtual char AskForMove(const string&, const string&, const char&);
    virtual char AskForContinue(const string&, const char&);
    virtual char GetCharOnTheRun();
    virtual void WaitForKeyAfterSession();

    // For Qt
    inline virtual bool UseSingleMagicCharChannel() { return false; };
    inline char MagicChar() { return _magicChar; }
    inline void SetMagicChar(const char& magicChar ) { _magicChar = magicChar; }

    // Signals to the Game
    virtual void StartGame();

    // Session
    virtual void PrepareNewSession() = 0;
    virtual void EndSession() = 0;

    virtual ~GUIPlaygroundBase() = 0;
private:
    char _magicChar{cnst::emptyChar};
};

#endif // GUIPLAYGROUNDBASE_H
