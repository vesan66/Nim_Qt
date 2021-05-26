#pragma once
#include <functional>
#include <vector>
#include <map>
#include "../gamelogic/globals_globals.h"
#include "LXMLObject_Consts.h"
#include "../LXML/LXMLTypes.h"
#include "../LXML/LXML.h"

using namespace LXMLP;
namespace LXMLObjects {

	class LXMLObject {
	public:
		LXMLObject();		
		bool StoreObjectToSource(const string& filePath);
		string GetXMLNode();
		bool LoadObjectFromSourceFile(const string& filePath, const bool& initializeIfNotPresent = false);
		bool LoadObjectFromSourceText(const string& xMLText, const bool& initializeIfNotPresent = false);
		virtual ~LXMLObject();

	protected:
		// Overrides:
		virtual string ClassNameXML() const = 0;
		virtual bool FillObjectFromSource(LXMLElement* pLXML) = 0;
		virtual bool FillSourceFromObject(LXMLElement* pLXML) = 0;


		// Properties:
		inline string NamespaceURL() const { return _namespaceURL; }
		inline void SetNamespaceXML(const string& namespaceURL) { _namespaceURL = namespaceURL; }
		inline string Version() const { return _version; }
		inline void SetVersion(const string& version) { _version = version; }
		inline string LXMLVersion() const { return _lXMLVersion; }
		inline void SetLXMLVersion(const string& lXMLVersion) { _lXMLVersion = lXMLVersion; }


		// Get Elements:
		string GetStringFromSource_Or_Default(LXMLElement* pLXML, const string& stringNameInContext, const string& defaultValue, bool& wasDefault_OUT);
		string GetDecodedValueString(LXMLElement* pLXML, const string& defaultValue, bool& wasDefault_OUT);
		bool GetBoolFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const bool& defaultValue, bool& wasDefault_OUT);
		int GetIntFromSource_Or_Default(LXMLElement* pLXML, const string& intNameInContext, const int& defaultValue, bool& wasDefault_OUT);
		double GetDoubleFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const double& defaultValue, bool& wasDefault_OUT);
		bool GetObjectFromSource(LXMLElement* pLXML, const string& objectNameInContext, const string& classnameXML, function<LXMLObject* ()>& objectCreator);
		bool GetKeyedContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<LXMLObject* ()>& objectCreator, function<bool(LXMLObject*, const string&)>& append);
		bool GetContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<LXMLObject* ()>& objectCreator, function<bool(LXMLObject*)>& append);

		bool GetSimpleContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<bool(LXMLElement*)>& append);

		bool GetSimpleKeyedContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, function<bool(LXMLElement*, const string&)>& append);
		

		// Add Elements:
		bool AddObjectNode(LXMLElement* pLXML, const string& objectNameInContext, LXMLObject* pObjectToAdd);
		bool AddStringNode(LXMLElement* pLXML, const string& varNameInContext, const string& value);		
		bool AddDoubleNode(LXMLElement* pLXML, const string& varNameInContext, const double& value);
		bool AddBoolNode(LXMLElement* pLXML, const string& varNameInContext, const bool& value);
		bool AddIntegerNode(LXMLElement* pLXML, const string& varNameInContext, const int& value);

		template< typename TContainer >
		bool AddContainerNode(LXMLElement* pLXML, const string& containerNameInContext, TContainer* pContainerToAdd);

		template<typename TKeyedContainer>
		bool AddKeyedContainerNode(LXMLElement* pLXML, const string& containerNameInContext, TKeyedContainer* pContainerToAdd);

		template<typename TContainerSimple>
		bool AddContainerNodeSimpleTypes(LXMLElement* pLXML, const string& containerNameInContext, const string& dataType, TContainerSimple* pContainerToAdd);

		template<typename TKeyedContainerSimple>
		bool AddKeyedContainerNodeSimpleTypes(LXMLElement* pLXML, const string& containerNameInContext, const string& dataType, TKeyedContainerSimple* pContainerToAdd);


		template<class TValue> 
		bool Dispatch(LXMLElement* pLXML, const string& varNameInContext, const TValue& value);
		
	private:
		string _namespaceURL{ "https://your-namespace.com" };
		string _version{ "1.0" };
		string _lXMLVersion{ kAttr_Value_LXMLVersion };

		bool Parse(LXML* pLXML);
		bool SetStringEncodingFlag(LXMLElement* pEl);
		
		bool CreateFullXMLNode(LXML* pLXML);
		bool GetObjectFromSource(LXMLElement* pLXML, const string& objectNameInContext, const string& classnameXML, LXMLObject* pObjectToFill);
		string GetValueFromSource_Or_Default(LXMLElement* pLXML, const string& varNameInContext, const string& expectedNodeType, bool& hasNoValue_OUT);
		bool GetAnyContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, const string& nodeType, function<LXMLObject* ()>& objectCreator, function<bool(LXMLObject*, const string&)>& append);
		bool GetSimpleAnyContainerFromSource(LXMLElement* pLXML, const string& containerNameInContext, const string& nodeType, function<bool(LXMLElement*, const string&)>& append);
		

		template<typename T>
		bool AddSimpleNode(LXMLElement* pLXML, const string& varNameInContext, const string& typeValue, const T& value);
	};


	template<typename T>
	inline bool LXMLObject::AddSimpleNode(LXMLElement* pLXML, const string& varNameInContext, const string& typeValue, const T& value) {
		bool result = false;

		if (pLXML == nullptr) { return result; }
		if (varNameInContext.empty()) { return result; }

		LXMLElement* pObject = pLXML->CreateNewChild(varNameInContext);
		if (pObject != nullptr) {
			TAttributes* pObjAttr = pObject->Attributes();
			pObjAttr->insert({ kAttr_Type, typeValue });
			pObject->SetHasChild(THasChild::eFalse);
			if (typeValue == kAttr_Type_Value_string) {

				// Default today: Strings are BinHex-Encoded.
				pObject->SetEncodeValue(EEncode::eBinHex);

				// Set a Flag for Encoded.
				if (pObject->EncodeValue() == EEncode::eBinHex) {
					pObjAttr->insert({ kAttr_Encoded, kAttr_Encoded_Value_BinHex });
				}
				else {
					pObjAttr->insert({ kAttr_Encoded, kAttr_Encoded_Value_No });
				}
			}

			pObject->SetValueStr(value);

			// This way, because before it is Type T.
			if ((typeValue == kAttr_Type_Value_string) && (pObject->EncodeValue() == EEncode::eBinHex)) {
				pObject->SetValueStr(pObject->EncodeString(pObject->ValueStr()));
			}

			result = pLXML->AddElement(pObject);
		}

		return result;
	}


	template<typename TContainer>
	inline bool LXMLObject::AddContainerNode(LXMLElement* pLXML, const string& containerNameInContext, TContainer* pContainerToAdd) {	

		bool result = false;

		if (pLXML == nullptr) { return result; }
		if (pContainerToAdd == nullptr) { return result; }
		if (containerNameInContext.empty()) { return result; }

		LXMLElement* pContainer = pLXML->CreateNewChild(containerNameInContext);
		if (pContainer != nullptr) {
			TAttributes* pObjAttr = pContainer->Attributes();
			pObjAttr->insert({ kAttr_Type, kAttr_Type_Value_container });			
			pLXML->AddElement(pContainer);
						
			for (auto item : *pContainerToAdd) {
				LXMLObject* pObject = static_cast<LXMLObject*>(item);
				if (!AddObjectNode(pContainer, kTag_ContainerItemNode, pObject)) {
					break;
				}
			}
		}

		return result;
	}

	
	template<typename TContainerSimple>
	inline bool LXMLObject::AddContainerNodeSimpleTypes(LXMLElement* pLXML, const string& containerNameInContext, const string& dataType, TContainerSimple* pContainerToAdd) {

		bool result = false;

		if (pLXML == nullptr) { return result; }
		if (pContainerToAdd == nullptr) { return result; }
		if (containerNameInContext.empty()) { return result; }

		LXMLElement* pContainer = pLXML->CreateNewChild(containerNameInContext);
		if (pContainer != nullptr) {
			TAttributes* pObjAttr = pContainer->Attributes();
			pObjAttr->insert({ kAttr_Type, kAttr_Type_Value_SimpleContainer });
			pLXML->AddElement(pContainer);

			for (auto item : *pContainerToAdd) {
				
				if ((dataType == kAttr_Type_Value_bool) || (dataType == kAttr_Type_Value_integer) || (dataType == kAttr_Type_Value_double) || (dataType == kAttr_Type_Value_string) ){							
					if (!Dispatch(pContainer, kTag_ContainerItemNode, item)) {
						break;
					}
					continue;
				}
			}
		}

		return result;
	}


	template<typename TKeyedContainerSimple>
	inline bool LXMLObject::AddKeyedContainerNodeSimpleTypes(LXMLElement* pLXML, const string& containerNameInContext, const string& dataType, TKeyedContainerSimple* pContainerToAdd) {

		bool result = false;

		if (pLXML == nullptr) { return result; }
		if (pContainerToAdd == nullptr) { return result; }
		if (containerNameInContext.empty()) { return result; }

		LXMLElement* pContainer = pLXML->CreateNewChild(containerNameInContext);
		if (pContainer != nullptr) {
			TAttributes* pObjAttr = pContainer->Attributes();
			pObjAttr->insert({ kAttr_Type, kAttr_Type_Value_KeyedSimpleContainer });
			pLXML->AddElement(pContainer);

			for (auto item : *pContainerToAdd) {
				string key = item.first;
				auto value = item.second;
				if ((dataType == kAttr_Type_Value_bool) || (dataType == kAttr_Type_Value_integer) || (dataType == kAttr_Type_Value_double) || (dataType == kAttr_Type_Value_string)) {
					if (!Dispatch(pContainer, key, value)) {
						break;
					}
					continue;
				}
			}
		}

		return result;
	}



	template<typename TKeyedContainer>
	inline bool LXMLObject::AddKeyedContainerNode(LXMLElement* pLXML, const string& containerNameInContext, TKeyedContainer* pContainerToAdd) {		

		bool result = false;

		if (pLXML == nullptr) { return result; }
		if (pContainerToAdd == nullptr) { return result; }
		if (containerNameInContext.empty()) { return result; }

		LXMLElement* pContainer = pLXML->CreateNewChild(containerNameInContext);
		if (pContainer != nullptr) {
			TAttributes* pObjAttr = pContainer->Attributes();
			pObjAttr->insert({ kAttr_Type, kAttr_Type_Value_keyedcontainer });
			pLXML->AddElement(pContainer);

			for (auto item : *pContainerToAdd) {
				string key = item.first;
				LXMLObject* pObject = static_cast<LXMLObject*>(item.second);
				if (key.empty()) { break; }
				if (!AddObjectNode(pContainer, key, pObject)) {
					break;
				}
			}
		}

		return result;
	}



	template<> 
	inline bool LXMLObject::Dispatch<int>(LXMLElement* pLXML, const string& varNameInContext, const int& value) {
		return AddIntegerNode(pLXML, varNameInContext, value);
	}

	template<>
	inline bool LXMLObject::Dispatch<double>(LXMLElement* pLXML, const string& varNameInContext, const double& value) {
		return AddDoubleNode(pLXML, varNameInContext, value);
	}

	template<>
	inline bool LXMLObject::Dispatch<bool>(LXMLElement* pLXML, const string& varNameInContext, const bool& value) {
		return AddBoolNode(pLXML, varNameInContext, value);
	}

	template<>
	inline bool LXMLObject::Dispatch<string>(LXMLElement* pLXML, const string& varNameInContext, const string& value) {
		return AddStringNode(pLXML, varNameInContext, value);
	}






}
