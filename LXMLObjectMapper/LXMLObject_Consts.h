#pragma once

namespace LXMLObjects {
	constexpr const char* kTag_TopNode{ "LXML" };
	constexpr const char* kTag_RootNode{ "ROOT" };
	constexpr const char* kTag_ContainerItemNode{ "ITEM" };

	constexpr const char* kAttr_NameSpace{ "xmlns" };
	constexpr const char* kAttr_LXMLVersion{ "lxmlversion" };
	constexpr const char* kAttr_Value_LXMLVersion{ "1.0" };

	constexpr const char* kAttr_Type{ "type" };
	constexpr const char* kAttr_Type_Value_object{ "object" };
	constexpr const char* kAttr_Type_Value_container{ "container" };
	constexpr const char* kAttr_Type_Value_keyedcontainer{ "keyedcontainer" };
	constexpr const char* kAttr_Type_Value_SimpleContainer{ "simplecontainer" };
	constexpr const char* kAttr_Type_Value_KeyedSimpleContainer{ "simplekeyedcontainer" };
	constexpr const char* kAttr_Type_Value_string{ "string" };
	constexpr const char* kAttr_Type_Value_integer{ "integer" };
	constexpr const char* kAttr_Type_Value_double{ "double" };
	constexpr const char* kAttr_Type_Value_bool{ "bool" };

	constexpr const char* kAttr_Encoded{ "encoded" };
	constexpr const char* kAttr_Encoded_Value_BinHex{ "binhex" };
	constexpr const char* kAttr_Encoded_Value_No{ "no" };



	constexpr const char* kAttr_ClassName{ "classname" };
	

	constexpr const char* kAttr_DataVersion{ "dataversion" };
}