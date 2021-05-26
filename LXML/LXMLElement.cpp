#include "LXMLElement.h"
#include "LXMLConnector.h"
#include "LXMLTypes.h"
#include "LXMLConsts.h"

using namespace MMKT;

namespace LXMLP { // => Light-XML-Parser


	LXMLElement::LXMLElement(LXMLElement* parent) : LXMLElement(parent, "") {}
	LXMLElement::LXMLElement(LXMLElement* parent, const TKeyStr& key) :
		MultimapKeyedTreeElement(parent, key),
		_pAttributes{ new TAttributes() } {
		SHOWC;
	}


	LXMLElement* LXMLElement::CreateNewChild() {
		return this->CreateNewChild("");
	}


	LXMLElement* LXMLElement::CreateNewChild(const TKeyStr& key) {		
		LXMLConnector* pCon =  static_cast<LXMLConnector*>(this->Connector());
		return pCon->CreateNewChild(this, key);
	}


	LXMLElement::ELXMLErrors LXMLElement::StateFromLoad() {
		LXMLElement::ELXMLErrors err = ELXMLErrors::Undefined;
		if (this->Parent() != nullptr) {
			LXMLElement* pParent = static_cast<LXMLElement*>(this->Parent());
			err = pParent->StateFromLoad();			
		}
		return err;
	}


	LXMLElement::ELXMLErrors LXMLElement::StateFromSave() {
		LXMLElement::ELXMLErrors err = ELXMLErrors::Undefined;
		if (this->Parent() != nullptr) {
			LXMLElement* pParent = static_cast<LXMLElement*>(this->Parent());
			err = pParent->StateFromSave();
		}
		return err;
	}


	LXMLElement::~LXMLElement() {
		SHOWD;
		if (_pAttributes != nullptr) { delete _pAttributes; _pAttributes = nullptr; }
	}

	MultimapKeyedTreeConnector* LXMLElement::CreateConnector() {
		return new LXMLConnector();
	}


  	bool LXMLElement::Parse(TXMLStr& text_IN_OUT) {
		LXMLConnector* pCon = static_cast<LXMLConnector*>(this->Connector());
		return pCon->Parse(this, text_IN_OUT);;
	}


	string LXMLElement::GetXMLNode() {
		string node = "";
		string content = GetXMLContent();
		string attributes = GenerateAttributesString();
		node += openSign + this->Key();
		node += attributes;
		if (content.empty()) {
			node += emptyCloseSign;
		}
		else {
			node += closeSign + content + closeUnEmptySign + this->Key() + closeSign;
		}
		return node;
	}


	string LXMLElement::GetXMLContent() const {
		string nodes = "";
		if (_hasChild == THasChild::eFalse) { 
			string value = _valueStr;
			//if (!value.empty()) {
			//	// At this point, the value must be encoded or not, cause this is set by the input.
			//	if (_encodeValue == EEncode::eBinHex) { 
			//		value = this->EncodeString(value);
			//	}  
			//}
			return value;
		}
		TMap* pMap = Childs();
		for (auto item : *pMap) {
			LXMLElement* e = dynamic_cast<LXMLElement*>(item.second);
			nodes += e->GetXMLNode();
		}
		return nodes;
	}


	string LXMLElement::EncodeString(const string& text) const {
		return StringToHexString(text);
	}


	string LXMLElement::DecodeString(const string& text) const {
		return HexStringToString(text);
	}


	LXMLElement* LXMLElement::GetElementByTagName(const TKeyTagStr& tagname) const {
		LXMLElement* result = nullptr;

		TMap* pChilds = this->Childs();
		auto iter = pChilds->find(tagname);
		if (iter == pChilds->end()) { return result; }
		result = static_cast<LXMLElement*>(iter->second);
		return result;
	}


	TValueStr LXMLElement::GetAttributeByName(const TAttributeStr& attributename) const {		
		TValueStr result = "";
		if (attributename.empty()) { return result; }
		if (_pAttributes == nullptr) { return result; }

		auto iter = _pAttributes->find(attributename);
		if (iter == _pAttributes->end()) { return result; }

		result = iter->second;

		return result;
	}


	string LXMLElement::GenerateAttributesString() const {
		string result = "";
		for (auto item : *_pAttributes) {
			result += " " + (string)item.first + "='" + (string)item.second + "'";
		}
		return result;
	}
}
