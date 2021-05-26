#include "MultimapKeyedTree.h"

namespace MMKT {
	MultimapKeyedTree::MultimapKeyedTree() : MultimapKeyedTree("") {
	}


	MultimapKeyedTree::MultimapKeyedTree(const TKeyStr& key) : MultimapKeyedTreeElement(nullptr, key) {
		SHOWC;
	}

}
