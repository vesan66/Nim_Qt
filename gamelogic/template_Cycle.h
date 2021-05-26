#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <time.h>       // ERROR - Correction

using namespace std;

template <class TItem, class TContent = std::vector<TItem> >
/// <summary>
/// This class provides a cyclic next item.
/// The class does NOT own the objects.
/// </summary>
/// <typeparam name="ITEM">Any Object.</typeparam>
class Cycle final{
public:
	typedef typename TContent::iterator iterator;
	typedef typename TContent::const_iterator const_iterator;

	Cycle();
	void AddItem(const TItem&);
	void Clear();
	const TItem& operator[](const size_t&) const;
	const TItem& at(const size_t&) const;

	const TItem& GetNextItem();

	void SetPosForNextItem(const size_t& position);
	void MixItB();

	Cycle::iterator begin() noexcept { return this->items->begin(); };
	Cycle::const_iterator begin() const noexcept { return this->items->begin(); };

	Cycle::iterator end() noexcept { return this->items->end(); };
	Cycle::const_iterator end() const noexcept { return this->items->end(); };

    size_t size() const;
	~Cycle();
private:
	vector<TItem>* items;
	int pos;

	void IncCycle(int& value, const int& min, const int& max);
	//void DecCycle(int& value, const int& min, const int& max);
	int GetRndBtw_0_And_Smaller_Than_Size(const unsigned int& upperLimit) const;
};


template <class TItem, class TContent>
inline Cycle<TItem, TContent>::Cycle() :
	items{ new vector<TItem> }, pos {0}
{
}

template<class TItem, class TContent>
inline void Cycle<TItem, TContent>::Clear() {
	this->items->clear();
	this->pos = 0;
}


template<class TItem, class TContent>
inline void Cycle<TItem, TContent>::MixItB() {

	if (this->items->empty()) { return; }

	vector<TItem>* itemsTMP = new vector<TItem>();

	while (this->items->empty() != true) {
		int p = this->GetRndBtw_0_And_Smaller_Than_Size(this->items->size());
		TItem tmp = this->items->at(p);
		itemsTMP->push_back(tmp);
		this->items->erase(this->items->begin() + p);
	}

	delete this->items;
	this->items = itemsTMP;
	this->pos = 0;
}


template<class TItem, class TContent>
inline void Cycle<TItem, TContent>::IncCycle(int& value, const int& min, const int& max) {
	if (value >= max) { value = min; return; }
	value++;
}


template<class TItem, class TContent>
inline void Cycle<TItem, TContent>::SetPosForNextItem(const size_t& position) {
	if ((position < 0) && (position >= this->items->size())) { return; }
	this->pos = position;
}


template <class TItem, class TContent>
inline void Cycle<TItem, TContent>::AddItem(const TItem& item) {
	this->items->push_back(item);
}


template <class TItem, class TContent>
inline const TItem& Cycle<TItem, TContent>::operator[](const size_t& pos) const {
	return this->items->at(pos);
}


template <class TItem, class TContent>
inline const TItem& Cycle<TItem, TContent>::at(const size_t& pos) const {
	return this->items->at(pos);
}


template <class TItem, class TContent>
/// <summary>
/// Get the next Item. At first: NextItem is equal to GetFirst-Something.
/// </summary>
/// <typeparam name="TItem"></typeparam>
/// <typeparam name="TContent"></typeparam>
/// <returns>Next Item.</returns>
inline const TItem& Cycle<TItem, TContent>::GetNextItem() {		
	assert(this->items->size() != 0);	

	TItem& result = this->items->at(pos);
	this->IncCycle(pos, 0, (this->items->size() - 1));

	return result;
}


template <class TItem, class TContent>
inline size_t Cycle<TItem, TContent>::size() const {
	return this->items->size();
}


template <class TItem, class TContent>
inline Cycle<TItem, TContent>::~Cycle() {
	if (this->items != nullptr) { delete this->items; this->items = nullptr; }
}

template<class TItem, class TContent>
inline int Cycle<TItem, TContent>::GetRndBtw_0_And_Smaller_Than_Size(const unsigned int& size) const{

	static bool wasOnceCalled = false;

	if (!wasOnceCalled) {
		srand((unsigned int)time(NULL));
		wasOnceCalled = true;
	}

	if (size == 0) {  
		return 0;
	} else {
		return (rand() % size);
	}
}
