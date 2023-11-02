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
        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 6);
        ImGui::InputFloat("cd", &cd, 0, 0, "%.2f");
        ImGui::PopItemWidth();
        cd = clampFloat(cd, 0.01f, 180.0f);



        // character table
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
        static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_SizingFixedFit;
        if (chara.size() > 0 && ImGui::BeginTable("character_table", 4, flags))
        {
            ImGui::TableSetupScrollFreeze(0, 1); 
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 2);
            ImGui::TableSetupColumn("Skill speed", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("New CD", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("SKS?", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableHeadersRow();
            
            int oldSks = 0;
            bool oldSksAffected = false;
            ImGuiListClipper clipper;
            clipper.Begin(chara.size());

            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    oldSks = chara[row].sks;
                    oldSksAffected = skillList[0].gcd;
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", row);
                    ImGui::TableNextColumn();
                    ImGui::PushItemWidth(TEXT_BASE_WIDTH * 4);
                    PushStyleCompact();
                    std::string id = fmt::format("###chara table{}", row);
                    ImGui::InputInt(id.c_str(), &chara[row].sks, 0, 0);
                    chara[row].sks = clampInt(chara[row].sks, 400, 2700);
                    PopStyleCompact();
                    ImGui::PopItemWidth();
                    ImGui::TableNextColumn();
                    ImGui::PushItemWidth(TEXT_BASE_WIDTH * 6);
                    
                    ImGui::Text("%.2f", chara[row].skills[0].skill->gcd ? newCd(cd, chara[row].sks) : cd);
                    ImGui::PopItemWidth();
                    ImGui::TableNextColumn();
                    id = fmt::format("###chara table gcd{}", row);
                    ImGui::Checkbox(id.c_str(), &skillList[0].gcd);
                    if (oldSks != chara[row].sks || oldCd != cd || oldSksAffected!=skillList[0].gcd) {
                        skillList[0].cd = int(cd * 1000);
                        chara[row].updateTicks(cd);
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