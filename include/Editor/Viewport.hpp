#ifndef _console_viewport_hpp
#define _console_viewport_hpp

#include <imgui.h>

namespace Editor {
class Viewport {
public:
  static void Render() {
    Size();
    // Position();

    ImGui::Begin("viewport", nullptr);
    // Display rendered texture here...
    ImGui::End();
  }

  static void Size() {
    ImVec2 size = ImGui::GetMainViewport()->Size;
    float width = ImGui::GetMainViewport()->Size.x * 0.75f;
    float height = ImGui::GetMainViewport()->Size.y * 0.75f;

    ImGui::SetNextWindowSize(ImVec2{width, height}, 0);
  }

  static void Position() {
    float width = ImGui::GetMainViewport()->Size.x * 0.75f;
    float xOffset = width / 2.0f;
    float height = ImGui::GetMainViewport()->Size.y * 0.75f;
    float yOffset = 0.0f;

    ImGui::SetNextWindowPos(ImVec2{xOffset, yOffset});
  }
};
} // namespace Editor

#endif
