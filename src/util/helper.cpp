#include <math.h>
#include "imgui.h"
#include <vector>
#include "character.h"

namespace FFRot {
	std::vector<Character> chara = {};


	float newCd(float cd, int sks) {
		return floor(cd * 1000 * (1000 + ceil(130.0f * (400 - sks) / 1900)) / 10000) / 100;
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
}