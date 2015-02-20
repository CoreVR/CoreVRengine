#include "mesh.h"
#include <stdio.h>
#include <stdlib.h>

Mesh::Mesh(const char* source)
{

	totalNumberofPoints=0;
	int mesh=Mesh::LoadMesh(source);
	if(mesh<0)
	{
		fputs("ERROR: Mesh loading failed", stderr);
	}
	else{
	glGenBuffers(1, &pointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(float), points.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(float), colors.data(), GL_STATIC_DRAW);


	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);	

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	}


}

void Mesh::Delete()
{
	glDeleteBuffers(1, &pointsVBO);
	glDeleteBuffers(1, &colorsVBO);
	glDeleteVertexArrays(1,&VAO);
}

Mesh::~Mesh()
{

}

Mesh& Mesh::operator=(const Mesh& rhs)
{
	totalNumberofPoints=rhs.totalNumberofPoints;
	points=rhs.points;
	colors=rhs.colors;
	pointsVBO=rhs.pointsVBO;
	colorsVBO=rhs.colorsVBO;
	VAO=rhs.VAO;
}

int Mesh::LoadMesh(const char* source)
{
	FILE* meshFilePointer=fopen(source, "r");
	if(meshFilePointer==NULL)
	{
		fprintf(stderr, "ERROR: Could not find file %s\n", source);
		return -1;
	}

	int pointCount=0;  //same number of colors as points
	int unsortedPointCount=0;
	int unsortedColorCount=0;

	char currentLineInFile[100];
	while(fgets(currentLineInFile, 100, meshFilePointer))
	{
		if(currentLineInFile[0]=='p')
		{
			pointCount++;
		}
	}
	totalNumberofPoints=pointCount;

	//points.resize(pointCount);
	//colors.resize(pointCount);

	rewind(meshFilePointer);
	while(fgets(currentLineInFile,100,meshFilePointer))
	{
		if(currentLineInFile[0]=='p')
		{
			float x, y, z;
			x=y=z=0.0f;
			sscanf(currentLineInFile, "p %f %f %f", &x, &y, &z);
			points.push_back(x);
			points.push_back(y);
			points.push_back(z);
		}
		else if(currentLineInFile[0]=='c')
		{
			float r, g, b;
			r=g=b=0.0f;
			sscanf(currentLineInFile, "c %f %f %f", &r, &g, &b);
			colors.push_back(r);
			colors.push_back(g);
			colors.push_back(b);
		}
	}
	//for(int i=0; i<points.size();i++)
	//{
	//	printf("%f %f\n", points[i], colors[i]);

	//}
	fclose(meshFilePointer);
	return 0;
}

void Mesh::Draw()
{	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, totalNumberofPoints);
}

void Mesh::BindVAO()
{
	glBindVertexArray(VAO);
}