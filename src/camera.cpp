#include "camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position,
		glm::vec3 up, float yaw,
		float pitch)
	: m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch),
	  m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED),
	  m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
		float upZ, float yaw, float pitch)
	: m_position(glm::vec3(posX, posY, posZ)), m_worldUp(upX, upY, upZ),
	  m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_yaw(yaw), m_pitch(pitch),
	  m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	if (direction == FORWARD)
		// move forward along the front vector
		m_position += m_front * velocity;
	if (direction == BACKWARD)
		// move backward along the front vector
		m_position -= m_front * velocity;
	if (direction == LEFT)
		// move along the right vector in opposite direction
		m_position -= m_right * velocity;
	if (direction == RIGHT)
		// move along the right vector
		m_position += m_right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset,
		bool constrainPitch)
{
	m_yaw += xOffset * m_mouseSensitivity;
	m_pitch += yOffset * m_mouseSensitivity;

	if (constrainPitch)
	{
		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{
	m_zoom -= yOffset;
	if (m_zoom > 45.0f) m_zoom = 45.0f;
	if (m_zoom < 1.0f) m_zoom = 1.0f;
}

void Camera::updateCameraVectors()
{
	// calculate the vector camera is pointing at
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	// calculate the camera right
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	// calculate the camera up
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

float Camera::getZoom()
{
	return m_zoom;
}
