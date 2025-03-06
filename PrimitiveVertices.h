#pragma once

struct FVertexSimple
{
	float x , y , z;    // Position
	float r , g , b , a; // Color
	float u = 0.5f, v = 0.5f;        // Texture Coordinates
};

extern FVertexSimple cube_vertices[36];
extern FVertexSimple sphere_vertices[2400];
extern FVertexSimple triangle_vertices[3];
extern FVertexSimple square_vertices[ 6 ];
