#include "ArraySorting.h"

ArraySorting::ArraySorting(int count, GLFWwindow* window)
{
	p_window = window;
	p_count = count;

	for (int i = 1; i <= p_count; i++)
	{
		p_array.push_back(i);
	}

	RandomizeArray(p_array.data(), p_count);
	CreateVertices();
	CreateIndicies();

	// Cordinates
	p_layout.Push<float>(3);
	// Color
	p_layout.Push<float>(3);

}


void ArraySorting::CreateVertices()			// Create data for VertexBuffer of rectangles that visualizes list to be sorted
{	
	int screen_width, screen_height;
	glfwGetWindowSize(p_window, &screen_width, &screen_height);

	float height_scale = (screen_height / p_count);
	float left_x_cord = (float)screen_width * 0.05f;
	float width = ((float)screen_width * 0.9f) / p_count;

	// Can do it faster later
	for (int i = 0; i < p_count; i++)
	{
		Vertex v1;

		v1.coordinates = { left_x_cord			,0				,0};
		p_vertices.push_back(v1);

		v1.coordinates = { left_x_cord + width	,0				,0};
		p_vertices.push_back(v1);

		v1.coordinates = { left_x_cord + width	,p_array[i] * height_scale		,0};
		p_vertices.push_back(v1);

		v1.coordinates = { left_x_cord			,p_array[i] * height_scale		,0};
		p_vertices.push_back(v1);

		left_x_cord += width;
	}
}

void ArraySorting::CreateIndicies() // Create data for IndexBuffer corresponding to array size
{
	int baseQuadIndecies[] = { 0,1,2,3,2,0 };
	int object_no = 0;

	// Can do faster later
	for (int i = 0; i < p_count * 6; i++)
	{
		p_indicies.push_back(baseQuadIndecies[i % 6] + 4 * object_no);

		if (i % 6 == 0 && i != 0)
			object_no++;
	}
}

void ArraySorting::UpdateVertices()		// This is slow and i could ubdate the vertex buffer while sorting but it will work
{
	for (int i = 0; i < p_count; i++)
	{
		p_vertices[i + 2].coordinates.y = p_array[i];
		p_vertices[i + 3].coordinates.y = p_array[i];
	}

}

void ArraySorting::RandomizeArray(float* arr, int size)
{
	srand(time(NULL));
	
	for (int i = 0; i < size; i++)
	{
		int random_index = rand() % size;
		p_floatSwap(i, random_index);

	}
}

			/*	GETTERS */
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

VertexBufferLayout ArraySorting::getLayout()
{
	return p_layout;
}

float ArraySorting::getQuadHeight(int index)
{
	return p_vertices[index * 4 + 3].coordinates.y;
}

			/*	SWAPING	*/
void ArraySorting::p_floatSwap(int index1, int index2) // Utility to swap values of the sorted array
{
	float holder = p_array[index1];
	p_array[index1] = p_array[index2];
	p_array[index2] = holder;

}

void ArraySorting::QuadSwap(int index1, int index2) // Utility to swap values of the sorted array
{	
	index1 = index1 * 4;
	index2 = index2 * 4;

	float holder1 = p_vertices[index1 + 2].coordinates.y;
	float holder2 = p_vertices[index1 + 3].coordinates.y;

	p_vertices[index1 + 2].coordinates.y = p_vertices[index2 + 2].coordinates.y;
	p_vertices[index1 + 3].coordinates.y = p_vertices[index2 + 3].coordinates.y;

	p_vertices[index2 + 2].coordinates.y = holder1;
	p_vertices[index2 + 3].coordinates.y = holder2;
}


			/*	SORTING	*/
void ArraySorting::BubbleSort(Renderer* renderer)
{
	for (int i = 0; i < p_count; i++)
	{
		for (int j = 0; j < p_count - i - 1; j++)
		{
			float a = getQuadHeight(j);
			float b = getQuadHeight(j+1);

			if (a > b)
			{
				renderer->Clear();
				QuadSwap(j + 1, j);
				renderer->SetVertexBuffer(getVBsize(), getVertices());
				renderer->SetIndexBuffer(getIBsize(), getIndicies());
				renderer->Draw(getIBsize() * 4);
				glfwSwapBuffers(p_window);
			}
			

		}
	}
}