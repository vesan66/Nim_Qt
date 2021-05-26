#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

namespace LXMLP { // => Light-XML-Parser
	// Types
	enum class EEncode : int { eNoEncoding = 99, eBinHex = 1 };
	typedef bool TIgnoreMissingXMLHead;
	typedef bool TDontCreateXMLHead;
	typedef EEncode TEncodeValue;
	typedef string TOpenTagStr;
	typedef string TAttributeStr;
	typedef string TValueStr;
	typedef string TXMLStr;
	typedef string TKeyTagStr;
	typedef pair<TAttributeStr, TValueStr> TAttributeAndValue;
	typedef map<TAttributeAndValue::first_type, TAttributeAndValue::second_type> TAttributes;

	enum class ETriState : int { eUndefined = 99, eTrue = 1, eFalse = 0 };

	using TIsEmptyNode = ETriState;
	using TTagIsClosed = ETriState;
	using THasChild = ETriState;

	using TSimpleList = vector<string>;
}