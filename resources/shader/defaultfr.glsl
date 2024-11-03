#version 330 core
out vec4 color;
uniform vec4 selected_color = vec4(1.0f,1.0f,1.0f,1.0f);       

void main() { 
color = selected_color;
}