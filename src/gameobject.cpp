#include "gameobject.h"

GameObject::GameObject(vec3 position, vec3 scale, vec3 rotation)
{
	worldPosition = position;
	localScale=scale;
	localRotation=rotation;
	CreateModelMat();	
}

GameObject::~GameObject()
{
	delete mesh;
	delete shader;
}

void GameObject::AttachMesh(const char* source)
{
	mesh= new Mesh(source);
}

void GameObject::AttachShader(std::string source)
{
	shader= new Shader(source);
}

void GameObject::CreateModelMat()
{

	mat4 scaleMat=scale(identity_mat4(), localScale);

	mat4 rotationMat;
	float quaternion[4];
	QuatFromAngle(quaternion, localRotation);
	QuatToMat4(rotationMat.m, quaternion);

	modelMat=translate(identity_mat4(), worldPosition)*rotationMat*scaleMat;
	
}

void GameObject::Render()
{
	shader->Use();
	mesh->Draw();
}