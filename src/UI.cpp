#include "UI.h"
#include "InputState.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

namespace
{
    constexpr int VISIBLE_ITEMS = 4;
    const char* items[] = { "Wall", "Start", "Goal" };

    void HelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::BeginItemTooltip())
        {
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
}

UI::UI(SDL_Window *window, SDL_Renderer *renderer)
    : window(window), renderer(renderer), show_demo_window(false),
      show_fps_counter(false), item_current(0)
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(this->window, this->renderer);

    ImGui_ImplSDLRenderer3_Init(this->renderer);

}

UI::~UI()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void UI::draw_and_process(InputState &is)
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    {
        ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Tile selection:");
        ImGui::ListBox("##tile_selection_list", &this->item_current,
                       items, IM_COUNTOF(items), VISIBLE_ITEMS);

        ImGui::SameLine(); HelpMarker("LMB - place tile\nRMB - clear tile");

        ImGui::Spacing();

        ImGui::SeparatorText("Functions");

        if (ImGui::Button("Run simulation", ImVec2(-1, 0)))
        {
            is.simulation_run = true;
        }

        if (ImGui::Button("Clear all", ImVec2(-1, 0)))
        {
            //TODO
        }

        if (ImGui::Button("Clear path", ImVec2(-1, 0)))
        {
            //TODO
        }

        ImGui::Spacing();
        ImGui::SeparatorText("Debug");
        ImGui::Checkbox("Show FPS counter", &this->show_fps_counter);
        ImGui::Checkbox("Show demo window", &this->show_demo_window);

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), this->renderer);
}

void UI::process_events(SDL_Event &e)
{
    ImGui_ImplSDL3_ProcessEvent(&e);
}

int UI::get_current_tile() const
{
    return this->item_current;
}
