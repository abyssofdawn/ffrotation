#include "imgui.h"
#include "views.h"
#include "fmt/format.h"
#include "../util/helper.h"
#include "../util/classes.h"
#include <sstream>


namespace FFRot {
	void ShowSkillsWindow() {


		ImGui::Begin("Skill");
		ImGui::Text("test");

		if (!jobClass.empty()) {

			static int curindex = 0;
			const char* combo_preview_value = Job_[jobClass[curindex].job].c_str();
			if (ImGui::BeginCombo("class dropdown", combo_preview_value)) {
				for (int i = 0; i < jobClass.size(); i++) {
					const bool is_selected = (curindex == i);
					if (ImGui::Selectable(Job_[jobClass[i].job].c_str(), is_selected))
						curindex = i;

					if (is_selected) ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			static int curskillindex = 0;
			JobClass& selectedjob = jobClass.at(curindex);
			Skill* selectedSkill = &selectedjob.skillList.at(curskillindex);


			if (!selectedjob.skillList.empty()) {
				const char* combo_preview_value_skill = selectedjob.skillList.at(curskillindex).name.c_str();

				if (ImGui::BeginCombo("skill dropdown", combo_preview_value_skill)) {
					for (int i = 0; i < selectedjob.skillList.size(); i++) {
						const bool is_selected_s = (curskillindex == i);
						
						if (ImGui::Selectable(selectedjob.skillList.at(i).name.c_str(), is_selected_s))
							curskillindex = i;

						if (is_selected_s) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

			}

			static Skill newSkill = Skill();

			if (ImGui::Button("New Skill")) {
				selectedjob.skillList.push_back(Skill());
				ImGui::OpenPopup("Build skill");

			}

			if (ImGui::BeginPopup("Build skill")) {
				bool isNameUnique = true;
				static std::string newname;
				ImGui::Text("test");
				//ImGui::InputText("Name##new skill name", &newname);
				newSkill = NewSkill(selectedjob.skillList.back());

				for (int i = 0; i < selectedjob.skillList.size()-1; i++)
				{
					if (selectedjob.skillList.at(i).name == newSkill.name) isNameUnique = false;
				}

				if (!isNameUnique)
					ImGui::BeginDisabled(true);

				if (ImGui::Button("OK"))
				{
					curskillindex = selectedjob.skillList.size()-1;
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					if (!isNameUnique)
						ImGui::SetTooltip("Name must be unique");
				}
				if (!isNameUnique)
					ImGui::EndDisabled();

				

				ImGui::EndPopup();
			}
			


			PushStyleCompact();
			ImGui::BeginTable("edit skill child", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedSame);
			ImGui::TableSetupColumn("skill base", ImGuiTableColumnFlags_WidthStretch, 1);
			ImGui::TableSetupColumn("effect base", ImGuiTableColumnFlags_WidthStretch, 1);
			ImGui::TableSetupColumn("status base", ImGuiTableColumnFlags_WidthStretch, 1);
			ImGui::TableHeadersRow();
			ImGui::PushID("skill table");

			selectedSkill = &selectedjob.skillList.at(curskillindex);

			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			NewSkill(selectedjob.skillList.at(curskillindex));
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			std::ostringstream os;
			os << std::setw(4) << json(*selectedSkill) << std::endl;
			ImGui::Text(os.str().c_str());
			ImGui::PopID();


			ImGui::EndTable();
			PopStyleCompact();;


		}

		ImGui::End();


	}
}


