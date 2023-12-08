#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 900) out;





out vec3 fColor;

void main() {


for( int i = 0; i < gl_in.length(); i++ )
        {
		fColor = vec3(1.0, 0.0, 1.0);
	
	       // fColor = gs_in[i].Color;
            gl_Position = gl_in[i].gl_Position;
            EmitVertex();  
        }
      EndPrimitive(); 
}
