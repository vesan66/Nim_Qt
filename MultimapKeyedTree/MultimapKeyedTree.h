#pragma once
#include "../gamelogic/globals_globals.h"
#include "MultimapKeyedTreeElement.h"


namespace MMKT {
	class MultimapKeyedTree : public MultimapKeyedTreeElement {
	public:
		// Constructors
		explicit MultimapKeyedTree();
		explicit MultimapKeyedTree(const TKeyStr& key);

		// Destructor
		inline virtual ~MultimapKeyedTree() override { 
			SHOWD; };
	};
}
