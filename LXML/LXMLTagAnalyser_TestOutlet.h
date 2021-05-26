#pragma once
#include "LXMLTagAnalyser.h"

namespace LXMLP { // => Light-XML-Parser
#if _DEBUG
	class LXMLTagAnalyser_TestOutlet {
	public:

		inline void SetKeyTag(LXMLTagAnalyser* instance, const TKeyTagStr& keyTag) { 
			instance->_keyTag = keyTag; 
		}

		inline bool ExplodeAttributes(LXMLTagAnalyser* instance, string& text) {
			return instance->ExplodeAttributes(text);
		}
	};
#endif // _DEBUG
}