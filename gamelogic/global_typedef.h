#pragma once
#include <vector>
#include <map>

using namespace std;

class Player;
class Move;
class Mug;

namespace cnst {
	typedef vector<Player*> PlayerList;
	//typedef PlayerList::iterator iterator;

	typedef vector<Move*> Moves;


	//typedef pair<const string&, Mug*> MugPair;
	//typedef map<MugPair::first_type, MugPair::second_type> Mugs;
	//typedef map<const string&, Mug*> Mugs;
}