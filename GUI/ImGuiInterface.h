#pragma once
#include <GuiInterface.h>

namespace NCL {

	class ImGuiInterface : public GuiInterface {
	public:
		
	};

//	class ImGuiFactory : GuiFactory {
//	public:
//		virtual GuiInterface* CeateGuiInterface() override {
//#ifdef WIN32
//	#if GRAPHICS_API == VULKAN
//			return new ImGuiInterface_VulkanWin32();
//	#endif
//
//	#if GRAPHICS_API == OPENGL3
//			return new ImGuiInterface_OpenGL3Win32();
//	#endif
//#endif // WIN32
//		}
//	};
}