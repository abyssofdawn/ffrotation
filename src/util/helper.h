#pragma once
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
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

	struct Skill {
		bool gcd = true;
		bool cast = false;
		int cd = 2500;
		int lock = 100;
	};

	extern std::vector<Skill> skillList;
	struct SkillTick {
		int ms;
		int delay;
	};
	struct CharSkill {
		Skill* skill;
		std::vector<SkillTick> ticks;
	};
	struct GeneralTick {
		Skill* skill;
		int ms;
		int recast;
	};
	class Character {

	public:
		int id;
		int ping;
		int str, wis, vit, sks, sps, det, dh, crit, pie, ten, hp, _int;
		int gcd;
		std::vector<CharSkill> skills = {};
		std::vector<GeneralTick> gcdTicks = {};
		std::vector<GeneralTick> generalTicks = {};

		void clearTicks();
		void clearSkills();
		void pushSkillTick(int index, int ms);
		int inUsableRange(int index, int ms);
		bool isOffCd(int index, int ms);
		int getLastUseByTime(int index, int ms);
		GeneralTick getLastUsedGCDByTime(int ms);
		int getLastUsedGeneralIndexByTime(int ms);
		int getNextUsedGeneralIndexByTime(int ms);
		GeneralTick getNextUsedGCDByTime(int ms);
		int getLastUsedGCDIndexByTime(int ms);
		int getNextUsedGCDIndexByTime(int ms);
		int getLatestUsedOGCDIndex();
		int getSpeedStatForSkill(int index);
		int getSpeedStatForSkill(Skill* skill);
		int getAnimationLockForSkill(int index);
		int getAnimationLockForSkill(Skill* skill);
		enum Job cjob;
		void updateTicks(int index);
		void fitGCDAuto(int maxSearch);
		void fitOGCDAuto(int maxSearch);
		void makeSkills();
		int selectedSkill = -1;
		Character();
		Character(int id);

	};
	extern std::vector<Character> chara;
	struct TimelineStats { 
		int zoom, dur;  
	};
	extern std::vector<TimelineStats> t_stats;
	extern void to_json(json& j, const Skill& skill);
	extern void from_json(const json& j, Skill& skill);
	extern int selectedChar;
	

}
#endif
