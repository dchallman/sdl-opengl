#include "triangle.h"

Triangle* Triangle::instance;
GLuint Triangle::trivao;

Triangle::Triangle(){}

void Triangle::Init(){
  if(Triangle::instance == NULL)
    Triangle::instance = new Triangle();

  glGenVertexArrays(1, &Triangle::trivao);
  glBindVertexArray(Triangle::trivao);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

  static GLuint buffers[2];
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle::vert), Triangle::vert, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle::color), Triangle::color, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(1);
}

void Triangle::Draw(){
  glBindVertexArray(Triangle::trivao);
  glDisable(GL_CULL_FACE);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
  glEnable(GL_CULL_FACE);
}
