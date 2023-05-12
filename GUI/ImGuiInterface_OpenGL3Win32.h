#pragma once
#include <GuiInterface.h>

namespace NCL {
	class ImGuiInterface_OpenGl3Win32 : public GuiInterface {
	public:
		virtual void Init() override;
		virtual void ProcessEvents() override;
		virtual void Render(std::function<void()> windowFunc) override;
		virtual void CleanUp() override;
	};

	class ImGuiFactory_OpenGL3Win32 : public GuiFactory {
	public:
		virtual GuiInterface* CeateGuiInterface() override {
			return new ImGuiInterface_OpenGl3Win32();
		}
	};
}