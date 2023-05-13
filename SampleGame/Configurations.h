#pragma once
#include <RendererBase.h>
#include <AssetLoader.h>
#include "PlayerController.h"
#include <GuiInterface.h>

namespace NCL {
	namespace CSC8599 {
		
		struct Configurations {
			Configurations() {
				// Determine which rendering API is used
				#ifdef VULKAN
						//guiFactory =  new ImGuiFactory_VulkanWin32();
				#endif
				#ifdef OPENGL3
						guiFactory = new ImGuiFactory_OpenGL3Win32();
						rendererFactory = new OGLSampleGameRendererFactory();
						assetLoaderFactory = new Assets::OGLAssetLoaderFactory();
						//playerControllerFactory = new Win32Pla;
				#endif
			}
			~Configurations() {
				delete rendererFactory;
				delete assetLoaderFactory;
				delete playerControllerFactory;
				delete guiFactory;
			}
			RendererFactory* rendererFactory = NULL;
			Assets::AssetLoaderFactory* assetLoaderFactory = NULL;
			PlayerControllerFactory* playerControllerFactory = NULL;
			GuiFactory* guiFactory = NULL;
		};
	}
}

