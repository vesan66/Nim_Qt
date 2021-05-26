//#pragma once // WARNING - Correction
#include "GUI.h"
#include "Controller.h"



GUI::GUI() {
    SHOWC;
    cnst::SetCodePageGerman();
	cnst::ClearScreen();
    this->pMt = new Mousetrap();
}

GUI::~GUI() {
	SHOWD;
	delete this->pMt; this->pMt = nullptr;
}


void GUI::Draw(Con* d, const TChangeSet&) {
	this->DrawAll(d);
}


void GUI::DrawAll(Con* d) {
    cnst::ClearScreen();
    this->DrawSessionsToPlay(d->GetSessions());
    this->DrawPlayerList(d->GetPlayerList(), d->IsMultiSession());
    cout << endl << endl;

    this->DrawPlayground(d->GetPlayground());
    this->DrawPlayedPlayground(d->GetPlayedPlayground());
    cout << endl;
    this->DrawPlayerComment(d->GetMoveDone());
    this->DrawBrainBefore(d->GetBraineBefore());
    this->DrawBrainAfter(d->GetBraineAfter());

    if (!d->GetWinner().empty()) {
        cout << endl;
        this->DrawWinner(d->GetWinner());
        this->DrawLooser(d->GetLooser());
        cout << endl;
    }
    else {
        cout << endl;
        this->GameWasCanceled(d->GetGameWasCanceled());
    }

    if (this->sessionIsOver == false) {
        cout << endl;
        this->DrawLoopState(*d);
        cout << endl;
    }

    this->DrawMoves(d->GetMoves());
    this->DrawLastMove(d->GetMoveDone());


    cout << endl;

}

char GUI::AskForMove(const string& name, const string& options, const char& cancel) {
	string question = name + ": Wieviele Elemente nehmen";	
	
	// Set position
	GotoScreenPos(0, 7);
	
	// Ask.
	this->pMt->SetSkipDetection(true);

	char result = GetChoosenValue(question, options, cancel);

	this->pMt->SetSkipDetection(false);
	return result;
}


char GUI::AskForContinue(const string& options, const char& cancel) {

	string question = "Spiel pausiert:\n (" + options.substr(0, 1) + ")alles abbrechen (" + options.substr(1, 1) + ")Weiter, (" + options.substr(2, 1) + ")Einzelspiel oder (" + options.substr(3, 1) + ")dieses Spiel abbrechen.";

	// Ask.
	this->pMt->SetSkipDetection(true);
	
	char result = GetChoosenValue(question, options, cancel);

	this->pMt->SetSkipDetection(false);
	return result;
}


char GUI::GetCharOnTheRun() {
	char result = this->pMt->GetReceivedChar();
	this->pMt->ConsumeReceivedChar();
	return result;
}


void GUI::WaitForKeyAfterSession() {
	cout << "Spiel beendet. Weiter mit Taste. ";
    WaitForKeyPress();
}


void GUI::PrepareNewSession() {
	this->sessionIsOver = false;
	this->pMt->StartTrap();
}


void GUI::EndSession() {
	this->pMt->TerminateTrap();
	this->sessionIsOver = true;	
}


void GUI::DrawPlayerList(const CPlayers& players, const bool& isMultiSession) {

	cout << "Spieler" << endl;

	for (auto item : players) {
		if (item.isActive) {
			cout << "*** ";
		} else {
			cout << "    ";
		}

		cout << item.name << " ";

		cout << Player::PlayerTypeToString(item.type);

		// Won Lost
		if (isMultiSession == true) {
			cout << " [ " << item.sessionsWon << " / " << item.sessionsLost << " ] ";
		}

		if (item.isActive) {
			cout << "*** ";
		}
		else {
			cout << "    ";
		}

		cout << "    ";

	}
}


void GUI::DrawPlayerSummary(const CPlayers& players) {

	cout << "Spieler Zusammenfassung:" << endl;

	for (auto item : players) {

		// Won Lost		
		cout << " [ " << item.sessionsWon << " / " << item.sessionsLost << " / " << item.sessionsUndefined << " ] ";

		cout << item.name << " ";

		switch (item.type) {
		case Player::PTypes::human: { cout << "[HU] "; break; }
		case Player::PTypes::machineAI: { cout << "[AI] "; break; }
		case Player::PTypes::machineRnd: { cout << "[RN] "; break; }
		default: { cout << "[UD] "; break; }
		}
		
		cout << endl;
	}
	cout << endl;
}


void GUI::DrawPlayground(const int& sticks) {
	cout << "Spielfeld" << endl;
	this->DrawRawPlayground(sticks);
}


void GUI::DrawRawPlayground(const int& sticks) {
	for (int i = 1; i <= sticks; i++) {
		cout << " " << i;
	}
	cout << endl;
}


void GUI::DrawPlayedPlayground(const int& sticks) {
	this->DrawRawPlayground(sticks);
}


void GUI::DrawMoves(const CMoves& moves) {
	cout << "Zuege" << endl;
	for (auto item : moves) {
		this->DrawMove(item);
	}
}


void GUI::DrawWinner(const string& name) {
	if (name.empty()) { return; }
	cout << "  *** " << name << " *** hat gewonnen." << endl;
}


void GUI::DrawLooser(const string& name) {
	if (name.empty()) { return; }
	cout << "  --- " << name << " --- hat verloren." << endl;
}


void GUI::DrawMove(const CMove& item) {
	cout.width(12);
	cout << left << item.name;
	cout.width(4);
	cout << left << item.sticks;
	cout << endl;
}


void GUI::DrawLastMove(const CMove& item) {
	if (item.name.empty()) { return; }
	this->DrawMove(item);
}


void GUI::DrawPlayerComment(const CMove& md) {
	if (md.name.empty()) { cout << endl; return; }
	cout << md.name << " nimmt " << md.sticks << "." <<endl;
}


void GUI::DrawSessionsToPlay(const CSessions& s) {
	if (s.sessionsToPlay <= 1) { return; }
	cout << "Spiel " << (s.sessionsPlayed + 1) << " von " << s.sessionsToPlay << endl;
	cout << endl;
}


string GUI::MakeBrain(const CMugs& cm) {
	string mugTxt = "";

	for (auto mug : cm) {
		mugTxt += FillNumberLeft(mug.number, cnst::mugKeyLength, ' ');
		mugTxt += "[";
		for (auto pearl : mug.pearls) {
			mugTxt += (pearl.number == -1) ? " " : to_string(pearl.number);
		}
		mugTxt += "](";
		mugTxt += mug.choosen != 0 ? to_string(mug.choosen) : " ";
		mugTxt += ") ";
		if ((mug.number == 10) && (mug.choosen == 1)) {
			cout << "";
		}
	}

	return mugTxt;
}


void GUI::DrawBrainBefore(const CMugs& cm) {
	cout << "" << this->MakeBrain(cm) << endl;
}


void GUI::DrawBrainAfter(const CMugs& cm) {
	cout << "" << this->MakeBrain(cm) << endl;
}


void GUI::DrawLoopState(const Con& d) {

	Con::CLoopStates current = d.GetLoopState();

	switch (current) {
	
	case Con::CLoopStates::stepRunning:
		this->pMt->SetSkipDetection(true);
		break;
	case Con::CLoopStates::running:
		cout << "--- 'p' für Pause ---" << endl;
		this->pMt->SetSkipDetection(false);
		break;

	case Con::CLoopStates::paused:
		this->pMt->SetSkipDetection(true);
		break;
	
	case Con::CLoopStates::otherInput:
		this->pMt->SetSkipDetection(true);
		break;

	case Con::CLoopStates::undefined:
		this->pMt->SetSkipDetection(true);
		break;

	default:
		// nothing to do.
		break;
		}
}


void GUI::GameWasCanceled(const bool& value) {
	if (!value) { return; }
	cout << "Spiel wurde abgebrochen." << endl;
}
