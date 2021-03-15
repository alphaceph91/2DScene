#version 330 core										

in vec3 inVertex;										
in vec3 inColor;
in vec2 inTexCoord;

out vec3 color;	
out vec2 texCoord;

void main() {									
  color = inColor;		
  texCoord = vec2(inTexCoord.x, 1-inTexCoord.y);
  gl_Position = vec4(inVertex.x, inVertex.y, inVertex.z, 1.0);	
}														
