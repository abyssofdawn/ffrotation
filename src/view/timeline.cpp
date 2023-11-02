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
		int height = 20;
		int pheight = height + padding;

		int width = sz.x - 2*padding;
		float step_size = FFRot::t_stats[0].dur / (width) > 0 ? FFRot::t_stats[0].dur / float(width) : 1.0f;
		draw_list->AddRectFilled(ImVec2(p0.x + padding, p0.y), ImVec2(width + p0.x+padding, p0.y + height), ImColor(100, 200, 255));
		int posx;

		// draws white lines for calculated gcd of first character 

		if (chara.size() > 0) {
			for (int i = 0; i < FFRot::t_stats[0].dur; i += int(newCd(2.5f, chara[0].sks)*1000)) {
				posx = int((i) / step_size);

				if (!(posx > width))
					draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y), ImVec2(p0.x + padding + posx + 1, p0.y + height), ImColor(255, 255, 255));
				else break;
			}
			int posy = ImGui::GetCursorPosY() + height;
			ImGui::SetCursorPosY(posy);
			// draws blue lines for tick marks stored

			for (int n = 0; n < chara[0].skills.size(); n++) {
				for (auto it = chara[0].skills[n].ticks.begin(); it != chara[0].skills[n].ticks.end(); ++it) {

					posx = int(it->ms / step_size);
					if (!(posx > width))
						draw_list->AddRectFilled(ImVec2(p0.x + padding + posx, p0.y), ImVec2(p0.x + padding + posx + 1, p0.y + height), ImColor(50, 100, 200));
					else break;
				}
			}

		}

		




		ImGui::PopStyleVar();
		
		if (chara.size() > 0) {
			if (ImGui::BeginListBox("ticks")) {
				if (chara[0].skills[0].ticks.size() > 0) {
					for (int n = 0; n < chara[0].skills[0].ticks.size(); n++) {
						ImGui::Text("ms=%d delay=%d", chara[0].skills[0].ticks[n].ms, chara[0].skills[0].ticks[n].delay);
					}
				}
				ImGui::EndListBox();
			}
		}

 		ImGui::End();
	}
}