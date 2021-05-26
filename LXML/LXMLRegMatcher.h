#pragma once
#include <iostream>
#include <regex>
#include <vector>
#include "../gamelogic/globals_globals.h"
#include "LXMLTypes.h"
#include "LXMLConsts.h"


namespace LXMLP { // => Light-XML-Parser

#if _DEBUG
	class LXMLRegMatcher_TestOutlet;
#endif // _DEBUG

	class LXMLRegMatcher {
	public:
#if _DEBUG
		friend class LXMLRegMatcher_TestOutlet;
#endif // _DEBUG

		inline LXMLRegMatcher() { SHOWC; };
		inline ~LXMLRegMatcher() { SHOWD; };

		//inline bool RegExer_FullMatch(const string& pattern, const string& text) {
		//	SHOWO;

		//	string localText = text;
		//	return RegExer(pattern, localText, 0, false, true, false);
		//}

		//inline bool RegExer_HaystackMatch(const string& pattern, const string& text) {
		//	SHOWO;

		//	string localText = text;
		//	return RegExer(pattern, localText, 0, false, false, false);
		//}

		inline TSimpleList SimpleResults() const { return _simpleResults; };

		bool RegExer_HaystackMatch_GroupMatchCount_Changing(
			const string& pattern,
			string& text_IN_OUT,
			const size_t& expectedGroupMatcheCount);

		bool RegExer_HaystackMatch_Changing(
			const string& pattern, 
			string& text_IN_OUT);

	protected:
		bool RegExer(
			const string& pattern, 
			string& text_IN_OUT,
			const size_t& expectedGroupMatcheCount,
			const bool& respectGroupMatcheCount,
			const bool& expectingFullMatch,
			const bool& removeFindings
		);
		
		
	private:
		TSimpleList	_simpleResults{};
	};
}
