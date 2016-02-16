#include "Camera2D.h"


namespace age {

	Camera2D::Camera2D() : m_pos(0), m_viewTransform(1.0f) {
		init(m_screenWidth, m_screenHeight);
	}

	Camera2D::~Camera2D() {}

	void Camera2D::init(int screenWidth, int screeHeight) {
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
		m_isUpdateNeeded = true;
	}

	void Camera2D::update() {
		if (m_isUpdateNeeded) {
			//glm::vec3 translation(-m_pos.x + m_screenWidth / 2.0f, -m_pos.y + m_screenHeight / 2.0f, 0.0f);
			glm::vec3 translation(-m_pos.x, -m_pos.y, 0.0f);
			m_viewTransform = glm::translate(m_orthoMatrix, translation);

			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_viewTransform = glm::scale(glm::mat4(1.0f), scale) * m_viewTransform;
			m_isUpdateNeeded = false;
		}
	}
}