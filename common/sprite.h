#ifndef SPRITE_H
#define SPRITE_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <common/texture.h>

class Sprite
{
	public:
		Sprite();
		virtual ~Sprite();

		GLuint texture() { return _texture; };
		GLuint vertexbuffer() { return _vertexbuffer; };
		GLuint uvbuffer() { return _uvbuffer; };
		
		float rotX(){ return _rotX; };
		float rotX( float newRot ){ _rotX = newRot; };
		float rotY(){ return _rotY; };
		float rotY( float newRot ){ _rotY = newRot; };
		float rotZ(){ return _rotZ; };
		float rotZ( float newRot ){ _rotZ = newRot; };

	private:
		GLuint _texture;
		GLuint _vertexbuffer;
		GLuint _uvbuffer;
		
		float _rotX;
		float _rotY;
		float _rotZ;
};

#endif /* SPRITE_H */
