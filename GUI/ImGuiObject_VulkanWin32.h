#pragma once
#include <GuiInterface.h>

namespace NCL {
	/*class ImGuiInterface : public GuiInterface {
	public:
		virtual void Init() = 0;
		virtual void ProcessEvents() = 0;
		virtual void Render() = 0;
	};*/

	class ImGuiInterface_VulkanWin32 : public GuiInterface {
	public:
		virtual void Init() override;
		virtual void ProcessEvents() override;
		virtual void Render() override;
	};

	class ImGuiInterface_OpenGl3Win32 : public GuiInterface {
	public:
		virtual void Init() override;
		virtual void ProcessEvents() override;
		virtual void Render() override;
	};

	class ImGuiFactory : GuiFactory {
	public:
		virtual GuiInterface* CeateGuiInterface() override {
#ifdef WIN32
	#if GRAPHICS_API == VULKAN
			return new ImGuiInterface_VulkanWin32();
	#endif

	#if GRAPHICS_API == OPENGL3
			return new ImGuiInterface_OpenGl3Win32();
	#endif
#endif // WIN32
		}
	};
}