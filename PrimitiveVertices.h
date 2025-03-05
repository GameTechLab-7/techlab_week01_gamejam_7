#pragma once

struct FVertexSimple
{
	float x , y , z;    // Position
	float r , g , b , a; // Color
};

extern FVertexSimple cube_vertices[36];
extern FVertexSimple sphere_vertices[2400];
extern FVertexSimple triangle_vertices[3];
