#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <assert.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "common/LoadShaders.h"
#include "objects/triangle.h"
#include "objects/plane.h"
#include "objects/cube.h"

void initSDL();
void initGL();
void update();
void render();
void keyboardMouseInput(int* xpos, int* ypos, int* isup, int* isdown, int* isleft, int* isright);

SDL_Window *gWindow = nullptr;

float width = 800.0, height = 600.0, angle = 0.1, fov = 1000.0;

enum Attrib_IDs { vPosition = 0, vColor = 1 };

glm::vec3 position = glm::vec3(0,3,0);

float fps = 1000/60.0;

GLuint projectionMatrixID;
glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), width/height, 0.1f, fov);

GLuint viewMatrixID;
glm::mat4 viewMatrix = glm::lookAt(
  position,
  position,
  glm::vec3(0,1,0)
  );

GLuint modelMatrixID;
glm::mat4 modelMatrix = glm::mat4(1.0f);

float horizontalAngle = 3.14f;
float verticleAngle = 0.0f;
float speed = 3.0f;
float mouseSpeed = 0.005f;

int main(int argc, char **argv){
  initSDL();

  float dt;
  int currentTime, lastTime = 0;

  while(1){
    currentTime = SDL_GetTicks();
    dt = currentTime - lastTime;

    if(dt > fps){

      lastTime = SDL_GetTicks();

      update();
      render();
    }
  }

  SDL_DestroyWindow(gWindow);
  return 0;
}

void initSDL(){
  assert(SDL_Init(SDL_INIT_VIDEO) == 0);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  gWindow = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

  assert(gWindow != NULL);

  assert(SDL_GL_CreateContext(gWindow) != NULL);

  SDL_ShowCursor(SDL_DISABLE);

  assert(glewInit() == 0);

  initGL();

  SDL_ShowWindow(gWindow);
}

void initGL(){
  glClearColor(1.0, 0.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  ShaderInfo shaders[] = {
    {GL_VERTEX_SHADER, "shader.vs"},
    {GL_FRAGMENT_SHADER, "shader.fs"},
    {GL_NONE, NULL}
  };

  GLuint program = LoadShaders(shaders);
  glUseProgram(program);

  modelMatrixID = glGetUniformLocation(program, "modelMatrix");
  viewMatrixID = glGetUniformLocation(program, "viewMatrix");
  projectionMatrixID = glGetUniformLocation(program, "projectionMatrix");

  glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
  glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
  glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);

  Plane::Plane::Init();
  Cube::Cube::Init();
  Triangle::Triangle::Init();
}

void render(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1000.0f, 0.0f, 1000.0f));
  glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
  Plane::Plane::Draw();

  int s;
  for(int i = 0; i < 1000000; i++){
    s = (i % 3 == 0) ? -1 : 1;
    if((position.x + fov > float(i) && position.x - fov < float(i)) || (position.z + fov > float(i) && position.z - fov < float(i))){
      modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i, 1.6f * i * 0.01, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f + s * angle), glm::vec3(1.0f, 1.0f, 1.0f));
      glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
      Cube::Cube::Draw();
    }
  }

  for(int i = 0; i < 1000000; i++){
    s = (i % 3 == 0) ? -1 : 1;
    if((position.x + fov > float(i) && position.x - fov < float(i)) || (position.z + fov > float(i) && position.z - fov < float(i))){
      modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.3f, i)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f + s * angle * 2), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
      glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
      Triangle::Triangle::Draw();
    }
  }

  angle += 1.0f;

  SDL_GL_SwapWindow(gWindow);
}

void update(){
  int xpos, ypos;
  glm::vec3 direction, right, up;
  int isup = false, isdown = false, isleft = false, isright = false;

  keyboardMouseInput(&xpos, &ypos, &isup, &isdown, &isleft, &isright);

  horizontalAngle += mouseSpeed * (width * 0.5 - xpos);
  verticleAngle += mouseSpeed *  (height * 0.5 - ypos);

  direction = glm::vec3(cos(verticleAngle) * sin(horizontalAngle), sin(verticleAngle), cos(verticleAngle) * cos(horizontalAngle));

  right = glm::vec3(sin(horizontalAngle - 3.14f * 0.5f), 0, cos(horizontalAngle - 3.14f * 0.5f));
  up = glm::cross(right, direction);

  if(isup)
    position += direction * speed;
  if(isdown)
    position -= direction * speed;
  if(isleft)
    position -= right * speed;
  if(isright)
    position += right * speed;

  viewMatrix = glm::lookAt(
    position,
    position + direction,
    up
    );

  glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
}

void keyboardMouseInput(int *xpos, int *ypos, int *isup, int *isdown, int *isleft, int *isright){
  SDL_Event event;

  while(SDL_PollEvent(&event) != 0){
    if(event.type == SDL_QUIT)
      exit(0);

    if(event.type == SDL_MOUSEMOTION){
      *xpos = event.motion.x;
      *ypos = event.motion.y;
    }

    if(event.type == SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_w:
        *isup = true;
        break;

      case SDLK_a:
        *isleft = true;
        break;

      case SDLK_s:
        *isdown = true;
        break;

      case SDLK_d:
        *isright = true;
        break;

      case SDLK_q:
        SDL_Quit();
        exit(0);
        break;
      }
    }
  }

  SDL_WarpMouseInWindow(gWindow, width * 0.5, height * 0.5);
}
