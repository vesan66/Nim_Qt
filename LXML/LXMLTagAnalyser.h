#pragma once
#include <iostream>
#include <regex>
#include <vector>
#include "../gamelogic/globals_globals.h"
#include "LXMLTypes.h"
#include "LXMLConsts.h"
#include "LXMLFunctions.h"
#include "LXMLRegMatcher.h"

using namespace std;

namespace LXMLP { // => Light-XML-Parser

#if _DEBUG
	class LXMLTagAnalyser_TestOutlet;
#endif // _DEBUG

	class LXMLElement;

	class LXMLTagAnalyser {
	public:
#if _DEBUG
		friend class LXMLTagAnalyser_TestOutlet;
#endif // _DEBUG

		TAttributes		Attributes() const { return _attributes; }
		TKeyTagStr		KeyTag() const { return _keyTag; }
		TIsEmptyNode	IsEmptyNode() const { return _isEmptyNode; }
		TOpenTagStr		OpenTag() const { return _openTag; }
		TTagIsClosed	TagIsClosed() const { return _tagIsClosed; }
		TValueStr		ValueStr() const { return _value; }
		THasChild		HasChild() const { return _hasChild; }


		inline LXMLTagAnalyser() { SHOWC; };
		inline ~LXMLTagAnalyser() { SHOWD; };

		bool Parse(LXMLElement* element, TXMLStr& text_IN_OUT);

		bool GetXMLHead(string& text_IN_OUT);

		inline bool CheckIfNextIsAnyOpenTag(const string& text) {
			SHOWO;
			string text_IN_OUT = text;
			LXMLTagAnalyser lvta{};
			return lvta.ExplodeOpenTagSpecific(text_IN_OUT, false, "");
		}

		inline bool CheckIfNextIs_MY_ClosingTag(const string& text) {
			SHOWO;
			string text_IN_OUT = text;
			LXMLTagAnalyser lvta{};
			return lvta.GetNextClosingTagByNameAndValueBefore(text_IN_OUT, true, _keyTag);
		}


		inline bool GetNextClosingForThisAndValueBefore(string& text_IN_OUT) {
			SHOWO;
			return GetNextClosingTagByNameAndValueBefore(text_IN_OUT, true, _keyTag);
		}


		inline bool ExplodeOpenTag(string& text_IN_OUT) {
			SHOWO;
			return ExplodeOpenTagSpecific(text_IN_OUT, false, "");
		}

	private:
		TOpenTagStr	_openTag{};
		TKeyTagStr	_keyTag{};
		TAttributes	_attributes{};
		TValueStr	_value{};

		TIsEmptyNode _isEmptyNode{ TIsEmptyNode::eUndefined };
		TTagIsClosed _tagIsClosed{ TTagIsClosed::eUndefined };
		THasChild    _hasChild{ THasChild::eUndefined };

		inline void ClearProperties() {
			_attributes.clear();
			_keyTag = "";
			_isEmptyNode = TIsEmptyNode::eUndefined;
			_tagIsClosed = TTagIsClosed::eUndefined;
			_hasChild = THasChild::eUndefined;
			_value = "";
			_openTag = "";
		}

		bool ExplodeOpenTagSpecific(string& text_IN_OUT, const bool& respectKeyTag, const TKeyTagStr& keyTag);
		bool ExplodeAttributes(string& text);
		bool GetNextClosingTagByNameAndValueBefore(string& text_IN_OUT, const bool& respectKeyTag, const TKeyTagStr& keyTag);
	};


}

