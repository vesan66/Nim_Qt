#pragma once
#include <iostream>
#include <locale>
#include <thread>
#include <chrono>
#include <conio.h>
#include "global_const.h"
#include "global_macros.h"
#include "global_func.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__
//do some stuff for Apple
#elif __linux__
//do stuff for Linux
#endif

using namespace std;

namespace cnst {	
	class Mousetrap final {
	public:
		inline Mousetrap() {}

		inline bool StartTrap() {
			if (this->t == nullptr) {
				this->receivedChar = '\0';
				this->wantsCancel = false;
				this->t = new thread(&Mousetrap::Trap, this);
				return true;
			}
			return false;
		}

		inline void TerminateTrap() {
			if (this->t != nullptr) {
				this->wantsCancel = true;
				this->t->join();
				delete this->t; this->t = nullptr;
			}
		}

		inline char GetReceivedChar() const { return this->receivedChar; }
		inline void ConsumeReceivedChar() { this->receivedChar = '\0'; }
		inline void SetSkipDetection(const bool& skip) { this->skip = skip; }

		inline ~Mousetrap() { SHOWD; this->TerminateTrap(); }

	private:
		const double slowdown = 1.00;
		//const double slowdown = 0.50;
		thread* t = nullptr;
		char receivedChar = '\0';
		bool wantsCancel = false;
		bool skip = false;

		inline static void Trap(Mousetrap* self) {
			while (!self->wantsCancel) {
				if (!self->skip) {
					if (_kbhit() != 0) {
						self->receivedChar = _getch();
						cin.clear();						
					}
				}
				cnst::WaitSeconds(self->slowdown);
				//cout << '.';
			}
		}
	};
}
