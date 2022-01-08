#include "plane.h"

Plane* Plane::instance;
GLuint Plane::planevao;

Plane::Plane(){}

void Plane::Init(){
  if(Plane::instance == NULL)
    Plane::instance = new Plane();

  glGenVertexArrays(1, &Plane::planevao);

  glBindVertexArray(Plane::planevao);

  static GLuint buffers[2];
  glGenBuffers(2, buffers);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Plane::vert), Plane::vert, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Plane::colors), Plane::colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(1);
}

void Plane::Draw(){
  glBindVertexArray(Plane::planevao);
  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
}
