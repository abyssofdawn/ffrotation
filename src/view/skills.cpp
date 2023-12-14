#include "imgui.h"
#include "views.h"
#include "fmt/format.h"
#include "../util/helper.h"
#include "../util/classes.h"


namespace FFRot {
	void ShowSkillsWindow() {


		ImGui::Begin("Skill");
		ImGui::Text("test");

		if (!jobClass.empty()) {

			static int curindex = 0;
			static int curskillindex = 0;
			const char* combo_preview_value = Job_[curindex].c_str();

			if (ImGui::BeginCombo("class dropdown", combo_preview_value)) {
				for (int i = 0; i < jobClass.size(); i++) {
					const bool is_selected = (curindex == i);
					if (ImGui::Selectable(Job_[i].c_str(), is_selected))
						curindex = i;

					if (is_selected) ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			static JobClass selectedjob = jobClass.at(curindex);


			if (!selectedjob.skillList.empty()) {
				static Skill selectedskill = selectedjob.skillList.at(curskillindex);
				const char* combo_preview_value_skill = selectedskill.name.c_str();

				if (ImGui::BeginCombo("skill dropdown", combo_preview_value_skill)) {
					for (int i = 0; i < selectedjob.skillList.size(); i++) {
						const bool is_selected = (curskillindex == i);
						
						if (ImGui::Selectable(selectedjob.skillList.at(i).name.c_str(), is_selected))
							curskillindex = i;

						if (is_selected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

			}




		}

		ImGui::End();


	}
}


