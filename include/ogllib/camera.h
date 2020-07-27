/*
 * camera.h
 *
 *  Created on: Jul 10, 2020
 *      Author: 123
 */

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

// default camera attributes
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;
const float SENSITIVITY = 0.1f;
const float SPEED = 2.0f;

/**
 * four movement directions for camera
 */
enum CameraMovement
{
	FORWARD, BACKWARD,
	LEFT, RIGHT,
	UPWARD, DOWNWARD
};

/**
 * A camera class to move around in an OpenGL scene
 */
class Camera
{
private:
	// camera directions
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	// camera orientation
	float m_yaw;
	float m_pitch;
	float m_zoom;

	// camera options
	float m_mouseSensitivity;
	float m_movementSpeed;

	// updates the camera orientation
	void updateCameraVectors();

public:
	/*
	 * create a camera with given vector directions
	 */
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	/*
	 * create a camera with given float directions
	 */
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	/*
	 * get the view matrix for OpenGL
	 */
	glm::mat4 getViewMatrix();
	/*
	 * process keyboard input keys
	 */
	void processKeyboard(CameraMovement direction, float deltaTime);
	/**
	 * process amount mouse movements
	 */
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch=true);
	/*
	 * process amount of mouse scroll
	 */
	void processMouseScroll(float yOffset);

	/*
	 * get the value of zoom
	 */
	float getZoom();

	/*
	 * get the position of the camera
	 */
	glm::vec3 getPosition();

	/*
	 * get the front direction of the camera
	 */
	glm::vec3 getFront();
};
