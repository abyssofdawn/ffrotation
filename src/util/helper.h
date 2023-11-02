#pragma once
#include <vector>
#ifndef HELPER
#define HELPER

namespace FFRot {
	enum struct Job { PLD, WAR, DRK, GNB, WHM, SCH, AST, SGE, MNK, DRG, NIN, SAM, RPR, BRD, MCH, DNC, BLM, SMN, RDM };
	extern float newCd(float cd, int sks); 
	extern int newCdms(float cd, int sks);
	extern int newCdms(int cd, int sks);
	inline int clampInt(int V, int MN, int MX) { return ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V)); }
	inline float clampFloat(float V, float MN, float MX) { return ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V)); }
	extern void PushStyleCompact();
	extern void PopStyleCompact();

	struct Tick {
		int ms;
		int delay;
	};

	struct Skill {
		bool gcd;
		int cd;
		int lock;
	};

	extern std::vector<Skill> skillList;

	class Character {
		struct CharSkill {
			Skill* skill;
			std::vector<Tick> ticks;
		};
	public:
		int ping;
		int str, wis, vit, sks, sps, det, dh, crit, pie, ten, hp, _int;
		int gcd;
		bool isSksAffected;
		std::vector<CharSkill> skills = {};
		//int id;
		enum Job cjob;
		void updateTicks(float cd);
		Character();
		int getLatestGCD(int ms);
		int getNextGCD(int ms);
		int getGCDNumber(int ms);
	};
	extern std::vector<Character> chara;
	struct TimelineStats { 
		int zoom, dur;  
	};
	extern std::vector<TimelineStats> t_stats;

	

}
#endif
