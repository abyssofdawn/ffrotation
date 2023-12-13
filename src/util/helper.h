#pragma once
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
#ifndef HELPER
#define HELPER

namespace FFRot {
	enum struct SkillType { GCD, OGCD, CAST_GCD, CAST_OGCD};
	enum struct Job { PLD = 0, WAR = 2, DRK = 3, GNB = 4, WHM = 5, SCH = 6, AST = 7, SGE = 8, MNK = 9, DRG = 10, NIN = 11, SAM = 12, RPR = 13, BRD = 14, MCH = 15, DNC = 16, BLM = 17, SMN =  18, RDM = 19, NONE = 20};
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
		HEAL,				//args: potency, stat					
		SET_HP,				//args: hp
		SHIELD,				//args: potency, stat
		BONUS_HP,			//args:	percent increase				
		AGGRO,				//args:	aggro type, aggro modifier (type: instant, buff)	
		MANA,				//args: delta
		CRIT,				//args:	percent increase
		DHIT,				//args: percent increase			
		STATUS,				//args:	id
		COND_STATUS,		//args:	id, triggers id, proc type (type: on out damage, on in damage, at hp threshold distance, on move, on expire, on combo, has buff)
		MOD_STATUS,			//args:	id, mod type (type: change dur, change stacks), amount
		STATUS_WITH_ARGS,	//args: id, arg 1, arg 2
		MOVE_SELF,			//args:	x, y
		MOVE_OTHER, 		//args: x, y
		MOVE_TOWARDS,		//args:	id		
		DMG_UP, 			//args:	percent increase
		DMG_DOWN,			//args:	percent decrease
		VULN_UP, 			//args:	percent increase
		VULN_DOWN,			//args:	percent decrease
		PARRY_UP,			//args:	rate, amount
		OUT_DMG,			//args:	potency, stat
		COOL_DOWN, 			//args:	id
		HASTE,				//args:	percent increase			
		COMBO,				//args: id
		SPECIAL,			//args: id
		NONE
	};

	enum class TargetType { SELF, FRIEND, FOE, SPECIAL };

	class StatusEffect {
	public:
		StatusEffect();
		int id;											//used in effect args
		std::string name;
		bool isBuff ;
		bool isFriendly;
		bool overTime ;
		bool hasStacks ;
		bool isGaugeBuff;
		int maxStacks;
		int duration;
		int effect;
		bool canCleanse;
		std::vector<int> procs;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(StatusEffect, id, name, isBuff, isFriendly, overTime, hasStacks, isGaugeBuff, maxStacks, duration, effect, canCleanse, procs);
	};

	class Effect {
	public:
		Effect();
		int id;
		std::vector<int> arg;								//contains things like potency and buff id
		int radius;											//radius of effect centered on the target
		EffectType type;									//default is do damage
		TargetType affectsType;								//who the effect applies to

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Effect, id, arg, radius, type, affectsType);

	};

	class Skill { 
	
	public:
		Skill();
		int id;
		std::string name;
		SkillType type;
		bool gcd;
		bool cast;
		int cd;
		int lock;
		int recast;
		int range;
		int maxStacks;
		std::vector<int> effects;
		std::vector<int> comboIds;
		bool breaksCombo;
		TargetType targetType;				//who the effect targets (for location)
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Skill, id, name, type, gcd, cast, cd, lock, recast, range, maxStacks, effects, comboIds, breaksCombo, targetType);
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
		Character& instance();
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
	extern int selectedChar;

}
#endif
