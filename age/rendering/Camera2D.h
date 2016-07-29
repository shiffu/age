#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <climits>

namespace age {

	class GameObject;

	class Camera2D
	{
	public:
		struct Constraint {
			bool onlyX = false;
			bool onlyY = false;
			int xMinBoundary = INT_MIN;
			int xMaxBoundary = INT_MAX;
			int yMinBoundary = INT_MIN;
			int yMaxBoundary = INT_MAX;
		};

	public:
		Camera2D();
		~Camera2D();

		void init(int viewWidth, int viewHeight);
		void update();

		void setX(float x) {
			m_pos.x = x;
			m_isUpdateNeeded = true;
		}

		void setY(float y) {
			m_pos.y = y;
			m_isUpdateNeeded = true;
		}

		void setPos(float x, float y) {
			setPos(glm::vec2(x, y));
		}

		void setPos(const glm::vec2& pos) {
			m_pos = pos;
			m_isUpdateNeeded = true;
		}

		glm::vec2 getPos() const { return m_pos; }
        glm::vec2 getSize() const { return glm::vec2(m_viewWidth, m_viewHeight); }

		void setScale(float scale) {
			m_scale = scale;
			m_isUpdateNeeded = true;
		}

		float getScale() const { return m_scale; }

		glm::mat4 getProjection() const { return m_viewTransform; }

		void follow(const GameObject* go, const Constraint* constraint = nullptr);

	private:
		bool m_isUpdateNeeded = true;
		float m_scale = 1.0f;
		glm::vec2 m_pos;
		glm::mat4 m_viewTransform;
		glm::mat4 m_orthoMatrix;
		int m_viewWidth = 1280;
		int m_viewHeight = 1024;
	};

}