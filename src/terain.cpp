#include "terain.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdio>

Terain::Terain(std::string source)
{

	error=false; 
	pointCount=0;

	error=LoadHeightMap(source.c_str());
	if(error)
	{
		fputs("ERROR: loading of height map failed\n", stderr);
	}

	else{
		GenerateVerteces();
		GenerateNormals();
		LoadOpenGLData();
	}
}

void Terain::GenerateVerteces()
{
	for(int pixel=0;pixel<colors.size();pixel++)
	{

		generatedPoints.push_back(width*((float)pixel/(float)width-(int(pixel/width))));
		//printf("%f\n", generatedPoints[generatedPoints.size()-1]);
		generatedPoints.push_back((float)colors[pixel]/(float)255);
		//generatedPoints.push_back(0.0f);
		//printf("%f\n", generatedPoints[generatedPoints.size()-1]);
		generatedPoints.push_back(-int(pixel/height));
		//printf("%f %f %f\n",generatedPoints[generatedPoints.size()-3], generatedPoints[generatedPoints.size()-2],generatedPoints[generatedPoints.size()-1]);
		pointCount+=1;
		vec3 v(generatedPoints[generatedPoints.size()-3], generatedPoints[generatedPoints.size()-2],generatedPoints[generatedPoints.size()-1]);
		points.push_back(v);

	}
}

void Terain::GenerateNormals()
{
	for(int vertex=0; vertex<points.size(); vertex++)
	{
		
	}


}


void Terain::LoadOpenGLData()
{
	


	
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int)vertexIndices.size()*sizeof(int), vertexIndices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (int)generatedPoints.size()*sizeof(float), generatedPoints.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);

	modelMat=translate(identity_mat4(), vec3(0.0f,0.0f,-5.0f));

}

void Terain::Delete(){
	glDeleteBuffers(1, &vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);

}
void Terain::Render()
{
	//printf("%i\n", pointCount);
	shader->Use();
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLE_STRIP,(int)vertexIndices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, pointCount);
}

//float Terain::GetHight(vec2 playerLocation)
//{
	
//}

void Terain::AttachShader(std::string source)
{
	shader= new Shader(source);
}

bool Terain::LoadHeightMap(const char* source)
{
	std::ifstream file(source, std::ifstream::in);
	if(file.bad())
	{
		fprintf(stderr,"ERROR: could not find file %s\n", source);
		return true;
	}
	
	char magicNumber[3]; //needs to be P2 for .pgm
	file.getline(magicNumber, 3);

	if(magicNumber[0]!='P' && magicNumber[1]!='2')
	{
		fputs("ERROR: file is not the correct format (.pgm)\n", stderr);
		printf("%s\n", magicNumber);
		return true;
	}

	char garbageBuffer[100];
	char buffer[10]="         ";
	file.getline(garbageBuffer, 100);
	file.getline(buffer, 10);
	//printf("%s\n", buffer);
	int length=0;
	int spaceIndex=0;
	bool once=false;
	
	for(char i:buffer)
	{
		if(i==' ' && !once)
		{	
			spaceIndex=length;
	    	once=true;
		}
		length++;
	}

	char widthString[spaceIndex];
	for(int j=0;j<=spaceIndex;j++)
	{
		widthString[j]=buffer[j];
	}
	width=atoi(widthString);

	char heightString[length-spaceIndex];
	for(int j=0;j<=(length-spaceIndex);j++)
	{
		heightString[j]=buffer[spaceIndex+j+1];
	}
	height=atoi(heightString);

	//max interger 
	file.getline(garbageBuffer, 100);

	//printf("%i x %i %i %i\n", width, height, spaceIndex, length);
	int totalSize=width*height;
	int isMoretoRead=0;
	int colorIndex=0;
	isMoretoRead=file.peek();


	while(isMoretoRead!=EOF)
	{
		char tempString[7];
		file.getline(tempString, 7);
		int temp=atoi(tempString);
		colors.push_back(temp);
		isMoretoRead=file.peek();
	}

	file.close();

	int numberofStripsRequire=height-1;
	int numberofDegeneratesRequired=2*(numberofStripsRequire-1);
	int verticesPerStrip=2*width;
	for(int y=0;y<height-1;y++)
	{	
		//degenerate begins, repeate first vertex
		if(y>0)
		{
			//vertexIndices[offset++]=y*height;
			vertexIndices.push_back(y*height);
			//vertexIndices.push_back(y*height);
		}

		//go through strip
		for(int x=0;x<width;x++)
		{
			//vertexIndices[offset++]=(y*height)+x;
			//vertexIndices[offset++]=((y+1)*height)+x;
			vertexIndices.push_back((y*height)+x);
			vertexIndices.push_back(((y+1)*height)+x);
		}

		//Degenerate ends, repeat last vertex
		if(y<height-2)
		{
			//vertexIndices[offset++]=((y+1)*height)+(width-1);
			vertexIndices.push_back(((y+1)*height)+(width-1));
		}

	}
	for(int i:vertexIndices)
	{
		//printf("%i\n", i);
	}
	//printf("%i\n", (int)vertexIndices.size());
	return false;

}

Terain::~Terain()
{

}