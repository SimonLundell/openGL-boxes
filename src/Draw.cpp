#include <Draw.hpp>

template<class Shape>
Draw<Shape>::Draw(Object obj, std::vector<Shape*> shapes) : 
_shader(new Shader("../resources/shader_sources/texture.vs", "../resources/shader_sources/texture.fs")),
_shapes(shapes)
{
  if (obj == Object::Cube)
  {
    // Allocate memory on the GPU and tell the GPU what type of graphics to draw (changing, static etc.)
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    // Take vertices from first object works since all are same shape, not ideal though
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*180, _shapes[0]->get_vertices(), GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 
  }
  else
  {
    std::cerr << "Unsupported type\n"; // Could add other objects to draw here pointing to other vertices.
  }

  this->generate_texture();
}

template<class Shape>
void Draw<Shape>::generate_texture()
{
  glGenTextures(1, &_texture1);
  glBindTexture(GL_TEXTURE_2D, _texture1);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load("../resources/images/container.jpg", &width, &height, &nrChannels, 0); // Load the container picture
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture\n";
  }
  stbi_image_free(data);

  glGenTextures(1, &_texture2);
  glBindTexture(GL_TEXTURE_2D, _texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  data = stbi_load("../resources/images/awesomeface.png", &width, &height, &nrChannels, 0); // Load the awesomeface picture
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture\n";
  }
  stbi_image_free(data);
  _shader->use();
  _shader->setInt("texture0", 0);
  _shader->setInt("texture1", 1);
}

// Draw the shapes which are in the _shapes vector using the defined textures/shaders. If shape is unsupported we exit
template<class Shape>
void Draw<Shape>::draw()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _texture2);

  _shader->use();
  // Camera things here
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
  _shader->setMat4("projection", projection); 
  glm::mat4 view = camera->get_view();
  _shader->setMat4("view", view);

  glBindVertexArray(_VAO);

  for (int i = 0; i < _shapes.size(); i++)
  {
    if (_shapes[i]->get_object_type() != Object::Cube)
    {
      std::cerr << "Attempting to draw unsupported object, exiting\n";
      exit(1);
    }
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _shapes[i]->get_position());
    float angle = 20.0f * 0;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    _shader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
}

template <class Shape>
std::vector<Shape*> Draw<Shape>::get_shapes()
{
  return _shapes;
}
template class Draw<Box>; // To not get errors when defining templated class outside the hpp file.