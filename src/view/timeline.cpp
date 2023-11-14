#include <imgui.h>
#include "views.h"
#include "fmt/format.h"
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
		GeneralTick lastGCD = {};
		GeneralTick nextGCD = {};
		ImGuiIO& io = ImGui::GetIO();
		int mousems = int((io.MousePos.x - p0.x) * step_size);



		if (chara.size() > 0 && chara.at(selectedChar).gcdTicks.size()>0) {
			lastGCD = chara.at(selectedChar).getLastUsedGCDByTime(mousems);
			nextGCD = chara.at(selectedChar).getNextUsedGCDByTime(mousems);

		}

		if (chara.size() > 0 && !skillList.empty()) {

			for (auto& tick : chara.at(selectedChar).gcdTicks) {//draws range where ogcds can be used (and assumes ogcd anim lock is 500ms, will be changed later for "selecting" ogcds)
				posx = int((tick.ms + tick.skill->lock + chara.at(selectedChar).ping) / step_size);
				int posx2 = int((tick.recast - 500 - chara.at(selectedChar).ping) / step_size);
				if (!(posx > width))
					draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y), ImVec2(p0.x + padding + posx2, p0.y + height), ImColor(110, 163, 108));
				else break;
			}
			for (int i = 0; i < chara.at(selectedChar).gcdTicks.size(); i++) {// draws white lines for calculated gcd of first character 
				posx = int((chara.at(selectedChar).gcdTicks[i].ms) / step_size);

				if (!(posx > width))
					draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y), ImVec2(p0.x + padding + posx + 1, p0.y + height), ImColor(255, 255, 255));
				else break;
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
			// draws blue lines for tick marks stored

			for (int n = 0; n < chara.at(selectedChar).skills.size(); n++) {
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);//moves cursor down for every skill
				for (auto it = chara.at(selectedChar).skills[n].ticks.begin(); it != chara.at(selectedChar).skills[n].ticks.end(); ++it) {//loop through all skills, draws delay and ticks on new lines

					posx = int(it->ms / step_size);
					dposx = int((it->ms - it->delay) / step_size);
					if (!(posx > width)) {
						draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y + (n + 1) * height), ImVec2(p0.x + padding + posx + 1, p0.y + (n + 2) * height), ImColor(50, 100, 200)); //delay
						draw_list->AddRectFilled(ImVec2(p0.x + padding + dposx, p0.y + (n + 1) * height), ImVec2(p0.x + padding + posx, p0.y + (n + 2) * height), ImColor(163, 91, 91));//tick
					}
					else break;
				}
			}


		}
		if (chara.size() > 0 && chara.at(selectedChar).gcdTicks.size() > 1 && skillList.size()>0) {
			posx = int(lastGCD.ms / step_size);
			int posx1 = int((lastGCD.ms + lastGCD.skill->lock + chara.at(selectedChar).ping)/step_size);
			int posx2 = int((nextGCD.ms - 500 - chara.at(selectedChar).ping) / step_size);
			if (mousems-lastGCD.ms > lastGCD.skill->lock + chara.at(selectedChar).ping
				&&	nextGCD.ms - mousems > 500+chara.at(selectedChar).ping) {

				draw_list->AddRectFilled(ImVec2(p0.x + padding + posx1, p0.y),
					ImVec2(p0.x + padding + posx2, io.MousePos.y), ImColor(110, 163, 108));
			}
			else if (posx < int(t_stats.at(0).dur / step_size)) {
				if (mousems - lastGCD.ms > lastGCD.skill->lock + chara.at(selectedChar).ping) {
					posx1 = posx2;
					posx2 = int(nextGCD.ms / step_size);

				}
				if (nextGCD.ms - mousems > 500 + chara.at(selectedChar).ping) {
					posx2 = posx1;
					posx1 = posx;
				}
				draw_list->AddRectFilled(ImVec2(p0.x + padding + posx1, p0.y),
					ImVec2(p0.x + padding + posx2, io.MousePos.y), ImColor(134, 89, 168));
			}

			draw_list->AddRectFilled({ p0.x + padding + posx, p0.y }, { p0.x + padding + posx + 1, io.MousePos.y }, IM_COL32_WHITE);
			posx = int(nextGCD.ms / step_size);
			draw_list->AddRectFilled({ p0.x + padding + posx, p0.y }, { p0.x + padding + posx + 1, io.MousePos.y }, IM_COL32_WHITE);

		}

		ImGui::PopStyleVar();


		if (chara.size() > 0 && !skillList.empty() && chara.at(selectedChar).selectedSkill > -1 ) 
		{

			Character* selchar = &chara.at(selectedChar);
			CharSkill selSkill = selchar->skills.at(selchar->selectedSkill);

			ImGui::Text(fmt::format("{} {} {}",
				selchar->getLastUsedGeneralIndexByTime(mousems),
				selchar->getNextUsedGeneralIndexByTime(mousems),
				selchar->generalTicks.at(selchar->getLastUsedGeneralIndexByTime(mousems)).ms
				).c_str());
			if (ImGui::BeginListBox("ticks")) {
				if (selSkill.ticks.size() > 0) {
					for (int n = 0; n < selSkill.ticks.size(); n++) {
						ImGui::Text(fmt::format("{} {}", selSkill.ticks.at(n).ms, selSkill.ticks.at(n).delay).c_str());
					}
				}
				/*if (chara.at(selectedChar).gcdTicks.size() > 0) {
					for (int n = 0; n < chara.at(selectedChar).gcdTicks.size(); n++) {
						ImGui::Text(fmt::format("{} {}", chara.at(selectedChar).gcdTicks.at(n).ms, chara.at(selectedChar).gcdTicks.at(n).recast).c_str());
					}
				}*/
				ImGui::EndListBox();
			}
		}

		ImGui::End();
	}
}