#pragma once
#include <GuiInterface.h>

namespace NCL {
	class ImGuiInterface_OpenGl3Win32 : public GuiInterface {
	public:
		ImGuiInterface_OpenGl3Win32();
		virtual void ProcessEvents() override;
		virtual void Render(std::function<void()> windowFunc) override;
		virtual ~ImGuiInterface_OpenGl3Win32() override;
	};

	class ImGuiFactory_OpenGL3Win32 : public GuiFactory {
	public:
		virtual GuiInterface* CeateGuiInterface() override {
			return new ImGuiInterface_OpenGl3Win32();
		}
	};
}