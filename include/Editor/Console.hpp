#ifndef _console_editor_hpp
#define _console_editor_hpp

#include <imgui.h>

namespace Editor {
class Console {
public:
  static void Render() {
    // Size();
    // Position();

    ImGui::Begin("console", nullptr);
    ImGui::Text("console...");
    ImGui::End();
  }

  static void Size() {
    ImGui::SetNextWindowSize(ImVec2{ImGui::GetMainViewport()->Size.x / 2,
                                    ImGui::GetMainViewport()->Size.y / 2},
                             0);
  }

  static void Position() {
    ImGui::SetNextWindowPos(ImVec2{ImGui::GetMainViewport()->Size.x -
                                       (ImGui::GetMainViewport()->Size.x / 2) -
                                       (ImGui::GetMainViewport()->Size.x / 4),
                                   0.0f});
  }
};
} // namespace Editor

#endif
