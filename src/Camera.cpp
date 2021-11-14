#include <Camera.hpp>

Camera::Camera() : 
_sensitivity(0.1f), 
_cameraSpeed(0.05f), 
_constraint(true), 
_deltaTime(0.0f), 
_lastFrame(0.0f),
_yaw(-90.0f), 
_pitch(0.0f),
_cameraPos(glm::vec3(0.0f, 0.0f,  3.0f)),
_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
_cameraUp(glm::vec3(0.0f, 1.0f,  0.0f)),
_worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
    update_camera_vectors();
}

void Camera::set_camera_front(const glm::vec3& direction)
{
    _cameraFront = direction;
}

void Camera::update_camera_vectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(front);
    _cameraRight = glm::normalize(glm::cross(_cameraFront, _worldUp));  
    _cameraUp = glm::normalize(glm::cross(_cameraRight, _cameraFront));
}

void Camera::process_mouse_movement(float& xoffset, float& yoffset)
{
    xoffset *= _sensitivity;
    yoffset *= _sensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    if (_constraint)
    {
        if (_pitch > 89.0f)
        {
            _pitch = 89.0f;
        }
        if (_pitch < -89.0f)
        {
            _pitch = -89.0f;
        }
    }
    update_camera_vectors();
}

void Camera::get_keyboard(const unsigned int& key)
{
    if (key == GLFW_KEY_W) // Forward
        _cameraPos += _cameraSpeed * _cameraFront;
    else if (key == GLFW_KEY_S) // Backward
        _cameraPos -= _cameraSpeed * _cameraFront;
    else if (key == GLFW_KEY_A) // Left
        _cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed;
    else if (key == GLFW_KEY_D) // Right
        _cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * _cameraSpeed; 
}

glm::mat4 Camera::get_view()
{
    float currentFrame = glfwGetTime();
    _deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;  

    glm::mat4 view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);

    return view;
}
