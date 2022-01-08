#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

out vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;;

void main(){
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
     color = vColor;
}