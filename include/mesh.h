#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
	Mesh(const char* source);
	~Mesh();
	Mesh& operator=(const Mesh& rhs);
	void Draw();
	void Delete();
	void BindVAO();
	std::vector<float> points;
	std::vector<float> colors;
private:

	int LoadMesh(const char* source);
	int totalNumberofPoints;

	GLuint pointsVBO;
	GLuint colorsVBO;
	GLuint VAO;

};

#endif //MESH_H