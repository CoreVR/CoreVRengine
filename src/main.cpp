#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cstring>
#include "display.h" 
#include "mesh.h"
#include "shader.h"
#include "graphicsmath.h"
#include "gameobject.h"
#include "camera.h"
#include "terain.h"
#include "bone.h"
#include <string>

#if defined NOVR
#define FPS 0.016666
#elif defined VR
#define FPS 0.013333
#endif

void InitializeGLEW();
void OpenGLInitState();
void ChangeWindowTitleWithRefreshRate(GLFWwindow* window);
void RenderObjects(std::vector<GameObject*> &objects);
void RenderTerains(std::vector<Terain*> &terains);
void DeleteOpenGLBuffers(std::vector<GameObject*> &objects, std::vector<Terain*> &terains);

int main()
{
	if(!glfwInit())
	{
		printf("ERROR: Could not start GLFW3");
		return 1;
	}

	//create window before initializing glew
	Display display(640, 480, "Core");

	InitializeGLEW();
	OpenGLInitState();
	std::vector<GameObject*> objects;
	std::vector<Terain*> terains;

	std::string standardcameraSource("shaders/standardcamera/standardcamera");
	GameObject triangle(vec3(0.0f,0.0f,-5.0f), vec3(1.0,1.0,1.0),vec3(0.0,0.0,0.0));
	triangle.AttachShader(standardcameraSource);
	triangle.AttachMesh("triangle.mo");
	triangle.shader->SetUniforms(triangle.modelMat, display.camera.viewMat, display.camera.projectionMat);
	objects.push_back(&triangle);

	GameObject plane(vec3(-2.0,0.0,-7.5), vec3(5.0,5.0,5.0), vec3(90.0,0.0,0.0));
	plane.AttachShader(standardcameraSource);
	plane.AttachMesh("plane.mo");
	plane.shader->SetUniforms(plane.modelMat, display.camera.viewMat, display.camera.projectionMat);
	objects.push_back(&plane);

	Terain terain(std::string("jaggedclaw.pgm"));
	terain.AttachShader(std::string("shaders/terain/basic"));
	terain.shader->SetUniforms(terain.modelMat, display.camera.viewMat, display.camera.projectionMat);
	terains.push_back(&terain);

	Bone bone(vec3(0,0,0), vec3(.5,.5,.5), NULL);

	while(!glfwWindowShouldClose(display.window))
	{
		double startTime=glfwGetTime();
		ChangeWindowTitleWithRefreshRate(display.window);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//RenderObjects(objects);
		bone.Draw();
		//RenderTerains(terains);
		//terain.shader->Use();
		//terain.Render();
		display.Update();
		if(display.camMoved)
		{

			QuatToMat4(display.camera.rotation.m, display.camera.quaternion);

			display.camera.position=display.camera.position+vec3(display.camera.forward)*-display.moveVector.v[2];
			display.camera.position=display.camera.position+vec3(display.camera.up)*display.moveVector.v[1];
			display.camera.position=display.camera.position+vec3(display.camera.right)*display.moveVector.v[0];
			display.moveVector=vec3(0.0,0.0,0.0);
			mat4 T=translate(identity_mat4(), vec3(display.camera.position));

			display.camera.viewMat=inverse(display.camera.rotation)*inverse(T);

			//print(display.camera.position);
			triangle.shader->SetViewMatrix(display.camera.viewMat);
			plane.shader->SetViewMatrix(display.camera.viewMat);
			terain.shader->SetViewMatrix(display.camera.viewMat);

			display.camMoved=false;
			display.camera.yaw=0.0f;
			display.camera.pitch=0.0f;
			display.camera.roll=0.0f;
		}
	
		double deltaTime=glfwGetTime()-startTime;
		while(deltaTime<FPS)
		{
			deltaTime=glfwGetTime()-startTime;
		}
	}

	DeleteOpenGLBuffers(objects, terains);
	return 1;
}

void RenderObjects(std::vector<GameObject*> &objects)
{
	for(GameObject* object:objects)
	{
		object->shader->Use();
		object->mesh->Draw();
	}
}

void RenderTerains(std::vector<Terain*> &terains)
{
	for(Terain* terain:terains)
	{
		terain->shader->Use();
		terain->Render();
	}
}

//I assume I will add more stuff to this is needed
//so I made it a function to consolidate.
void InitializeGLEW()
{
	glewExperimental=GL_TRUE;
	glewInit();
}

//may change
void OpenGLInitState()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LESS);
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glViewport(0,0,640,480);
	glDisable(GL_CULL_FACE);
	glPointSize(10.0);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

}

void DeleteOpenGLBuffers(std::vector<GameObject*> &allObjects, std::vector<Terain*> &allTerain)
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	for(GameObject* object:allObjects)
	{
		object->mesh->Delete();
	}
	for(Terain* terain:allTerain)
	{
		terain->Delete();
	}
}

void ChangeWindowTitleWithRefreshRate(GLFWwindow* window)
{
	static double previousTime=glfwGetTime();
	static int frameCount;
	double currentTime=glfwGetTime();
	double elapsedTime=currentTime-previousTime;
	if(elapsedTime>0.25)
	{
		previousTime=currentTime;
		double fps=(double)frameCount/elapsedTime;
		char temp[128];
		sprintf(temp, "CORE -fps: %.2f", fps);
		glfwSetWindowTitle(window, temp);
		frameCount=0;
	}	
	frameCount++;
}