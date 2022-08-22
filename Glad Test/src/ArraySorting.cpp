#include "ArraySorting.h"

ArraySorting::ArraySorting(int count)
{
	p_count = count;

	for (int i = 0; i < p_count; i++)
	{
		p_array.push_back(i);
	}

}


void ArraySorting::CreateVertices()
{
	float left_x_cord = p_padding - 100;
	float width = 1.0f;

	// Can do it faster later
	for (int i = 0; i < p_count; i++)
	{
		Vertex v1;

		v1.coordinates = { left_x_cord			,0				,0};
		p_vertices.push_back(v1);

		v1.coordinates = { left_x_cord + width	,0				,0};
		p_vertices.push_back(v1);

		v1.coordinates = { left_x_cord + width	,p_array[i]		,0};
		p_vertices.push_back(v1);

		v1.coordinates = { left_x_cord			,p_array[i]		,0};
		p_vertices.push_back(v1);

		left_x_cord += width;
	}
}

void ArraySorting::CreateIndicies()
{
	int baseQuadIndecies[] = { 0,1,2,2,3,0 };
	int object_no = 0;

	// Can do faster later
	for (int i = 0; i < p_count * 6; i++)
	{
		p_indicies.push_back(baseQuadIndecies[i % 6] + 4 * object_no);

		if (i % 6 == 0 && i != 0)
			object_no++;
	}
}

int  ArraySorting::getIBsize()
{
	return p_indicies.size() * sizeof(int);
}
int  ArraySorting::getVBsize()
{
	return p_vertices.size() * sizeof(Vertex);
}

void* ArraySorting::getVertices()
{
	return p_vertices.data();
}

void* ArraySorting::getIndicies()
{
	return p_indicies.data();
}
