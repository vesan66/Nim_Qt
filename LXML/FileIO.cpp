#include "FileIO.h"

namespace LXMLP { // => Light-XML-Parser



	FileIO::EFileIOErrors FileIO::LoadFromFile(const string& filePath, string& text_OUT) {

		FileIO::EFileIOErrors result = EFileIOErrors::undefined;
		
		if (filePath.empty()) { 
			result = EFileIOErrors::MissingFilePath;
			return result; 
		}

		result = FileExists(filePath);
		if (result != EFileIOErrors::OK) { return result; }

		text_OUT = "";
		ifstream is(filePath, ifstream::binary);
		if (is) {

			is.seekg(0, is.end);
			streamoff length = is.tellg();
			is.seekg(0, is.beg);

			char* buffer = new char[(unsigned int)length];

			// read data as a block:
			is.read(buffer, length);

			if (!is) {
				//string errMsg = "error: only " + std::to_string(is.gcount()) + " could be read";
				//throw exception(errMsg.c_str());
				return EFileIOErrors::ReadError;
			}

			text_OUT = string(buffer, (size_t)length);
			is.close();			
			delete[] buffer;
			return EFileIOErrors::OK;
		}
		else {
			result = EFileIOErrors::UnableToOpenFileForReading;
		}
		return result;
	}


	FileIO::EFileIOErrors FileIO::FileExists(const string& filePath) {
		fstream fIn;

		if (filePath.empty()) {			
			return EFileIOErrors::MissingFilePath;;
		}

		fIn.open(filePath, ios_base::in | ios_base::binary);
		if (fIn.is_open()) {
			fIn.close();
			return EFileIOErrors::OK;
		}
		return EFileIOErrors::FileNotFound;
	}


	FileIO::EFileIOErrors FileIO::SaveToFile(const string& filePath, const string& text) {

		FileIO::EFileIOErrors result = EFileIOErrors::undefined;

		if (filePath.empty()) {
			result = EFileIOErrors::MissingFilePath;
			return result;
		}

		fstream fOut;

		fOut.open(filePath, ios_base::out | ios_base::binary);
		if (!fOut.is_open()) {
			//string errMsg = "Not possible to write to file: " + filePath;
			//throw exception(errMsg.c_str());
			result = EFileIOErrors::UnableToOpenFileFoSaving;
			return result;
		}

		fOut << text;
		fOut.close();

		result = EFileIOErrors::OK;

		return result;
	}


	bool FileIO::TouchFile(const string& filePath) {
		if (filePath.empty()) return false;

		fstream f;
		f.open(filePath, ios_base::in);
		if (f.is_open()) {
			f.close();
			return true;
		}

		ofstream output(filePath);
		if (output.is_open()) {
			output.flush();
			output.close();
			return true;
		}
		return false;
	}


}
