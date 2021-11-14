#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <math.h>
#include <vector>

#include <GL/glew.h> // needs to be included before glfw
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <Shader.hpp>
#include <Stb_image.hpp>
#include <Camera.hpp>
#include <Box.hpp>

extern const unsigned int WIDTH;
extern const unsigned int HEIGHT;
extern Camera* camera;

template <class Shape>
class Draw
{
    public:
        // Constructor for cubes
        Draw<Shape>(Object obj, std::vector<Shape*> shapes);
    
        void create_vertex_shader();
        void create_fragment_shader();
        void draw();
        std::vector<Shape*> get_shapes();
        void generate_texture();

    private:
        Shader* _shader;
        std::vector<Shape*> _shapes;
        unsigned int _VBO;
        unsigned int _VAO;
        unsigned int _EBO;
        unsigned int _texture1;
        unsigned int _texture2;

};

#endif