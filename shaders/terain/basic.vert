#version 430

layout(location=0) in vec3 position;
out vec3 pos;
uniform mat4 proj, view, model;

void main()
{
	pos=position;
	gl_Position=proj*view*model*vec4(position, 1.0);

}