#pragma once
#include <functional>

namespace NCL {
	
	class GuiInterface {
	public:
		virtual void Init() = 0;
		virtual void ProcessEvents() = 0;
		virtual void Render(std::function<void()> windowFunc) = 0;
		virtual void CleanUp() = 0;

	};

	class GuiFactory {
	public:
		virtual ~GuiFactory() {}
		virtual GuiInterface* CeateGuiInterface() = 0;
	};
}