#include "MultimapKeyedTreeConnector.h"

namespace MMKT {


	MultimapKeyedTreeElement* MultimapKeyedTreeConnector::CreateNewChild(MultimapKeyedTreeElement* pParent, const MultimapKeyedTreeElement::TKeyStr& key) {
		MultimapKeyedTreeElement* pElement = new MultimapKeyedTreeElement(pParent, key);
		return pElement;
	}
}
