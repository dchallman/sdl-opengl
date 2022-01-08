#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>

class Plane{
private:
  static GLuint planevao;
  static Plane *instance;

  constexpr static GLfloat vert[] = {
    -1, 0.0,  1,
     1, 0.0,  1,
    -1, 0.0, -1,
     1, 0.0, -1,
    -1, 0.0, -1,
     1, 0.0,  1
  };

  constexpr static GLfloat colors[] = {
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.982f,  0.099f,  0.879f
  };

  Plane();

public:
  static void Init();
  static void Draw();
};

#endif
