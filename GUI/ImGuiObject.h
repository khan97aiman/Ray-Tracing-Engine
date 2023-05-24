#pragma once
#include <GuiObject.h>
#include <string>

namespace NCL {
	class ImGuiObject : public GuiObject {
	public:
		virtual void CreateGuiWindow(const char* identifier) override;
		virtual void CloseGuiWindow() override;
		virtual void CreateButton(const char* identifier, std::function<void()> onClickEvent) override;
	};

}