#pragma once
#include <math.h>
#include "imgui.h"
#include <vector>
#include "helper.h"

namespace FFRot {


	Skill::Skill() {
		id = -1;
		name = "test name";
		type = SkillType::GCD;
		gcd = true;
		cast = false;
		cd = 2500;
		lock = 100;
		recast = 2500;
		range = 0;
		maxStacks = 1;
		effects = {};
		comboIds = {};
		breaksCombo = false;
		targetType = TargetType::SELF;				//who the effect targets (for location)
	}


	Effect::Effect() {

		id = -1;
		arg = {};								//contains things like potency and buff id
		radius = 0;											//radius of effect centered on the target
		type = EffectType::OUT_DMG;					//default is do damage
		affectsType = TargetType::SELF;				//who the effect applies to

	};

	StatusEffect::StatusEffect() {
		id = -1;											//used in effect args
		name = "";
		isBuff = true;
		isFriendly = true;
		overTime = true;
		hasStacks = false;
		isGaugeBuff = false;
		maxStacks = -1;
		duration = -1;
		effect = -1;
		canCleanse = false;
		procs = {};		
	};
	std::vector<Character> chara = {};
	std::vector<TimelineStats> t_stats = {};
	std::vector<std::vector<int>> ticks = {};
	std::vector<Skill> skillList = {};
	std::string Job_[] = { "PLD" , "WAR", "DRK", "GNB", "WHM", "SCH", "AST", "SGE", "MNK" , "DRG" , "NIN" , "SAM" , "RPR" , "BRD" , "MCH" , "DNC" , "BLM" , "SMN" , "RDM" , "NONE" };

	float newCd(float cd, int sks) {
		return floor(cd * 1000 * (1000 + ceil(130.0f * (400 - sks) / 1900)) / 10000) / 100;
	}

	int newCdms(float cd, int sks) {
		return floor(cd * 1000 * (1000 + ceil(130.0f * (400 - sks) / 1900)) / 10000) * 10;
	}

	int newCdms(int cd, int sks) {
		return floor(cd * (1000 + ceil(130.0f * (400 - sks) / 1900)) / 10000) * 10;
	}

	void PushStyleCompact()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
	}

	void PopStyleCompact()
	{
		ImGui::PopStyleVar(2);
	}

	int selectedChar = 0;




}