#version 330 core    
layout (location = 0) in vec4 pos;	     
layout (location = 1) in vec3 color;   

uniform mat4 orthoMatrix;
uniform mat4 viewMatrix;

out vec3 Color;	// Output color to the fragment shader  

void main() {  

	vec4 position = vec4(pos.x, pos.y, pos.z, 1.0);
	mat4 PVM = transpose(orthoMatrix) * transpose(viewMatrix);

    gl_Position = PVM * position;
			
    if (pos.w == 1) { Color = color; }
    else if (pos.w == 0) { Color = vec3(1.0, 0.0, 0.0); }
}
