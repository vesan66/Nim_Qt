#include "LXMLConnector.h"
#include "LXMLElement.h"
#include "LXMLTagAnalyser.h"

using namespace MMKT;
namespace LXMLP { // => Light-XML-Parser

	LXMLElement* LXMLConnector::CreateNewChild(LXMLElement* pParent, const MultimapKeyedTreeElement::TKeyStr& key) {
		LXMLElement* pElement = new LXMLElement(pParent, key);
		return pElement;
	}


    bool LXMLConnector::Parse(LXMLElement* parent, TXMLStr& text_IN_OUT) {
        LXMLTagAnalyser* pLVTA = new LXMLTagAnalyser();
        bool result = pLVTA->Parse(parent, text_IN_OUT);
        if (result == true) {
            TAttributes atr = pLVTA->Attributes();
            parent->Attributes()->insert(atr.begin(), atr.end());
            parent->_hasChild = pLVTA->HasChild();
            parent->_tagIsClosed = pLVTA->TagIsClosed();
            parent->_valueStr = pLVTA->ValueStr();
        }
        delete pLVTA; pLVTA = nullptr;
        return result;
    }


    bool LXMLConnector::GetXMLHead(LXMLElement* parent, TXMLStr& text_IN_OUT) {
        LXMLTagAnalyser* pLVTA = new LXMLTagAnalyser();
        bool result = pLVTA->GetXMLHead(text_IN_OUT);
        if (result == true) {
            TAttributes atr = pLVTA->Attributes();
            parent->Attributes()->insert(atr.begin(), atr.end());
            parent->_hasChild = pLVTA->HasChild();
            parent->_tagIsClosed = pLVTA->TagIsClosed();
        }
        delete pLVTA; pLVTA = nullptr;
        return result;
    }


}
