#version 330 core									

in vec3 color;		
in vec2 texCoord;

uniform sampler2D tex;

float lum; //luminance

vec3 GSW = vec3(0.2125,0.7154, 0.0721); //greyscale weight

out vec4 fragColor;	

void main() {
   lum = dot(texture(tex,texCoord).rgb, GSW);
   fragColor = vec4(lum, lum, lum, 1.0);
}