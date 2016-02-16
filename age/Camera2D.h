#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace age {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screeHeight);
		void update();

		void setPos(const glm::vec2& pos) {
			m_pos = pos;
			m_isUpdateNeeded = true;
		}

		glm::vec2 getPos() const { return m_pos; }

		void setScale(float scale) {
			m_scale = scale;
			m_isUpdateNeeded = true;
		}

		float getScale() const { return m_scale; }

		glm::mat4 getProjection() { return m_viewTransform; }

	private:
		bool m_isUpdateNeeded = true;
		float m_scale = 1.0f;
		glm::vec2 m_pos;
		glm::mat4 m_viewTransform;
		glm::mat4 m_orthoMatrix;
		int m_screenWidth = 1280;
		int m_screenHeight = 1024;
	};

}