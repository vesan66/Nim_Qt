#pragma once
#include "../gamelogic/globals_globals.h"
#include "../MultimapKeyedTree/MultimapKeyedTreeElement.h"
#include "LXMLConsts.h"
#include "LXMLFunctions.h"
#include "LXMLElement.h"
#include "LXMLConnector.h"
#include "FileIO.h"

using namespace MMKT;

namespace LXMLP { // => Light-XML-Parser

	class LXML : public LXMLElement {
	public:
		// Constructors / Destructor
		explicit LXML();
		
		inline virtual ~LXML() override { SHOWD; };

	//
	//	XML-Part
	//	
	public:
		


		// Properties
		inline void SetText(const TXMLStr& text) { this->_text = Sanitize(text); }
		inline TXMLStr Text() const { return this->_text; };

		inline void SetIgnoreMissingXMLHead(const TIgnoreMissingXMLHead value) { _ignoreMissingXMLHead = value; }
		inline TIgnoreMissingXMLHead IgnoreMissingXMLHead() const { return _ignoreMissingXMLHead; };

		inline void SetDontCreateXMLHead(const TDontCreateXMLHead value) { _dontCreateXMLHead = value; }
		inline TDontCreateXMLHead DontCreateXMLHead() const { return _dontCreateXMLHead; };

		void SetStandalone(const bool& value);
		void SetEncoding(const string& value);

		inline TXMLStr ChangingText() const { return _changingText; }

		inline virtual ELXMLErrors StateFromLoad() override { return _stateFromLoad; }
		inline virtual ELXMLErrors StateFromSave() override { return _stateFromSave; }

		inline void SetStateFromLoad(const ELXMLErrors& value) { _stateFromLoad = value; }
		inline void SetStateFromSave(const ELXMLErrors& value) { _stateFromSave = value; }

		// Methods
		bool Parse(const TXMLStr& text);
		bool Parse();
		
		virtual string GetXMLNode() override;
		bool LoadXMLFromFile(const string& filepath);
		bool LoadXMLFromFile(const string& filepath, ELXMLErrors& errorCode_OUT);
		bool SaveXMLToFile(const string& filepath);
		bool SaveXMLToFile(const string& filepath, ELXMLErrors& errorCode_OUT);
		
		/// <summary>
		/// Remove some spacial chars.
		/// E.G.: Linebreaks.
		/// </summary>
		/// <param name="text">Text to escape.</param>
		/// <returns>A escaped COPY of the text.</returns>
		string Sanitize(const string& text);

	protected:
		// Methods		
		bool Parse(TXMLStr& text_IN_OUT) override;
		bool ParseForHead(TXMLStr& text_IN_OUT);
		string GenerateAttributesHeadString() const;
		void InsertHeadAttributesIfNotPresent();

		ELXMLErrors MapFileIOErrors(const FileIO::EFileIOErrors& fileIOError);
	private:
		TXMLStr					_text;
		TXMLStr					_changingText;
		TIgnoreMissingXMLHead	_ignoreMissingXMLHead = false;
		TDontCreateXMLHead		_dontCreateXMLHead = false;
		ELXMLErrors _stateFromLoad = ELXMLErrors::Undefined;
		ELXMLErrors _stateFromSave = ELXMLErrors::Undefined;
		explicit LXML(const TKeyStr& key);
	};
}

