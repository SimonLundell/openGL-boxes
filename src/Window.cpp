#include <Window.hpp>

Window::Window(const int& width, const int& height, const char* name, const int& major_ver, const int& minor_ver) : _width(width), _height(height), _name(name) 
{
  // tell glfw that we want to use OpenGL 3.3+
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_ver);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_ver);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // tell glfw that the window should be floating on top of other windows
  glfwWindowHint(GLFW_FLOATING, GL_TRUE);

  // tell glfw that the window should not be resizable
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  this->create_window();
}

GLFWwindow* Window::create_window()
{
    _window = glfwCreateWindow(this->get_width(), this->get_height(), this->get_name(), NULL, NULL);

    if (!_window)
    {
        std::cerr << "Failed to create window.\n";
        exit(1);
    }
    
    glfwMakeContextCurrent(this->get_window());
    return _window;
}

int Window::process_input()
{
    if (glfwGetKey(get_window(),GLFW_KEY_ESCAPE) == GLFW_PRESS) return GLFW_KEY_ESCAPE;
    else if (glfwGetKey(get_window(),GLFW_KEY_W) == GLFW_PRESS) return GLFW_KEY_W;
    else if (glfwGetKey(get_window(),GLFW_KEY_A) == GLFW_PRESS) return GLFW_KEY_A;
    else if (glfwGetKey(get_window(),GLFW_KEY_S) == GLFW_PRESS) return GLFW_KEY_S;
    else if (glfwGetKey(get_window(),GLFW_KEY_D) == GLFW_PRESS) return GLFW_KEY_D;
}

GLFWwindow* Window::get_window() const
{
    return _window;
}

int Window::get_height() const 
{
    return this->_height;
}
int Window::get_width() const 
{
    return this->_width;
}
const char* Window::get_name() const
{
    return this->_name;
}