#include "ImGuiInterface_OpenGL3Win32.h"
#include <imgui_impl_win32.h>
#include <imgui_impl_opengl3.h>
#include "Win32Window.h"

NCL::ImGuiInterface_OpenGl3Win32::ImGuiInterface_OpenGl3Win32() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//Init Win32
	ImGui_ImplWin32_Init(((NCL::Win32Code::Win32Window*)Window::GetWindow())->GetHandle());
	//Init OpenGL Imgui Implementation
	ImGui_ImplOpenGL3_Init();
	// Setup style
	ImGui::StyleColorsClassic();
}

void NCL::ImGuiInterface_OpenGl3Win32::ProcessEvents() {
}

void NCL::ImGuiInterface_OpenGl3Win32::Render(std::function<void()> windowFunc) {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//show Main Window
	windowFunc();
	ImGui::EndFrame();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

NCL::ImGuiInterface_OpenGl3Win32::~ImGuiInterface_OpenGl3Win32() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
