#include "Window.h"
#include "WindowUtils.h"
#include "Input.h"
#include <GLFW/glfw3.h>


namespace Window {

	GLFWwindow* _window;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (action)
		{
		case GLFW_PRESS:
			Input::KeyPressed(static_cast<Input::KeyCode>(key));
			break;
		case GLFW_RELEASE:
			Input::KeyReleased(static_cast<Input::KeyCode>(key));
			break;
		case GLFW_REPEAT:

			break;
		default:
			break;
		}
	}

	void error_callback(int error, const char* description) {

	}

	void Init()
	{
		if (!glfwInit()) {

		}
		glfwSetErrorCallback(error_callback);
		_window = glfwCreateWindow(1366, 768, "Title", NULL, NULL);
		assert(_window != nullptr);
		glfwMakeContextCurrent(_window);
		glfwSetKeyCallback(_window, key_callback);

	}
	void Finish()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}
	bool IsOpen()
	{
		return !glfwWindowShouldClose(_window);
	}
	void PollEvents()
	{
		glfwPollEvents();
	}
	void ShowFrame()
	{
		glfwSwapBuffers(_window);
	}
	void Close()
	{
		glfwDestroyWindow(_window);
	}
	Rect GetWindowBounds()
	{
		Rect bounds;
		glm::tvec2<int> top_left;
		glm::tvec2<int> bottom_right;

		glfwGetWindowFrameSize(_window, &top_left.x, &top_left.y, &bottom_right.x, &bottom_right.y);
		bounds.x = top_left.x;
		bounds.y = bottom_right.y;
		bounds.width = bottom_right.x - top_left.x;
		bounds.height = top_left.y - bottom_right.y;
		return bounds;
	}
	Rect GetViewport()
	{
		Rect viewport;
		int width, height;
		viewport.x = 0;
		viewport.y = 0;
		glfwGetFramebufferSize(_window, &width, &height);
		viewport.width = width;
		viewport.height = height;
		return viewport;
	}
	glm::vec2 GetWindowSize()
	{
		glm::tvec2<int> size;
		glfwGetWindowSize(_window, &size.x, &size.y);
		return size;
	}
	glm::vec2 NormalizeScreenCoordinates(glm::vec2 screen_coordinate)
	{
		glm::tvec2<int> size = GetWindowSize();
		return (glm::vec2(screen_coordinate.x / size.x, -screen_coordinate.y / size.y) * 2.0f) - glm::vec2(1, -1);
	}
	Window * GetWindowPointer()
	{
		return _window;
	}
}