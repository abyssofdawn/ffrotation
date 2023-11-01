#pragma once
#include <vector>
#ifndef HELPER
#define HELPER

namespace FFRot {
	enum struct Job { PLD, WAR, DRK, GNB, WHM, SCH, AST, SGE, MNK, DRG, NIN, SAM, RPR, BRD, MCH, DNC, BLM, SMN, RDM };
	extern float newCd(float cd, int sks); 
	inline int clampInt(int V, int MN, int MX) { return ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V)); }
	inline float clampFloat(float V, float MN, float MX) { return ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V)); }
	extern void PushStyleCompact();
	extern void PopStyleCompact();
	class Character {

	public:
		int str, wis, vit, sks, sps, det, dh, crit, pie, ten, hp;
		std::vector<std::vector<int>> ticksById = {};
		//int id;
		enum Job cjob;

		void updateTicks(float cd);
	};
	extern std::vector<Character> chara;
	struct TimelineStats { 
		int zoom, dur;  
	};
	extern std::vector<TimelineStats> t_stats;

 

}
#endif
