#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>

#include <GL/glew.h> // needs to be included before glfw
#include <GLFW/glfw3.h>

#include <Camera.hpp>

class Window
{
    public:
        // Constructor
        Window(const int& width, const int& height, const char* name, const int& major_ver, const int& minor_ver);
        
        GLFWwindow* create_window();
        
        // Getters
        int get_height() const;
        int get_width() const;
        const char* get_name() const;
        GLFWwindow* get_window() const;
        int process_input();

    private:
        const int _width;
        const int _height;
        const char* _name;
        GLFWwindow* _window;
};

#endif