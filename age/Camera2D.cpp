#include "Camera2D.h"


namespace age {

	Camera2D::Camera2D() : m_pos(0), m_viewTransform(1.0f) {
		init(m_viewWidth, m_viewHeight);
	}

	Camera2D::~Camera2D() {}

	void Camera2D::init(int viewWidth, int viewHeight) {
        m_viewWidth = viewWidth;
        m_viewHeight = viewHeight;
        
		m_orthoMatrix = glm::ortho(0.0f, (float)m_viewWidth, 0.0f, (float)m_viewHeight);
		m_isUpdateNeeded = true;
	}

	void Camera2D::update() {
		if (m_isUpdateNeeded) {
			//glm::vec3 translation(-m_pos.x + m_viewWidth / 2.0f, -m_pos.y + m_viewHeight / 2.0f, 0.0f);
			glm::vec3 translation(-m_pos.x, -m_pos.y, 0.0f);
			m_viewTransform = glm::translate(m_orthoMatrix, translation);

			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_viewTransform = glm::scale(glm::mat4(1.0f), scale) * m_viewTransform;
			m_isUpdateNeeded = false;
		}
	}
}