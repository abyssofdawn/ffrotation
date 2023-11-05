#pragma once
#include <vector>
#ifndef HELPER
#define HELPER

namespace FFRot {
	enum struct SkillType { GCD, OGCD, CAST_GCD, CAST_OGCD};
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
		bool gcd = true;
		bool cast = false;
		int cd = 2500;
		int lock = 100;
	};

	extern std::vector<Skill> skillList;
	struct CharSkill {
		Skill* skill;
		std::vector<Tick> ticks;
	};
	struct GCDTick {
		Skill* skill;
		Tick tick;

	};
	class Character {

	public:
		int id;
		int ping;
		int str, wis, vit, sks, sps, det, dh, crit, pie, ten, hp, _int;
		int gcd;
		std::vector<CharSkill> skills = {};
		std::vector<GCDTick> gcdTicks = {};
		void clearTicks();
		void fitOGCD(int index, int ms);
		enum Job cjob;
		void updateTicks(int index);
		bool isOnCD(int index, int ms);
		void fitGCDAuto(int maxSearch);
		void addTick(int index, int ms);
		int getGCDLength(int index);
		int getAdjustedCD(Skill* skill);
		int getLastTickDelta(int index, int ms);
		Character();
		Character(int id);
		GCDTick getLatestGCD(int ms);
		int getNextGCD(int ms);
		int getGCDNumber(int ms);
		int getLastUsedAtTime(int index, int ms);
		int getLastUsed(int index);
	};
	extern std::vector<Character> chara;
	struct TimelineStats { 
		int zoom, dur;  
	};
	extern std::vector<TimelineStats> t_stats;

	

}
#endif
