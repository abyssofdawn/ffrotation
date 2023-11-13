#include <imgui.h>
#include "views.h"
#include "../util/helper.h"

namespace FFRot {
	void ShowTimelineWindow() {
		ImGui::Begin("Timeline");
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImGui::Text("Timeline!!"); ImGui::SameLine();
		ImGui::InputInt("##timeline_duration", &FFRot::t_stats[0].dur, 0, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImVec2 p0 = ImGui::GetCursorScreenPos();
		ImVec2 sz = ImGui::GetContentRegionAvail();
		int padding = 0;
		int ypadding = 5;
		int height = 5;
		int pheight = height + padding;

		int width = sz.x - 2 * padding;
		float step_size = FFRot::t_stats[0].dur / (width) > 0 ? FFRot::t_stats[0].dur / float(width) : 1.0f;
		draw_list->AddRectFilled(ImVec2(p0.x + padding, p0.y), ImVec2(width + p0.x + padding, p0.y + height), ImColor(100, 200, 255));
		int posx;
		int dposx;

		if (chara.size() > 0 && !skillList.empty()) {

			for (auto& tick : chara.at(selectedChar).gcdTicks) {//draws range where ogcds can be used (and assumes ogcd anim lock is 500ms, will be changed later for "selecting" ogcds)
				posx = int((tick.tick.ms + tick.skill->lock + chara.at(selectedChar).ping) / step_size);
				int posx2 = int((tick.tick.ms + tick.tick.delay - 500) / step_size);
				if (!(posx > width))
					draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y), ImVec2(p0.x + padding + posx2, p0.y + height), ImColor(110, 163, 108));
				else break;
			}
			for (int i = 0; i < chara.at(selectedChar).gcdTicks.size(); i++) {// draws white lines for calculated gcd of first character 
				posx = int((chara.at(selectedChar).gcdTicks[i].tick.ms) / step_size);

				if (!(posx > width))
					draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y), ImVec2(p0.x + padding + posx + 1, p0.y + height), ImColor(255, 255, 255));
				else break;
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
			// draws blue lines for tick marks stored

			for (int n = 0; n < chara.at(selectedChar).skills.size(); n++) {
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);//moves cursor down for every skill
				for (auto it = chara.at(selectedChar).skills[n].ticks.begin(); it != chara.at(selectedChar).skills[n].ticks.end(); ++it) {//loop through all skills, draws delay and ticks on separate lines that go up to the top of the original timeline

					posx = int(it->ms / step_size);
					dposx = int((it->ms - it->delay) / step_size);
					if (!(posx > width)) {
						draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y + (n + 1) * height), ImVec2(p0.x + padding + posx + 1, p0.y + (n + 2) * height), ImColor(50, 100, 200));
						draw_list->AddRectFilled(ImVec2(p0.x + padding + dposx, p0.y + (n + 1) * height), ImVec2(p0.x + padding + posx, p0.y + (n + 2) * height), ImColor(163, 91, 91));
					}
					else break;
				}
			}


		}


		ImGui::PopStyleVar();

		if (chara.size() > 0 && !skillList.empty()) {
			if (ImGui::BeginListBox("ticks")) {
				if (chara.at(selectedChar).skills.at(0).ticks.size() > 0) {
					for (int n = 0; n < chara.at(selectedChar).skills.at(0).ticks.size(); n++) {
						ImGui::Text("%d", chara.at(selectedChar).getLastUsedAtTime(0, chara.at(selectedChar).skills.at(0).ticks.at(n).ms));
					}
				}
				ImGui::EndListBox();
			}
		}

		ImGui::End();
	}
}