#pragma once
#include "LXMLRegMatcher.h"

namespace LXMLP { // => Light-XML-Parser
#if _DEBUG
	class LXMLRegMatcher_TestOutlet {
	public:
		
		inline bool RegExer(
			LXMLRegMatcher* instance,
			const string& pattern,
			string& text_IN_OUT,
			const size_t& expectedGroupMatcheCount,
			const bool& respectGroupMatcheCount,
			const bool& expectingFullMatch,
			const bool& removeFindings
		) {
			return instance->RegExer(
				pattern,
				text_IN_OUT,
				expectedGroupMatcheCount,
				respectGroupMatcheCount,
				expectingFullMatch,
				removeFindings
			);
		}


	};
#endif // _DEBUG
}