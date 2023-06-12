#pragma once
#include "ImGuiObject.h"

namespace NCL {
	class ImGuiObject_VulkanWin32 : public ImGuiObject {
	public:
		ImGuiObject_VulkanWin32();
		virtual void ProcessEvents() override;
		virtual void Render(std::function<void()> windowFunc) override;
		virtual ~ImGuiObject_VulkanWin32() override;
	};

	class ImGuiFactory_VulkanWin32 : public GuiFactory {
	public:
		virtual GuiObject* CeateGuiObject() override {
			return new ImGuiObject_VulkanWin32();
		}
	};
}