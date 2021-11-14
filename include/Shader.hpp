#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm.hpp>


class Shader
{
    public:
        // Constructor to generate shaders
        Shader(const char* vertexPath, const char* fragmentPath);

        // Activate the shader
        void use();

        void setInt(const std::string &name, int value) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        
        // Check compilation errors
        void checkCompileErrors(unsigned int shader, std::string type);

    private:
        unsigned int ID;
};
#endif