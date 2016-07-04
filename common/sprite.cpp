#include "sprite.h"


Sprite::Sprite()
{
    std::string texture_file = "assets/hoi.bmp";

    // Load the texture (see: texture.h/cpp)
	_texture = loadBMP_custom(texture_file.c_str());

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A sprite has 1 face (quad) with 2 triangles each, so this makes 1*2=2 triangles, and 2*3 vertices
	int sprite_width = 512;
	int sprite_height = 512;
	GLfloat g_vertex_buffer_data[] = {
		 0.5f * sprite_width, -0.5f * sprite_height, 0.0f,
		-0.5f * sprite_width, -0.5f * sprite_height, 0.0f,
		-0.5f * sprite_width,  0.5f * sprite_height, 0.0f,
		-0.5f * sprite_width,  0.5f * sprite_height, 0.0f,
		 0.5f * sprite_width,  0.5f * sprite_height, 0.0f,
		 0.5f * sprite_width, -0.5f * sprite_height, 0.0f
	};

	// Two UV coordinates for each vertex.
	GLfloat g_uv_buffer_data[] = {
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	
	_rotX = 0;
	_rotY = 0;
	_rotZ = 0;
	
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
}
