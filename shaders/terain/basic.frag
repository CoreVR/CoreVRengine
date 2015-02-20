#version 430
in vec3 pos;
void main()
{
	gl_FragColor=vec4(1.0,0.0,0.0,1.0) +vec4(pos,1.0);
}