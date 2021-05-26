#pragma once
#include <iostream>
#include <locale>
#include <thread>
#include <chrono>
#include <conio.h>
#include <string>
#include "global_const.h"
#include "global_flags.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__
//do some stuff for Apple
#elif __linux__
//do stuff for Linux
#endif

using namespace std;

namespace cnst {    
    inline void SetCodePageGerman() {
#if _USEQT == false
        // That causes massive kills, if done in Qt!
        locale loc = locale(cnst::codePageGerman);
        locale::global(loc);            // Umlaute
        cout.imbue(loc);                // Punkt zu Komma etc.
        cin.imbue(loc);                 // Das Selbe für die Eingabe.
#endif
    }


    inline void WaitForKeyPress() {
        _getch();  // WARNING - Correction
        cin.clear();

    }


    inline string GetInput(const string& text) {

        string input;

        cout << text << " ";
        getline(cin, input);
        return input;
    }


    /// <summary>
    /// Get a Random ID between 0 and (Count-1)
    /// </summary>
    /// <param name="itemsCount">Number of given Items.</param>
    /// <returns>The diced ID. Is '-1', if itemsCount was 0.</returns>
    inline int GetRandomIdForItemsCount(const unsigned int& itemsCount) {
        
        static bool wasOnceCalled = false;

        if (!wasOnceCalled) {
            srand((unsigned int)time(NULL)); 
            wasOnceCalled = true;
        }

        if (itemsCount < 1) {
            return -1;
        } else if (itemsCount == 1) {
            return 0;
        }
        else {
            return (rand() % itemsCount);
        }
    }


    inline void WaitSeconds(const double& seconds) {
        if (seconds == 0) { return; }
        this_thread::sleep_for(chrono::milliseconds((int)(seconds * 1000)));
    }


    inline void ClearScreen() {
        system("cls");
    }


    inline void ClearCache() {
        cin.clear();
        {
#pragma push_macro("max") // in conflict with num-size.
#undef max
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
#pragma pop_macro("max")
    }


    inline char GetChoosenValue(const string& text, const string& validInput, const char& abort) {

        string line = text;
        string choose = "";
        string validInputOrAbort = validInput;
        char result = '\0';
        for (size_t i = 0; i < validInput.size(); i++) {
            if (i > 0) {
                if (i < (validInput.size() - 1)) {
                    choose += ", ";
                }
                else {
                    choose += " oder ";
                }
            }
            choose += validInput.at(i);
        }
        line += " (" + choose + ")";
        if (abort != '\0') {
            line += " " + string(1, abort) + " für Abbruch: ";
            validInputOrAbort += string(1, abort);
        }
        else {
            line += ": ";
        }
        cout << line;

        bool inputIsValid = false;
        char input{};
        do {
            input = _getch();
            if (validInputOrAbort.find(input) != std::string::npos) {
                cout << input;
                result = input;
                inputIsValid = true;
            }
        } while (!inputIsValid);

        return result;
    }

    inline string FillNumberLeft(const int& number, const int& width = 3, const char& fillchar = ' ') {
        string str = to_string(number);
        return string(width - str.length(), fillchar) + str;
    }
#ifdef WIN32
    inline void GotoScreenPos(const SHORT& x, const SHORT& y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { x, y };
        SetConsoleCursorPosition(hConsole, pos);
    }
#elif __APPLE__
    inline void GotoScreenPos(const int& x, const int& y) {
        printf("%c[%d;%df", 0x1B, y, x);
}
#elif __linux__
    inline void GotoScreenPos(const int& x, const int& y) {
        printf("%c[%d;%df", 0x1B, y, x);
}
#endif

    inline void ReplaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr) {
        // Just Works from: https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string/5878802
        size_t pos = data.find(toSearch);
        while (pos != std::string::npos) {
            data.replace(pos, toSearch.size(), replaceStr);
            pos = data.find(toSearch, pos + replaceStr.size());
        }
    }

    inline string CharToHex(const unsigned char& c) {
        char rawBuffer[4]{};
        char resultBuffer[3]{};
        sprintf_s(rawBuffer, "0%X", (unsigned int)c);
        size_t count = strlen(rawBuffer);
        resultBuffer[0] = rawBuffer[count - 2];
        resultBuffer[1] = rawBuffer[count - 1];
        return string(resultBuffer);
    }


    inline string StringToHexString(const string& text) {
        string result = "";
        for (auto c : text) { result += CharToHex(c); }
        return result;
    }


    inline string HexStringToString(const string& hexText) {
        string strNumber{};
        string result{};
        char c{};
        if ((hexText.length() % 2) != 0) { return ""; }
        for (size_t i = 0; i < hexText.length(); i += 2) {
            strNumber = hexText.substr(i, 2);
            int i_hex = std::stoi(strNumber, nullptr, 16);
            c = (char)i_hex;
            result += c;
        }
        return result;
    }

}
