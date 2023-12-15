#include "views.h"
#include "../util/classes.h"
#include "../util/helper.h"
#include <sstream>

namespace FFRot {
	void SkillTableWidget(Skill& skill) {
		//if (ImGui::BeginTable("Skill Table", 2)) {
		//
		//	ImGui::TableSetupColumn("stat");
		//	ImGui::TableSetupColumn("value");
		//
		//	ImGui::TableHeadersRow();
		//
		//	ImGui::TableNextRow();
		//	ImGui::NextColumn();
		//	ImGui::Text("Name");
		//	ImGui::NextColumn();
		//	ImGui::InputText("name##skill name table", &skill.name);
		//
		//
		//
		//
		//	ImGui::EndTable();
		//}


	}

	Skill NewSkill(Skill& oldskill) {
		Skill skill = oldskill;

		ImGui::InputText("Name##name", &oldskill.name );
		ImGui::Checkbox("Breaks combo##combo break", &oldskill.breaksCombo);
		ImGui::Checkbox("Is cast##cast", &oldskill.cast);
		ImGui::PushItemWidth(ImGui::GetFontSize() * 7);
		ImGui::InputInt("Is gcd##gcd", &oldskill.gcd);
		ImGui::InputInt("Cooldown##cd", &oldskill.cd);
		ImGui::InputInt("Recast##recast", &oldskill.recast);
		ImGui::InputInt("Animation lock##lock", &oldskill.lock);
		ImGui::InputInt("Max stack##max stack", &oldskill.maxStacks);
		ImGui::InputInt("Range##range", &oldskill.range);
		ImGui::PopItemWidth();

		oldskill.cd = clampInt(oldskill.cd, 10, 720000);	
		oldskill.recast = clampInt(oldskill.recast, 10, 60000);
		oldskill.gcd = clampInt(oldskill.gcd, 10, 5000);
		oldskill.lock = clampInt(oldskill.lock, 10, 5000);
		oldskill.maxStacks = clampInt(oldskill.maxStacks, 1, 10);
		oldskill.range = clampInt(oldskill.range, 0, 100);
		return skill;
	}
	
}