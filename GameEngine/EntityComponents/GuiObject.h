#pragma once
#include <functional>

namespace NCL {
	
	class GuiObject {
	public:
		virtual void ProcessEvents() = 0;
		virtual void Render(std::function<void()> windowFunc) = 0;
		virtual void CreateGuiWindow(const char* identifier) = 0;
		virtual void CloseGuiWindow() = 0;
		virtual void CreateButton(const char* identifier, std::function<void()> onClickEvent) = 0;
		virtual ~GuiObject() {}
	};

	class GuiFactory {
	public:
		virtual ~GuiFactory() {}
		virtual GuiObject* CeateGuiObject() = 0;
	};
}