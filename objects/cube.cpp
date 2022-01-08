#include "cube.h"

Cube* Cube::instance;
GLuint Cube::cubevao;

Cube::Cube(){}

void Cube::Init(){
  if(Cube::instance == NULL)
    Cube::instance = new Cube();

  glGenVertexArrays(1, &Cube::cubevao);

  glBindVertexArray(Cube::cubevao);

  static GLuint buffers[2];
  glGenBuffers(2, buffers);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vert), Cube::vert, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::colors), Cube::colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(1);
}

void Cube::Draw(){
  glBindVertexArray(Cube::cubevao);
  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
}
