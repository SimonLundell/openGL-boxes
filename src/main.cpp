#include <iostream>

#include <GL/glew.h> // needs to be included before glfw
#include <GLFW/glfw3.h>

#include <Box.hpp>
#include <Window.hpp>
#include <Camera.hpp>
#include <Draw.hpp>

// Setup screen and constants
const unsigned int WIDTH = 640;
const unsigned int HEIGHT = 480;

// Initial values for mouse
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse =  true;

// Capture mouse movements
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Make camera global to be used in mouse_callback
Camera* camera = new Camera;

int main(int argc, char* argv[]) {
// 1. Initialize GLFW
if (!glfwInit())
{
  std::cout << "Failed to initialize GLFW.\n";
  return 1;
}

Window* window = new Window(WIDTH, HEIGHT, "BoxWindow", 3, 3); 

GLenum err = glewInit();
if (err != GLEW_OK) {
  std::cerr << "GLEW error: " << glewGetErrorString(err) << "\n";
  return 1;
}
glfwSetCursorPosCallback(window->get_window(), mouse_callback);
glfwSetInputMode(window->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
glViewport(0, 0, WIDTH, HEIGHT); // remind OpenGL about our window size.

// Read shaderes from source-files
// Create box/boxes and add to shapes
Box* box1 = new Box(Object::Cube, glm::vec3(0.0f,0.0f,0.0f)); // Main box

Box* box2 = new Box(box1, glm::vec3(-1.0f, -1.0f, -1.0f)); // Copy of main box with relative position
Box* box3 = new Box(box1, glm::vec3(1.0f, 1.0f, 1.0f)); // Another copy

std::vector<Box*> boxes{box1, box2, box3}; // Adding the boxes to a vector

Draw<Box>* drawer = new Draw<Box>(Object::Cube, boxes); // Creating a drawing object with array of shapes we want to draw

// Print coordinates of the boxes
//std::cout << boxes;

while (!glfwWindowShouldClose(window->get_window())) {
  // Quit if escape pressed
  glfwSetWindowShouldClose(window->get_window(), (window->process_input() == GLFW_KEY_ESCAPE));
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen
  // update and draw here
  camera->get_keyboard(window->process_input());
  drawer->draw(); // Drawing

  glfwSwapBuffers(window->get_window()); // tell glfw to go to next frame
  glfwPollEvents();
  }


// window was closed, so let's exit.
glfwDestroyWindow(window->get_window());
glfwTerminate();
return 0;
}

// Defining what to do when mouse is moved
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

if (firstMouse) // initially set to true
{
  lastX = xpos;
  lastY = ypos;
  firstMouse = false;
}  
float xoffset = xpos - lastX;
float yoffset = lastY - ypos; 
lastX = xpos;
lastY = ypos;

camera->process_mouse_movement(xoffset, yoffset);
} 
