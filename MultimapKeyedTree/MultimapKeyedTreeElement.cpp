#include "MultimapKeyedTreeElement.h"
#include "MultimapKeyedTreeConnector.h"

namespace MMKT {
	MultimapKeyedTreeElement::MultimapKeyedTreeElement(MultimapKeyedTreeElement* pParent) :
		MultimapKeyedTreeElement(pParent, "") {
	};


	MultimapKeyedTreeElement::MultimapKeyedTreeElement(MultimapKeyedTreeElement* pParent, const TKeyStr& key) :
		_pParent{ pParent },
		_pConnector{ nullptr },			// Will be set on the getter!
		_pMap{ new TMap() },
		_key{ key },
		_wasInserted{ false } {
		SHOWC;

		// Klar:	Im Konstruktor werden keine Child-Überschreibungen aufgerufen.
        //			Die gibt es naemlich noch gar nicht.
		//_pConnector = CreateConnector();
	}


	MultimapKeyedTreeElement::~MultimapKeyedTreeElement() {
		SHOWD;
		if (_pMap != nullptr) {
			while (_pMap->empty() == false) {
				auto item = _pMap->begin();
				MultimapKeyedTreeElement* content = item->second;
				if (content != nullptr) { delete content; content = nullptr; }
				_pMap->erase(item);
			}
			_pMap->clear();
			delete _pMap; _pMap = nullptr;
		}

		if (_pConnector != nullptr) { 
			delete _pConnector; _pConnector = nullptr; }
		if (_pParent != nullptr) { _pParent = nullptr; }
	}

	MultimapKeyedTreeConnector* MultimapKeyedTreeElement::CreateConnector() {
		return new MultimapKeyedTreeConnector();
	}


	MultimapKeyedTreeElement* MultimapKeyedTreeElement::CreateNewChild() {
		return this->CreateNewChild("");
	}


	MultimapKeyedTreeElement* MultimapKeyedTreeElement::CreateNewChild(const TKeyStr& key) {
		return this->Connector()->CreateNewChild(this, key);
	}


	bool MultimapKeyedTreeElement::AddElement(MultimapKeyedTreeElement* element) {
		if (element == nullptr) { return false; }
		TKeyStr key = element->Key();
		if (key.empty()) { return false; }
		MultimapKeyedTreeElement* pP = element->Parent();
		if (pP == nullptr) { return false; }
		
		// TODO: Check this!
		//if (typeid(*pP) != typeid((*this)) ) { return false; }
		if (pP != this) { return false; }

		if (element->WasInserted()) { return false; }
		this->_pMap->insert(TItem(key, element));
		element->SetWasInserted();
		return true;
	}
}
