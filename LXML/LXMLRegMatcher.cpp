#include "LXMLRegMatcher.h"


namespace LXMLP { // => Light-XML-Parser
	bool LXMLRegMatcher::RegExer_HaystackMatch_Changing(const string& pattern, string& text_IN_OUT) {
		SHOWO;

		return RegExer(pattern, text_IN_OUT, 0, false, false, true);
	}


	bool LXMLRegMatcher::RegExer_HaystackMatch_GroupMatchCount_Changing(
		const string& pattern,
		string& text_IN_OUT,
		const size_t& expectedGroupMatcheCount) {
		SHOWO;

		return RegExer(pattern, text_IN_OUT, expectedGroupMatcheCount, true, false, true);
	}


	bool LXMLRegMatcher::RegExer(const string& pattern, string& text_IN_OUT,
		const size_t& expectedGroupMatcheCount,
		const bool& respectGroupMatcheCount,
		const bool& expectingFullMatch,
		const bool& removeFindings) {
		SHOWO;

		_simpleResults.clear();
		smatch matchList = smatch();
		regex regexPattern = regex(pattern);

		// Check, if it is a full match: regex_match
		if (expectingFullMatch) {
			bool fullMatch = regex_match(text_IN_OUT, regexPattern);
			if (fullMatch == false) {								
				SHOWOMessage(": Failed: Full match expected!");
				SHOWOMessage("pattern: " + pattern);				
				SHOWOMessage("text_IN_OUT: \n" + text_IN_OUT);
				return false;
			}
		}

		// Search for the parts: regex_search
		regex_search(text_IN_OUT, matchList, regexPattern);

		// Check if the match count has restrictions.
		if (respectGroupMatcheCount) {
			size_t count = matchList.size();
			if (count != expectedGroupMatcheCount) {							
				SHOWOMessage("Failed: Special matchcount expected!");
				SHOWOMessage("expectedMatchesCount: " + std::to_string(expectedGroupMatcheCount));
				SHOWOMessage("but was: " + std::to_string(count));
				SHOWOMessage("pattern: " + pattern);
				SHOWOMessage("text_IN_OUT: \n" + text_IN_OUT);
				return false;
			}
		}

		// Put the stuff in a simple list.
		for (size_t i = 0; i < matchList.size(); ++i) {
			_simpleResults.push_back(matchList.str(i));
		}

		// Erase the matching parts.
		if (removeFindings) {
			text_IN_OUT = regex_replace(text_IN_OUT, regexPattern, "", std::regex_constants::format_first_only);			
			SHOWOMessage("Result after remove: \n" + text_IN_OUT);
		}
		if (respectGroupMatcheCount) {
			return  (matchList.size() == expectedGroupMatcheCount);
		}
		else {
			return  (matchList.size() != 0);
		}
		// Hopefully never reachable
		return false;
	}


}
