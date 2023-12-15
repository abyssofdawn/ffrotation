#pragma once
#include "../util/helper.h"
#include "../util/classes.h"


#ifndef VIEWS
#define VIEWS
namespace FFRot {
	extern bool ShowSkillBuilder(JobClass& job);
	extern void ShowSkillsWindow();
	extern void ShowSKSWindow();
	extern void ShowTimelineWindow();
	extern void SkillTableWidget(Skill& skill);
	extern Skill NewSkill(Skill& oldskill);
}
#endif