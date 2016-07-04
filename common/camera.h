#ifndef CAMERA_H
#define CAMERA_H

void computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 getViewMatrix();
glm::vec3 getCursor();

#endif
