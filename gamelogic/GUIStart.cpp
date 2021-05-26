#include "GUIStart.h"


void GUIStart::DrawPage(const CPlayer& playerOne, const CPlayer& playerTwo,
	const int& noOfSessions, const bool& resetBrain) {
	this->ClearScreen();
	cnst::SetCodePageGerman();
	this->DrawInfo();
	this->DrawConfig(playerOne, playerTwo, noOfSessions, resetBrain);
	this->DrawMenu();	
}


void GUIStart::DrawMenu() {	
	cout << "1) Spiele-Set in aktueller Konfiguration starten." << endl;
	cout << "2) Spieler ändern." << endl;
	cout << "3) Anzahl der Runden ändern." << endl;
	cout << "4) Reset der KI nach jedem Spiele-Set ändern." << endl;
	cout << "5) Matrix der KIs anzeigen." << endl;
	cout << "x) Beenden" << endl;
	cout << endl;
}


void GUIStart::DrawInfo() {
    cout << cnst::info_text_title << endl;
	cout << endl;

    cout << cnst::info_text_line_1 << endl;
    cout << cnst::info_text_line_2 << endl;
    cout << cnst::info_text_line_3 << endl;
    cout << cnst::info_text_line_4 << endl;
	cout << endl;
}


void GUIStart::DrawConfig(const CPlayer& playerOne, const CPlayer& playerTwo,
	const int& noOfSessions, const bool& resetBrain) {

	string p1 = playerOne.name + " " + Player::PlayerTypeToString(playerOne.type);
	string p2 = playerTwo.name + " " + Player::PlayerTypeToString(playerTwo.type);

	cout << "Aktuelle Konfiguration" << endl;
	cout << " Spieler 1: " << p1 << endl;
	cout << " Spieler 2: " << p2 <<endl;
	cout << " Anzahl der Runden: " << noOfSessions << endl;
	string yesNo = resetBrain ? "ja" : "nein";
	cout << " KI nach jedem Spiele-Set zurücksetzen: " << yesNo << endl;
	cout << endl;
}

int GUIStart::AskForSessionCount(const int& current) {

	cout << endl;
	string question = "Anzahl der zu spielenden Runden (aktuell " + to_string(current) + ")?";
	string askresult = cnst::GetInput(question);
	int result = 0;
	try 	{
		result = stoi(askresult);
	}
	catch (const std::exception&) 	{
		result = 0;
	}

	return result;
}


char GUIStart::AskForBrain(const string& options, const bool& current) {

	string yesNo = current ? "ja" : "nein";
	cout << endl;

	string question = "Nach einer Session die KI zurücksetzen? (aktuell " + yesNo + ")?";
	char askresult = GetChoosenValue(question, options, '\0');

	return askresult;
}


int GUIStart::AskForPlayerID(const int& playerNumber, const string& options) {
	
	cout << endl;

	string question = "Spieler "+ to_string(playerNumber) +"?";
	char askresult = GetChoosenValue(question, options, '\0');

	int result = 0;
	try {
		result = atoi(&askresult);
	}
	catch (const std::exception&) {
		result = 0;
	}

	return result;
}


char GUIStart::AskForMainMenuInput(const string& options, const char& cancel) {

	string question = "Auswahl ";
	char result = GetChoosenValue(question, options, cancel);
	cout << endl;
	return result;
}

string GUIStart::DrawPlayerListGetIdList(const CPlayers& players, const int& currentP1, const int& currentP2) {
	
	ClearScreen();

	cout << "Spieler" << endl;
	string idList{};
	for (auto item : players) {

		cout << item.id << ") ";
		idList += to_string(item.id);
		cout << item.name << " ";

		cout << Player::PlayerTypeToString(item.type);

		if ((item.id == currentP1) || (item.id == currentP2)) {
			cout << " aktiv ";
		}

		cout << endl;
	}
	return idList;
}


void GUIStart::ClearScreen() {
	cnst::ClearScreen();
}


void GUIStart::DrawBrain(const CPlayer& player, const CMugs& cm) {
	cout << endl;
	cout << endl;
	cout << player.name << endl;
	cout << endl;
	cout << MakeBrain(cm);
	cout << endl;
}


string GUIStart::MakeBrain(const CMugs& cm) {
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


void GUIStart::WaitForKey() {
	cout << endl;
	cout << "Bitte Taste drücken, um zu schließen." << endl;
	cnst::WaitForKeyPress();
}

