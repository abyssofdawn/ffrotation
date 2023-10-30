#pragma once
#include <vector>
#include "character.h"
#ifndef HELPER
#define HELPER

namespace FFRot {
	extern float newCd(float cd, int sks); 
	inline int clampInt(int V, int MN, int MX) { return ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V)); }
	extern void PushStyleCompact();
	extern void PopStyleCompact();
	extern float TEXT_BASE_WIDTH;
	extern float TEXT_BASE_HEIGHT;
	extern std::vector<Character> chara;

}
#endif
