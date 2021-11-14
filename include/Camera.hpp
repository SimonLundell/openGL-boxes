#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <Window.hpp>

class Camera
{
    public:
        Camera();
        glm::mat4 get_view();
        void update_camera_vectors();
        void process_mouse_movement(float& xoffset, float& yoffset);
        void set_camera_front(const glm::vec3& direction);
        void get_keyboard(const unsigned int& key);

    private:
        bool _constraint;
        float _deltaTime;
        float _lastFrame;
        float _yaw;
        float _pitch;
        const float _sensitivity;
        const float _cameraSpeed;
        glm::vec3 _cameraPos;
        glm::vec3 _cameraFront;
        glm::vec3 _cameraUp;
        glm::vec3 _cameraRight;
        glm::vec3 _worldUp;
};

#endif