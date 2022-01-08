#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>

class Triangle{
private:
  static GLuint trivao;
  static Triangle *instance;

  constexpr static GLfloat vert[] {
    -1.0f, -1.0f,  0.0f,  1.0f,
     1.0f, -1.0f,  0.0f,  1.0f,
    -1.0f,  1.0f,  0.0f,  1.0f,
  };

  constexpr static GLushort indicies[] = {
    0, 1, 2
  };

  constexpr static GLfloat color[] = {
    0.583f,  0.771f,  0.014f, 0.014f,
    0.609f,  0.115f,  0.436f, 0.436f,
    0.327f,  0.483f,  0.844f, 0.844f,
  };

  Triangle();

public:
  static void Init();
  static void Draw();
};

#endif
