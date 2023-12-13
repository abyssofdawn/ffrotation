#pragma once
#include "views.h"
#include <imgui.h>
#include "fmt/format.h"
#include "../util/helper.h"
#include "../util/classes.h"


namespace FFRot {
	void ShowSkillsWindow() {

		float TEXT_BASE_WIDTH = 4.0f * ImGui::GetFontSize() / 6.0f;
		float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

		ImGui::Begin("Skills window");
		ImGui::Text("test");

		if (!jobClass.empty()) {
			int curindex = 0;
			if (ImGui::BeginListBox("class dropdown")) {
				for (int i = 0; i < jobClass.size(); i++) {
					const bool is_selected = (curindex == i);
					if (ImGui::Selectable(fmt::format("class: {}", int(jobClass.at(i).job)).c_str(), is_selected))
						curindex = i;

					if (is_selected) ImGui::SetItemDefaultFocus();
				}
			}




		}

		ImGui::End();


	}
}