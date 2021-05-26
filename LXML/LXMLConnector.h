#pragma once
#include "../MultimapKeyedTree/MultimapKeyedTreeConnector.h"
#include "LXMLElement.h"

using namespace MMKT;
namespace LXMLP { // => Light-XML-Parser

	class LXMLConnector: public MultimapKeyedTreeConnector {
	public:
		// Friend
		friend class LXMLElement;

		// Methods
		virtual LXMLElement* CreateNewChild(LXMLElement* pParent, const MultimapKeyedTreeElement::TKeyStr& key);
		bool Parse(LXMLElement* parent, TXMLStr& text_IN_OUT);
		bool GetXMLHead(LXMLElement* parent, TXMLStr& text_IN_OUT);

	protected:
		// Constructors / Destructors
		inline LXMLConnector(): MultimapKeyedTreeConnector() { SHOWC; };
		inline virtual ~LXMLConnector() override { SHOWD; } ;


	//
	//	XML-Part
	//	
	public:

	private:



	};
}