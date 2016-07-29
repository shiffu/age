#include "InputManager.h"

namespace age {

	InputManager::InputManager() {}
	InputManager::~InputManager() {}

	void InputManager::keyPressed(unsigned int keyId) {
		m_keyMap[keyId] = true;
	}

	void InputManager::keyReleased(unsigned int keyId) {
		m_keyMap[keyId] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyId) const {
		auto it = m_keyMap.find(keyId);
		if (it != m_keyMap.end()) {
			return it->second;
		}

		return false;
	}
    
    void InputManager::mouseButtonPressed(unsigned int buttonId) {
        m_mouseButtonsMap[buttonId] = true;
    }
    
    void InputManager::mouseButtonReleased(unsigned int buttonId) {
        m_mouseButtonsMap[buttonId] = false;
    }
    
    bool InputManager::isMouseButtonPressed(unsigned int buttonId) const {
        auto it = m_mouseButtonsMap.find(buttonId);
        if (it != m_mouseButtonsMap.end()) {
            return it->second;
        }
        
        return false;        
    }
    
    void InputManager::mousePosition(int x, int y) {
        m_mousePos = glm::vec2(x, y);
    }
    
    glm::vec2 InputManager::mousePosition() const {
        return m_mousePos;
    }
}