#include <Box.hpp>

Box::Box(Object obj, glm::vec3 position) : _obj(obj), _position(position)
{}
// Using the shaders, every shader/rendering call will refer to the program used defined below. Then delete the shaders.

glm::vec3 Box::get_position()
{
  return _position;
}

Box::Box(const Box *org, const glm::vec3& offset)
{
  _position.x = org->_position.x - offset.x;
  _position.y = org->_position.y - offset.y;
  _position.z = org->_position.z - offset.z;
}

Object Box::get_object_type()
{
  return _obj;
}

float* Box::get_vertices()
{
  return _vertices;
}