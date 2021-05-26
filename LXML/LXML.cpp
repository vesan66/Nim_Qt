#include "LXML.h"

using namespace MMKT;
namespace LXMLP { // => Light-XML-Parser

	LXML::LXML() : LXML("") { }
	LXML::LXML(const TKeyStr& key) : LXMLElement(nullptr, key) { SHOWC; 	
	}


	string LXML::Sanitize(const string& text) {
		string newText = text;
		ReplaceAll(newText, "\n", "");
		ReplaceAll(newText, "\r", "");
		return newText;
	}


	bool LXML::Parse(TXMLStr& text_IN_OUT) {
		if (_ignoreMissingXMLHead == false) {
			if (ParseForHead(text_IN_OUT)) { 
				LXMLElement* pChild = this->CreateNewChild();				
				if (pChild->Parse(text_IN_OUT)) {
					this->AddElement(pChild);
					return true;
				}
			} else {
				return false;
			}
		}
		return LXMLElement::Parse(text_IN_OUT);		
	}

	
	bool LXML::ParseForHead(TXMLStr& text_IN_OUT) {		
		// Parse the XML-Header
		LXMLConnector* pCon = static_cast<LXMLConnector*>(this->Connector());
		bool result = pCon->GetXMLHead(this, text_IN_OUT);
		if (result) {
			InsertHeadAttributesIfNotPresent();

		}
		return result;
	}


	void LXML::InsertHeadAttributesIfNotPresent() {
		TAttributes::iterator pIter{};
		pIter = Attributes()->find(xmlHeadAttrVersion);
		if (pIter == Attributes()->end()) {
			Attributes()->insert({ xmlHeadAttrVersion, xmlHeadAttrVersionValue });
		}
		pIter = Attributes()->find(xmlHeadAttrStandalone);
		if (pIter == Attributes()->end()) {
			Attributes()->insert({ xmlHeadAttrStandalone, xmlHeadAttrStandaloneValue });
		}

		pIter = Attributes()->find(xmlHeadAttrEncoding);
		if (pIter == Attributes()->end()) {
			Attributes()->insert({ xmlHeadAttrEncoding, xmlHeadAttrEncodingValue });
		}
	}


	void LXML::SetStandalone(const bool& value) {
		string yn = (value == true) ? "yes" : "no";
		this->Attributes()->at(xmlHeadAttrStandalone) = yn;
	}


	void LXML::SetEncoding(const string& value) {		
		this->Attributes()->at(xmlHeadAttrEncoding) = value;
	}


	bool LXML::Parse(const TXMLStr& text) {
		this->_text = Sanitize(text);
		this->_changingText = this->_text;
		return Parse(_changingText);
	}


	bool LXML::Parse() {
		if (this->_text.empty()) { return false; }		
		this->_changingText = this->_text;
		return Parse(_changingText);
	}


	string LXMLP::LXML::GetXMLNode() {
		if (_dontCreateXMLHead) {
			return LXMLElement::GetXMLNode();
		}

		InsertHeadAttributesIfNotPresent();
		
		string attributes = GenerateAttributesHeadString();
		string text{};
		text += openSignXMLHead + attributes + closeSignXMLHead;
		auto elemIter = Childs()->begin();
		bool hasOne = elemIter != Childs()->end();
		if (hasOne) {
			LXMLElement* pChild = static_cast<LXMLElement*>(elemIter->second);
			if (pChild != nullptr) {
				text += pChild->GetXMLNode();
			}
		}
		return text;
	}


	bool LXMLP::LXML::LoadXMLFromFile(const string& filepath) {
		LXML::ELXMLErrors innerResult = ELXMLErrors::Undefined;
		return LoadXMLFromFile(filepath, innerResult);
	}


	bool LXML::LoadXMLFromFile(const string& filepath, LXML::ELXMLErrors& errorCode) {
		FileIO fio{};
		string text{};
		
		bool result = false;
		FileIO::EFileIOErrors loadResult = fio.LoadFromFile(filepath, text);
		errorCode = MapFileIOErrors(loadResult);
		this->_stateFromLoad = errorCode;
		result = (errorCode == LXML::ELXMLErrors::OK);
		if (result) {
			text = Sanitize(text);
			if (!text.empty()) {
				this->_text = text;
				result = true;
			}
		}
		return result;
	}


	bool LXMLP::LXML::SaveXMLToFile(const string& filepath) {
		LXML::ELXMLErrors innerResult = ELXMLErrors::Undefined;
		return SaveXMLToFile(filepath, innerResult);
	}


	bool LXML::SaveXMLToFile(const string& filepath, LXML::ELXMLErrors& errorCode) {
		bool result = false;
		FileIO fio{};
		string text = GetXMLNode();
		if (!text.empty()) {
			FileIO::EFileIOErrors saveResult = fio.SaveToFile(filepath, text);
			errorCode = MapFileIOErrors(saveResult);
			this->_stateFromSave = errorCode;
			result = (errorCode == LXML::ELXMLErrors::OK);
		}
		return result;
	}


	string LXML::GenerateAttributesHeadString() const {
		string result = "";
		TAttributes::iterator pIter{};		

		pIter = Attributes()->find(xmlHeadAttrVersion);
		if (pIter != Attributes()->end()) {
			result += " " + (string)pIter->first + "='" + (string)pIter->second + "'";
		}
		pIter = Attributes()->find(xmlHeadAttrEncoding);
		if (pIter != Attributes()->end()) {
			result += " " + (string)pIter->first + "='" + (string)pIter->second + "'";
		}
		pIter = Attributes()->find(xmlHeadAttrStandalone);
		if (pIter != Attributes()->end()) {
			result += " " + (string)pIter->first + "='" + (string)pIter->second + "'";
		}
		return result;
	}


	LXML::ELXMLErrors LXML::MapFileIOErrors(const FileIO::EFileIOErrors& fileIOError) {
		LXML::ELXMLErrors result = LXML::ELXMLErrors::Undefined;
		switch (fileIOError) {
		case  FileIO::EFileIOErrors::FileNotFound: {
			result = LXML::ELXMLErrors::FileNotFound;
			break;
		}
		case  FileIO::EFileIOErrors::ReadError: {
			result = LXML::ELXMLErrors::ReadError;
			break;
		}
		case  FileIO::EFileIOErrors::WriteError: {
			result = LXML::ELXMLErrors::WriteError;
			break;
		}
		case  FileIO::EFileIOErrors::UnableToOpenFileForReading: {
			result = LXML::ELXMLErrors::UnableToOpenFileForReading;
			break;
		}
		case  FileIO::EFileIOErrors::UnableToOpenFileFoSaving: {
			result = LXML::ELXMLErrors::UnableToOpenFileFoSaving;
			break;
		}
		case  FileIO::EFileIOErrors::MissingFilePath: {
			result = LXML::ELXMLErrors::MissingFilePath;
			break;
		}
		case  FileIO::EFileIOErrors::OK: {
			result = LXML::ELXMLErrors::OK;
			break;
		}
		default: { break; }
		}

		return result;
	}
}
