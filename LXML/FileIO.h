#pragma once
#include "../gamelogic/globals_globals.h"
#include <fstream>

using namespace std;

namespace LXMLP { // => Light-XML-Parser

	class FileIO {
	public:
		enum class EFileIOErrors: int { 
			OK = 1, 
			FileNotFound = 2, 
			ReadError = 3, 
			WriteError = 4, 
			undefined = 5, 
			UnableToOpenFileForReading = 6, 
			UnableToOpenFileFoSaving = 7,
			MissingFilePath = 8
		};
		EFileIOErrors LoadFromFile(const string& filePath, string& text_OUT);
		EFileIOErrors FileExists(const string& filePath);
		EFileIOErrors SaveToFile(const string& filePath, const string& text);
		bool TouchFile(const string& filePath);
	};
}
