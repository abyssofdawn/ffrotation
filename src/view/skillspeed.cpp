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



        // character table
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
        static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_SizingFixedFit;
        if (chara.size() > 0 && ImGui::BeginTable("character_table", 5, flags))
        {
            ImGui::TableSetupScrollFreeze(0, 1); 
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 2);
            ImGui::TableSetupColumn("Skill speed", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("New CD", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("SKS?", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("hehe");

            ImGui::TableHeadersRow();
            
            int oldSks = 0;
            bool oldSksAffected = false;
            ImGuiListClipper clipper;
            clipper.Begin(chara.size());


            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    for (int skill = 0; skill < chara[row].skills.size(); skill++)
                    {
                        oldSks = chara[row].sks;
                        oldSksAffected = chara[row].skills[skill].skill->gcd;
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        ImGui::Text("%d", row);
                        ImGui::TableNextColumn();
                        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 8);
                        PushStyleCompact();
                        std::string id = fmt::format("###chara table{}", row);
                        ImGui::InputInt(id.c_str(), &chara[row].sks, 1, 10);
                        chara[row].sks = clampInt(chara[row].sks, 400, 2700);
                        PopStyleCompact();
                        ImGui::PopItemWidth();
                        ImGui::TableNextColumn();
                        float tempcd = 0;
                        ImGui::InputFloat("cd", &tempcd, .01f, 0.1f, "%.2f");
                        (chara[row].skills[skill].skill->cd) = tempcd;
                        ImGui::TableNextColumn();
                        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 6);

                        ImGui::Text("%.2f", chara[row].skills[skill].skill->gcd ? newCd(cd, chara[row].sks) : cd);
                        ImGui::PopItemWidth();
                        ImGui::TableNextColumn();
                        id = fmt::format("###chara table gcd{}", row);
                        ImGui::Checkbox(id.c_str(), &(chara[row].skills[skill].skill->gcd));
                        if (oldSks != chara[row].sks || oldCd != cd || oldSksAffected != chara[row].skills[skill].skill->gcd) {
                            chara[row].skills[skill].skill->cd = int(cd * 1000);
                            chara[row].updateTicks(skill);
                        }
                    }

                }
            }

            ImGui::EndTable();
        }
        else if (chara.size() == 0) {
            ImGui::Text("Add some characters");
        }

        ImGui::End();
    }
}