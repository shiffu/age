#include "InputManager.h"

namespace age {

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::keyPressed(unsigned int keyId) {
		m_keyMap[keyId] = true;

	}

	void InputManager::keyReleased(unsigned int keyId) {
		m_keyMap[keyId] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyId) {
		auto it = m_keyMap.find(keyId);
		if (it != m_keyMap.end()) {
			return it->second;
		}

		return false;
	}

}