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
		int width = sz.x - 10;
		float step_size = FFRot::t_stats[0].dur / (width) > 0 ? FFRot::t_stats[0].dur / float(width) : 1.0f;
		draw_list->AddRectFilled(ImVec2(p0.x + 5, p0.y), ImVec2(width + p0.x+5, p0.y + 50), ImColor(100, 200, 255));
		int posx;

		// draws white lines for calculated gcd of first character 

		if (chara.size() > 0) {
			for (int i = 0; i < FFRot::t_stats[0].dur; i += int(newCd(2.5f, chara[0].sks)*1000)) {
				posx = int((i) / step_size);

				if (!(posx > width))
					draw_list->AddRectFilled(ImVec2(p0.x + 5 + posx, p0.y), ImVec2(p0.x + 5 + posx + 1, p0.y + 50), ImColor(255, 255, 255));
				else break;
			}

			// draws blue lines for tick marks stored, will be changed later to support dynamic cds
			if (chara[0].ticksById.size() > 0) {
				for (auto it = chara[0].ticksById[0].begin(); it != chara[0].ticksById[0].end(); ++it) {

					posx = int((*it) / step_size);
					if (!(posx > width))
						draw_list->AddRectFilled(ImVec2(p0.x + 5 + posx, p0.y), ImVec2(p0.x + 5 + posx + 1, p0.y + 50), ImColor(50, 100, 200));
					else break;
				}
			}
		}

		




		ImGui::PopStyleVar();

 		ImGui::End();
	}
}