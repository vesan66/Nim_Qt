#pragma once


namespace LXMLP { // => Light-XML-Parser 

	constexpr const char* value_True{ "true" };
	constexpr const char* value_False{ "false" };

	constexpr const char* closeSign{ ">" };
	constexpr const char* emptyCloseSign{ "/>" };
	constexpr const char* closeUnEmptySign{ "</" };
	constexpr const char* openSign{ "<" };
	constexpr const char* openSignXMLHead{ "<?xml" };
	constexpr const char* closeSignXMLHead{ "?>" };

	// XML-Head.
	constexpr const char* xmlHeadTagPattern{"^<\\?xml ([ A-Za-z='0-9.-]+)\\?>"};
	constexpr const char* xmlHeadAttrVersion{ "version" };
	constexpr const char* xmlHeadAttrVersionValue{ "1.0" };
	constexpr const char* xmlHeadAttrEncoding{ "encoding" };
	constexpr const char* xmlHeadAttrEncodingValue{ "UTF-8" };
	constexpr const char* xmlHeadAttrStandalone{ "standalone" };
	constexpr const char* xmlHeadAttrStandaloneValue{ "yes" };

	// Open tag.
	constexpr const char* openTagPattern{ "^<([a-zA-Z0-9]{1,20})(?:[ ]([ ='_a-zA-Z0-9:.,-\\/]{1,90}?)|)(\\/?>)" };
	constexpr const char* openTagPattern_repl{ "^<([%1]{1,20})(?:[ ]([ ='_a-zA-Z0-9:.,-\\/]{1,90}?)|)(\\/?>)" };

	// Attributes inside the open tag.
	constexpr const char* attribValuePattern{ "^([a-zA-Z]+)='([_a-zA-Z0-9:.,-\\/]*)'(?: |$)" };

	// Value and closing tag.
	constexpr const char* closeTagPatternAndValue{ "^([a-zA-Z-_.,0-9]*)<\\/([a-zA-Z0-9]{1,20})>" };		// Give me value and xml closing tag. Value must not contain XML.
	constexpr const char* closeTagPatternAndValue_repl{ "^([a-zA-Z-_.,0-9]*)<\\/([%1]{1,20})>" };
}