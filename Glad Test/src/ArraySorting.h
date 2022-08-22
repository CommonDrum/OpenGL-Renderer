#pragma once
#include <vector>
#include <array>

struct Vec3
{
	float x, y, z;
};

struct Vertex
{
	Vec3 coordinates = { 0,0,0 };
	Vec3 colors = { 1.0f,1.0f,1.0f };

};

static std::array<Vertex,4> GenQuad(float x, float y, float width)
{
	Vertex v1;
	v1.coordinates = { x,0,0 };
	Vertex v2;
	v2.coordinates = { x + width,0,0 };
	Vertex v3;
	v3.coordinates = { x + width,y,0 };
	Vertex v4;
	v4.coordinates = { x, y, 0 };


	return { v1,v2,v3,v4 };
}

class ArraySorting
{
public:
	ArraySorting(int count);

	void CreateVertices();
	void CreateIndicies();

	void* getVertices();
	void* getIndicies();
	 int getIBsize();
	 int getVBsize();


private:
	std::vector<Vertex> p_vertices;
	std::vector<int> p_indicies;
	std::vector<float> p_array;

	float p_padding = 10.0f;
	int p_count;
	


};

