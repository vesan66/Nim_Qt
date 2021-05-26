#pragma once
#include "../gamelogic/globals_globals.h"
#include "MultimapKeyedTreeElement.h"

namespace MMKT {
	class MultimapKeyedTreeConnector {
	public:
		friend class MultimapKeyedTreeElement;
		virtual MultimapKeyedTreeElement* CreateNewChild(MultimapKeyedTreeElement* pParent, const MultimapKeyedTreeElement::TKeyStr& key);
	protected:
		inline MultimapKeyedTreeConnector() { SHOWC; };
		inline virtual ~MultimapKeyedTreeConnector() { SHOWD; };
	};
}
