#include "ImGuiObject.h"
#include <imgui.h>

void NCL::ImGuiObject::CreateGuiWindow(const char* identifier) {
	ImGui::Begin(identifier);
}

void NCL::ImGuiObject::CloseGuiWindow() {
	ImGui::End();
}

void NCL::ImGuiObject::CreateButton(const char* identifier, std::function<void()> onClickEvent) {
	if (ImGui::Button(identifier)) {
		onClickEvent();
	}
}

