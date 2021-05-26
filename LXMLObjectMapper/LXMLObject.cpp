#include "LXMLObject.h"

namespace LXMLObjects {

	LXMLObject::LXMLObject() {
		SHOWC;
	}


	bool LXMLObject::Parse(LXML* pLXML) {

		bool result = false;

		if (pLXML == nullptr) { return result; }

		// Check for correct 'Header' of class.
		if (pLXML->Parse()) {
			LXMLElement* pEl = pLXML->GetElementByTagName(kTag_TopNode);
			if (pEl != nullptr) {
				string namespaceURL = pEl->GetAttributeByName(kAttr_NameSpace);
				if (!namespaceURL.empty()) { SetNamespaceXML(namespaceURL); }

				string dataVersion = pEl->GetAttributeByName(kAttr_DataVersion);
				SetVersion(dataVersion);

				string lXMLVer = pEl->GetAttributeByName(kAttr_LXMLVersion);
				// Today, there is only one version, which must be set.
				if (lXMLVer == LXMLVersion()) {
					// Set the encodeFlag
					if (SetStringEncodingFlag(pEl)) {
						result = GetObjectFromSource(pEl, kTag_RootNode, ClassNameXML(), this);
					}
				}
			}
		}
		
		return result;
	}


	bool LXMLObject::LoadObjectFromSourceText(const string& xMLText, const bool& initializeIfNotPresent) {
		bool result = false;
		if (xMLText.empty() && (initializeIfNotPresent == false)) { return result; }
		LXML* pLXML = new LXML();
		if (pLXML == nullptr) { return result; }
		if (xMLText.empty() && (initializeIfNotPresent == true)) {
			// This is the case, if the first start occures. Everything is default.
			string initialText = this->GetXMLNode();
			pLXML->SetText(initialText);
		}
		else {
			pLXML->SetText(xMLText);
		}
		pLXML->SetStateFromLoad(LXML::ELXMLErrors::WasNotLoadedFromFile);
		result = this->Parse(pLXML);
		delete pLXML; pLXML = nullptr;
		return result;
	}


	bool LXMLObject::LoadObjectFromSourceFile(const string& filePath, const bool& initializeIfNotPresent ) {

		bool result = false;

		if (filePath.empty()) { return result; }
		LXML* pLXML = new LXML();
		if (pLXML == nullptr) { return result; }
		LXML::ELXMLErrors errorCode = LXML::ELXMLErrors::Undefined;
		bool innerResult = pLXML->LoadXMLFromFile(filePath, errorCode);
		if ((initializeIfNotPresent == true) && (innerResult == false) && (errorCode == LXML::ELXMLErrors::FileNotFound)) {
			// This is the case, if the first start occures. Everything is default.
			string initialText = this->GetXMLNode();
			pLXML->SetText(initialText);
			innerResult = true;
		}
		if (innerResult){			
			result = this->Parse(pLXML);			
		}
		delete pLXML; pLXML = nullptr;
		return result;
	}


	string LXMLObject::GetStringFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const string& defaultValue, bool& wasDefault_OUT) {
		
		string result = defaultValue;
		wasDefault_OUT = true;
		
		if (pLXML == nullptr) { return result; }
		if (varNameInContext.empty()) { return result; }

		LXMLElement* item = pLXML->GetElementByTagName(varNameInContext);
		if (item != nullptr) {
			string nodeType = item->GetAttributeByName(kAttr_Type);
			if (nodeType == kAttr_Type_Value_string) {
				string encoded = item->GetAttributeByName(kAttr_Encoded);				
				if (encoded == kAttr_Encoded_Value_No) {					
					result = item->ValueStr();	
					wasDefault_OUT = false;
				}
				if (encoded == kAttr_Encoded_Value_BinHex) {
					result = item->DecodeString(item->ValueStr());
					wasDefault_OUT = false;
				}				
			}			
		}
		return result;
	}


	string LXMLObject::GetDecodedValueString(LXMLElement* pLXML, const string& defaultValue, bool& wasDefault_OUT) {
		string result = defaultValue;
		wasDefault_OUT = true;

		if (pLXML == nullptr) { return result; }

		string nodeType = pLXML->GetAttributeByName(kAttr_Type);
		if (nodeType == kAttr_Type_Value_string) {
			string encoded = pLXML->GetAttributeByName(kAttr_Encoded);
			if (encoded == kAttr_Encoded_Value_No) {
				result = pLXML->ValueStr();
				wasDefault_OUT = false;
			}
			if (encoded == kAttr_Encoded_Value_BinHex) {
				result = pLXML->DecodeString(pLXML->ValueStr());
				wasDefault_OUT = false;
			}
		}
		return result;
	}



	int LXMLObject::GetIntFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const int& defaultValue, bool& wasDefault_OUT) {
		int result = defaultValue;
		bool hasNoValue = true;
		string sResult = GetValueFromSource_Or_Default(pLXML, varNameInContext, kAttr_Type_Value_integer, hasNoValue);
		wasDefault_OUT = hasNoValue;
		if (hasNoValue == false) {
			result = stoi(sResult);
		}
		return result;
	}


	double LXMLObject::GetDoubleFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const double& defaultValue, bool& wasDefault_OUT) {
		double result = defaultValue;
		bool hasNoValue = true;
		string sResult = GetValueFromSource_Or_Default(pLXML, varNameInContext, kAttr_Type_Value_double, hasNoValue);
		wasDefault_OUT = hasNoValue;
		if (hasNoValue == false) {
			result = stod(sResult);
		}
		return result;
	}


	bool LXMLObject::GetBoolFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const bool& defaultValue, bool& wasDefault_OUT) {
		bool result = defaultValue;
		bool hasNoValue = true;
		string sResult = GetValueFromSource_Or_Default(pLXML, varNameInContext, kAttr_Type_Value_bool, hasNoValue);
		wasDefault_OUT = hasNoValue;
		if (hasNoValue == false) {
			result = (sResult == value_True) ? true : false;			
		}
		return result;
	}


	string LXMLObject::GetValueFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const string& expectedNodeType, bool& hasNoValue_OUT) {
		string result = "";
		hasNoValue_OUT = true;

		if (pLXML == nullptr) { return result; }
		if (varNameInContext.empty()) { return result; }
		if (expectedNodeType.empty()) { return result; }

		LXMLElement* item = pLXML->GetElementByTagName(varNameInContext);
		if (item != nullptr) {
			string nodeType = item->GetAttributeByName(kAttr_Type);
			if (nodeType == expectedNodeType) {
				result = item->ValueStr();
				hasNoValue_OUT = false;
			}
		}
		return result;
	}


	bool LXMLObject::SetStringEncodingFlag(LXMLElement* pEl) {
		bool result = false;
		if (pEl == nullptr) { return result; }
		if (pEl->HasChild() == THasChild::eFalse) {
			string nodeType = pEl->GetAttributeByName(kAttr_Type);
			if (nodeType == kAttr_Type_Value_string) {
				string value = pEl->GetAttributeByName(kAttr_Encoded);
				if (value == kAttr_Encoded_Value_No) {
					pEl->SetEncodeValue(EEncode::eNoEncoding);
				}
				if (value == kAttr_Encoded_Value_BinHex) {
					pEl->SetEncodeValue(EEncode::eBinHex);
				}
			}
			result = true;
		} else if (pEl->HasChild() == THasChild::eTrue) {
			//if (pEl->Childs()->size() == 0) { return result; }  // Might be an container, but w/o childs.
			MMKT::MultimapKeyedTreeElement::TMap* pChilds = pEl->Childs();
			for (auto pItem : *pChilds) {
				LXMLElement* pElem = static_cast<LXMLElement*>(pItem.second);
				result = this->SetStringEncodingFlag(pElem);
			}
		} else {
			result = false;
		}
		return result;
	}


	string LXMLObject::GetXMLNode() {
		string result = "";

		LXML* pLXML = new LXML();

		if (CreateFullXMLNode(pLXML)) {
			result = pLXML->GetXMLNode();
		}
		delete pLXML; pLXML = nullptr;
		return result;
	};


	bool LXMLObject::CreateFullXMLNode(LXML* pLXML) {

		bool result = false;
		if (pLXML == nullptr) { return false; }

		// Define 'Header' for this class.
		LXMLElement* pEl = pLXML->CreateNewChild(kTag_TopNode);
		TAttributes* pAttr = pEl->Attributes();
		pAttr->insert({ kAttr_NameSpace, NamespaceURL() });
		pAttr->insert({ kAttr_DataVersion, Version() });
		pAttr->insert({ kAttr_LXMLVersion, kAttr_Value_LXMLVersion });
		pLXML->AddElement(pEl);

		result = AddObjectNode(pEl, kTag_RootNode, this);
		return result;
	}


	bool LXMLObject::StoreObjectToSource(const string& filePath) {

		bool result = false;

		if (filePath.empty()) { return false; }
		LXML* pLXML = new LXML();

		if (CreateFullXMLNode(pLXML)) {
			result = pLXML->SaveXMLToFile(filePath);
		}
		delete pLXML; pLXML = nullptr;
		return result;
	}


	bool LXMLObject::GetObjectFromSource(LXMLElement* pLXML, const string& objectNameInContext, const string& classnameXML, LXMLObject* pObjectToFill) {
		
		bool result = false;
		if (pLXML == nullptr) { return result; }
		if (pObjectToFill == nullptr) { return result; }

		function<LXMLObject* ()> creator = [&]()->LXMLObject* { return pObjectToFill;  };
		result = GetObjectFromSource(pLXML, objectNameInContext, classnameXML, creator);
		return result;
	}


	bool LXMLObject::GetObjectFromSource(LXMLElement* pLXML, const string& objectNameInContext, const string& classnameXML, function<LXMLObject* ()>& objectCreator) {
		
		bool result = false;
		if (pLXML == nullptr) { return result; }

		LXMLElement* pObject = pLXML->GetElementByTagName(objectNameInContext);
		if (pObject != nullptr) {
			string nodeType = pObject->GetAttributeByName(kAttr_Type);
			if (nodeType == kAttr_Type_Value_object) {
				string className = pObject->GetAttributeByName(kAttr_ClassName);
				if (className == classnameXML) {
					LXMLObject* pObjectToFill = objectCreator();
					if (pObjectToFill != nullptr) {
						result = pObjectToFill->FillObjectFromSource(pObject);
					}
				}
			}
		}
		return result;
	}


	bool LXMLObject::GetContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<LXMLObject* ()>& objectCreator, function<bool (LXMLObject*)>& append) {

		bool result = false;
        function<bool(LXMLObject*, const string&)> append_function = [&append](LXMLObject* pItem, const string& /*key*/)->bool {
			return append(pItem);  };

		result = GetAnyContainerFromSource(pLXML, containerNameInContext, kAttr_Type_Value_container, objectCreator, append_function);

		return result;
	}


	bool LXMLObject::GetKeyedContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<LXMLObject* ()>& objectCreator, function<bool(LXMLObject*, const string&)>& append) {
		return GetAnyContainerFromSource(pLXML, containerNameInContext, kAttr_Type_Value_keyedcontainer, objectCreator, append);
	}


	bool LXMLObject::GetAnyContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, 
												const string& nodeType,
												function<LXMLObject* ()>& objectCreator, 
												function<bool(LXMLObject*, const string&)>& append) {

		bool result = false;
		if (pLXML == nullptr) { return result; }
		if (nodeType.empty()) { return result; }

		LXMLElement* pContainer = pLXML->GetElementByTagName(containerNameInContext);
		if (pContainer != nullptr) {
			string nodeType = pContainer->GetAttributeByName(kAttr_Type);
			if ((nodeType == kAttr_Type_Value_container) || (nodeType == kAttr_Type_Value_keyedcontainer)) {

                //LXMLElement* pItem{};
				MMKT::MultimapKeyedTreeElement::TMap* pChilds = pContainer->Childs();
				if (pChilds->empty()) { result = true; }
				for (auto item : *pChilds) {
					LXMLElement* pObject = static_cast<LXMLElement*>(item.second);
					if (pObject != nullptr) {
						string className = pObject->GetAttributeByName(kAttr_ClassName);
						if (className.empty()) { break; }											
						string key = pObject->Key();
						if (!key.empty()) {
							if (((key == kTag_ContainerItemNode) && (nodeType == kAttr_Type_Value_container)) || (nodeType == kAttr_Type_Value_keyedcontainer )) {
								LXMLObject* pObjectToFill = objectCreator();
								result = pObjectToFill->FillObjectFromSource(pObject);
								if (!result) { break; }
								result = append(pObjectToFill, key);
								if (!result) { break; }
							} else {
								break;
							}
						}
					}
				}
			}
		}
		return result;
	}


	bool LXMLObject::GetSimpleContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<bool(LXMLElement*)>& append) {

		bool result = false;
        function<bool(LXMLElement*, const string&)> append_function = [&append](LXMLElement* pItem, const string& /*key*/)->bool {
			return append(pItem);  };

		result = GetSimpleAnyContainerFromSource(pLXML, containerNameInContext, kAttr_Type_Value_SimpleContainer, append_function);

		return result;
	}


	bool LXMLObject::GetSimpleKeyedContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<bool(LXMLElement*, const string&)>& append) {
		return GetSimpleAnyContainerFromSource(pLXML, containerNameInContext, kAttr_Type_Value_KeyedSimpleContainer, append);
	}


	bool LXMLObject::GetSimpleAnyContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext,
		const string& nodeType,
		function<bool(LXMLElement*, const string&)>& append) {

		bool result = false;
		if (pLXML == nullptr) { return result; }
		if (nodeType.empty()) { return result; }

		LXMLElement* pContainer = pLXML->GetElementByTagName(containerNameInContext);
		if (pContainer != nullptr) {
			string nodeType = pContainer->GetAttributeByName(kAttr_Type);
			if ((nodeType == kAttr_Type_Value_SimpleContainer) || (nodeType == kAttr_Type_Value_KeyedSimpleContainer)) {

                //LXMLElement* pItem{};
				MMKT::MultimapKeyedTreeElement::TMap* pChilds = pContainer->Childs();
				if (pChilds->empty()) { result = true; }
                for (const auto item : *pChilds) {
					LXMLElement* pElment = static_cast<LXMLElement*>(item.second);
					if (pElment != nullptr) {
						string key = pElment->Key();
						if (!key.empty()) {
							if (((key == kTag_ContainerItemNode) && (nodeType == kAttr_Type_Value_SimpleContainer)) || (nodeType == kAttr_Type_Value_KeyedSimpleContainer)) {																															
								result = append(pElment, key);
								if (!result) { break; }
							}
							else {
								break;
							}
						}
					}
				}
			}
		}
		return result;
	}

	bool LXMLObject::AddObjectNode(LXMLElement* pLXML, const string& objectNameInContext, LXMLObject* pObjectToAdd) {

		bool result = false;

		if (pLXML == nullptr) { return result; }
		if (pObjectToAdd == nullptr) { return result; }
		if (objectNameInContext.empty()) { return result; }

		LXMLElement* pObject = pLXML->CreateNewChild(objectNameInContext);
		if (pObject != nullptr) {
			TAttributes* pObjAttr = pObject->Attributes();
			pObjAttr->insert({ kAttr_Type, kAttr_Type_Value_object });
			pObjAttr->insert({ kAttr_ClassName, pObjectToAdd->ClassNameXML() });
			pLXML->AddElement(pObject);

			// Call the enrich xml methods.
			result = pObjectToAdd->FillSourceFromObject(pObject);
		}

		return result;
	}


	bool LXMLObject::AddStringNode(LXMLElement* pLXML, const string& varNameInContext, const string& value) {
		return AddSimpleNode(pLXML, varNameInContext, kAttr_Type_Value_string, value);
	}


	bool LXMLObject::AddIntegerNode(LXMLElement* pLXML, const string& varNameInContext, const int& value) {		
		return AddSimpleNode(pLXML, varNameInContext, kAttr_Type_Value_integer, value);
	}


	bool LXMLObject::AddDoubleNode(LXMLElement* pLXML, const string& varNameInContext, const double& value) {
		return AddSimpleNode(pLXML, varNameInContext, kAttr_Type_Value_double, value);
	}


	bool LXMLObject::AddBoolNode(LXMLElement* pLXML, const string& varNameInContext, const bool& value) {
		return AddSimpleNode(pLXML, varNameInContext, kAttr_Type_Value_bool, value);
	}


	LXMLObject::~LXMLObject() {
		SHOWD;
	}

}
