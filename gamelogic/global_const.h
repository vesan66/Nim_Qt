#pragma once

namespace cnst {
	//constexpr const char* codePageGerman{ "de_DE.UTF8" };
	constexpr const char* codePageGerman{ "de_DE.UTF8" };
	constexpr const char cancelChar{ 'X' };
	constexpr const char pauseChar{ 'p' };
    constexpr const char stepLoopChar{ 'e' };
    constexpr const char terminateChar{ 'T' };
    constexpr const char emptyChar{ '\0' };
    constexpr const char continueChar{ 'w' };


    // Info-Text
    constexpr const char* info_text_title{ "NIM-Spiel" };
    constexpr const char* info_text_line_1{ "Informationen zum Nim-Spiel unter: https://de.wikipedia.org/wiki/Nim-Spiel" };
    constexpr const char* info_text_line_2{ "Eine Implementierung des Nim-Spiels, wie es auf der Seite https://www.i-am.ai/build-your-own-ai.html beschrieben wird." };
    constexpr const char* info_text_line_3{ "Man kann in dieser Ausfühung zwei unterschiedlilche Strategien (Zufall / AI) gegeneinander spielen lassen und damit die 'Becher-KI' trainieren." };
    constexpr const char* info_text_line_4{ "Natürlich kann man auch selbst spielen." };

	constexpr const double prgVersion = 0.1;

	constexpr double waitAfterMove = 0.5;
	//constexpr double waitAfterMove = 1.5;
	constexpr double waitAfterWin = 1;	
	//constexpr double waitAfterWin = 3;


	constexpr int  mugKeyLength = 3;	

	constexpr int maxSessions = 200;
}
