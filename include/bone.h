#ifndef BONE_H
#define BONE_H
#include "graphicsmath.h"
#include <vector>
#include <GL/glew.h>

class Bone{
	public:
		Bone(vec3 p1, vec3 p2, Bone* parent);
		~Bone();
		void Draw();
		void Move(vec3 trans, vec3 rotate, vec3 scale);
		void CreateVertices();
	private:
		vec3 point1;
		vec3 point2;
		Bone* parent;
		vec3 translate;
		vec3 rotate;
		vec3 scale;
		GLuint pointsVBO;
		GLuint colorsVBO;
		GLuint VAO;
};
#endif