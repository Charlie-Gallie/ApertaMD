#include "Window.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

AMD_NAMESPACE_BEGIN

void Window::GLFWErrorCallback(int errorCode, const char* errorMessage)
{
	AMD_ERROR("[GLFW Error #%i]: %s", errorCode, errorMessage);
}

Status Window::Initialize()
{
	/* GLFW vvv */

	// Set the error callback which GLFW sends error codes and messages to
	glfwSetErrorCallback(GLFWErrorCallback);

	// Initialize the GLFW library
	glfwInit();

	// Start the window maximized
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	// Construct the window instance
	glfwWindow = glfwCreateWindow(configuration.width, configuration.height, configuration.title.c_str(), NULL, NULL);

	AMD_ASSERT(glfwWindow != nullptr, "Failed to create GLFW window")
	{
		return Status::FAIL;
	}

	glfwMakeContextCurrent(glfwWindow);

	/* ImGUI vvv */

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();

	// Enable keyboard controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Set style to dark theme
	ImGui::StyleColorsDark();

	// Initialize ImGui with GLFW + OpenGL
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);

	// Initialize OpenGL for ImGui
	ImGui_ImplOpenGL3_Init("#version 130");

	return Status::SUCCESS;
}

Status Window::PreRenderUpdate()
{
	// Begin ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	return Status::SUCCESS;
}

Status Window::PostRenderUpdate()
{
	// End ImGui frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwPollEvents();
	glfwSwapBuffers(glfwWindow);

	// Clear the screen
	glViewport(0, 0, configuration.width, configuration.height);
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	return Status::SUCCESS;
}

AMD_NAMESPACE_END