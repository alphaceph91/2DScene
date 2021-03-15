#version 330 core									

in vec3 color;		
in vec2 texCoord;

uniform sampler2D tex;

out vec4 fragColor;		

void main() {				
	vec4 texture = texture(tex, texCoord);
	fragColor = vec4(texture * vec4(color, 1.0));
}