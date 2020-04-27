#version 330

in vec4 vertex;

out vec3 pos;

void main( void )
{
    gl_Position = vertex;
    pos = vertex.xyz;
}
