#include "views.h"
#include "imgui.h"
#include "../util/helper.h"
#include "fmt/format.h"
#include "views.h"
namespace FFRot {
    void ShowSKSWindow() {
        float TEXT_BASE_WIDTH = 4.0f * ImGui::GetFontSize() / 6.0f;
        float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        static float cd = 2.5f;
        ImGui::SetNextWindowSizeConstraints(ImVec2(22 * TEXT_BASE_WIDTH, (TEXT_BASE_HEIGHT + 1) * (5 + chara.size())), ImVec2(INT_MAX, INT_MAX));
        ImGui::Begin("Skill Speed");
        float oldCd = cd;
        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 20);

        ImGui::PopItemWidth();
        cd = clampFloat(cd, 0.01f, 180.0f);
        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 4);

        if (chara.size() > 0 && ImGui::BeginCombo("pick char", fmt::format("{}", selectedChar).c_str())) {
            for (int i = 0; i < chara.size(); i++) {
                if (ImGui::Selectable(fmt::format("{}##char num{}", i, i).c_str(), selectedChar == i))
                    selectedChar = i;
            }
            ImGui::EndCombo();
        }
        ImGui::PopItemWidth();

        // character table
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
        static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_SizingFixedFit;
        if (chara.size() > 0 && ImGui::BeginTable("character_table", 6, flags))
        {
            ImGui::TableSetupScrollFreeze(0, 1); 
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 2);
            ImGui::TableSetupColumn("Skill speed", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("CD", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("New CD", ImGuiTableColumnFlags_WidthStretch);

            ImGui::TableSetupColumn("GCD?", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Cast?", ImGuiTableColumnFlags_WidthFixed);

            ImGui::TableHeadersRow();
            
            int oldSks = 0;
            bool oldSksAffected = false;
            for (int row = 0; row < chara.size(); row++)
            {
                ImGuiListClipper clipper;
                clipper.Begin(chara.at(row).skills.size());
                while (clipper.Step())
                {
                    for (int _skill = clipper.DisplayStart; _skill < clipper.DisplayEnd; _skill++)
                    {
                        CharSkill skill = chara.at(row).skills[_skill];
                        ImGui::TableNextRow();

                            
                        ImGui::TableNextColumn(); //character id
                        std::string id = fmt::format("{}##skill id {}", _skill, row);
                        if (ImGui::Selectable(id.c_str(), chara.at(selectedChar).selectedSkill == _skill)) 
                        {
                            chara.at(selectedChar).selectedSkill = _skill;
                        }
                        PushStyleCompact();
                        ImGui::TableNextColumn(); //sks/sps
                        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 12);
                        id = fmt::format("{}##chara table{} {}", (skill.skill->cast ? "sps" : "sks"), row, _skill);
                        ImGui::InputInt(id.c_str(), (skill.skill->cast ? &chara.at(row).sps : &chara.at(row).sks), 1, 10);
                        chara.at(row).sks = clampInt(chara.at(row).sks, 400, 2700);
                        chara.at(row).sps = clampInt(chara.at(row).sps, 400, 2700);
 
                        ImGui::PopItemWidth();

                        ImGui::TableNextColumn(); //original cd in ms
                        cd = skill.skill->cd / 1000.0f;
                        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 18);
                        id = fmt::format("##chara table cd{} {}", row, _skill);
                        ImGui::InputInt(id.c_str(), &skill.skill->cd, 10, 100);
                        skill.skill->cd = clampInt(skill.skill->cd, 200, 180000);
                        ImGui::PopItemWidth();

                        ImGui::TableNextColumn(); //new cd in s
                        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 6);
                        ImGui::Text("%.2f", skill.skill->gcd ? newCd(cd, (skill.skill->cast ? chara.at(row).sps : chara.at(row).sks)) : cd);
                        ImGui::PopItemWidth();

                        ImGui::TableNextColumn(); //is a gcd
                        id = fmt::format("##chara table gcd{} {}", row, _skill);
                        ImGui::Checkbox(id.c_str(), &(skill.skill->gcd));
                            
                        ImGui::TableNextColumn(); //is cast
                        id = fmt::format("##chara table cast{} {}", row, _skill);
                        ImGui::Checkbox(id.c_str(), &(skill.skill->cast));

                        PopStyleCompact();
                    }
                }
                chara.at(row).updateTicks(0);
            }

            ImGui::EndTable();
        }
        else if (chara.size() == 0) 
        {
            ImGui::Text("Add some characters");
        }

        ImGui::End();
    }
}