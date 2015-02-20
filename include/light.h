#ifndef LIGHT_H
#define LIGHT_H
#include "graphicsmath.h"
#include "enums.h"

class Light
{
	public:
		Light(vec3 pos, LIGHT_SOURCES type );
		~Light();

	private:
		vec3 position;
		vec3 color;

};



#endif