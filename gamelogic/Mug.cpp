#include "Mug.h"


Mug::Mug(const int& mugnumber, const int& countOfPearls, Mug* previous) : _number{ mugnumber } {

	_pPrevious = previous;
	this->_pMug = new PearlSet();
	for (Pearl i = 1; i <= countOfPearls; i++) {
		this->_pMug->insert(i);
	}
}


bool Mug::PullARandomPearl() {

	bool result = false;

	if (this->_pearl != 0) { return false; }
	if (this->_pMug->empty() == true) { return false; }

	int index = this->ElectAPearl(this->_pMug->size());

	int i = 0;
	Pearl selected = 0;
	for (auto item : *(this->_pMug)) {
		if (i == index) {
			selected = item;
			break;
		}
		i++;
	}

	if (selected > 0) {
		result = this->PullAPearl(selected);
	}	

	return result;
}


bool Mug::PullAPearl(const Pearl& pearl) {

	bool result = false;

	if (this->PearlIsInMug(pearl)) {
		this->_pMug->erase(pearl);
		this->_pearl = pearl;
		result = true;
	}
	return result;
}


bool Mug::PushPearlBackToMug() {
	if (this->_pearl == 0) { return false; }
	this->_pMug->insert(this->_pearl);
	return this->DiscardElected();;
}


bool Mug::DiscardElected() {
	if (this->_pearl == 0) { return false; }
	this->_pearl = 0;
	return true;
}


/// <summary>
/// Random number.
/// size = 3 returns numbers 0, 1, 2.
/// </summary>
/// <param name="size">upper bound</param>
/// <returns>number</returns>
int Mug::ElectAPearl(const unsigned int& sizeOfMug) {

	static bool wasOnceCalled = false;

	if (!wasOnceCalled) {
		srand((unsigned int)time(NULL));
		wasOnceCalled = true;
	}

	if (sizeOfMug == 0) {
		return 0;
	}
	else {
		return (rand() % (sizeOfMug));
	}
}


string Mug::GetDispalyString() {
	return string();
}

Mug::~Mug() {
	SHOWD;
	if (this->_pMug != nullptr) {
		delete this->_pMug; this->_pMug = nullptr;
	}
}
