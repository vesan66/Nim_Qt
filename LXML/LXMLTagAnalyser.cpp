#include "LXMLTagAnalyser.h"
#include "LXMLElement.h"

namespace LXMLP { // => Light-XML-Parser
	bool LXMLTagAnalyser::Parse(LXMLElement* element, TXMLStr& text_IN_OUT) {
		if (element == nullptr) { return false; }
		if (text_IN_OUT.empty() == true) { return true; }

		bool innerResult = false;
		bool result = false;
		bool foundMe = false;

		do {
			innerResult = false;
			if (CheckIfNextIsAnyOpenTag(text_IN_OUT)) {
				if (foundMe == false) {
					innerResult = ExplodeOpenTag(text_IN_OUT);
					// Found a open Tag.
					if (innerResult == false) { break; }
					foundMe = true;
					// Fill Data! // The rest outside.
					element->SetKey(this->KeyTag());
					if (this->TagIsClosed() == TTagIsClosed::eTrue) { result = true;  break; }
				}
				else {
					// Go down!
					LXMLElement* pSubElement = element->CreateNewChild();
					innerResult = pSubElement->Parse(text_IN_OUT);
					if (innerResult == false) { break; }
					if (pSubElement->Key().empty()) { break; }
					element->AddElement(pSubElement);
					_hasChild = THasChild::eTrue;
				}
			}

			if (foundMe == true) {
				if (CheckIfNextIs_MY_ClosingTag(text_IN_OUT)) {
					// My Close! Wonderfull. That was easy.
					innerResult = GetNextClosingForThisAndValueBefore(text_IN_OUT);
					if (innerResult == false) { break; }
					if (_hasChild == THasChild::eUndefined) { _hasChild = THasChild::eFalse; }
					if (this->TagIsClosed() == TTagIsClosed::eTrue) { result = true; break; }
				}
			}

		} while ((!text_IN_OUT.empty()) && (innerResult == true));

		return result;
	}


	bool LXMLTagAnalyser::ExplodeOpenTagSpecific(string& text_IN_OUT, const bool& respectKeyTag, const TKeyTagStr& keyTag) {
		SHOWO;

		string pattern = "";
		string returnedKeyTag = "";
		string returnedCloseTag = "";

		const size_t expectedSize = 4;
		const int wholeOpenTag = 0;
		const int keyTagAtPos = 1;
		const int innerContentAt = 2;
		const int closingSignAtPos = 3;

		int checkCount = 0;
		int checkCountExpected = 3;

		ClearProperties();

		// Stage 1: The Tag.	
		if (respectKeyTag) {
			if (!keyTag.empty()) {
				pattern = openTagPattern_repl;
				ReplaceAll(pattern, "%1", keyTag);
			}
			else {
				return false;
			}
		}
		else {
			pattern = openTagPattern;
		}

		LXMLRegMatcher lVRM{};
		bool innerResult = lVRM.RegExer_HaystackMatch_Changing(pattern, text_IN_OUT);
		if (innerResult) {
			TSimpleList sl = lVRM.SimpleResults();
			if (sl.size() == expectedSize) {

				// The Tag
				if (checkCount == 0) {
					returnedKeyTag = sl[keyTagAtPos];
					if (!returnedKeyTag.empty()) {
						if (!keyTag.empty()) {
							_keyTag = (returnedKeyTag == keyTag) ? returnedKeyTag : "";
						}
						else {
							_keyTag = returnedKeyTag;
						}
						_openTag = sl[wholeOpenTag];
						_tagIsClosed = TTagIsClosed::eFalse;
					}
					if (!_keyTag.empty()) {
						checkCount++;
					}
				}

				// Stage 2: The attributes
				if (checkCount == 1) {
					string innerContent = sl[innerContentAt];
					if (!innerContent.empty()) {
						if (ExplodeAttributes(innerContent)) {
							checkCount++;
						}
					}
					else {
						checkCount++;
					}
				}

				// Check for Empty ValueStr Type:  <Tag/>
				if (checkCount == 2) {
					returnedCloseTag = sl[closingSignAtPos];
					if (!returnedCloseTag.empty()) {
						if (returnedCloseTag == emptyCloseSign) {
							_isEmptyNode = TIsEmptyNode::eTrue;
							_hasChild = THasChild::eFalse;
							_tagIsClosed = TTagIsClosed::eTrue;
						}
						if (returnedCloseTag == closeSign) {
							_isEmptyNode = TIsEmptyNode::eFalse;
						}
						if (_isEmptyNode != TIsEmptyNode::eUndefined) {
							checkCount++;
						}
					}
				}
			}
		}

		if (checkCount != checkCountExpected) {
			ClearProperties();
		}

		return (checkCount == checkCountExpected);
	}


	bool LXMLTagAnalyser::ExplodeAttributes(string& text) {
		SHOWO;

		const int expectedInnerSize = 3;
		const int attribAtPos = 1;
		const int valueAtPos = 2;

		_attributes.clear();
		bool result = false;

		if (!text.empty()) {
			// Stage 2
			LXMLRegMatcher lVRM_Inner{};
			string innerPattern = attribValuePattern;
			bool error = false;
			do {

				bool innerResult =
					lVRM_Inner.RegExer_HaystackMatch_GroupMatchCount_Changing(
						innerPattern,
						text,
						expectedInnerSize
					);
				if (innerResult) {
					TSimpleList sl_inner = lVRM_Inner.SimpleResults();
					if (sl_inner.size() == expectedInnerSize) {
						TAttributeStr attr = sl_inner[attribAtPos];
						TValueStr value = sl_inner[valueAtPos];
						if (!attr.empty()) {
							_attributes.insert({ attr, value });
						}
					}
				}
				else {
					error = true;
					break;
				}
			} while (!text.empty());
			result = !error;
		}
		else {
			// This is possible and OK. There are no attributes.
			result = true;
		}
		return result;
	}


	bool LXMLTagAnalyser::GetNextClosingTagByNameAndValueBefore(string& text_IN_OUT, const bool& respectKeyTag, const TKeyTagStr& keyTag) {
		SHOWO;

		string pattern = "";
		const size_t expectedSize = 3;
		const int valueAtPos = 1;

		if (respectKeyTag) {
			if (!keyTag.empty()) {
				pattern = closeTagPatternAndValue_repl;
				ReplaceAll(pattern, "%1", keyTag);
			}
			else {
				return false;
			}
		}
		else {
			pattern = closeTagPatternAndValue;
		}

		LXMLRegMatcher lVRM{};
		bool innerResult = lVRM.RegExer_HaystackMatch_Changing(pattern, text_IN_OUT);
		if (innerResult) {
			TSimpleList sl = lVRM.SimpleResults();
			if (sl.size() != expectedSize) { return false; }
			_value = sl[valueAtPos];
			_tagIsClosed = TTagIsClosed::eTrue;
			return true;
		}

		return false;
	}


	bool LXMLTagAnalyser::GetXMLHead(string& text_IN_OUT) {
		SHOWO;

		string pattern = "";
		const size_t expectedSize = 2;
		const int attributesAtPos = 1;

		pattern = xmlHeadTagPattern;

		LXMLRegMatcher lVRM{};
		bool innerResult = lVRM.RegExer_HaystackMatch_Changing(pattern, text_IN_OUT);
		if (innerResult) {
			TSimpleList sl = lVRM.SimpleResults();
			if (sl.size() != expectedSize) { return false; }
			string innerContent = sl[attributesAtPos];
			if (!innerContent.empty()) {
				if (ExplodeAttributes(innerContent)) {
					auto a = _attributes.find(xmlHeadAttrVersion);
					if (a != _attributes.end()) {
						_hasChild = THasChild::eFalse;
						_tagIsClosed = TTagIsClosed::eTrue;
						return true;
					}
				} 
			} 
		}

		return false;
	}

}
