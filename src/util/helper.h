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
	class Character;
	class Effect;
	enum class EffectType {
		HEAL, SHIELD, BONUS_HP,									//healing things
		AGGRO,													//tank things
		CRIT, DHIT,												//dps things
		BUFF, DEBUFF, COND_STATUS, MOD_BUFF,					//status effect
		MOVE_SELF, MOVE_OTHER, MOVE_TOWARDS,					//movement things
		//MOD_GAUGE,											//gauge
		DMG_UP, DMG_DOWN, VULN_UP, VULN_DOWN,					//passive effect
		OUT_DMG, COOL_DOWN, HASTE								//misc
	};

	enum class TargetType { SELF, FRIEND, FOE, SPECIAL };

	class StatusEffect {
	public:
		int id = -1;
		std::string name = "";
		bool isBuff = true;
		bool isFriendly = true;
		bool overTime = true;
		bool hasStacks = false;
		bool isGaugeBuff = false;
		int maxStacks = -1;
		int duration = -1;
		Effect* effect;
	};

	class Effect {
	public:
		EffectType type = EffectType::OUT_DMG;					//default is do damage
		std::vector<int> args = {};
		int radius = 0;
		TargetType targetType = TargetType::SELF;
	};

	class Skill
	{
	public:
		int id = -1;
		std::string name = "";
		bool gcd = true;
		bool cast = false;
		int cd = 2500;
		int lock = 100;
		int recast = 2500;
		int range = 0;
		int maxStacks = 1;
		std::vector<Effect> effects;
		std::vector<int> comboIds;
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
		int getLatestGeneralUseForIndex(int index);
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
