#pragma once
#include <map>
#include "../gamelogic/globals_globals.h"

namespace MMKT {

	class MultimapKeyedTreeConnector;

	class MultimapKeyedTreeElement {
	public:
		// Friend
		friend class MultimapKeyedTreeConnector;

		// Types
		typedef string TKeyStr;
		typedef bool   TWasInserted;
		typedef pair<TKeyStr, MultimapKeyedTreeElement*> TItem;
		typedef multimap<TItem::first_type, TItem::second_type> TMap;

		// Constructors
		MultimapKeyedTreeElement() = delete;
		MultimapKeyedTreeElement(const MultimapKeyedTreeElement&) = delete;
		MultimapKeyedTreeElement& operator=(const MultimapKeyedTreeElement&) = delete;

		// Properties
		inline TWasInserted WasInserted() const { return this->_wasInserted; }
		inline void SetWasInserted() { this->_wasInserted = true; }

		inline TKeyStr Key() const { return this->_key; }
		inline bool SetKey(const TKeyStr& key) {
			if (key.empty()) { return false; }
			if (this->_wasInserted) { return false; }
			this->_key = key;
			return true;
		};

		inline TMap* Childs() const { return _pMap; };

		inline MultimapKeyedTreeElement* Parent() const { return this->_pParent; }

		// Methods
		virtual MultimapKeyedTreeElement* CreateNewChild();
		virtual MultimapKeyedTreeElement* CreateNewChild(const TKeyStr& key);
		bool AddElement(MultimapKeyedTreeElement* element);		

	protected:
		explicit MultimapKeyedTreeElement(MultimapKeyedTreeElement* parent);
		explicit MultimapKeyedTreeElement(MultimapKeyedTreeElement* parent, const TKeyStr& key);
		virtual ~MultimapKeyedTreeElement();

		virtual MultimapKeyedTreeConnector* CreateConnector();
		inline virtual MultimapKeyedTreeConnector* Connector() { 
			if (_pConnector == nullptr) {
				_pConnector = CreateConnector();
			}			
			return _pConnector; }
	private:
		MultimapKeyedTreeElement* _pParent{};
		MultimapKeyedTreeConnector* _pConnector{};	// I own.
		TMap* _pMap{};		// I own.					
		TKeyStr						_key{};
		TWasInserted				_wasInserted{};
	};
}
