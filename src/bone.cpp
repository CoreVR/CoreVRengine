#include "bone.h"

Bone::Bone(vec3 p1, vec3 p2, Bone* parent)
{
	translate=vec3(0.0f,0.0f,0.0f);
	rotate=vec3(0.0f,0.0f,0.0f);
	scale=vec3(0.0f,0.0f,0.0f);

	point1=p1;
	if(parent==NULL)
	{
		point2=p2;
	}
	else{
		point2=parent->point1;
	}
	//this->parent=parent;

	pointsVBO=0;
	colorsVBO=0;
	VAO=0;
	CreateVertices();
}

Bone::~Bone()
{

}

void Bone::CreateVertices()
{
	float points[6]={
		point1.v[0], point1.v[1], point1.v[2],
		point2.v[0], point2.v[1], point2.v[2]
	};

	float colors[6]={
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f
	};

	glGenBuffers(1, &pointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, points, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, colors, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Bone::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
}

void Bone::Move(vec3 trans, vec3 rotate, vec3 scale)
{
	point1=point2-point1*(dot((point2-point1),scale));
	vec3 curDirection=point2-point1;
	vec3 newDirection=curDirection*dot(curDirection,rotate);
	point1=point2-newDirection;
	point1+=trans;
	point2+=trans;
	CreateVertices();
}

