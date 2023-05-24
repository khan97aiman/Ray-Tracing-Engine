#pragma once
#include "ImGuiObject.h"

namespace NCL {
	class ImGuiObject_OpenGl3Win32 : public ImGuiObject {
	public:
		ImGuiObject_OpenGl3Win32();
		virtual void ProcessEvents() override;
		virtual void Render(std::function<void()> windowFunc) override;
		virtual ~ImGuiObject_OpenGl3Win32() override;
	};

	class ImGuiFactory_OpenGL3Win32 : public GuiFactory {
	public:
		virtual GuiObject* CeateGuiObject() override {
			return new ImGuiObject_OpenGl3Win32();
		}
	};
}