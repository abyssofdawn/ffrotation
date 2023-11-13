#include <math.h>
#include "imgui.h"
#include <vector>
#include "helper.h"

namespace FFRot {
	std::vector<Character> chara = {};
	std::vector<TimelineStats> t_stats = {};
	std::vector<std::vector<int>> ticks = {};
	std::vector<Skill> skillList = {};

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

	void to_json(json& j, const Skill& skill)
	{
		j = json{ {"gcd", skill.gcd}, {"cast", skill.cast}, {"cd", skill.cd}, {"lock", skill.lock} };
	}

	void from_json(const json& j, Skill& skill)
	{
		j.at("gcd").get_to(skill.gcd);
		j.at("cast").get_to(skill.cast);
		j.at("cd").get_to(skill.cd);
		j.at("lock").get_to(skill.lock);

	}

	int selectedChar = 0;



}