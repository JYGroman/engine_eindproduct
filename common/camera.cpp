// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

glm::mat4 ViewMatrix;

// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 );
glm::vec3 rotation = glm::vec3( 0, 40, 0 );
glm::vec3 cursor = glm::vec3( 0, 0, 0 );

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}

glm::vec3 getCursor(){
	return cursor;
}

float speed = 300.0f; // 300 units / second


void computeMatricesFromInputs(GLFWwindow* window)
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	cursor = glm::vec3( xpos, ypos, 0 );

	// Right and Down vector
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 up = glm::vec3(0, -1, 0);
	
	// Move up
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += up * deltaTime * speed;
	}
	
	// Move down
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= up * deltaTime * speed;
	}
	
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}
	
	// Turn camera
	if(glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}
	
	// View matrix
	ViewMatrix = glm::lookAt(
			position, // Camera is at (xpos,ypos,5), in World Space
			position + glm::vec3(0, 0, -5), // and looks towards Z
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
