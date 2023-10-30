#pragma once
#include <vector>
#include "character.h"
#ifndef HELPER
#define HELPER

namespace FFRot {
	extern float newCd(float cd, int sks); 
	inline int clampInt(int V, int MN, int MX) { return ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V)); }
	inline float clampFloat(float V, float MN, float MX) { return ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V)); }
	extern void PushStyleCompact();
	extern void PopStyleCompact();
	extern std::vector<Character> chara;
	struct TimelineStats { 
		int zoom, dur;  
	};
	extern std::vector<TimelineStats> t_stats;
	extern std::vector<std::vector<int>> ticks;
}
#endif
