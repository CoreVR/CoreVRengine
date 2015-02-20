#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "graphicsmath.h"
#include "mesh.h"
#include "shader.h"
#include <string>

class GameObject
{
	public:
		GameObject(vec3 position, vec3 scale, vec3 rotation);
		~GameObject();
		void Render();
		void AttachMesh(const char* source);
		void AttachShader(std::string source);
		void CreateModelMat();
		mat4 modelMat;
		vec3 worldPosition;
		vec3 localScale;
		vec3 localRotation;
		Shader* shader;
		Mesh* mesh;

};

#endif