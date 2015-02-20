#ifndef TERAIN_H
#define TERAIN_H
#include <vector>
#include <GL/glew.h>
#include <string>
#include "shader.h"
#include "graphicsmath.h"

class Terain
{
	public:
		Terain(std::string source);
		~Terain();
		bool LoadHeightMap(const char* source); //returns true for success, false for failure
		void AttachShader(std::string source);
		void Render();
		void Delete();
		float GetHeight(vec2 playerLocation);
		bool error;
		Shader* shader;
		mat4 modelMat;
	private:
		std::vector<vec3> points;
		void GenerateVerteces();
		void GenerateNormals();
		std::vector<int> vertexIndices;
		int pointCount;
		int width;
		int height;
		void LoadOpenGLData();
		std::string errorMessage;
		std::vector<float> normals;
		std::vector<int> colors;
		std::vector<float> generatedPoints;
		GLuint vbo;
		GLuint ibo; //index buffer
		GLuint vao;

};



#endif