#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

namespace age {

	class InputManager {
	public:
		InputManager();
		~InputManager();

		void keyPressed(unsigned int keyId);
		void keyReleased(unsigned int keyId);
		bool isKeyPressed(unsigned int keyId) const;
        
        void mouseButtonPressed(unsigned int buttonId);
        void mouseButtonReleased(unsigned int buttonId);
        bool isMouseButtonPressed(unsigned int buttonId) const;
        void mousePosition(int x, int y);
        glm::vec2 mousePosition() const;

	private:
        std::unordered_map<unsigned int, bool> m_keyMap;
        std::unordered_map<unsigned int, bool> m_mouseButtonsMap;
        glm::vec2 m_mousePos;
	};

}