#pragma once
#include <string>
#include"../gamelogic/globals_globals.h"
#include "../MultimapKeyedTree/MultimapKeyedTreeElement.h"
#include "LXMLTypes.h"
#include "LXMLConsts.h"
#include "LXMLFunctions.h"

using namespace MMKT;
namespace LXMLP { // => Light-XML-Parser

	class LXMLConnector;

	class LXMLElement : public MultimapKeyedTreeElement {
	public:

		enum class ELXMLErrors : int {
			Undefined = 0,
			OK = 1,
			FileNotFound = 2,
			ParseError = 3,
			ReadError = 5,
			WriteError = 6,
			UnableToOpenFileForReading = 7,
			UnableToOpenFileFoSaving = 8,
			MissingFilePath = 9,
			WasNotLoadedFromFile = 10
		};

		// Friend
		friend class LXMLConnector;

		// Methods
		virtual LXMLElement* CreateNewChild() override;
		virtual LXMLElement* CreateNewChild(const TKeyStr& key) override;

		virtual ELXMLErrors StateFromLoad();
		virtual ELXMLErrors StateFromSave();

	protected:
		// Constructors / Destructors
		explicit LXMLElement(LXMLElement* parent);
		explicit LXMLElement(LXMLElement* parent, const TKeyStr& key);
		virtual ~LXMLElement() override;

		// Methods
		virtual MultimapKeyedTreeConnector* CreateConnector() override;

	//
	//	XML-Part
	//	
	public:

		// Properties		
		inline TAttributes*	Attributes()	{ return _pAttributes; }
		inline TAttributes*	Attributes() const	{ return _pAttributes; }
		inline THasChild	HasChild() const { return _hasChild; }
		inline void			SetHasChild(const THasChild& value) { _hasChild = value; }
		inline TTagIsClosed	TagIsClosed() const { return _tagIsClosed; }
		inline TValueStr	ValueStr()		{ return _valueStr; }		

		inline void			SetValueStr(const TValueStr& value) { _valueStr = value; }
		inline void			SetValueStr(const int& value) { _valueStr = std::to_string(value); }
		inline void			SetValueStr(const double& value) { _valueStr = std::to_string(value); }
		inline void			SetValueStr(const bool& value) { _valueStr = value ? value_True : value_False; }

		inline TEncodeValue	EncodeValue()	{ return _encodeValue; }
		inline void SetEncodeValue(const TEncodeValue& value) { _encodeValue = value; }

		// Methods
		virtual bool Parse(TXMLStr& text_IN_OUT);
		virtual string GetXMLNode();
		string GetXMLContent() const;
		string EncodeString(const string&) const;
		string DecodeString(const string&) const;
		LXMLElement* GetElementByTagName(const TKeyTagStr& tagname) const;
		TValueStr GetAttributeByName(const TAttributeStr& attributename) const;
	
	protected:

		// Methods
		string GenerateAttributesString() const;

	private:

		// Tag properties
		TAttributes*	_pAttributes{};		// I Own		
		THasChild       _hasChild{ THasChild::eUndefined };
		TTagIsClosed	_tagIsClosed{ TTagIsClosed::eUndefined };
		TValueStr       _valueStr{};
		TEncodeValue	_encodeValue{};

	};
}

